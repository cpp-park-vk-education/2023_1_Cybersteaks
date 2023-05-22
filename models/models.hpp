#include <string>
#include <map>
#include "./ORM/include/IModelManager.hpp"

struct User;

class UserModelManager : public IModelManager<User> {
public:
    std::string GetModelName() override {
        return "User";
    }

    std::string GetFilterExpression(User filter_object) override {
        std::string expression = "";
        if(filter_object.ID != -1)
            expression += "ID = " + std::to_string(filter_object.ID) + " AND ";
        if(filter_object.login != "")
            expression += "login = " + filter_object.login + " AND ";
        if(filter_object.password != "")
            expression += "password = " + filter_object.password + " AND ";
        if(filter_object.first_name != "")
            expression += "first_name = " + filter_object.first_name + " AND ";
        if(filter_object.second_name != "")
            expression += "second_name = " + filter_object.second_name + " AND ";
        if(filter_object.photo != "")
            expression += "photo = " + filter_object.photo + " AND ";
        if(filter_object.subscribers != -1)
            expression += "subscribers = " + std::to_string(filter_object.subscribers) + " AND ";
        if(filter_object.subscriptions != -1)
            expression += "subcribtions = " + std::to_string(filter_object.subscriptions);
        return expression;
    }

    std::map<std::string, std::string> Serialize(User object) override {
        std::map<std::string, std::string> serialize_obj;
        serialize_obj["ID"] = std::to_string(object.ID);
        serialize_obj["login"] = object.login;
        serialize_obj["password"] = object.password;
        serialize_obj["first_name"] = object.first_name;
        serialize_obj["second_name"] = object.second_name;
        serialize_obj["photo"] = object.photo;
        serialize_obj["subscribers"] = std::to_string(object.subscribers);
        serialize_obj["subscriptions"] = std::to_string(object.subscriptions);
        return serialize_obj;
    }

    User Deserialize(std::map<std::string, std::string> dict) override {
        User object;
        object.ID = std::stoi(dict["ID"]);
        object.login = dict["login"];
        object.password = dict["password"];
        object.first_name = dict["first_name"];
        object.second_name = dict["second_name"];
        object.photo = dict["photo"];
        object.subscribers = std::stoi(dict["subscribers"]);
        object.subscriptions = std::stoi(dict["subscriptions"]);
        return object;
    }
};

struct User {
    int ID = -1;
    std::string login = "";
    std::string password = "";
    std::string first_name = "";
    std::string second_name = "";
    std::string photo = "";
    int subscriptions = -1;
    int subscribers = -1;
    static UserModelManager model_manager;
};

std::string FilterFabric(std::string model_name, std::map<std::string, std::string> model_map){
    if(model_name == "User"){
        auto filter = User::model_manager.Deserialize(model_map);
        return User::model_manager.GetFilterExpression(filter);
    }
}

std::vector<FilterSet> filtersets = {
    FilterSet("Musicians", {
        Filter("Группа", "checkbox", "type"),
        Filter("Количество участников", "integer", "member_count"),
        Filter("Жанр музыки", "text", "genre")
    }),
    FilterSet("Artists", {
        Filter("Пейзажисты", "checkbox", "type"),
        Filter("Количество участников", "integer", "member_count"),
        Filter("Жанр картин", "text", "genre")
    }),
    FilterSet("Programmers", {
        Filter("Gamedev", "checkbox", "type"),
    })
};
