#include "../include/Generator.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

std::ifstream ORMGenerator::ReadModels()
{
    std::ifstream config_file("../config.json");
    nlohmann::json config = nlohmann::json::parse(config_file);
    std::string models_name = "../";
    models_name += config["Models"];
    return std::ifstream(models_name);
}

void ORMGenerator::Generate()
{
    auto models_file = ReadModels();
    nlohmann::json models_json;
    models_file >> models_json;
    auto generator = Generator(models_json);
    out << "#include \"./ORM/include/ORM.hpp\"" << std::endl
        << std::endl;
    out << generator.GenerateModelsDefenitions() << std::endl
        << std::endl;
    out << generator.GenerateModelManagers() << std::endl
        << std::endl;
    out << generator.GenerateModels() << std::endl
        << std::endl;
    std::ofstream res_models(modelsOut);
    res_models << out.str();
}

Generator::Generator(const nlohmann::json &models)
{
    this->models = models;
}

std::string Generator::GenerateModelsDefenitions()
{
    std::string result;
    for (auto &table : models.items())
    {
        result += ModelDef(table.key());
    }
    return result;
}

std::string Generator::GenerateModels()
{
    std::string result;
    for (auto table : models.items())
    {
        result += Model(table.key(), table.value().get<std::map<std::string, std::string>>());
    }
    return result;
}

std::string Generator::ModelDef(const std::string &model)
{
    return "struct " + model + ";\n";
}

std::string Generator::Model(const std::string &name, const std::map<std::string, std::string> properties)
{
    std::string result;
    result += "\nstruct " + name + "\n{\n";
    for (auto [field, type] : properties)
    {
        result += "    " + ConvertType(type) + " " + field + " = " + DefaultVal(type) + ";\n";
    }
    result += "};\n";
    return result;
}

std::string Generator::ConvertType(const std::string &type)
{
    if (type == "string")
        return "std::string";
    else if (type == "integer")
        return "int";
    else if (type == "date")
        return "std::string";
    else if (type == "foreign_key")
        return "int";
    else
        return "";
}

std::string Generator::DefaultVal(const std::string &type)
{
    if (type == "string")
        return "\"\"";
    else if (type == "integer")
        return "0";
    else if (type == "date")
        return "\"\"";
    else if (type == "foreign_key")
        return "-1";
    else
        return "";
}

std::string Generator::GenerateModelManagers()
{
    std::string result = "\n";
    for (auto table : models.items())
    {
        result += ManagerDefenition(table.key());
        result += ManagerGetName(table.key());
        result += "};\n\n";
    }
    return result;
}

std::string Generator::ManagerDefenition(const std::string &name)
{
    return "class " + name + "ModelManager : public IModelManager<" + name + ">\n{\npublic:\n";
}

std::string Generator::ManagerGetName(const std::string &name)
{
    return "    std::string GetModelName() override\n    {\n        return \"" + name + "\";\n    }\n";
}