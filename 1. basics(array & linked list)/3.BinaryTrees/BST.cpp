#include "BST.h"
#include <queue>

BST::BST()
{
    this->head = nullptr;
}

Node *BST::getRoot()
{
    return head;
}

// helper function
bool allHasOneNode(Node *rootNode)
{

    Node *currentNode = rootNode;

    if (currentNode)
    {
        Node *leftNode = currentNode->left;
        Node *rightNode = currentNode->right;

        if (rightNode && leftNode)
            return false;

        allHasOneNode(leftNode);
        allHasOneNode(rightNode);
    }

    return true;
}

bool BST::eachInternalNodeHasOneChild()
{
    if (head->left || head->right)
        return allHasOneNode(head);
    return false;

    /*
    Check if every internal node has one child.
    Internal node if node that is not a leaf.
    Return true if each internal node has one child
    otherwise return false
    */
}

// helper function
Node *getLowestCommonAncestor(Node *node, int value1, int value2, Node *currentNode)
{ // implemented with preorder traversal

    if (!node->left || !node->right)
        return currentNode;

    if ((node->left->val == value1 && node->right->val == value1) ||
        (node->left->val == value2 && node->right->val == value2))
    {
        if (currentNode)
        {
            currentNode = node;
        }
    }
    if (node->left)
        getLowestCommonAncestor(node->left, value1, value2, currentNode);

    if (node->right)
        getLowestCommonAncestor(node->right, value1, value2, currentNode);

    return currentNode;
}

Node *BST::lowestCommonAncestor(int value1, int value2)
{
    if (head)
        return getLowestCommonAncestor(head, value1, value2, nullptr);
    else
        return nullptr;
    /*
    Find lowest common ancestor of values `value1` and `value2`
    Assume both values exist in the tree
    Returns node being the lowest common ancestor, in other words
    return the smallest subtree containing both values
    */
}

// helper function
Node *getLargestLessOrEqual(Node *node, int value, Node *currentNode)
{ // implemented with postorder traversal

    if (node->left)
        getLargestLessOrEqual(node->left, value, currentNode);

    if (node->right)
        getLargestLessOrEqual(node->right, value, currentNode);

    if (!node)
        return currentNode; // better than returning nullptr I think

    if (node->val <= value)
    {
        if (currentNode)
        {
            if (node->val > currentNode->val)
                currentNode = node;
        }
        else
            currentNode = node;
    }
    return currentNode;
}

Node *BST::largestLessOrEqual(int value)
{
    return getLargestLessOrEqual(head, value, nullptr);
    /*
    Return such node that its value is the biggest
    value smaller than parameter `value`.
    You can assume this node exists.
    */
}

BST::~BST()
{
    Node *root = getRoot();
    queue<Node *> myqueue;
    myqueue.push(root);

    while (!myqueue.empty())
    {
        Node *node = myqueue.front();
        myqueue.pop();

        if (node->left)
            myqueue.push(node->left);
        if (node->right)
            myqueue.push(node->right);
        delete node;
    }
}

// // helper function

// bool valueExists(Node *node, int value)
// { // implemented with preorder traversal
//     if (!node)
//         return false;
//     if (node->val == value)
//         return true;

//     bool leftExists = false;
//     bool rightExists = false;

//     if (node->left)
//         valueExists(node->left, value);
//     if (node->right)
//         valueExists(node->right, value);

//     if (leftExists)
//         return true;

//     else if (rightExists)
//         return true;
// }

// helper method
Node *getSearchNode(Node *node, int value)
{
    if (!node || node->val == value)
        return node;

    if (value < node->val && node->left)
        return getSearchNode(node->left, value);
    else if (node->right)
        return getSearchNode(node->right, value);
}

Node *BST::search(int value)
{
    return getSearchNode(head, value);
}

// helper function
bool isALeaf(Node *node)
{
    if (!node)
        return false;

    return (!node->left && !node->right);
}

void doAdd(Node *node, int value)
{// implemented with inorder traversal
//Not sure abt this function... was overthinking :)
    if(node->left)
        doAdd(node->left, value);

        
    if (isALeaf(node) && node->val > value)
    {
        node->left = new Node(value);
        return;
    }
    else if (node->val > value && node->left && !node->right)
    {
        if(node->left->val < value)
        {
            node->right = new Node(value);
            return;
        }   
    }

    if(node->right)
        doAdd(node->right, value);
}

void BST::add(int value)
{
    if (!head)
    {
        this->head = new Node(value);
        return;
    }

    if (search(value))
        throw -2;
    
    doAdd(head, value);
}

//helper function
MinMaxNode getMinMax(Node* node, MinMaxNode minMax)
{ // implemented with postorder traversal

    if (node->left)
        getMinMax(node->left, minMax);

    if (node->right)
        getMinMax(node->right, minMax);

    if (!node)
        return minMax;

    if (node->val < minMax.minNode->val)
        minMax.minNode = node;
    else if(node->val > minMax.maxNode->val)
        minMax.maxNode = node;

    return minMax;
}

MinMaxNode BST::findMinMaxNode()
{
    MinMaxNode minMax;
    if(head){
        minMax.maxNode = head;
        minMax.minNode = head;
        return getMinMax(head, minMax);
    }
    else
        return minMax;
}
