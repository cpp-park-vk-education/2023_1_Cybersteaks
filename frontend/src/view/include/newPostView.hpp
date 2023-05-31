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
#include <Wt/WFileUpload.h>
#include <Wt/WProgressBar.h>
#include <Wt/WPushButton.h>
#include <Wt/WTextArea.h>

class newPostView : public Wt::WContainerWidget {
public:
    newPostView(const std::string& token);
    Wt::Signal<>& go_to_userpage() { return go_to_userpage_; };
    void DoGetRequest(const std::string& url);
    void ShowingFunction();
    void UpdateToken(const std::string& new_token) { token_ = new_token; };
private:
    Wt::WContainerWidget* head_;
    Wt::WContainerWidget* body_;
    Wt::WContainerWidget* portfolio_form_;
    Wt::WFileUpload* file_;
    Wt::WPushButton* upload_file_;
    Wt::WContainerWidget* blog_form_;

    Wt::Json::Object user_;
    Wt::Http::Client *client_;
    std::string token_;

    Wt::Signal<> go_to_userpage_;

    void AddCssStyles();
    void RenderUser();
    void UpdateUserInfo();
    void HandleHttpResponse(std::error_code err, const Wt::Http::Message& response);
};