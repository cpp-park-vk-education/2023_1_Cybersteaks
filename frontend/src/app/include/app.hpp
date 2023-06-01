#pragma once

#include <iostream>
#include <string>
#include <system_error>
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/Http/Client.h>
#include <Wt/Json/Parser.h>
#include <Wt/Json/Object.h>
#include <Wt/WImage.h>
#include <Wt/WSignal.h>

#include "feedView.hpp"
#include "loginView.hpp"
#include "userView.hpp"
#include "postView.hpp"
#include "newPostView.hpp"
#include "groupsView.hpp"
#include "store.hpp"
#include "model.hpp"

class INcreaApplication : public Wt::WApplication
{
public:
    INcreaApplication(const Wt::WEnvironment& env);

private:
    Wt::WContainerWidget *head_;
    Wt::WContainerWidget *body_;
    Token token;
    Wt::Json::Object user_;
    std::string group_name_;
    std::string username_;
    feedView* feedView_;
    userView* userView_;
    loginView* loginView_;
    newPostView* newPostView_;
    groupsView* groupsView_;
    void CreateStatic();
    void Clear();
    void HandlePathChange(const std::string& path);
    void CreateViews();
    void CreateConnectForViews();
    void HideViews();
};