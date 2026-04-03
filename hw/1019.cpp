#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main()
{
    stack<int> special_stack;
    string current_line;
    while(getline(cin, current_line))
    {
        for(int i = 0;i < current_line.length();i++)
        {
            if(current_line[i] == '/' && i + 1 < current_line.length() && current_line[i + 1] == '*')
            {
                special_stack.push(4);
                i++; 
                continue;
            }
            else if(current_line[i] == '*' && i + 1 < current_line.length() && current_line[i + 1] == '/')
            {
                if(special_stack.empty() || special_stack.top() != 4)
                {
                    cout << "NO" << endl;
                    return 0;
                }
                special_stack.pop();
                i++;
                 continue;
            }
            else
            {
                switch(current_line[i])
                {
                    case '(':
                        special_stack.push(1);
                        break;
                        
                    case '[':
                        special_stack.push(2);
                        break;

                    case '{':
                        special_stack.push(3);
                        break;
                    case ')':
                        if(special_stack.empty() || special_stack.top() != 1)
                        {
                            cout << "NO" << endl;         
                            return 0;
                        }
                        special_stack.pop();
                        break;

                    case ']':
                        if(special_stack.empty() || special_stack.top() != 2)
                        {
                            cout << "NO" << endl;         
                            return 0;
                        }
                        special_stack.pop();
                        break;
                    case '}':
                        if(special_stack.empty() || special_stack.top() != 3)
                        {
                            cout << "NO" << endl;         
                            return 0;
                        }
                        special_stack.pop();
                        break;
                }
            }

        }
    }
    if(!special_stack.empty())
    {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    return 0;
}