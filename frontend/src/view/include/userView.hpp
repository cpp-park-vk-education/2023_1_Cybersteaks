#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <Wt/WImage.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/Http/Client.h>
#include <Wt/Http/Message.h>
#include <Wt/Json/Parser.h>
#include <Wt/Json/Object.h>
#include <Wt/Json/Array.h>
#include <Wt/Json/Value.h>
#include <Wt/WSignal.h>

#include "model.hpp"
#include "postView.hpp"

class userView : public Wt::WContainerWidget {
public:
    userView(const std::string& token);
    //userView(const Wt::Json::Object& user);
    Wt::Signal<Wt::Json::Object>& update_user() { return update_user_; };
    Wt::Signal<>& go_to_main_page() { return go_to_main_page_; };
    Wt::Signal<>& logout() { return logout_; };
    void DoGetRequest(const std::string& url);
    void ShowingFunction();
    void UpdateToken(const std::string& new_token) { token_ = new_token; };
private:
    User user;
    Wt::WContainerWidget* head_;
    Wt::WContainerWidget* user_widget_;
    Wt::WContainerWidget* options_;
    Wt::WContainerWidget* portfolio_option_;
    Wt::WContainerWidget* blog_option_;
    Wt::WContainerWidget* body_;
    Wt::WContainerWidget* portfolio_;
    Wt::WContainerWidget* blog_;
    Wt::Json::Object user_;
    Wt::Http::Client *client_;
    std::string token_;

    Wt::Signal<Wt::Json::Object> update_user_;
    Wt::Signal<> go_to_main_page_;
    Wt::Signal<> logout_;

    void AddCssStyles();
    void RenderUser();
    void UpdateUserInfo();
    void HandleHttpResponse(std::error_code err, const Wt::Http::Message& response);
};