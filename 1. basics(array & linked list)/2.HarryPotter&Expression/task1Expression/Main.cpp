#include "Stack.hpp"

using namespace std;
int main(){
ArrayStack stack;

cout << "Enter expression: ";
string expression;
cin >> expression;

bool broken = false;

for(char ch : expression)
{

    if(ch == '(' || ch == '{' || ch == '[' )
        stack.push(ch);

    else if(ch == ')')
    {
        char c = stack.pop();
        if(c != '(')
        {
             cout << "Wrong. The type doesn't match" << std::endl;
             broken = true;
            break;
        }
           
    }

    else if(ch == '}')
    {
        char c = stack.pop();
        if(c != '{')
        {
            cout << "Wrong. The type doesn't match" << std::endl;
            broken = true;
            break;
        }
            
    }

    else if(ch == ']')
    {
        char c = stack.pop();
        if(c != '[')
        {
            cout << "Wrong. The type doesn't match" << std::endl;
            broken = true;
            break;
        }
            
    }
}

if(!stack.isEmpty() && !broken)
    cout << "Wrong. the count doesn't match" << std::endl;


//stack.status();

return 0;
}