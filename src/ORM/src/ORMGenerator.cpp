#include "ORM.hpp"
#include "ORMConstants.hpp"

#include <nlohmann/json.hpp>
#include <map>
#include <fstream>
#include <iostream>

void ORMGenerator::Migrate()
{

    std::ifstream fileModels(MODELS);
    std::ifstream fileSchema(SCHEMA);
    nlohmann::json dataModels;
    nlohmann::json dataSchema;
    fileModels >> dataModels;
    fileSchema >> dataSchema;
    fileModels.close();
    fileSchema.close();
    /*for (auto &table : dataModels.items())
    {
        std::map<std::string, std::string> values = table.value().get<std::map<std::string, std::string>>();
        for (auto &[key, value] : values)
            value = convertTypes.at(value);
        std::cout << ORM::CreateTable(table.key(), values);
    }

    std::map<std::string, std::string> test_values = {
        {"id", "1"},
        {"content", "text"},
        {"creation_date", "01.01.1000"},
        {"likes", "1"},
        {"group_id", "1"}};
    //std::cout << ORM::Insert("Post", test_values);
    std::cout << ORM::Delete("Post", "1");*/
    std::map<std::string, std::string> test_values = {
        {"id", "1"},
        {"post_id", "5"},
        {"user_id", "6"}};
    for (auto row : ORM::Find("Likes", "1"))
        std::cout << row[std::distance(test_values.begin(), test_values.find("user_id"))] << " ";
    std::cout << std::endl;
}
