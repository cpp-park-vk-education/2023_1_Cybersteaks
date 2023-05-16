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
#include <Wt/WImage.h>

#include "feedView.hpp"
#include "store.hpp"

class INcreaApplication : public Wt::WApplication
{
public:
    INcreaApplication(const Wt::WEnvironment& env);

private:
    Wt::WContainerWidget *head_;
    Wt::WContainerWidget *body_;
    void CreateStatic();
    void Clear();
    void HandlePathChange(const std::string& path);
};