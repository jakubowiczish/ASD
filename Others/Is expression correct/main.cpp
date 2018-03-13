#include <iostream>
#include <string>
using namespace std;

bool valid(string expression);
bool is_operator(char op);

char operators[5]={'+','-','*','/','^'};

int main()
{
    string expression;
    cout << "Enter the expression: " << endl;
    getline(cin,expression);
    if(valid(expression))
        cout << "The expression is valid" << endl;
    else
        cout << "The expression is faulty!" << endl;
    return 0;
}

bool valid(string expression)
{
    int brackets_counter = 0;
    int operators_counter = 0;
    int counter = 0;

    for(int i = 0; i < expression.length(); i++) {
        if(expression[i] == '(')
            brackets_counter++;
        if(expression[i] == ')') {
            brackets_counter--;
            if(brackets_counter < 0)
                return false;
        }
        if(expression[i]>='a' and expression[i]<='z') {
            counter++;
        }

        if(is_operator(expression[i])){
            operators_counter++;
            if(i == 0) return false;
        }
    }
    if((operators_counter - counter) == -1)
        return true;
    return false;
}

bool is_operator(char op)
{
    for(int i=0; i < 5; i++)
        if(op == operators[i])
            return true;
    return false;
}