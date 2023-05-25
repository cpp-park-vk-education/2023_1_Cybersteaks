#include "ORM.hpp"

#include <nlohmann/json.hpp>
#include <map>
#include <fstream>
#include <iostream>

void ORMGenerator::Migrate()
{

    std::ifstream file(sources.find("models"));
    nlohmann::json data;
    file >> data;
    file.close();
    for (auto &table : data.items())
        ORM::CreateTable(table.key(), table.value().get<std::map<std::string, std::string>>());
}
