#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>

struct Node
{
    int val;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;

    Node(int val) : val(val) {}
};

std::string getCharCode(Node *node)
{
    std::string code = "";
    Node *currentNode = node;

    while (currentNode)
    {
        if (currentNode->parent)
        {
            if (currentNode == currentNode->parent->right)
                code += "1";
            else if (currentNode == currentNode->parent->left)
                code += "0";
        }
        currentNode = currentNode->parent;
    }

    reverse(code.begin(), code.end());
    return code;
}

Node *populateTree(std::vector<std::pair<char, int>> &charVector, std::vector<std::pair<char, std::string>> &codeVector)
{
    int totalCount = 0;
    for (auto p : charVector)
        totalCount += p.second;

    Node *head = new Node(totalCount);
    Node *activeNode = head;

    while (!charVector.empty())
    {
        // the charVector is sorted ascendingly. Here we populate the tree from the back.
        // the greatest available taking the right child of rightPlusLeftNodes node.
        // the remainder of all totalcount goes to the left node of currentNode.
        if (charVector.size() >= 2)
        {
            Node *rightCharNode = new Node(charVector.at(charVector.size() - 1).first);
            int freq1 = charVector.at(charVector.size() - 1).second;
            charVector.pop_back();

            Node *leftCharNode = new Node(charVector.at(charVector.size() - 1).first);
            int freq2 = charVector.at(charVector.size() - 1).second;
            charVector.pop_back();

            Node *rightPlusLeftCharNodes = new Node(freq1 + freq2);
            rightPlusLeftCharNodes->right = rightCharNode;
            rightPlusLeftCharNodes->left = leftCharNode;
            leftCharNode->parent = rightPlusLeftCharNodes;
            rightCharNode->parent = rightPlusLeftCharNodes;

            activeNode->right = rightPlusLeftCharNodes;
            rightPlusLeftCharNodes->parent = activeNode;

            Node *leftRemainderNode = new Node(totalCount - rightPlusLeftCharNodes->val);
            activeNode->left = leftRemainderNode;
            leftRemainderNode->parent = activeNode;

            activeNode = activeNode->left;

            totalCount -= rightPlusLeftCharNodes->val;
            codeVector.push_back(std::make_pair(rightCharNode->val, getCharCode(rightCharNode)));
            codeVector.push_back(std::make_pair(leftCharNode->val, getCharCode(leftCharNode)));
        }
        else // the last charVector element incase they were odd
        {
            Node *rightCharNode = new Node(charVector.at(charVector.size() - 1).first);
            int freq = charVector.at(charVector.size() - 1).second;
            charVector.pop_back();

            activeNode->right = rightCharNode;
            rightCharNode->parent = activeNode;

            totalCount -= freq;
            codeVector.push_back(std::make_pair(rightCharNode->val, getCharCode(rightCharNode)));
        }
    }
    return head;
};

void freeMemory(Node *node)
{
    if (node)
    {
        if (node->left)
            freeMemory(node->left);
        if (node->right)
            freeMemory(node->right);
        delete node;
    }
}

int main()
{
    std::string dictionaryString;

    std::ifstream dictionary("dictionary.txt");
    if (dictionary.is_open())
    {
        std::getline(dictionary, dictionaryString);
    }
    else
        exit(-1);

    std::vector<std::pair<char, int>> charVector;

    for (char c : dictionaryString)
    {
        bool found = false;
        std::for_each(charVector.begin(), charVector.end(), [&](std::pair<char, int> &aPair)
                      {
            if(aPair.first == c){
                aPair.second ++;
                found = true;
                return;
            } });
        if (!found)
            charVector.push_back(std::make_pair(c, 1));
    }

    std::sort(charVector.begin(), charVector.end(), [](auto a, auto b)
              { return a.second < b.second; }); // sort elements ascendingly

    std::vector<std::pair<char, std::string>> codeVector;
    Node *memoryToFree = populateTree(charVector, codeVector);
    // Dictionary
    std::cout << "\nDICTIONARY\n--------------------------" << std::endl;
    for (const auto &p : codeVector)
    {
        std::cout << p.first << " -> " << p.second << std::endl;
    }

    // User asking for string to encode
    std::cout << "\nEnter a string/sentence to encode(should be in DICTIONARY, edit dictionary.txt to add more:)" << std::endl;
    std::string inputString;
    std::getline(std::cin, inputString);

    std::cout << "\nEncoding:" << std::endl;

    for (char c : inputString)
    {
        std::for_each(codeVector.begin(), codeVector.end(), [&](std::pair<char, std::string> &aPair)
                      {
            if(aPair.first == c){
                std::cout << aPair.second;
                return;
            } });
    }
    std::cout << std::endl;

    // Asking for string to decode
    std::cout << "\nEnter a string/sentence to decode(should be in DICTIONARY, edit dictionary.txt to add more):" << std::endl;
    inputString = "";
    std::getline(std::cin, inputString);

    std::cout << "\nDecoding:" << std::endl;

    std::string tmp;
    for (char c : inputString)
    {
        tmp += c;
        std::for_each(codeVector.begin(), codeVector.end(), [&](std::pair<char, std::string> &aPair)
                      {
            if(aPair.second == tmp){
                std::cout << aPair.first;
                tmp = "";
                return;
            } });
    }
    std::cout << std::endl;

    // freeing memory
    freeMemory(memoryToFree);

    exit(0);
}