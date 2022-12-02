//
// Created by daniel on 20.11.22.
//
#pragma once
#include <vector>
using namespace std;

class Graph
{
private:
    int grahSize;
    vector<vector<int>> adj;
public:
    Graph(int size);
    void addEdge(int index, int value);
    vector<vector<int>> getAdj();
    int size();
};
