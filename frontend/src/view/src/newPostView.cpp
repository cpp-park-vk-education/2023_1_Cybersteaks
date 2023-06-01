#include "newPostView.hpp"

void newPostView::AddCssStyles() {
    head_->addStyleClass("new_post_head");
    body_->addStyleClass("new_post_body");
    portfolio_form_->addStyleClass("new_post_portfolio_form");
    blog_form_->addStyleClass("new_post_blog_form");
}

void newPostView::DoGetRequest(const std::string& url) {

}

void newPostView::ShowingFunction() {

}

void newPostView::UpdateUserInfo() {

}
void newPostView::HandleHttpResponse(std::error_code err, const Wt::Http::Message& response) {

}

newPostView::newPostView(const std::string& token) {
    token_ = token;
    head_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* go_back = head_->addWidget(std::make_unique<Wt::WContainerWidget>());
    go_back->addWidget(std::make_unique<Wt::WText>("Назад"));
    go_back->clicked().connect([=] (const Wt::WMouseEvent& e) {
        go_to_userpage_.emit();
    });
    head_->addWidget(std::make_unique<Wt::WText>("Добавление"));
    body_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());

    portfolio_form_ = body_->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* portfolio_head = portfolio_form_->addWidget(std::make_unique<Wt::WContainerWidget>());
    portfolio_head->addWidget(std::make_unique<Wt::WText>("Загрузить в портфолио"));
    file_ = portfolio_form_->addNew<Wt::WFileUpload>();
    file_->setProgressBar(std::make_unique<Wt::WProgressBar>());
    file_->setMargin(10, Wt::Side::Right);
    file_->setFileTextSize(1024 * 1024);
    upload_file_ = portfolio_form_->addNew<Wt::WPushButton>("Выбрать файл");
    upload_file_->setMargin(10, Wt::Side::Left | Wt::Side::Right);
    Wt::WText *out = portfolio_form_->addNew<Wt::WText>();
    upload_file_->clicked().connect([=] {
        file_->upload();
        upload_file_->disable();
    });
    file_->changed().connect([=] {
        file_->upload();
        upload_file_->disable();
        out->setText("Файл загружается");
    });
    file_->uploaded().connect([=] {
        out->setText("Файл загружен");
    });
    file_->fileTooLarge().connect([=] {
        out->setText("Слишком большой размер");
    });
    Wt::WContainerWidget* p_button_box = portfolio_form_->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* p_button = p_button_box->addWidget(std::make_unique<Wt::WContainerWidget>());
    p_button->addWidget(std::make_unique<Wt::WText>("Опубликовать"));
    p_button->clicked().connect([=] (const Wt::WMouseEvent& e) {
        go_to_userpage_.emit();
    });

    blog_form_ = body_->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* text_box = blog_form_->addWidget(std::make_unique<Wt::WContainerWidget>());
    blog_text = text_box->addWidget(std::make_unique<Wt::WTextArea>());
    Wt::WContainerWidget* button_box = blog_form_->addWidget(std::make_unique<Wt::WContainerWidget>());
    blog_button = button_box->addWidget(std::make_unique<Wt::WContainerWidget>());    
    blog_button->addWidget(std::make_unique<Wt::WText>("Добавить пост"));
    blog_button->clicked().connect([=] (const Wt::WMouseEvent& e) {
        go_to_userpage_.emit();
    });

    client_ = addChild(std::make_unique<Wt::Http::Client>());
    client_->done().connect(this, &newPostView::HandleHttpResponse); 

    AddCssStyles();
    text_box->addStyleClass("new_post_text");
    button_box->addStyleClass("new_post_button");
    p_button_box->addStyleClass("new_post_p_button");
    go_back->addStyleClass("new_post_go_back");
}