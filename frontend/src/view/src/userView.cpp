#include "userView.hpp"

void userView::AddCssStyles() {
    head_->addStyleClass("user_head");
    user_widget_->addStyleClass("user_block");
    options_->addStyleClass("user_options");
    portfolio_option_->addStyleClass("user_portfolio_op");
    blog_option_->addStyleClass("user_blog_op");
    body_->addStyleClass("user_body");
    portfolio_->addStyleClass("user_portfolio");
    blog_->addStyleClass("user_blog");
}

void userView::DoGetRequest(const std::string& url) {
    std::cout << "=============GET REQUEST" << std::endl;
    std::cout << token_ << std::endl;
    Wt::Http::Message message;
    message.addHeader("Content-Type", "application/json");
    message.addHeader("Authorization", token_);
    std::vector<Wt::Http::Message::Header> headers;
    headers.push_back(Wt::Http::Message::Header("Content-Type", "application/json"));
    headers.push_back(Wt::Http::Message::Header("Authorization", token_));
    if (client_->get(url, headers)) {
        std::cout << "=============GET USER URL" << std::endl;
        //username = username_->valueText().toUTF8();
    }
    else {
        std::cout << "URL ERROR" << std::endl;
        //error = "url error";
    };
}
void userView::UpdateUserInfo() {
    update_user_.emit(user_);
}

void userView::RenderUser() {
    if (user_.get("login") != "") {
        user_widget_->clear();
        Wt::WImage* user_icon_ = user_widget_->addWidget(std::make_unique<Wt::WImage>("src/images/little_user.svg"));
        Wt::WContainerWidget* full_name = user_widget_->addWidget(std::make_unique<Wt::WContainerWidget>());
        Wt::WContainerWidget* first_name = full_name->addWidget(std::make_unique<Wt::WContainerWidget>());
        first_name->addWidget(std::make_unique<Wt::WText>(user_.get("first_name")));
        Wt::WContainerWidget* last_name = full_name->addWidget(std::make_unique<Wt::WContainerWidget>());
        last_name->addWidget(std::make_unique<Wt::WText>(user_.get("last_name")));
        Wt::WContainerWidget* login = user_widget_->addWidget(std::make_unique<Wt::WContainerWidget>());
        login->addWidget(std::make_unique<Wt::WText>(user_.get("login")));
        Wt::WContainerWidget* birthday = user_widget_->addWidget(std::make_unique<Wt::WContainerWidget>());
        birthday->addWidget(std::make_unique<Wt::WText>(user_.get("день рождения: " + user_.get("birthday"))));

        full_name->addStyleClass("user_full_name");
        first_name->addStyleClass("user_block_text");
        last_name->addStyleClass("user_block_text");
        login->addStyleClass("user_block_text");
        birthday->addStyleClass("user_block_text");
    }
    else {
        DoGetRequest("http://127.0.0.1:1026/account/settings");
    }
}

void userView::HandleHttpResponse(std::error_code err, const Wt::Http::Message& response) {
    std::cout << "=============HANDLE RESPONSE START" << std::endl;
    if (!err & response.status() == 200) {
        std::cout << "=============HANDLE RESPONSE" << std::endl;
        std::cout << response.body() << std::endl;
        Wt::Json::Object json_body;
        std::cout << response.body() << std::endl;
        Wt::Json::parse(response.body(), json_body);
        user_ = json_body;
        std::cout << std::string(user_.get("first_name")) << std::endl;
        UpdateUserInfo();
        RenderUser();
    }
    else if (response.status() != 200) {
        std::cout << "Err:";
        std::cout << response.status();
        std::cout << response.body();
        std::cout << "=============HANDLE ERROR RESPONSE" << std::endl;
    }
}

void userView::ShowingFunction() {
    DoGetRequest("http://127.0.0.1:1026/account/settings");
}

userView::userView(const std::string& token) {
    token_ = token;
    head_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* go_to_main = head_->addWidget(std::make_unique<Wt::WContainerWidget>());
    go_to_main->addWidget(std::make_unique<Wt::WText>("Главная"));
    go_to_main->clicked().connect([=] (const Wt::WMouseEvent& e) {
        go_to_main_page_.emit();
    });
    Wt::WContainerWidget* logout_widget = head_->addWidget(std::make_unique<Wt::WContainerWidget>());
    user_widget_ = head_->addWidget(std::make_unique<Wt::WContainerWidget>());
    options_ = head_->addWidget(std::make_unique<Wt::WContainerWidget>());

    portfolio_option_ = options_->addWidget(std::make_unique<Wt::WContainerWidget>());
    portfolio_option_->addWidget(std::make_unique<Wt::WText>("Портфолио"));

    blog_option_ = options_->addWidget(std::make_unique<Wt::WContainerWidget>());
    blog_option_->addWidget(std::make_unique<Wt::WText>("Блог"));

    body_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());
    portfolio_ = body_->addWidget(std::make_unique<Wt::WContainerWidget>());
    blog_ = body_->addWidget(std::make_unique<Wt::WContainerWidget>());   
    blog_->hide();
    portfolio_option_->addStyleClass("user_select");

    postView* postView_ = blog_->addWidget(std::make_unique<postView>());
    portfolio_->addWidget(std::make_unique<Wt::WText>("PORTFOLIO"));

    portfolio_option_->clicked().connect([=] (const Wt::WMouseEvent& e) {
        if (blog_option_->hasStyleClass("user_select"))
            blog_option_->removeStyleClass("user_select");
        if (!blog_option_->hasStyleClass("user_non_select"))
            blog_option_->addStyleClass("user_non_select");
        if (!portfolio_option_->hasStyleClass("user_select"))
            portfolio_option_->addStyleClass("user_select");    
        if (portfolio_option_->hasStyleClass("user_non_select"))
            portfolio_option_->removeStyleClass("user_non_select"); 
        blog_->hide();
        portfolio_->show();
    });
    blog_option_->clicked().connect([=] (const Wt::WMouseEvent& e) {
        if (portfolio_option_->hasStyleClass("user_select"))
            portfolio_option_->removeStyleClass("user_select");
        if (!portfolio_option_->hasStyleClass("user_non_select"))
            portfolio_option_->addStyleClass("user_non_select");
        if (!blog_option_->hasStyleClass("user_select"))
            blog_option_->addStyleClass("user_select");    
        if (blog_option_->hasStyleClass("user_non_select"))
            blog_option_->removeStyleClass("user_non_select"); 
        blog_->show();
        postView_->ShowingFunction();
        portfolio_->hide();
    });

    client_ = addChild(std::make_unique<Wt::Http::Client>());
    client_->done().connect(this, &userView::HandleHttpResponse); 

    AddCssStyles();
    go_to_main->addStyleClass("user_main");
    logout_widget->addStyleClass("user_logout");

    DoGetRequest("http://127.0.0.1:1026/account/settings");
}