#ifndef ARRAYSTACK_HPP
#define ARRAYSTACK_HPP
#include <iostream>

#define MAXN 10

struct Node
{
    int data;
    Node *next;

    Node(int data) : data(data), next(nullptr) {}
};

class ListStack
{
private:
    static int count;
    Node *top;
    int index;

public:
    ListStack();

    bool isEmpty();

    void status();

    int pop();

    void push(int data);

    bool isFull();
};

// implementation

int ListStack::count = -1;

ListStack::ListStack() : top(nullptr) {}

void ListStack::push(int data)
{
    if (count < MAXN - 1)
    {
        if (!top)
        {
            top = new Node(data);
            count++;
            return;
        }

        Node *tmp = new Node(data);
        tmp->next = top;
        top = tmp;
        count++;
    }
    else
        std::cout << "stack full, MAX = " << MAXN << std::endl;
}

int ListStack::pop()
{
    if (!top)
        return -1000;

    int tmpData = top->data;
    Node *tmpNode = top;
    top = top->next;
    delete tmpNode;
    count--;
    std::cout << std::endl
              << "pop operation" << std::endl;
    return tmpData;
};

bool ListStack::isEmpty()
{
    return top == nullptr;
}

bool ListStack::isFull()
{
    return false;
}

void ListStack::status()
{
    std::cout << "top: " << count << std::endl
              << std::endl;

    int i = 0;
    Node *tmp = top;
    std::cout << "Stack: " << std::endl;
    while (tmp)
    {
        std::cout << count - i << ". " << tmp->data << std::endl;
        tmp = tmp->next;
        i++;
    }
}

#endif
