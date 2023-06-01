#include "groupsView.hpp"

void groupsView::LoadingInitialSize() {
    //
}

void groupsView::DoGetRequest(const std::string& url) {
    std::cout << "=============GET REQUEST" << std::endl;
    std::cout << url << std::endl;
    if (client_->get(url)) {

    }
    else {
        std::cout << "URL ERROR" << std::endl;
    };
}

void groupsView::RenderGroup(const Wt::Json::Value& group) {
    Wt::WContainerWidget* c_group = group_box_->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* name = c_group->addWidget(std::make_unique<Wt::WContainerWidget>());
    name->addWidget(std::make_unique<Wt::WText>(std::string(group)));
    std::cout << std::string(group) << std::endl;
    c_group->clicked().connect([=] (const Wt::WMouseEvent& e) {
        group_box_->hide();
        sub_group_posts->show();
        g_name_box_->clear();
        g_name_box_->addWidget(std::make_unique<Wt::WText>(std::string(group)));
        g_name_box_->addStyleClass("subgroup_name");
        post_list->ShowingFunction(std::string(group));
    });
    c_group->addStyleClass("feed_group_unit");
    name->addStyleClass("feed_group_name");
}

void groupsView::RenderGroups() {
    group_box_->clear();
    for (int i = 0; i < groups_.size(); ++i) {
        RenderGroup(groups_[i]);
    }
}

void groupsView::HandleHttpResponse(std::error_code err, const Wt::Http::Message& response) {
    std::cout << "=============HANDLE RESPONSE START" << std::endl;
    if (!err & response.status() == 200) {
        std::cout << "=============HANDLE RESPONSE" << std::endl;
        std::cout << response.body() << std::endl;
        Wt::Json::Object json_body;
        Wt::Json::Array groups;
        groups_.clear();
        Wt::Json::parse(response.body(), json_body);
        groups = json_body.get("cluster_groups");
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

void groupsView::GoToTheUserPage() {
    internal_path_.emit("/userpage");
}

void groupsView::AddCssStyles() {
    header_->addStyleClass("feed_header");
    user_icon_->addStyleClass("feed_user_icon");
}

void groupsView::ShowingFunction() {
    std::string query = group_name_;
    query[0] = std::tolower(query[0]);
    DoGetRequest("http://127.0.0.1:1026/clusters/groups/?type=" + query);
}

void groupsView::UpdateGroupName(const std::string& new_name) { 
    group_name_ = new_name;
    name_box_->clear();
    name_box_->addWidget(std::make_unique<Wt::WText>(group_name_));
    name_box_->clicked().connect([=] (const Wt::WMouseEvent& e) {
        ShowingFunction();
        group_box_->show();
        sub_group_posts->hide();
    });
    name_box_->setMargin(15, Wt::Side::Bottom);
    name_box_->setMargin(15, Wt::Side::Top);
}

groupsView::groupsView(const std::string& group_name)
{
    std::cout << "GROUPS VIEW IS START TO WORK" << std::endl;
    LoadingInitialSize();
    group_name_ = group_name;
    header_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());
    header_->setHeight(100);
    user_icon_ = header_->addWidget(std::make_unique<Wt::WImage>("src/images/little_user.svg"));
    user_icon_->setAlternateText("user_icon");
    user_icon_->clicked().connect(this, &groupsView::GoToTheUserPage);

    name_box_ = header_->addWidget(std::make_unique<Wt::WContainerWidget>());
    name_box_->addWidget(std::make_unique<Wt::WText>(group_name_));
    Wt::WContainerWidget* main_box = header_->addWidget(std::make_unique<Wt::WContainerWidget>());
    main_box->addWidget(std::make_unique<Wt::WText>("На главную"));    
    main_box->clicked().connect([=] (const Wt::WMouseEvent& e) {
        internal_path_.emit("/");
    });

    body_ = this->addWidget(std::make_unique<Wt::WContainerWidget>());
    group_box_ = body_->addWidget(std::make_unique<Wt::WContainerWidget>());
    sub_group_posts = body_->addWidget(std::make_unique<Wt::WContainerWidget>());
    g_name_box_ = sub_group_posts->addWidget(std::make_unique<Wt::WContainerWidget>());
    post_list = sub_group_posts->addWidget(std::make_unique<groupPostsView>(""));
    sub_group_posts->hide();

    client_ = addChild(std::make_unique<Wt::Http::Client>());
    client_->done().connect(this, &groupsView::HandleHttpResponse);

    header_->addStyleClass("feed_header");
    user_icon_->addStyleClass("feed_user_icon");
    name_box_->addStyleClass("feed_main");
    body_->addStyleClass("feed_body");
    group_box_->addStyleClass("feed_group_box");
    main_box->addStyleClass("groups_go_to_main");
}