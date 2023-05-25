#include "ORM.hpp"

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <exception>
#include <boost/algorithm/string.hpp>
#include <mysqlx/xdevapi.h>

class Error : public std::exception
{
public:
    Error(const std::string &message) : message_(message) {}

    const char *what() const noexcept override
    {
        return message_.c_str();
    }
    const std::string getMessage() const
    {
        return message_;
    }

private:
    std::string message_;
};

std::vector<mysqlx::Row> ORM::Select(const std::string &table)
{
    std::unique_ptr<mysqlx::Session> connection = ConnectionDB();
    if (!connection)
        throw Error("Connection is failed.");
    mysqlx::Schema db = (*connection).getSchema(dataBaseName);
    mysqlx::Table dbTable = db.getTable(table);
    mysqlx::RowResult result = dbTable.select("*").execute();

    return result.fetchAll();
}

std::vector<mysqlx::Row> ORM::Filter(const std::string &table, const std::string &parameter)
{
    std::unique_ptr<mysqlx::Session> connection = ConnectionDB();
    if (!connection)
        throw Error("Connection is failed.");
    mysqlx::Schema db = (*connection).getSchema(dataBaseName);
    mysqlx::Table dbTable = db.getTable(table);
    mysqlx::RowResult result = dbTable.select("*").where(parameter).execute();

    return result.fetchAll();
}

std::vector<mysqlx::Row> ORM::Find(const std::string &table, const std::string &object_id)
{
    std::unique_ptr<mysqlx::Session> connection = ConnectionDB();
    if (!connection)
        throw Error("Connection is failed.");

    mysqlx::Schema db = (*connection).getSchema(dataBaseName);
    mysqlx::Table dbTable = db.getTable(table);
    mysqlx::RowResult result = dbTable.select("*").where("ID = " + object_id).execute();

    return result.fetchAll();
}

bool ORM::Delete(const std::string &table, const std::string &object_id)
{
    std::unique_ptr<mysqlx::Session> connection = ConnectionDB();
    if (!connection)
        throw Error("Connection is failed.");

    mysqlx::Schema db = (*connection).getSchema(dataBaseName);
    mysqlx::Table dbTable = db.getTable(table);

    (*connection).startTransaction();
    try
    {
        dbTable.remove().where("ID = " + object_id).execute();
        return true;
    }
    catch (const mysqlx::Error &err)
    {
        (*connection).rollback();
    }

    return false;
}

bool ORM::Insert(const std::string &table, std::map<std::string, std::string> &object)
{
    std::unique_ptr<mysqlx::Session> connection = ConnectionDB();
    if (!connection)
        throw Error("Connection is failed.");

    mysqlx::Schema db = (*connection).getSchema(dataBaseName);
    mysqlx::Table dbTable = db.getTable(table);

    std::vector<std::string> fields;
    std::vector<std::string> values;

    for (auto field = object.begin(); field != object.end(); ++field)
    {
        fields.push_back(field->first);
        values.push_back(field->second);
    }

    (*connection).startTransaction();
    try
    {
        dbTable.insert(fields.begin(), fields.end()).values(values.begin(), values.end()).execute();
        (*connection).commit();
        return true;
    }
    catch (const mysqlx::Error &err)
    {
        (*connection).rollback();
    }

    return false;
}

bool ORM::Update(const std::string &table, std::map<std::string, std::string> &object)
{
    std::unique_ptr<mysqlx::Session> connection = ConnectionDB();
    if (!connection)
        throw Error("Connection is failed.");

    mysqlx::Schema db = (*connection).getSchema(dataBaseName);
    mysqlx::Table dbTable = db.getTable(table);

    const std::string ID = object["ID"];

    std::vector<std::string> fields;
    std::vector<std::string> values;

    for (auto field = object.begin(); field != object.end(); ++field)
    {
        if (field->first != "ID")
        {
            fields.push_back(field->first);
            values.push_back(field->second);
        }
    }

    (*connection).startTransaction();
    try
    {
        mysqlx::TableUpdate updateTable = dbTable.update();
        for (int i = 0; i < object.size(); ++i)
            updateTable.set(fields[i], values[i]);

        updateTable.where("ID = " + ID).execute();

        (*connection).commit();
        return true;
    }
    catch (const mysqlx::Error &err)
    {
        (*connection).rollback();
    }

    return false;
}

bool ORM::CreateTable(const std::string &table, std::map<std::string, std::string> &columns_names_and_types)
{

    std::unique_ptr<mysqlx::Session> connection = ConnectionDB();
    if (!connection)
        throw Error("Connection is failed.");

    (*connection).startTransaction();
    try
    {
        std::string SQLRequest = "CREATE TABLE " + table + "(\n";
        for (auto &column : columns_names_and_types)
            SQLRequest += column.first + " " + column.second + "\n";
        SQLRequest += ");";
        (*connection).sql(SQLRequest);
        (*connection).commit();
        return true;
    }
    catch (const mysqlx::Error &err)
    {
        (*connection).rollback();
    }

    return false;
}

bool ORM::DeleteTable(const std::string &table)
{
    std::unique_ptr<mysqlx::Session> connection = ConnectionDB();
    if (!connection)
        throw Error("Connection is failed.");

    (*connection).startTransaction();
    try
    {
        (*connection).sql("DROP TABLE " + table);
        (*connection).commit();
        return true;
    }
    catch (const mysqlx::Error &err)
    {
        (*connection).rollback();
    }

    return false;
}

bool ORM::DropDatabase(const std::string &database)
{
    std::unique_ptr<mysqlx::Session> connection = ConnectionDB();
    if (!connection)
        throw Error("Connection is failed.");

    try
    {
        (*connection).dropSchema(dataBaseName);
        return true;
    }
    catch (const Error &err)
    {
        std::cerr << "Error: " << err.what() << std::endl;
    }

    return false;
}

std::unique_ptr<mysqlx::Session> ORM::ConnectionDB()
{
    std::ifstream SQLConfig(pathToConfigFile);
    std::string Host;
    std::getline(SQLConfig, Host);
    boost::algorithm::trim(Host = Host.substr(Host.find(":") + 1));
    std::string Port;
    std::getline(SQLConfig, Port);
    boost::algorithm::trim(Port = Port.substr(Port.find(":") + 1));
    std::string Username;
    std::getline(SQLConfig, Username);
    boost::algorithm::trim(Username = Username.substr(Username.find(":") + 1));
    std::string Password;
    std::getline(SQLConfig, Password);
    boost::algorithm::trim(Password = Password.substr(Password.find(":") + 1));
    SQLConfig.close();

    try
    {
        auto session = std::make_unique<mysqlx::Session>(Host, std::stoi(Port), Username, Password);
        return session;
    }
    catch (const mysqlx::Error &err)
    {
        return nullptr;
    }
    return nullptr;
}
