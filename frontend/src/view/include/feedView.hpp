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
#include <Wt/Json/Parser.h>
#include <Wt/Json/Object.h>
#include <Wt/Json/Array.h>
#include <Wt/Json/Value.h>
#include <Wt/WSignal.h>

#include "model.hpp"

class feedView : public Wt::WContainerWidget {
public:
    feedView();
    void GoToTheUserPage();
    void ShowingFunction();
    Wt::Signal<std::string>& internal_path() { return internal_path_; };
private:
    Wt::WContainerWidget *body_;
    Wt::WContainerWidget *header_;
    Wt::WContainerWidget *group_box_;
    Wt::WImage *user_icon_;
    Wt::WContainerWidget *search_box_;
    Wt::WLineEdit *request_text_;
    Wt::Http::Client *client_;
    std::vector<Wt::Json::Value> groups_;
    Wt::WContainerWidget *groups_render_;
    Wt::Signal<std::string> internal_path_;
    void DoGetRequest(const std::string& url);
    void RenderGroup(const Wt::Json::Value& group);
    void RenderGroups();
    void LoadingInitialSize();
    void AddCssStyles();
    void HandleHttpResponse(std::error_code err, const Wt::Http::Message& response);
};