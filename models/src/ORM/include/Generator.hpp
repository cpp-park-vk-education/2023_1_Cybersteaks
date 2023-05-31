#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <nlohmann/json.hpp>

class ORMGenerator
{
private:
    std::stringstream out;
    const std::string model_out = "../models.hpp";

public:
    void Migrate();
    void Generate();
    std::ifstream ReadModels();
};


class Generator
{
private:
    std::string ModelDef(const std::string& name);
    std::string Model(const std::string& name, const std::map<std::string, std::string> properties);
    std::string ConvertType(const std::string& type);
    std::string DefaultVal(const std::string& type);
    std::string ManagerGetName(const std::string& name);
    std::string ManagerDefenition(const std::string& name);
    nlohmann::json models;

public:
    Generator(const nlohmann::json& models);

    std::string GenerateModelsDefenitions();
    std::string GenerateModelManagers();
    std::string GenerateModels();
};
