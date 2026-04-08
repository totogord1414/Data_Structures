#include <iostream>
#include <string>

using namespace std;

int main()
{
    string target;
    cin >> target;
    int command_num;
    cin >> command_num;
    for(int i = 0;i < command_num;i++)
    {
        int begin, end;
        string yank_board;
        string front, tail; 
        cin >> begin >> end >> front >> tail;
        yank_board = target.substr(begin - 1, end - begin + 1);
        target.erase(begin - 1, end - begin + 1);

        size_t pos = target.find(front + tail);
        if(pos == string::npos)
        {
            target = target + yank_board;
            continue;
        }
        else
        {
            size_t ac_pos = pos + front.length();
            target.insert(ac_pos, yank_board);
        }
    }
    cout << target << "\n";
    return 0;
}