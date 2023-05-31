#include <string>
#include <map>

const std::string MODELS = "../models.json";
const std::string CONFIG = "../config.json";

const std::map<std::string, std::string> convertTypes = {
    {"integer", "INT"},
    {"string", "TEXT"},
    {"foreign_key", "FOREIGN KEY"},
    {"date", "DATETIME"}};
