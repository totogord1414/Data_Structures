/* a genius way of bitmasking!!!!!!  
    so brilliant!!!!!*/
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int state = 0;
    int n, q;
    string s;
    cin >> n >> s >> q;
    int curr = q;
    while(curr >= 1)
    {
        char c = s[curr - 1];
        state = state ^ (1 << (c - 'a'));
        curr = curr / 2;
    }
    if(state & (state - 1))
    {
        cout << "No\n";
    }
    else
    {
        cout << "Yes\n";
    }
}

int main()
{
    int T;
    cin >> T;
    for(T; T > 0; T--)
    {
        solve();
    }
    return 0;
}