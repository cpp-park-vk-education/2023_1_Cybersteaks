#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <typeinfo>
#include <limits>
#include "Wt/Json/Value.h"
#include "Wt/Json/Array.h"
#include "Wt/Json/Object.h"

class ModelJsonValue {
public:
    ModelJsonValue(const std::string& new_name, const std::string& new_value, const std::string& new_type) {
        name = new_name;
        value = new_value;
        type = new_type;
    };
    ModelJsonValue(const std::string& new_name, const int new_value) {
        name = new_name;
        value = std::to_string(new_value);
        type = "number";
    };
    ModelJsonValue(const std::string& new_name, const std::string& new_value) {
        name = new_name;
        value = new_value;
        type = "string";
    };
    std::string GetJsonValue();
    ModelJsonValue& operator = (const int new_value) { 
        value = std::to_string(new_value); 
        return *this; 
    };
    ModelJsonValue& operator = (const std::string& new_value) { 
        value = new_value; 
        return *this; 
    };
    std::string GetType() { return type; };
    std::string GetName() { return name; };
    std::string GetValue() { return value; };
    void SetName(const std::string& new_name) { name = new_name; };
    void SetValue(const std::string& new_value) { value = new_value; };
    operator int() const {
        int result = 0;
        try {
            result = std::stoi(value);
        }
        catch (std::out_of_range const& ex) { result = 10000; }
        catch (std::invalid_argument const& ex) { result = 0; }
        return result;
    }
    /*operator bool() const {
        if (value == "true")
            return true;
        else if (value == "false")
            return false;
        return false;
    }*/
    operator std::string() const {
        return value;
    }
protected:
    std::string name;
    std::string value;
    std::string type;
};


class Model {
public:
    std::string JSONSerializer();
    void JsonParse(const Wt::Json::Object obj);
    ModelJsonValue& operator [] (const std::string& v_name);
protected:
    std::vector<ModelJsonValue> values;
};

class Group : public Model {
public:
    Group();
};

class User : public Model {
public:
    User();
};

class Token {
public:
    Token() {
        access_token = "";
        token_name = "";
    };
    Token(const std::string& t_name) {
        access_token = "";
        token_name = t_name;
    };
    Token(const std::string& a_token, const std::string& t_name) {
        access_token = a_token;
        token_name = t_name;
    };
    std::string GetToken() { return access_token; };
    void SetToken(const std::string& new_token) { access_token = new_token; };
    std::string AuthString() { return token_name + " " + access_token; };
private:
    std::string access_token;
    std::string token_name;
};