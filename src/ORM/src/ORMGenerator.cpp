#include "ORM.hpp"
#include "ORMConstants.hpp"
#include "TopologicalSort.hpp"
#include "Exeption.hpp"

#include <nlohmann/json.hpp>
#include <map>
#include <deque>
#include <fstream>
#include <iostream>

void ORMGenerator::Migrate()
{

    std::ifstream fileModels(MODELS);
    nlohmann::json dataModels;
    fileModels >> dataModels;
    fileModels.close();

    ORM::DropDatabase();
    ORM::CreateDatabase();

    std::vector<std::pair<std::string, std::map<std::string, std::string>>> tables;

    for (auto &table : dataModels.items())
    {
        std::map<std::string, std::string> model = table.value().get<std::map<std::string, std::string>>();
        for (auto &field : model)
            field.second = convertTypes.at(field.second);
        tables.push_back(std::pair(table.key(), model));
    }

    ListGraph graph(tables.size());

    for (int i = 0; i < tables.size(); ++i)
    {
        std::vector<std::string> foreignKeys;
        for (auto &field : tables[i].second)
            if (field.second == "FOREIGN KEY")
                foreignKeys.push_back(field.first.substr(0, field.first.find("_")));
        if (foreignKeys.size() == 0)
            graph.AddEdge(i, i);
        else
        {
            for (std::string &foreignKey : foreignKeys)
            {
                auto iteratorOnTable = std::find_if(tables.begin(), tables.end(), [&](const std::pair<std::string, std::map<std::string, std::string>> &table)
                                                    { return table.first == foreignKey; });
                graph.AddEdge(i, std::distance(tables.begin(), iteratorOnTable));
            }
        }
    }

    std::deque<int> sortedGraph = mainTopologicalSort(graph);

    while (!sortedGraph.empty())
    {
        int vertex = sortedGraph.back();
        sortedGraph.pop_back();

        ORM::CreateTable(tables[vertex].first, tables[vertex].second);
    }
}
