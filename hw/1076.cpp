#include <iostream>
#include <stack>

using namespace std;

int getPriority(char op)
{
    if(op == '*' || op == '/') return 2;
    if(op == '+' || op == '-') return 1;
    return 0;
}
int main()
{
    int num;
    cin >> num;
    stack<char> s;
    char word;
    for(int i = 0; i < num;i++)
    {
        cin >> word;
        if(word == '(')
            s.push(word);
        else if(word == ')')
        {
            while(!s.empty() && s.top() != '(')
            {
                cout << s.top();
                s.pop();
            }
            if(!s.empty())
                s.pop();
        }
        else if(word == '+' || word == '-' || word == '*' || word == '/')
        {
            while(!s.empty() && getPriority(word) <=  getPriority(s.top()))
            {
                cout << s.top();
                s.pop();
            }
            s.push(word);
        }
        else
            cout << word;
    }
    while(!s.empty())
    {
        cout << s.top();
        s.pop();
    }
    return 0;
}