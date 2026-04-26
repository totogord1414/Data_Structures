#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<unordered_map>

using namespace std;

const int MAXN = 1e6 + 5;
struct Node{int left = 0; int right = 0;};
Node tree[MAXN];

int pre_order[MAXN];
int in_order[MAXN];
int pos[MAXN];
vector<int> dict;

int get_id(int val)
{
    return lower_bound(dict.begin(), dict.end(), val) - dict.begin() + 1;
}

int build_tree(int pre_l, int pre_r, int in_l, int in_r)
{
    if(pre_l > pre_r || in_l > in_r)
    {
        return 0;
    }
    int root = pre_order[pre_l];
    int root_id = get_id(root);
    int position = pos[root_id];


    int left_size = position - in_l;
    int root_left = build_tree(pre_l + 1, pre_l + position - in_l, in_l, position - 1);
    int root_right = build_tree(pre_l + left_size + 1, pre_r, position + 1, in_r);
    tree[root_id].left = root_left;
    tree[root_id].right = root_right;
    return root_id;
}
void print_binary_tree(int root)
{
    queue<int> q;
    q.push(root);
    while(! q.empty())
    {
        int r = q.front();
        if(tree[r].left != 0)
            q.push(tree[r].left);
        if(tree[r].right != 0)
            q.push(tree[r].right);
        cout << dict[r - 1] << " ";
        q.pop();
    }
    cout << endl;
}
void print_multi_tree(int root)
{
    queue<int> q;
    q.push(root);
    
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        cout << dict[u - 1] << " ";
        int child = tree[u].left;
        while(child != 0)
        {
            q.push(child);
            child = tree[child].right; 
        }
    }
    cout << endl; 
}

int main()
{
    ios::sync_with_stdio(false);    

    int node_num;
    cin >> node_num;
    for(int i = 0;i < node_num; i++)
    {
        cin >> pre_order[i];
        dict.push_back(pre_order[i]);
    }
    for(int i = 0; i < node_num; i++)
    {
        cin >> in_order[i];
        dict.push_back(in_order[i]);
    }    
    
    sort(dict.begin(), dict.end());
    dict.erase(unique(dict.begin(), dict.end()), dict.end());
    for(int i = 0; i < node_num; i++)
    {
        int original_val = in_order[i];
        int id = get_id(original_val);
        pos[id] = i;
    }

    int root_id = build_tree(0, node_num - 1, 0, node_num - 1);
    cout << dict[root_id - 1] <<endl;
    print_binary_tree(root_id);
    print_multi_tree(root_id);

    return 0;
}