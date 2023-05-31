#include "ORM.hpp"
#include "Exeption.hpp"

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <exception>
#include <nlohmann/json.hpp>
#include <mysqlx/xdevapi.h>

std::vector<mysqlx::Row> ORM::Select(const std::string &table) // work
{
    std::unique_ptr<mysqlx::Session> connection = ConnectionDB();

    mysqlx::Schema db = connection->getSchema(DatabaseInfo()["Name"]);
    mysqlx::Table dbTable = db.getTable(table);
    mysqlx::RowResult result = dbTable.select("*").execute();

    return result.fetchAll();
}

std::vector<mysqlx::Row> ORM::Filter(const std::string &table, const std::string &parameter) // work
{
    std::unique_ptr<mysqlx::Session> connection = ConnectionDB();

    mysqlx::Schema db = connection->getSchema(DatabaseInfo()["Name"]);
    mysqlx::Table dbTable = db.getTable(table);
    mysqlx::RowResult result = dbTable.select("*").where(parameter).execute();

    return result.fetchAll();
}

std::vector<mysqlx::Row> ORM::Find(const std::string &table, const std::string &object_id) // work
{
    std::unique_ptr<mysqlx::Session> connection = ConnectionDB();
    if (!connection)
        throw Error("Connection is failed.");

    mysqlx::Schema db = connection->getSchema(DatabaseInfo()["Name"]);
    mysqlx::Table dbTable = db.getTable(table);
    mysqlx::RowResult result = dbTable.select("*").where("ID = " + object_id).execute();

    return result.fetchAll();
}

bool ORM::Delete(const std::string &table, const std::string &object_id) // work
{
    std::unique_ptr<mysqlx::Session> connection = ConnectionDB();

    mysqlx::Schema db = connection->getSchema(DatabaseInfo()["Name"]);
    mysqlx::Table dbTable = db.getTable(table);

    connection->startTransaction();
    try
    {
        dbTable.remove().where("ID = " + object_id).execute();
        connection->commit();
        return true;
    }
    catch (const mysqlx::Error &err)
    {
        connection->rollback();
        std::cerr << err.what() << std::endl;
    }

    return false;
}

bool ORM::Insert(const std::string &table, const std::map<std::string, std::string> &object) // work
{
    std::unique_ptr<mysqlx::Session> connection = ConnectionDB();

    mysqlx::Schema db = connection->getSchema(DatabaseInfo()["Name"]);
    mysqlx::Table dbTable = db.getTable(table);

    std::vector<std::string> fields;
    std::vector<std::string> values;

    for (auto field = object.begin(); field != object.end(); ++field)
    {
        fields.push_back(field->first);
        values.push_back(field->second);
    }

    connection->startTransaction();
    try
    {
        dbTable.insert(fields.begin(), fields.end()).values(values.begin(), values.end()).execute();
        connection->commit();
        return true;
    }
    catch (const mysqlx::Error &err)
    {
        connection->rollback();
        std::cerr << err.what() << std::endl;
    }

    return false;
}

bool ORM::Update(const std::string &table, const std::map<std::string, std::string> &object) // work
{
    std::unique_ptr<mysqlx::Session> connection = ConnectionDB();

    mysqlx::Schema db = connection->getSchema(DatabaseInfo()["Name"]);
    mysqlx::Table dbTable = db.getTable(table);

    const std::string id = object.at("id");

    std::vector<std::string> fields;
    std::vector<std::string> values;

    for (auto field = object.begin(); field != object.end(); ++field)
    {
        if (field->first != "id")
        {
            fields.push_back(field->first);
            values.push_back(field->second);
        }
    }

    connection->startTransaction();
    try
    {
        mysqlx::TableUpdate updatedTable = dbTable.update();
        for (size_t i = 0; i != fields.size(); ++i)
            updatedTable.set(fields[i], values[i]);
        updatedTable.where("id = " + id).execute();

        connection->commit();
        return true;
    }
    catch (const mysqlx::Error &err)
    {
        connection->rollback();
        std::cerr << err.what() << std::endl;
    }

    return false;
}

bool ORM::CreateTable(const std::string &table, const std::map<std::string, std::string> &columns_names_and_types) // Don't work
{

    std::unique_ptr<mysqlx::Session> connection = ConnectionDB();

    std::map<std::string, std::string> foreignKeys;

    connection->startTransaction();
    try
    {
        connection->sql("USE " + DatabaseInfo()["Name"] + ";").execute();
        std::string SQLRequest = "CREATE TABLE " + table + "\n(\n";
        for (auto &column : columns_names_and_types)
            if (column.second != "FOREIGN KEY")
                SQLRequest += "    " + column.first + " " + column.second + ",\n";
            else
            {
                std::string refTable = column.first.substr(0, column.first.find("_"));
                std::string field = column.first.substr(column.first.find("_") + 1, column.first.size() - 1);
                foreignKeys[column.first] = "    FOREIGN KEY (" + field + ") REFERENCES " + refTable + "(" + field + ") ON DELETE CASCADE,\n";
            }
        SQLRequest += "    PRIMARY KEY (id),\n";
        if (foreignKeys.size() != 0)
        {
            for (auto &key : foreignKeys)
                SQLRequest += key.second;
        }
        SQLRequest.pop_back();
        SQLRequest.pop_back();
        SQLRequest += "\n);";
        connection->sql(SQLRequest).execute();
        connection->commit();
        return true;
    }
    catch (const mysqlx::Error &err)
    {
        connection->rollback();
        std::cerr << err.what() << std::endl;
    }

    return false;
}

bool ORM::DeleteTable(const std::string &table) // work
{
    std::unique_ptr<mysqlx::Session> connection = ConnectionDB();

    connection->startTransaction();
    try
    {
        connection->sql("USE " + DatabaseInfo()["Name"] + ";").execute();
        connection->sql("DROP TABLE " + table + " CASCADE;").execute();
        connection->commit();
        return true;
    }
    catch (const mysqlx::Error &err)
    {
        connection->rollback();
        std::cerr << err.what() << std::endl;
    }

    return false;
}

bool ORM::DropDatabase() // work
{
    std::unique_ptr<mysqlx::Session> connection = ConnectionDB();

    try
    {
        connection->dropSchema(DatabaseInfo()["Name"]);
        return true;
    }
    catch (const Error &err)
    {
        std::cerr << err.what() << std::endl;
    }

    return false;
}

bool ORM::CreateDatabase() // work
{
    std::unique_ptr<mysqlx::Session> connection = ConnectionDB();

    try
    {
        connection->createSchema(DatabaseInfo()["Name"]);
        return true;
    }
    catch (const Error &err)
    {
        std::cerr << err.what() << std::endl;
    }

    return false;
}

std::map<std::string, std::string> ORM::DatabaseInfo() // work
{
    std::ifstream jsonConfig("../config.json");
    nlohmann::json config;
    jsonConfig >> config;
    jsonConfig.close();
    return config["Database"].get<std::map<std::string, std::string>>();
}

std::unique_ptr<mysqlx::Session> ORM::ConnectionDB() // work
{
    std::map<std::string, std::string> databaseConfig = DatabaseInfo();

    try
    {
        auto session = std::make_unique<mysqlx::Session>(DatabaseInfo()["Host"],
                                                         std::stoi(DatabaseInfo()["Port"]),
                                                         DatabaseInfo()["Username"],
                                                         DatabaseInfo()["Password"]);
        return session;
    }
    catch (const mysqlx::Error &err)
    {
        throw Error("Connection is failed.");
    }
    return nullptr;
}
