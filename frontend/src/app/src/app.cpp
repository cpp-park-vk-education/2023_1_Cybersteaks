#include "app.hpp"

#include <Wt/WWidget.h>
#include <Wt/WLink.h>

void INcreaApplication::CreateStatic() {
}

void INcreaApplication::Clear() {
    head_->clear();
    body_->clear();
}

void INcreaApplication::HandlePathChange(const std::string& path) {
    std::cout << "=============function" << std::endl;
    Wt::WApplication *app = Wt::WApplication::instance();
    Clear();
    CreateStatic();
    std::cout << "==============CURRENT URL PATH: " << path << std::endl;
    if (path == "/") {
        feedView* fview = body_->addWidget(std::make_unique<feedView>());
        fview->internal_path().connect(this, [=] (const std::string& url) {
            std::string next_url = url;
            if (token.GetToken() == "")
                next_url = "/login";
            app->setInternalPath(next_url);
            HandlePathChange(next_url);
        });
    }
    else if (path == "/userpage") {
        std::cout << "Creating userpage" << std::endl;
        body_->addWidget(std::make_unique<Wt::WText>("userpage"));
    }
    else if (path == "/login") {
        loginView* lView = body_->addWidget(std::make_unique<loginView>());
        lView->internal_path().connect(this, [=] (const std::string& new_token, const std::string& username, const std::string& error) {
            if (error == "") {
                std::string next_url = "/userpage";
                if (new_token == "")
                    next_url = "/login";
                app->setInternalPath(next_url);
                HandlePathChange(next_url);
            }
        });
    }
    else if (path == "/registration") {
        body_->addWidget(std::make_unique<Wt::WText>("registraton"));
    }
}

INcreaApplication::INcreaApplication(const Wt::WEnvironment& env)
    : WApplication(env)
{
    useStyleSheet("src/css/feed_view.css");
    useStyleSheet("src/css/login_view.css");
    head_ = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    body_ = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    Clear();
    CreateStatic();
    HandlePathChange(internalPath());
}

