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
    for (auto &table : dataModels.items())
    {
        std::map<std::string, std::string> values = table.value().get<std::map<std::string, std::string>>();
        for (auto &[key, value] : values)
            value = convertTypes.at(value);
        std::cout << ORM::DeleteTable(table.key());
        //std::cout << ORM::CreateTable(table.key(), values, false);
    }

    for (auto &table : dataSchema.items())
    {
        std::map<std::string, std::string> values = table.value().get<std::map<std::string, std::string>>();
        for (auto &[key, value] : values)
            value = convertTypes.at(value);
        std::cout << ORM::DeleteTable(table.key());
        // std::cout << ORM::CreateTable(table.key(), values, true);
    }
}
