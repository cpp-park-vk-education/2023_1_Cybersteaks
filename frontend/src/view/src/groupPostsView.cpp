#include "groupPostsView.hpp"

void groupPostsView::DoGetRequest(const std::string& url) {
    std::cout << "=============GET REQUEST" << std::endl;
    Wt::Http::Message message;
    message.addHeader("Content-Type", "application/json");
    std::vector<Wt::Http::Message::Header> headers;
    headers.push_back(Wt::Http::Message::Header("Content-Type", "application/json"));
    if (client_->get(url, headers)) {
        //username = username_->valueText().toUTF8();
    }
    else {
        std::cout << "URL ERROR" << std::endl;
        //error = "url error";
    };
}

void groupPostsView::RenderPosts() {
    body_->clear();
    for (int i = 0; i < posts_.size(); ++i) {
        Wt::WContainerWidget* post = body_->addWidget(std::make_unique<Wt::WContainerWidget>());
        Wt::WContainerWidget* post_name = post->addWidget(std::make_unique<Wt::WContainerWidget>());
        Wt::WContainerWidget* post_text = post->addWidget(std::make_unique<Wt::WContainerWidget>());
        post_text->addWidget(std::make_unique<Wt::WText>(std::string(posts_[i])));
        std::cout << std::string(posts_[i]) << std::endl;
        post->addStyleClass("post");
        post_name->addStyleClass("post_name");
        post_text->addStyleClass("post_text");
    }
}

void groupPostsView::HandleHttpResponse(std::error_code err, const Wt::Http::Message& response) {
    if (!err & response.status() == 200) {
        std::cout << "=============HANDLE RESPONSE" << std::endl;
        std::cout << response.body() << std::endl;
        Wt::Json::Object json_body;
        Wt::Json::parse(response.body(), json_body);
        posts_ = json_body.get("group_posts");
        RenderPosts();
    }
    else if (response.status() != 200) {
        std::cout << "Err:";
        std::cout << response.status();
        std::cout << response.body();
        std::cout << "=============HANDLE ERROR RESPONSE" << std::endl;
    }
}

void groupPostsView::ShowingFunction(const std::string& name) {
    DoGetRequest("http://127.0.0.1:1026/clusters/groups/posts/?type=" + name);
}

groupPostsView::groupPostsView(const std::string& new_name) {
    std::cout << "NEW NAME: " << new_name << std::endl;
    name_ = new_name;
    head_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());
    body_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());  
    client_ = addChild(std::make_unique<Wt::Http::Client>());
    client_->done().connect(this, &groupPostsView::HandleHttpResponse); 
}