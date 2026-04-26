#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
using namespace std;
#define MAXN 1005
void front_recursive_print(int root, const vector<vector<int>>& children)
{
    cout << root <<" ";
    for(int child: children[root])
    {
        front_recursive_print(child, children);
    }
}
int back_recursive_print(int root, const vector<vector<int>>& children)
{
    int height = 0;
    for(int child: children[root])
    {
        height = max(height, back_recursive_print(child, children));
    }
    cout << root << " ";
    return height + 1;
}
void bfs(int root, const vector<vector<int>>& children)
{
    queue<int> q;
    q.push(root);
    while(!q.empty())
    {
        int curr = q.front();
        q.pop();
        cout << curr << " ";
        for(int child: children[curr])
        {
            q.push(child);
        }
    }
}
int print_leaf(int root, const vector<vector<int>>& children)
{
    if(children[root].size() == 0)
    {
        cout << root << " ";
        return 1;
    }
    int count = 0;
    for(int child: children[root])
    {
        count += print_leaf(child, children);
    }
    return count;
}
int main()
{
    vector<vector<int>> children(MAXN);
    int root = -1;
    int index, parent;
    int MAX_idx = 0;
    while(cin >> index >> parent)
    {
        MAX_idx++;
        if(parent == -1)
            root = index;
        else
        {
            children[parent].push_back(index);
        }
    }
    cout << root << endl;
    front_recursive_print(root, children);
    cout<<endl;
    int height = back_recursive_print(root, children);
    cout<<endl;
    bfs(root, children);
    cout<<endl;    
    cout<<MAX_idx<<endl;
    int count = print_leaf(root, children);
    cout<<endl;
    cout<<count<<endl;
    cout<<height<<endl;
}