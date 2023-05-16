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

std::string Group::JSONSerializer() {
    std::string result = "{\n";
    for (int i = 0; i < values.size(); ++i) {
        result += values[i].GetJsonValue();
        if (i != values.size() - 1)
            result +=  + ",\n";
    }
    result += "}\n";
    return result;
}

Group::Group() {
    values.push_back(ModelJsonValue("ID", 3));
    values.push_back(ModelJsonValue("name", "name"));
    values.push_back(ModelJsonValue("descriptions", "descriptions"));
    values.push_back(ModelJsonValue("photo", "photo"));
    values.push_back(ModelJsonValue("type", "type"));
}