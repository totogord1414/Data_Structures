#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> weight(n + 1);
    vector<int> lchild(n + 1);
    vector<int> rchild(n + 1);
    int root;
    for(int i = 1; i <= n; i++) cin >> weight[i];
    for(int i = 1; i <= n; i++) cin >> lchild[i];
    for(int i = 1; i <= n; i++) cin >> rchild[i];
    cin >> root;

    auto is_valid = [&](auto& self, int curr,  long long lower_bound, long long upper_bound)->bool
    {
        if(curr == n + 1)
        {
            return true;
        }
        if(weight[curr] <= lower_bound || weight[curr] >= upper_bound)
        {
            return false;
        }
        return self(self, lchild[curr], lower_bound, weight[curr]) 
        && self(self, rchild[curr], weight[curr], upper_bound);
    };

    if(is_valid(is_valid, root, LLONG_MIN, LLONG_MAX))
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }
}

int main()
{
    int T;
    cin >> T;
    for(T; T >0; T--)
    {
        solve();
    }
    return 0;
}