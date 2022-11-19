#ifndef ARRAYSTACK_HPP
#define ARRAYSTACK_HPP
#include <iostream>

#define MAXN 10

class ArrayStack
{
private:
    int array[MAXN];
    int count;

public:
    ArrayStack();

    bool isEmpty();

    void status();

    int pop();

    void push(int data);

    bool isFull();
};

// implementation

ArrayStack::ArrayStack() : count(0) {}

void ArrayStack::push(int data)
{
    if (!isFull())
    {
        this->array[count] = data;
        count++;
    }
    else
        std::cout << "stack full, MAX = " << MAXN << std::endl;
}

int ArrayStack::pop()
{
    if (isEmpty())
        return -1000;

    int tmp = array[count - 1];
    array[count - 1] = -1000;
    std::cout << std::endl
              << "pop operation" << std::endl;
    count--;
    return tmp;
};

bool ArrayStack::isEmpty()
{
    return count == 0;
}

bool ArrayStack::isFull()
{
    return count >= MAXN;
}

void ArrayStack::status()
{
    std::cout << "top: " << count - 1 << std::endl
              << std::endl;

    std::cout << "Stack: " << std::endl;
    for (int i = count - 1; i >= 0; i--)
    {
        std::cout << i << ". " << array[i] << std::endl;
    }
}

#endif