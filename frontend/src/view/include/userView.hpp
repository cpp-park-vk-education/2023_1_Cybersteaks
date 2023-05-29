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

class userView : public Wt::WContainerWidget {
public:
    userView(const std::string& n_username, const Token& n_token);
private:
    User user;
    Token token;
    Wt::WContainerWidget* head_;
    Wt::WContainerWidget* options_;
    Wt::WContainerWidget* body_;
    void DoGetRequest(const std::string& url);
    void HandleHttpResponse(std::error_code err, const Wt::Http::Message& response);

    void AddCssStyles();
};