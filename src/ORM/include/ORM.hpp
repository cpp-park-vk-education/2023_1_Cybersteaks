#pragma once

#include <string>
#include <map>
#include <vector>
#include <mysqlx/xdevapi.h>
class ORM
{
public:
    static std::vector<mysqlx::Row> Select(const std::string &table);
    static std::vector<mysqlx::Row> Filter(const std::string &table, const std::string &parametr);
    static std::vector<mysqlx::Row> Find(const std::string &table, const std::string &object_id);
    static bool Delete(const std::string &table, const std::string &object_id);
    static bool Insert(const std::string &table, const std::map<std::string, std::string> &object);
    static bool Update(const std::string &table, const std::map<std::string, std::string> &object);
    static bool CreateTable(const std::string &table, const std::map<std::string, std::string> &columns);
    static bool DeleteTable(const std::string &table);
    static bool DropDatabase();

private:
    static std::map<std::string, std::string> DatabaseInfo();
    static std::unique_ptr<mysqlx::Session> ConnectionDB();
};

class ORMGenerator
{
public:
    void Migrate();
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
    std::string Get(std::vector<size_t> objects_id);
    void Delete(Model filter_object);
    void Insert(Model object);

    virtual std::string GetModelName() = 0;
    virtual std::string GetFilterExpression(Model filter_object) = 0;
    virtual std::map<std::string, std::string> Serialize(Model object) = 0;
    virtual Model Deserialize(std::map<std::string, std::string> object) = 0;
};
