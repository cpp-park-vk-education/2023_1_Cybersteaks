#include "userView.hpp"

void userView::DoGetRequest(const std::string& url) {

}

void userView::HandleHttpResponse(std::error_code err, const Wt::Http::Message& response) {

}

void userView::AddCssStyles() {
    body_->addStyleClass("user_body");
    head_->addStyleClass("user_header");
    options_->addStyleClass("user_options");
}

userView::userView(const std::string& n_username, const Token& n_token) {
    head_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());
    options_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());
    body_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());
    user["login"] = n_username;
    token = token;
    AddCssStyles();
}