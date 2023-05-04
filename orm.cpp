#include <iostream>
#include <vector>
#include <string>

struct User {
    int ID;
    std::string login;
    std::string password;
    std::string first_name;
    std::string second_name;
    std::string photo;
    int subscroptions;
    int subscribers;
    std::string creation_date;
    std::string birthday;
    std::string last_seen_claster;
};

struct Model {
    std::string Serialize() { return ""; };
    std::string Deserialize() { return ""; };
    void Set(std::string field, std::string value) {};
};

class ModelFabric {
public:
    static Model CreateModel(std::string model_name) {
        return Model();
    };
};

class Feed {
public:
    std::vector<Model> GetFeed(User user) {
        std::vector<Model> res;
        res.push_back(Model());
        return res;
    };
};

User user;

Model model, model1, model2;
ModelFabric fabric;
Feed feed;

std::vector<Model> models = {
    model1,
    model2
};