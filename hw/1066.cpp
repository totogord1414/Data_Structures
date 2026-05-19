#include <bits/stdc++.h>

using namespace std;

struct valid_tree{
    long long min;
    long long max;
    bool demand_tree;
};

valid_tree solve_helper(int n, int root, vector<long long>& weight, vector<int>& lchild, vector<int>& rchild)
{
    if(root == n + 1)
    {
        return {LLONG_MAX, LLONG_MIN, true};
    }
    valid_tree left = solve_helper(n, lchild[root], weight, lchild, rchild);
    valid_tree right = solve_helper(n, rchild[root], weight, lchild, rchild);
    long long r_weight = weight[root];
    if(!left.demand_tree || !right.demand_tree || left.max >= r_weight || right.min <= r_weight)
    {
        return {r_weight, r_weight, false};
    }
    else
    {
        return {min(left.min, r_weight), max(right.max, r_weight), true};
    }
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for(int i = 0; i < T; i++)
    {
        int n;
        cin >> n;
        vector<long long> weight(n + 1);
        vector<int> lchild(n + 1);
        vector<int> rchild(n + 1);
        int r;
        for(int j = 1; j <= n; j++)
        {
            cin >> weight[j];
        }
        for(int j = 1; j <= n; j++)
        {
            cin >> lchild[j];
        }
        for(int j = 1; j <= n; j++)
        {
            cin >> rchild[j];
        }
        cin >> r;
        if(solve_helper(n, r, weight, lchild, rchild).demand_tree)
        {
            cout << "Yes" << "\n";
        }
        else
        {
            cout << "No" << "\n";
        }
    }
}