#include <iostream>
//#include "ListStack.hpp"
#include "ArrayStack.hpp"

int main()
{
    ArrayStack stack1;

    stack1.push(1);
    stack1.push(3);
    stack1.push(54);
    stack1.push(32);
    stack1.push(23);
    stack1.push(523);
    stack1.push(23);
    stack1.push(35);
    stack1.push(878);
    stack1.push(0);
    stack1.push(3);
    stack1.push(54);

    stack1.pop();
    stack1.status();
    stack1.pop();
    stack1.pop();
    stack1.pop();
    stack1.pop();
    stack1.pop();
    stack1.pop();
    stack1.pop();
    stack1.pop();
    stack1.push(2123);

    stack1.status();
    return 0;
}