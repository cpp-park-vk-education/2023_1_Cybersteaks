#include "feedView.hpp"

void feedView::LoadingInitialSize() {
    groups_.push_back(Group());
    groups_.push_back(Group());
    groups_.push_back(Group());
    groups_.push_back(Group());
    groups_[0]["name"] = "name1";
    groups_[1]["name"] = "name2";
}

void feedView::DoGetRequest(const std::string& url) {
    std::cout << "=============GET REQUEST" << std::endl;
    if (client_->get(url)) {

    }
    else {
        std::cout << "URL ERROR" << std::endl;
    };
}

void feedView::RenderGroup(Group group) {
    Wt::WContainerWidget* c_group = group_box_->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* name = c_group->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* type = c_group->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* descriptions = c_group->addWidget(std::make_unique<Wt::WContainerWidget>());
    name->addWidget(std::make_unique<Wt::WText>(std::string(group["name"])));
    type->addWidget(std::make_unique<Wt::WText>(std::string(group["type"])));
    descriptions->addWidget(std::make_unique<Wt::WText>(std::string(group["descriptions"])));

    c_group->addStyleClass("feed_group_unit");
    name->addStyleClass("feed_group_name");
    type->addStyleClass("feed_group_type");
    descriptions->addStyleClass("feed_group_descriptions");
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
        groups = json_body.get("groups");
        for (int i = 0; i < groups.size(); ++i) {
            Group group;
            Wt::Json::Object group_obj = groups[i];  
            group.JsonParse(group_obj);
            groups_.push_back(group);
        }
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

feedView::feedView()
{
    LoadingInitialSize();
    header_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());
    user_icon_ = header_->addWidget(std::make_unique<Wt::WImage>("src/images/little_user.svg"));
    user_icon_->setAlternateText("user_icon");
    user_icon_->clicked().connect(this, &feedView::GoToTheUserPage);

    Wt::WContainerWidget *text = header_->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget *type = header_->addWidget(std::make_unique<Wt::WContainerWidget>());
    text->addWidget(std::make_unique<Wt::WText>("Главная"));
    type->addWidget(std::make_unique<Wt::WText>("Тема аккаунта"));
    Wt::WContainerWidget *search = header_->addWidget(std::make_unique<Wt::WContainerWidget>());

    search_box_ = search->addWidget(std::make_unique<Wt::WContainerWidget>());
    search_box_->setId("search_icon");
    search_box_->clicked().connect([=] (const Wt::WMouseEvent& e) {
        DoGetRequest("http://127.0.0.1:1026/clusters");
    });
    Wt::WImage *search_icon = search_box_->addWidget(std::make_unique<Wt::WImage>("src/images/search.svg"));

    request_text_ = search->addWidget(std::make_unique<Wt::WLineEdit>());

    body_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());
    group_box_ = body_->addWidget(std::make_unique<Wt::WContainerWidget>());
    RenderGroups();

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