#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <bits/stdc++.h>
#include <cassert>

class ListGraph
{
public:
    explicit ListGraph(int size)
        : adjacencyLists(size)
    {
    }

    ~ListGraph()
    {
    }

    void AddEdge(int from, int to);
    int VerticesCount() const;
    std::vector<int> GetNextVertices(int vertex) const;
    std::vector<int> GetPrevVertices(int vertex) const;

private:
    std::vector<std::vector<int>> adjacencyLists;
};

void ListGraph::AddEdge(int from, int to)
{
    assert(0 <= from && from < adjacencyLists.size());
    assert(0 <= to && to < adjacencyLists.size());

    adjacencyLists[from].push_back(to);
}

int ListGraph::VerticesCount() const
{
    return static_cast<int>(adjacencyLists.size());
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const
{
    assert(0 <= vertex && vertex < adjacencyLists.size());

    return adjacencyLists[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const
{
    assert(0 <= vertex && vertex < adjacencyLists.size());

    std::vector<int> prevVertices;

    for (int from = 0; from < adjacencyLists.size(); ++from)
        for (int to = 0; to < adjacencyLists[from].size(); ++to)
            if (adjacencyLists[from][to] == vertex)
                prevVertices.push_back(from);

    return prevVertices;
}

void topologicalSort(const ListGraph &graph, int vertex, std::vector<bool> &visited, std::deque<int> &sorted)
{
    visited[vertex] = true;
    for (int nextVertex : graph.GetNextVertices(vertex))
        if (!visited[nextVertex])
            topologicalSort(graph, nextVertex, visited, sorted);

    sorted.push_front(vertex);
}

std::deque<int> mainTopologicalSort(const ListGraph &graph)
{
    std::deque<int> sorted;
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); ++i)
        if (!visited[i])
            topologicalSort(graph, i, visited, sorted);

    return sorted;
}