#include <sstream>
#include "Testing.h"
#include "BST.h"

vector<LevelNode<>> AddT1 = {LevelNode<>(0, 0)};
vector<LevelNode<>> AddT2 = {LevelNode<>(1, 0), LevelNode<>(2, 1), LevelNode<>(3, 2)};
vector<LevelNode<>> AddT3 = {LevelNode<>(2, 0), LevelNode<>(1, 1), LevelNode<>(3, 1)};
vector<LevelNode<>> AddT4 = {LevelNode<>(2, 0), LevelNode<>(1, 1), LevelNode<>(3, 1), LevelNode<>(1, 1)};
vector<LevelNode<>> AddT5 = {LevelNode<>(1, 0), LevelNode<>(2, 1)};

vector<LevelNode<>> T1 = {
    LevelNode<>(7, 0),
    LevelNode<>(6, 1),
    LevelNode<>(5, 2),
    LevelNode<>(4, 3)};

vector<LevelNode<>> T2 = {
    LevelNode<>(4, 0),
    LevelNode<>(5, 1),
    LevelNode<>(6, 2),
    LevelNode<>(7, 3)};

vector<LevelNode<>> T3 = {
    LevelNode<>(50, 0),
    LevelNode<>(0, 1),
    LevelNode<>(-10, 2),
    LevelNode<>(30, 2),
    LevelNode<>(-5, 3),
    LevelNode<>(20, 3)};

vector<LevelNode<>> T4 = {
    LevelNode<>(50, 0),
    LevelNode<>(0, 1),
    LevelNode<>(-10, 2),
    LevelNode<>(30, 2),
    LevelNode<>(20, 3),
    LevelNode<>(40, 3)};

vector<LevelNode<>> T5 = {
    LevelNode<>(50, 0),
    LevelNode<>(10, 1),
    LevelNode<>(100, 1),
    LevelNode<>(70, 2),
    LevelNode<>(200, 2)};

vector<LevelNode<>> T6 = {
    LevelNode<>(5, 0),
    LevelNode<>(1, 1),
    LevelNode<>(10, 1),
    LevelNode<>(-2, 2),
    LevelNode<>(3, 2),
    LevelNode<>(7, 2),
    LevelNode<>(13, 2),
    LevelNode<>(-3, 3),
    LevelNode<>(0, 3),
    LevelNode<>(2, 3),
    LevelNode<>(4, 3),
    LevelNode<>(6, 3),
    LevelNode<>(8, 3),
    LevelNode<>(12, 3),
    LevelNode<>(14, 3)};

vector<LevelNode<>> T7 = {
    LevelNode<>(50, 0),
    LevelNode<>(10, 1),
    LevelNode<>(100, 1),
    LevelNode<>(-20, 2),
    LevelNode<>(30, 2),
    LevelNode<>(70, 2),
    LevelNode<>(130, 2),
    LevelNode<>(-30, 3),
    LevelNode<>(0, 3),
    LevelNode<>(20, 3),
    LevelNode<>(40, 3),
    LevelNode<>(60, 3),
    LevelNode<>(80, 3),
    LevelNode<>(120, 3),
    LevelNode<>(140, 3)};

vector<LevelNode<>> T8 = {
    LevelNode<>(10, 0),
    LevelNode<>(1, 1),
    LevelNode<>(100, 1),
    LevelNode<>(-10, 2),
    LevelNode<>(7, 2),
    LevelNode<>(50, 2),
    LevelNode<>(200, 2),
    LevelNode<>(-11, 3),
    LevelNode<>(-5, 3),
    LevelNode<>(5, 3),
    LevelNode<>(-12, 4),
    LevelNode<>(6, 4),
    LevelNode<>(-13, 5),
    LevelNode<>(-14, 6)};

vector<LevelNode<>> T9 = {
    LevelNode<>(5, 0)};

vector<LevelNode<>> T10 = {
    LevelNode<>(10, 0),
    LevelNode<>(1, 1),
    LevelNode<>(9, 2),
    LevelNode<>(2, 3),
    LevelNode<>(3, 4),
    LevelNode<>(8, 5),
    LevelNode<>(6, 6),
    LevelNode<>(4, 7)};

vector<LevelNode<>> T11 = {
    LevelNode<>(10, 0),
    LevelNode<>(1, 1),
    LevelNode<>(9, 2),
    LevelNode<>(2, 3),
    LevelNode<>(3, 4),
    LevelNode<>(8, 5),
    LevelNode<>(6, 6),
    LevelNode<>(4, 7),
    LevelNode<>(7, 7)};

struct LN
{
    Node *node;
    int level;
    LN(Node *node, int level) : node(node), level(level) {}
};

