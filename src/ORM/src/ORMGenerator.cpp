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
    for (auto &table : dataModels.items()){
        //ORM::CreateTable(table.key(), table.value().get<std::map<std::string, std::string>>());
        std::cout << table.key() << std::endl;
    }
}
