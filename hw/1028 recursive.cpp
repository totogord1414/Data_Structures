#include<iostream>
#include<vector>

using namespace std;

void recursive_print(int parent, const vector<vector<int>>& children)
{
    for(int child : children[parent])
    {
        recursive_print(child, children);
    }
    cout << parent << " ";
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
    recursive_print(0, children);
    return 0; 
}