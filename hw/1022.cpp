#include <iostream>
#include <string>
#include <stack>
#include <sstream>

using namespace std;
void push_queue(stack<int>& s2, int x)
{
    s2.push(x);
}



void queue_operation(stack<int>& s1, stack<int>& s2)
{
    while(!s2.empty())
    {
        s1.push(s2.top());
        s2.pop();
    }
}




void pop_queue(stack<int>& s1, stack<int>& s2)
{
   if(s1.empty())
   {
        queue_operation(s1, s2);
   }
   s1.pop();
   return;
}

void query_top(stack<int>& s1, stack<int>& s2)
{
    if(s1.empty())
    {
        queue_operation(s1, s2);
    }
    cout << s1.top() << endl;
    return;
}
void query_size(stack<int>& s1, stack<int>& s2)
{
    cout << s1.size() << " " << s2.size() << endl;
}

int main() 
{
    int n;
    cin >> n;
    cin.ignore();
    stack<int> s1;
    stack<int> s2;
    for(int i = 0;i < n;i++)
    {
        string command;
        int operand = 0;
        string line;
        if(getline(cin, line))
        {
            stringstream ss(line);
            ss >> command;
            if(command == "pop")
            {
                pop_queue(s1, s2);
                continue;
            }
            else
            {
                ss >> operand;
                if(command == "push")
                {
                    push_queue(s2, operand);
                    continue;
                }
                else if(command == "query" && operand == 1)
                {
                    query_top(s1, s2);
                    continue;
                }
                else if(command == "query" && operand == 2)
                {
                    query_size(s1, s2);
                    continue;
                }
                else
                {
                    cout << "something went wrong" << command << " " << operand << endl;
                }
            }
        }
    }
}