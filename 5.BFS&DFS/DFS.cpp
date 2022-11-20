//
// Created by daniel on 20.11.22.
//
#include <iostream>
#include "Graph.h"
#include "Graph.cpp"
#include <stack>

using namespace std;

vector<int> DSF(int start, vector<vector<int>> adj)
{
    size_t size = adj.size();
    vector<int> visitedIndices;
    vector<bool> visited(size - start, false);

    for (int i = start; i < size ; ++i)
    {
        if(!visited[i] && !adj[i].empty())
        {
            stack<int> toTraverse;
            visited[i] = true;
            toTraverse.push(i);

            while(!toTraverse.empty())
            {
                int currentVertIndex = toTraverse.top();
                toTraverse.pop();
                visitedIndices.push_back(currentVertIndex);

                for(int j : adj[currentVertIndex])
                {
                    if(!visited[j])
                    {
                        visited[j] = true;
                        toTraverse.push(j);
                    }
                }
            }
        }

    }
    return visitedIndices;
}

int main()
{
    Graph g(14);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 5);//
    g.addEdge(1, 7);//
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    g.addEdge(3, 4);//
    g.addEdge(3, 6);//
    g.addEdge(4, 4);
    g.addEdge(5, 10);
    g.addEdge(6, 9);
    g.addEdge(7, 8);
    g.addEdge(9, 11);
    g.addEdge(8, 10);
    g.addEdge(11, 13);


    int j = 1;
    for(int i : DSF(2, g.getAdj()))
        cout << j++ << ". "<< i << " " << endl;

}