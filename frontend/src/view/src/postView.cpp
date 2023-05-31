#include "postView.hpp"

void postView::DoGetRequest(const std::string& url) {
    std::cout << "=============GET REQUEST" << std::endl;
    Wt::Http::Message message;
    message.addHeader("Content-Type", "application/json");
    std::vector<Wt::Http::Message::Header> headers;
    headers.push_back(Wt::Http::Message::Header("Content-Type", "application/json"));
    headers.push_back(Wt::Http::Message::Header("Authorization", "aGVsbG8="));
    if (client_->get(url, headers)) {
        //username = username_->valueText().toUTF8();
    }
    else {
        std::cout << "URL ERROR" << std::endl;
        //error = "url error";
    };
}

void postView::RenderPosts() {
    body_->clear();
    for (int i = 0; i < posts_.size(); ++i) {
        Wt::WContainerWidget* post = body_->addWidget(std::make_unique<Wt::WContainerWidget>());
        Wt::WContainerWidget* post_name = post->addWidget(std::make_unique<Wt::WContainerWidget>());
        Wt::WContainerWidget* post_text = post->addWidget(std::make_unique<Wt::WContainerWidget>());
        post_name->addWidget(std::make_unique<Wt::WText>("Новый пост"));
        post_text->addWidget(std::make_unique<Wt::WText>(std::string(posts_[i])));
        post->setMargin(10);
        post_name->addStyleClass("post_name");
        post_text->addStyleClass("post_text");
    }
}

void postView::HandleHttpResponse(std::error_code err, const Wt::Http::Message& response) {
    if (!err & response.status() == 200) {
        std::cout << "=============HANDLE RESPONSE" << std::endl;
        std::cout << response.body() << std::endl;
        Wt::Json::Object json_body;
        Wt::Json::parse(response.body(), json_body);
        posts_ = json_body.get("posts");
        //std::cout << std::string(json_body.get("posts")) << std::endl;
        RenderPosts();
    }
    else if (response.status() != 200) {
        std::cout << "Err:";
        std::cout << response.status();
        std::cout << response.body();
        std::cout << "=============HANDLE ERROR RESPONSE" << std::endl;
    }
}

void postView::ShowingFunction() {
    DoGetRequest("http://127.0.0.1:1026/account/posts");
}

postView::postView() {
    head_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());
    body_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());  

    client_ = addChild(std::make_unique<Wt::Http::Client>());
    client_->done().connect(this, &postView::HandleHttpResponse); 
}