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
    c_group->addWidget(std::make_unique<Wt::WText>(std::string(group["name"])));
    c_group->addWidget(std::make_unique<Wt::WText>(std::string(group["type"])));
    c_group->addWidget(std::make_unique<Wt::WText>(std::string(group["descriptions"])));
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
        Wt::Json::Array groups;
        groups_.clear();
        Wt::Json::parse(response.body(), groups);
        for (int i = 0; i < groups.size(); ++i) {
            Group group; 
            group["ID"] = groups[i]["ID"];
            group["name"] = groups[i]["name"];
            group["descriptions"] = groups[i]["descriptions"];
            group["type"] = groups[i]["type"];
            groups_.push_back(group);
        }
        RenderGroups();
    }
    else if (response.status() != 200) {
        std::cout << "=============HANDLE ERROR RESPONSE" << std::endl;
    }
}

void feedView::GoToTheUserPage() {
    internal_path_.emit("/userpage");
}

feedView::feedView()
{
    LoadingInitialSize();
    std::unique_ptr<Wt::WContainerWidget> header = std::make_unique<Wt::WContainerWidget>();
    user_icon_ = header->addWidget(std::make_unique<Wt::WImage>("src/images/little_user.svg"));
    user_icon_->setAlternateText("user_icon");
    user_icon_->clicked().connect(this, &feedView::GoToTheUserPage);

    Wt::WText *text = header->addWidget(std::make_unique<Wt::WText>("Главная"));
    Wt::WText *type = header->addWidget(std::make_unique<Wt::WText>("Тема аккаунта"));
    Wt::WContainerWidget *search = header->addWidget(std::make_unique<Wt::WContainerWidget>());

    search_box_ = search->addWidget(std::make_unique<Wt::WContainerWidget>());
    search_box_->setId("search_icon");
    search_box_->clicked().connect([=] (const Wt::WMouseEvent& e) {
        DoGetRequest("");
    });
    Wt::WImage *search_icon = search_box_->addWidget(std::make_unique<Wt::WImage>("src/images/search.svg"));

    request_text_ = search->addWidget(std::make_unique<Wt::WLineEdit>());
    this->addWidget(std::move(header));
    body_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());
    group_box_ = body_->addWidget(std::make_unique<Wt::WContainerWidget>());
    RenderGroups();

    client_ = addChild(std::make_unique<Wt::Http::Client>());
    client_->done().connect(this, &feedView::HandleHttpResponse);
}