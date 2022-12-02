#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iterator>
#include <limits>

#define INF std::numeric_limits<int>::max();
using namespace std;

struct Node
{
    char id;
    int weight;
    Node *prev = nullptr;
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

bool contains(vector<Node *> nodes, Node *node)
{
    for (int i = 0; i < nodes.size(); i++)
        if (nodes[i]->id == node->id)
            return true;

    return false;
}

void removeNode(vector<Node *> &nodes, Node *node)
{
    for (vector<Node *>::iterator it = nodes.begin(); it != nodes.end(); it++)
        if (*it == node)
        {
            nodes.erase(it);
            break;
        }
}

void printPath(Node *node)
{
    if (node->prev == nullptr)
        return;
    printPath(node->prev);
    cout << node->prev->id;
}

void printTopology(vector<Node *> nodes)
{
    cout << " NODE\t\t"
         << "DISTANCE\t\t"
         << "PATH" << endl;
    for (int i = 1; i < nodes.size(); i++)
    {
        cout << nodes[0]->id << " -> " << nodes[i]->id << "\t\t   ";

        int inf = INF;
        if (nodes[i]->weight < inf)
            cout << nodes[i]->weight << "\t\t\t ";
        else
            cout << "INF"
                 << "\t\t\t ";

        if (nodes[i]->prev)
        {
            printPath(nodes[i]);
            cout << nodes[i]->id << endl;
        }
        else
            cout << "-" << endl;
    }

    cout << endl
         << endl;
}

void dijkstra(vector<Node *> graph, Node *start)
{
    vector<Node *> univisited;
    vector<Node *> visited;

    for (int i = 0; i < graph.size(); i++) // assign weigth infinity to all nodes
    {
        graph[i]->weight = INF;
        univisited.push_back(graph[i]);
    }

    // assign weight zero the start node
    start->weight = 0;
    Node *current = start;

    while (!univisited.empty())
    {
        // current node adjacency
        vector<Node *> adj;
        for (pair<Node *, int> edge : current->edges)
        {
            if (contains(univisited, edge.first))
            {
                long tmpWeight = current->weight + abs(edge.second);
                if (tmpWeight < edge.first->weight)
                    edge.first->weight = tmpWeight;
                edge.first->prev = current;
                adj.push_back(edge.first);
            }
        }
        // sorting current node adjacency
        sort(adj.begin(), adj.end(), [](const Node *a, const Node *b)
             { return a->weight < b->weight; });

        visited.push_back(current);

        removeNode(univisited, current);

        if (!adj.empty())
            current = adj.front();
        else // incase there're some out of current adjacency
            current = univisited.front();
    }

    sort(visited.begin(), visited.end(), [](const Node *a, const Node *b) // sort by id... just for ordering
         { return a->id < b->id; });
    printTopology(visited);
}

int main()
{
    vector<Node *> graph;

    // negative weights are simply absoluted.

    Node a('A');
    graph.push_back(&a);
    Node b('B');
    graph.push_back(&b);
    Node c('C');
    graph.push_back(&c);
    Node d('D');
    graph.push_back(&d);
    Node e('E');
    graph.push_back(&e);
    Node f('F');
    graph.push_back(&f);
    Node g('G');
    graph.push_back(&g);
    Node h('H');
    graph.push_back(&h);
    Node i('I');
    graph.push_back(&i);

    a.addEdge(&b, 4);
    a.addEdge(&h, 8);

    b.addEdge(&h, 11);
    b.addEdge(&c, 8);

    c.addEdge(&i, 2);
    c.addEdge(&f, 4);
    c.addEdge(&d, 7);

    d.addEdge(&e, 9);
    d.addEdge(&f, 14);

    e.addEdge(&f, -10);

    f.addEdge(&g, 2);

    g.addEdge(&i, 6);
    g.addEdge(&h, -1);

    h.addEdge(&i, 7);

    c.addEdge(&b, 4);

    dijkstra(graph, &a);

    return 0;
}