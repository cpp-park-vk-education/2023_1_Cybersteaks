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
    newPostView_->hide();
    groupsView_->hide();
    std::cout << "END HIDE VIEWS" << std::endl;
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
    feedView_->go_sub_groups().connect(this, [=] (const std::string& name) {
        app->setInternalPath("/groups");
        groupsView_->UpdateGroupName(name);
        group_name_ = name;
        groupsView_->ShowingFunction();
        HandlePathChange("/groups");
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
    userView_->logout().connect(this, [=] () {
        token.SetToken("");
        app->setInternalPath("/login");
        HandlePathChange("/login");
    });
    userView_->go_to_new_post().connect(this, [=] () {
        app->setInternalPath("/new_post");
        HandlePathChange("/new_post");
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

    newPostView_->go_to_userpage().connect(this, [=] () {
        app->setInternalPath("/userpage");
        HandlePathChange("/userpage");
    });

    groupsView_->internal_path().connect(this, [=] (const std::string& url) {
        app->setInternalPath(url);
        HandlePathChange(url);
    });
}

void INcreaApplication::CreateViews() {
    Wt::WApplication *app = Wt::WApplication::instance();

    feedView_ = body_->addWidget(std::make_unique<feedView>());
    userView_ = body_->addWidget(std::make_unique<userView>(token.GetToken()));
    loginView_ = body_->addWidget(std::make_unique<loginView>());
    newPostView_ = body_->addWidget(std::make_unique<newPostView>(token.GetToken()));
    groupsView_ = body_->addWidget(std::make_unique<groupsView>(""));
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
    else if (path == "/groups") {
        if (group_name_ != "") {
            HideViews();
            groupsView_->show();
            groupsView_->UpdateGroupName(group_name_);
            groupsView_->ShowingFunction();
            groupsView_->ShowingFunction();
        }
    }
    else if (path == "/new_post") {
        if (token.GetToken() == "") {
            HideViews();
            loginView_->show();
        }
        else {
            HideViews();
            newPostView_->show();
        }
    }
}

INcreaApplication::INcreaApplication(const Wt::WEnvironment& env)
    : WApplication(env)
{
    std::cout << "CREATING APPLICATION" << std::endl;
    useStyleSheet("src/css/feed_view.css");
    useStyleSheet("src/css/login_view.css");
    useStyleSheet("src/css/user_view.css");
    useStyleSheet("src/css/new_post_view.css");
    head_ = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    body_ = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    Clear();
    CreateStatic();
    CreateViews();
    CreateConnectForViews();
    HandlePathChange(internalPath());
}

