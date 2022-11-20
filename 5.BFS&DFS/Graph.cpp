//
// Created by daniel on 20.11.22.
//
#include "Graph.h"

Graph::Graph(int size) : grahSize(size)
{
    this->adj.resize(size);
}

void Graph::addEdge(int index, int value) {
    this->adj[index].push_back(value);
}
vector<vector<int>> Graph::getAdj()
{
    return this->adj;
}

int Graph::size()
{
    return this->grahSize;
}