#include "newPostView.hpp"

void newPostView::AddCssStyles() {

}

void newPostView::RenderUser() {

}

void newPostView::UpdateUserInfo() {

}
void newPostView::HandleHttpResponse(std::error_code err, const Wt::Http::Message& response) {

}

newPostView::newPostView(const std::string& token) {
    token_ = token;
    head_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());
    head_->addWidget(std::make_unique<Wt::WText>("Добавление"));
    
    body_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());
}