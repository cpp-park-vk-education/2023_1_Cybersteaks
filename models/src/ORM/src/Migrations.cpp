#include "Generator.hpp"

#include <nlohmann/json.hpp>
#include <map>
#include <fstream>
#include <iostream>

const std::map<std::string, std::string> convertTypes = {
    {"integer", "INT"},
    {"string", "TEXT"},
    {"foreign_key", "FOREIGN KEY"},
    {"date", "DATETIME"}};


void ORMGenerator::Migrate()
{
    //read from config
    //do like Kraskal
}
