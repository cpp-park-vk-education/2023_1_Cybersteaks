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

class loginView : public Wt::WContainerWidget {
public:
    loginView();
    void GoToTheUserPage();
    Wt::Signal<std::string, std::string, std::string>& internal_path() { return internal_path_; };
private:
    std::string token;
    std::string username;
    std::string error;
    Wt::Http::Client *client_;
    Wt::Signal<std::string, std::string, std::string> internal_path_;
    void DoGetRequest(const std::string& url);
    void HandleHttpResponse(std::error_code err, const Wt::Http::Message& response);

    Wt::WContainerWidget* body_;
    Wt::WContainerWidget* form_;
    Wt::WLineEdit* username_;
    Wt::WLineEdit* password_;
    Wt::WContainerWidget* button_;
    void AddCssStyles();
};