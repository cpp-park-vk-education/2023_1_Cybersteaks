#include "model.hpp"

std::string ModelJsonValue::GetJsonValue() {
    std::string result;
    result += "'" + name + "': ";
    if (type == "string")
        result += "'";
    result += value;
    if (type == "string")
        result += "'";
    return result;
}

ModelJsonValue& Model::operator[] (const std::string& v_name) {
    for (int i = 0; i < values.size(); ++i) {
        if (values[i].GetName() == v_name)
            return values[i];
    }
    return values[0];
}

std::string Model::JSONSerializer() {
    std::string result = "{\n";
    for (int i = 0; i < values.size(); ++i) {
        result += values[i].GetJsonValue();
        if (i != values.size() - 1)
            result +=  + ",\n";
    }
    result += "}\n";
    return result;
}

void Model::JsonParse(const Wt::Json::Object obj) {
    for (int i = 0; i < values.size(); ++i)
        values[i].SetValue(std::string(obj.get(values[i].GetName())));
}

Group::Group() {
    values.push_back(ModelJsonValue("ID", 0));
    values.push_back(ModelJsonValue("name", "name"));
    values.push_back(ModelJsonValue("descriptions", "descriptions"));
    values.push_back(ModelJsonValue("photo", "photo"));
    values.push_back(ModelJsonValue("type", "type"));
}

User::User() {
    values.push_back(ModelJsonValue("ID", 0));
    values.push_back(ModelJsonValue("login", ""));
    values.push_back(ModelJsonValue("first_name", ""));
    values.push_back(ModelJsonValue("second_name", ""));
    values.push_back(ModelJsonValue("photo", ""));
    values.push_back(ModelJsonValue("subscriptions", 0));
    values.push_back(ModelJsonValue("subscribers", 0));
    values.push_back(ModelJsonValue("creation_date", ""));
    values.push_back(ModelJsonValue("birthday", ""));
}