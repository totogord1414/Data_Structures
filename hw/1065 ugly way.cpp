/* this is a way that is not so elegant QAQ*/
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n, q;
    string s;
    cin >> n >> s >> q;
    int curr = q;
    int state[26];

    while(curr >= 1)
    {
        char c = s[curr - 1];
        state[c - 'a'] += 1;
        curr = curr / 2;
    }
    int count = 0;
    for(int i = 0; i < 26; i++)
    {
        if(state[i] % 2)
        {
            count++;
        }
        if(count > 1)
        {
            break;
        }
    }
    if(count > 1)
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
    ios::sync_with_stdio(false);    
    cin.tie(NULL);

    int T;
    cin >> T;
    for(T; T > 0; T--)
    {
        solve();
    }
    return 0;
}