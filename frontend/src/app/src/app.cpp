#include "app.hpp"

#include <Wt/WWidget.h>
#include <Wt/WLink.h>

void INcreaApplication::CreateStatic() {
}

void INcreaApplication::Clear() {
    head_->clear();
    body_->clear();
}

void INcreaApplication::HideViews() {
    std::cout << "START HIDE VIEWS" << std::endl;
    feedView_->hide();
    userView_->hide();
    loginView_->hide();
    postView_->hide();
    std::cout << "END HIDE VIEWS" << std::endl;
}

void INcreaApplication::CreateFeedView() {
    /*Wt::WApplication *app = Wt::WApplication::instance();
    if (!feedView_) {
        feedView_ = body_->addWidget(std::make_unique<feedView>());
        feedView_->internal_path().connect(this, [=] (const std::string& url) {
            std::string next_url = url;
            //if (token.GetToken() == "")
            //    next_url = "/login";
            app->setInternalPath(next_url);
            HandlePathChange(next_url);
        });
    }
    else feedView_->show();
    */
}

void INcreaApplication::CreateLoginView() {
    /*Wt::WApplication *app = Wt::WApplication::instance();
    if (!loginView_) {
        loginView_ = body_->addWidget(std::make_unique<loginView>());
        loginView_->internal_path().connect(this, [=] (const std::string& new_token, const std::string& username, const std::string& error) {
            if (error == "") {
                std::cout << "LOGIN -> GO TO USERPAGE" << std::endl;
                std::string next_url = "/userpage";
                if (new_token == "")
                    next_url = "/login";
                token.SetToken(new_token);
                app->setInternalPath(next_url);
                HandlePathChange(next_url);
            }
        });
        loginView_->reg_path().connect(this, [=] (const std::string& url) {
            app->setInternalPath(url);
            HandlePathChange(url);
        });
    }
    else loginView_->show();
    */
}

void INcreaApplication::CreateUserPageView() {
    /*Wt::WApplication *app = Wt::WApplication::instance();
    if (!userView_) {
        userView_ = body_->addWidget(std::make_unique<userView>(token.GetToken()));
        userView_->update_user().connect(this, [=] (const Wt::Json::Object& new_user) {
            user_ = new_user;
            //username_ = std::string(user_.get("login"));
        });
        userView_->go_to_main_page().connect(this, [=] () {
            app->setInternalPath("/");
            HandlePathChange("/");
        });
    }
    else userView_->show();
    */
}

void INcreaApplication::CreatePostView() {
    /*Wt::WApplication *app = Wt::WApplication::instance();
    if (!postView_)
        postView_  = body_->addWidget(std::make_unique<postView>());
    else postView_->show();
    */
}

void INcreaApplication::CreateConnectForViews() {
    Wt::WApplication *app = Wt::WApplication::instance();

    feedView_->internal_path().connect(this, [=] (const std::string& url) {
        std::string next_url = url;
        //if (token.GetToken() == "")
        //    next_url = "/login";
        app->setInternalPath(next_url);
        HandlePathChange(next_url);
    });

    userView_->update_user().connect(this, [=] (const Wt::Json::Object& new_user) {
        user_ = new_user;
        //if (user_.get("login"))
        //    username_ = std::string(user_.get("login"));
    });
    userView_->go_to_main_page().connect(this, [=] () {
        app->setInternalPath("/");
        HandlePathChange("/");
    });

    loginView_->internal_path().connect(this, [=] (const std::string& new_token, const std::string& username, const std::string& error) {
        if (error == "") {
            std::cout << "LOGIN -> GO TO USERPAGE" << std::endl;
            std::string next_url = "/userpage";
            if (new_token == "")
                next_url = "/login";
            token.SetToken(new_token);
            app->setInternalPath(next_url);
            HandlePathChange(next_url);
        }
    });
    loginView_->reg_path().connect(this, [=] (const std::string& url) {
        app->setInternalPath(url);
        HandlePathChange(url);
    });
}

void INcreaApplication::CreateViews() {
    Wt::WApplication *app = Wt::WApplication::instance();

    feedView_ = body_->addWidget(std::make_unique<feedView>());
    postView_  = body_->addWidget(std::make_unique<postView>());
    userView_ = body_->addWidget(std::make_unique<userView>(token.GetToken()));
    loginView_ = body_->addWidget(std::make_unique<loginView>());
    HideViews();

    std::cout << "VIEWS ARE CREATED" << std::endl;
}

void INcreaApplication::HandlePathChange(const std::string& path) {
    Wt::WApplication *app = Wt::WApplication::instance();
    CreateStatic();
    std::cout << "==============CURRENT URL PATH: " << path << std::endl;
    if (path == "/") {
        std::cout << "SHOW FEED VIEW" << std::endl;
        HideViews();
        feedView_->show();
        std::cout << "MAKE SHOWING FUNCTION" << std::endl;
        feedView_->ShowingFunction();
    }
    else if (path == "/userpage") {
        std::cout << "TOKEN : " <<  token.GetToken() << std::endl;
        if (token.GetToken() == "") {
            HideViews();
            loginView_->show();
        }
        else {
            std::cout << "SHOW USERPAGE VIEW" << std::endl;
            HideViews();
            userView_->show();
            userView_->UpdateToken(token.GetToken());
            userView_->ShowingFunction();
        }
    }
    else if (path == "/login") {
        HideViews();
        loginView_->show();
    }
    else if (path == "/registration") {
        body_->addWidget(std::make_unique<Wt::WText>("registraton"));
    }
    else if (path == "/posts") {
        HideViews();
        postView_->show();
        postView_->ShowingFunction();
    }
}

INcreaApplication::INcreaApplication(const Wt::WEnvironment& env)
    : WApplication(env)
{
    std::cout << "CREATING APPLICATION" << std::endl;
    useStyleSheet("src/css/feed_view.css");
    useStyleSheet("src/css/login_view.css");
    useStyleSheet("src/css/user_view.css");
    head_ = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    body_ = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    Clear();
    std::cout << "CREATING STATIC" << std::endl;
    CreateStatic();
    std::cout << "HANDLE PATH " << internalPath() << std::endl;
    CreateViews();
    CreateConnectForViews();
    HandlePathChange(internalPath());
}

