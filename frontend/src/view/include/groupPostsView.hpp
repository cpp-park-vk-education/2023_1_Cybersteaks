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

class groupPostsView : public Wt::WContainerWidget {
public:
    groupPostsView(const std::string& new_name);
    void ShowingFunction(const std::string& name);
    void DoGetRequest(const std::string& url);
private:
    Wt::WContainerWidget* head_;
    Wt::WContainerWidget* body_;
    Wt::Http::Client *client_;
    Wt::Json::Array posts_;
    std::string name_;

    void RenderPosts();
    void HandleHttpResponse(std::error_code err, const Wt::Http::Message& response);
};