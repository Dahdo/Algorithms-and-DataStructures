#include <iostream>
#include <vector>
#include <utility>

using namespace std;

struct Node
{
    char id;
    int weight;
    vector<pair<Node *, int>> edges; // edge defines a pair of node and edge cost

    Node(char id, int weight = 0)
    {
        this->id = id;
        this->weight = weight;
    }

    void addEdge(Node *node, int cost)
    {
        edges.push_back(make_pair(node, cost));
    }
};

void dijkstra(Node *start);

int main()
{
    Node a('A');
    Node b('B');
    Node c('C');

    a.addEdge(&b, 3);
    a.addEdge(&c, 3);
    a.addEdge(&a, 0);

    b.addEdge(&c, 5);
    b.addEdge(&a, 8);

    c.addEdge(&b, 4);

    while (!b.edges.empty())
    {
        pair<Node *, int> pair = b.edges.back();
        b.edges.pop_back();
        cout << pair.first->id << ", " << pair.second << endl;
    }

    return 0;
}