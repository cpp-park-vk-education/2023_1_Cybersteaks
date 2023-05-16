#pragma once

#include <string>
#include <map>
#include <vector>
#include <mysql/include/mysqlx/xdevapi.h>

const std::string pathToConfigFile = "../SQLConfig.txt";
const std::string dataBaseName = "MockDB";

class ORM
{
public:
    static std::vector<mysqlx::Row> Select(std::string &table);
    static std::vector<mysqlx::Row> ORM::Filter(std::string &table, std::string &parametr);
    static std::vector<mysqlx::Row> ORM::Find(std::string &table, std::string &object_id);
    static bool Delete(std::string &table, std::string &object_id);
    static bool Insert(std::string &table, std::map<std::string, std::string> &object);
    static bool Update(std::string &table, std::map<std::string, std::string> &object);
    static bool CreateTable(std::string &table, std::vector<std::string> &columns);
    static bool DeleteTable(std::string &table);
    static bool DropDatabase(std::string &database);

private:
    static std::unique_ptr<mysqlx::Session> ConnectionDB();
    ;
};

class ORMGenerator
{
public:
    const std::string model_file;
    void GenerateFilters();
    void GenerateModelManager();
    void GenerateModels();
    void FillModels();
};

template <typename Model>
class IModelManager
{
public:
    std::vector<Model> All();
    std::vector<Model> Filter(Model filter_object);
    std::string<Model> Get(std::vector<size_t> objects_id);
    void Delete(Model filter_object);
    void Insert(Model object);

    virtual std::string GetModelName() = 0;
    virtual std::string GetFilterExpression(Model filter_object) = 0;
    virtual std::map<std::string, std::string> Serialize(Model object) = 0;
    virtual Model Deserialize(std::map<std::string, std::string> object) = 0;
};

struct Filter
{
    std::string name;
    std::string type;
    std::string model_field;
    Filter(const std::string &name, const std::string &type, const std::string &model_field)
    {
        this->name = name;
        this->type = type;
        this->model_field = model_field;
    }
};

struct FilterSet
{
    std::vector<Filter> filters;
    std::string model;
    FilterSet(const std::string &model, std::vector<Filter> filters)
    {
        this->filters = filters;
        this->model = model;
    }
};