vector<LevelNode<>> tree2LevelNodes(Node *root)
{
    queue<LN> myqueue;
    vector<LevelNode<>> ans;
    myqueue.push(LN(root, 0));

    while (!myqueue.empty())
    {
        LN act = myqueue.front();
        myqueue.pop();
        int level = act.level;
        Node *node = act.node;

        ans.push_back(LevelNode<>(node->val, level));
        if (node->left)
            myqueue.push(LN(node->left, level + 1));
        if (node->right)
            myqueue.push(LN(node->right, level + 1));
    }
    return ans;
}

int oneInternalIterator = 0;
vector<bool> oneInternalAnswers = {true, false, true, false};

bool expectedOneInternalScenario(vector<LevelNode<>> data)
{
    return oneInternalAnswers[oneInternalIterator++];
}

bool actualOneInternalScenario(vector<LevelNode<>> data)
{
    BST tree;
    for (int i = 0; i < (int)data.size(); i++)
        tree.add(data[i].val);

    return tree.eachInternalNodeHasOneChild();
}

vector<LevelNode<>> expectedAddScenario(vector<LevelNode<>> data)
{
    return data;
}

vector<LevelNode<>> actualAddScenario(vector<LevelNode<>> data)
{
    BST tree;
    for (int i = 0; i < (int)data.size(); i++)
        tree.add(data[i].val);

    Node *root = tree.getRoot();
    return tree2LevelNodes(root);
}

int data2iterator = 0;
int data2[][3] = {
    {-3, 0, -2},
    {4, 2, 3},
    {7, 13, 10},
    {3, 7, 5},
    {1, 10, 5},
    {-3, -2, -2},
    {0, 12, 5},
    {5, 6, 5}};

int expectedCommonAncestorScenario(vector<LevelNode<>> data)
{
    return data2[data2iterator][2];
}

int actualCommonAncestorScenario(vector<LevelNode<>> data)
{
    BST tree;
    for (int i = 0; i < (int)data.size(); i++)
        tree.add(data[i].val);

    int ans = tree.lowestCommonAncestor(data2[data2iterator][0], data2[data2iterator][1])->val;
    data2iterator++;
    return ans;
}

int data3iterator = 0;
int data3[][2] = {
    {70, 70},
    {50, 50},
    {49, 40},
    {31, 30},
    {1000, 140},
    {20, 20},
    {51, 50},
    {131, 130}};

int expectedLargestNodeScenario(vector<LevelNode<>> data)
{
    return data3[data3iterator][1];
}

int actualLargestNodeScenario(vector<LevelNode<>> data)
{
    BST tree;
    for (int i = 0; i < (int)data.size(); i++)
        tree.add(data[i].val);

    int ans = tree.largestLessOrEqual(data3[data3iterator][0])->val;
    data3iterator++;
    return ans;
}

int main()
{
    Testing<int, vector<LevelNode<>>> addTests("add Tests");
    addTests.TreeTest("Single node", AddT1, expectedAddScenario, actualAddScenario);
    addTests.TreeTest("Adding 1, 2, 3", AddT2, expectedAddScenario, actualAddScenario);
    addTests.TreeTest("Adding 2, 1, 3", AddT3, expectedAddScenario, actualAddScenario);
    addTests.TreeTest("Big tree", T8, expectedAddScenario, actualAddScenario);
    addTests.ExceptionTest("Adding '1' two times", AddT4, actualAddScenario);
    addTests.PrintStats();

    Testing<bool, vector<LevelNode<>>> internalNodesTests("eachInternalNodeHasOneChild Tests");
    internalNodesTests.ValuesTest("2 nodes", AddT5, expectedOneInternalScenario, actualOneInternalScenario);
    internalNodesTests.ValuesTest("3 nodes", AddT3, expectedOneInternalScenario, actualOneInternalScenario);
    internalNodesTests.ValuesTest("Snake", T10, expectedOneInternalScenario, actualOneInternalScenario);
    internalNodesTests.ValuesTest("Snake with 2 ends", T11, expectedOneInternalScenario, actualOneInternalScenario);
    internalNodesTests.PrintStats();

    Testing<int, vector<LevelNode<>>> lowestCommonAncestorTests("lowestCommonAncestor Tests");
    for (int i = 0; i < 8; i++)
    {
        ostringstream o;
        o << "T6: " << data2[i][0] << ", " << data2[i][1];
        lowestCommonAncestorTests.ValuesTest(o.str(), T6, expectedCommonAncestorScenario, actualCommonAncestorScenario);
    }
    lowestCommonAncestorTests.PrintStats();

    Testing<int, vector<LevelNode<>>> largestLessOrEqualTests("largestLessOrEqual Tests");
    for (int i = 0; i < 8; i++)
    {
        ostringstream o;
        o << "T7: " << data3[i][0];
        largestLessOrEqualTests.ValuesTest(o.str(), T7, expectedLargestNodeScenario, actualLargestNodeScenario);
    }
    largestLessOrEqualTests.PrintStats();
    return 0;
}