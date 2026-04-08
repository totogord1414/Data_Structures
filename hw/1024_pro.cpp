#include <string>
#include <iostream>
#include <queue>
#include <vector>

#define MAXSIZE 200005

using namespace std;

struct member{int group;
bool in_queue = false;};
int main()
{
    int member_num;
    cin >> member_num;
    queue<int> large_queue;
    vector<queue<int>> group_queue(MAXSIZE);
    vector<member> member_group(MAXSIZE);
    for(int i = 0;i < member_num;i++)
    {
        cin >> member_group[i].group;
    }
    int command_num;
    cin >> command_num;
    for(int i = 0;i < command_num; i++)
    {
        string command;
        cin >> command;
        if(command == "DEQUEUE" )
        {
            if(large_queue.empty())
            {
                return -1;
            }
            else
            {
                int curr_group = large_queue.front();
                int curr_number = group_queue[curr_group].front();
                member_group[curr_number].in_queue = false;
                group_queue[curr_group].pop();
                if(group_queue[curr_group].empty())
                {
                    large_queue.pop();
                }
                cout << curr_number << endl;
            }
        }
        else if(command == "ENQUEUE")
        {
            int operand;
            cin >> operand;
            if(member_group[operand].in_queue)
            {
                continue;
            }
            else if(group_queue[member_group[operand].group].empty())
            {
                large_queue.push(member_group[operand].group);
            }

            group_queue[member_group[operand].group].push(operand);
            member_group[operand].in_queue = true;

        }
        else
        {
            cout << "wrong command";
            return -1;
        }
    }
    return 0;
}