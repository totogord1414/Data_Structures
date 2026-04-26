#include <iostream>
#include <vector>
#include <utility>
#include <stack>

using namespace std;
void iterative_print(const vector<vector<int>>& children)//this is so elegant!!!
{

}

void pure_iterative_print(const vector<vector<int>>& children)
{
    stack<pair<int, int>> s;
    s.push({0, 0});

    while(!s.empty())
    {
        auto& current = s.top();
        int parent = current.first;
        int child_idx = current.second;
        if(child_idx < children[parent].size())
        {
            current.second++;
            s.push({children[parent][child_idx], 0});
        }
        else
        {
            s.pop();
            cout << parent << " ";
        }
    }
}
int main()
{
    int num;
    cin >> num;
    vector<vector<int>> children(num);
    for(int i = 0; i < num; i++)
    {
        int parent;
        cin >> parent;
        if(parent != -1)
            children[parent].push_back(i);
    }
}