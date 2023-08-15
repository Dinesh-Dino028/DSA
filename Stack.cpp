#include <iostream>
#include <limits.h>

using namespace std;

class Stack
{
#define MAX 20
    int a[MAX];
    int top = -1;

public:
    void push(int val)
    {
        if(top == MAX-1){
            cout<<"Stack is full!"<<endl;
        }
        a[++top] = val;
    }

    int pop()
    {
        if (top == -1)
        {
            cout << "stack is empty" << endl;
            return INT_MIN;
        }
        return a[top--];
    }

    int peek()
    {
        if (top == -1)
        {
            cout << "stack is empty" << endl;
            return INT_MIN;
        }
        return a[top];
    }

   
    
};

 int main()
    {
        Stack s;
        s.push(1);
        s.push(2);
        s.push(3);
        cout << "pop value is " << s.pop()<<endl;
        cout << "peek value is " << s.peek();
    }