#include "loginView.hpp"

void loginView::AddCssStyles() {
    body_->addStyleClass("login_body");
    form_->addStyleClass("login_form");
    button_->addStyleClass("login_form_button");
    reg_link_->addStyleClass("login_form_link");
}

void loginView::GoToTheUserPage() {
    internal_path_.emit(token, username, error);
}

void loginView::GoToRegistration() {
    reg_path_.emit("/registration");
}

void loginView::DoGetRequest(const std::string& url) {
    std::cout << "=============GET REQUEST" << std::endl;
    Wt::Http::Message message;
    message.addHeader("Content-Type", "application/json");
    message.addBodyText("{\"login\": \"" + username_->valueText().toUTF8() + "\", \"password\": \"" + password_->valueText().toUTF8() + "\"}");
    if (client_->post(url, message)) {
        username = username_->valueText().toUTF8();
    }
    else {
        std::cout << "URL ERROR" << std::endl;
        error = "url error";
    };
}

void loginView::HandleHttpResponse(std::error_code err, const Wt::Http::Message& response) {
    std::cout << "=============HANDLE RESPONSE START" << std::endl;
    if (!err & response.status() == 200) {
        std::cout << "=============HANDLE RESPONSE" << std::endl;
        std::cout << response.body() << std::endl;
        Wt::Json::Object json_body;
        Wt::Json::parse(response.body(), json_body);
        Wt::Json::Value token_value = json_body.get("token");
        std::cout << std::string(json_body.get("token")) << std::endl;
        error = "";
        token = std::string(json_body.get("token"));
        GoToTheUserPage();
    }
    else if (response.status() != 200) {
        std::cout << "Err:";
        std::cout << response.status();
        std::cout << response.body();
        std::cout << "=============HANDLE ERROR RESPONSE" << std::endl;
    }
}

loginView::loginView() {
    body_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());
    form_ = body_->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* form_text_box = form_->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WText* form_text = form_text_box->addWidget(std::make_unique<Wt::WText>("Вход"));
    Wt::WContainerWidget* username_box = form_->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* password_box = form_->addWidget(std::make_unique<Wt::WContainerWidget>());
    username_ = username_box->addWidget(std::make_unique<Wt::WLineEdit>());
    password_ = password_box->addWidget(std::make_unique<Wt::WLineEdit>());
    username_->setPlaceholderText("логин");
    password_->setEchoMode(Wt::EchoMode::Password);
    password_->setPlaceholderText("пароль");
    button_ = form_->addWidget(std::make_unique<Wt::WContainerWidget>());
    button_->addWidget(std::make_unique<Wt::WText>("войти"));
    button_->clicked().connect([=] (const Wt::WMouseEvent& e) {
        DoGetRequest("http://127.0.0.1:1026/account/login"); //it's url for creating token
    });
    reg_link_ = form_->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WText* link = reg_link_->addWidget(std::make_unique<Wt::WText>("Регистрация"));
    link->clicked().connect([=] (const Wt::WMouseEvent& e) {
        GoToRegistration();
    });
    token = "";
    error = "no data in form";
    username = "";

    client_ = addChild(std::make_unique<Wt::Http::Client>());
    client_->done().connect(this, &loginView::HandleHttpResponse);

    AddCssStyles();
    form_text_box->addStyleClass("login_form_text");
    username_box->addStyleClass("login_form_username");
    password_box->addStyleClass("login_form_password");
}