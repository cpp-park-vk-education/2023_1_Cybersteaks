#include <string>
#include <map>
#include "./ORM/lib/include/IModel.hpp"

struct Users : public IModel {
    int ID = -1;
    std::string login = "";
    std::string password = "";
    std::string first_name = "";
    std::string second_name = "";
    std::string photo = "";
    int subscriptions = -1;
    int subcribers = -1;

    ModelManager<User> model_manager;

    static std::string GetModelName() override {
        return "User";
    }

    std::string GetFilterExpression(User filter_object) override {
        std::string expression = "WHERE ";
        if(filter_object.ID != -1)
            expression += "ID = " + std::to_string(filter_object.ID);
        if(filter_object.login != "")
            expression += "login = " + filter_object.login;
        if(filter_object.password != "")
            expression += "password = " + filter_object.password;
        if(fileter_object.first_name != "")
            expression += "first_name = " + filter_object.first_name;
        if(fileter_object.second_name != "")
            expression += "second_name = " + filter_object.second_name;
        if(fileter_object.photo != "")
            expression += "photo = " + filter_object.photo;
        if(fileter_object.subcribers != -1)
            expression += "subscribers = " + std::to_string(fileter_object.subcribers);
        if(filter_object.subscriptions != -1)
            expression += "subscriptions = " + std::to_string(fileter_object.subcribtions);
        return expression;
    }

    std::map<std::string, std::string> Serialize(User object){
        std::map<std::string, std::string> serialize_obj;
        serialize_obj["ID"] = std::to_string(object.ID);
        serialize_obj["login"] = object.login;
        serialize_obj["password"] = object.password;
        serialize_obj["first_name"] = object.first_name;
        serialize_obj["second_name"] = object.second_name;
        serialize_obj["photo"] = object.photo;
        serialize_obj["subscribers"] = std::to_string(object.subcribers);
        serialize_obj["subscriptions"] = std::to_string(object.subcribtions);
    }

    User Deserialize(std::map<std::string, std::string> dict){
        User object;
        object.ID = dict["ID"];
        object.login = dict["login"];
        object.password = dict["password"];
        object.first_name = dict["first_name"];
        object.second_name = dict["second_name"];
        object.photo = dict["photo"];
        object.subcribers = dict["subscribers"];
        object.subcribtions = dict["subscriptions"];
    }
}

IModel ModelFabric(std::string model_name){
    if(model_name == "User")
        return User();
}