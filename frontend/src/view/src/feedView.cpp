#include "feedView.hpp"

void feedView::LoadingInitialSize() {
    //
}

void feedView::DoGetRequest(const std::string& url) {
    std::cout << "=============GET REQUEST" << std::endl;
    std::cout << url << std::endl;
    if (client_->get(url)) {

    }
    else {
        std::cout << "URL ERROR" << std::endl;
    };
}

void feedView::RenderGroup(const Wt::Json::Value& group) {
    Wt::WContainerWidget* c_group = group_box_->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* name = c_group->addWidget(std::make_unique<Wt::WContainerWidget>());
    name->addWidget(std::make_unique<Wt::WText>(std::string(group)));
    c_group->addStyleClass("feed_group_unit");
    name->addStyleClass("feed_group_name");
}

void feedView::RenderGroups() {
    group_box_->clear();
    for (int i = 0; i < groups_.size(); ++i) {
        RenderGroup(groups_[i]);
    }
}

void feedView::HandleHttpResponse(std::error_code err, const Wt::Http::Message& response) {
    std::cout << "=============HANDLE RESPONSE START" << std::endl;
    if (!err & response.status() == 200) {
        std::cout << "=============HANDLE RESPONSE" << std::endl;
        std::cout << response.body() << std::endl;
        Wt::Json::Object json_body;
        Wt::Json::Array groups;
        groups_.clear();
        Wt::Json::parse(response.body(), json_body);
        groups = json_body.get("clusters");
        for (int i = 0; i < groups.size(); ++i) {
            Wt::Json::Value value = groups[i];
            groups_.push_back(value);
        }
        std::cout << "start render groups" << std::endl;
        RenderGroups();
    }
    else if (response.status() != 200) {
        std::cout << "Err:";
        std::cout << response.status();
        std::cout << response.body();
        std::cout << "=============HANDLE ERROR RESPONSE" << std::endl;
    }
}

void feedView::GoToTheUserPage() {
    internal_path_.emit("/userpage");
}

void feedView::AddCssStyles() {
    header_->addStyleClass("feed_header");
    user_icon_->addStyleClass("feed_user_icon");
}

void feedView::ShowingFunction() {
    std::string type = "";
    if (request_text_->valueText().toUTF8() != "")
        type = "/?type=" + request_text_->valueText().toUTF8();
    DoGetRequest("http://127.0.0.1:1026/clusters" + type);
}

feedView::feedView()
{
    std::cout << "FEED VIEW IS START TO WORK" << std::endl;
    LoadingInitialSize();
    header_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());
    user_icon_ = header_->addWidget(std::make_unique<Wt::WImage>("src/images/little_user.svg"));
    user_icon_->setAlternateText("user_icon");
    user_icon_->clicked().connect(this, &feedView::GoToTheUserPage);

    Wt::WContainerWidget *text = header_->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget *type = header_->addWidget(std::make_unique<Wt::WContainerWidget>());
    text->addWidget(std::make_unique<Wt::WText>("Главная"));
    type->addWidget(std::make_unique<Wt::WText>("Поиск"));
    Wt::WContainerWidget *search = header_->addWidget(std::make_unique<Wt::WContainerWidget>());

    search_box_ = search->addWidget(std::make_unique<Wt::WContainerWidget>());
    search_box_->setId("search_icon");
    search_box_->clicked().connect([=] (const Wt::WMouseEvent& e) {
        std::string type = "";
        if (request_text_->valueText().toUTF8() != "")
            type = "/?type=" + request_text_->valueText().toUTF8();
        DoGetRequest("http://127.0.0.1:1026/clusters/" + type);
    });
    Wt::WImage *search_icon = search_box_->addWidget(std::make_unique<Wt::WImage>("src/images/search.svg"));

    request_text_ = search->addWidget(std::make_unique<Wt::WLineEdit>());

    body_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());
    group_box_ = body_->addWidget(std::make_unique<Wt::WContainerWidget>());

    client_ = addChild(std::make_unique<Wt::Http::Client>());
    client_->done().connect(this, &feedView::HandleHttpResponse);

    header_->addStyleClass("feed_header");
    user_icon_->addStyleClass("feed_user_icon");
    text->addStyleClass("feed_main");
    type->addStyleClass("feed_type");
    search->addStyleClass("feed_search_box");
    request_text_->addStyleClass("feed_request_text");
    body_->addStyleClass("feed_body");
    group_box_->addStyleClass("feed_group_box");
}