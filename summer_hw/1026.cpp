#include <bits/stdc++.h>

using namespace std;

const long long INF = 1e18;

void solve() {
    int w1, w2;
    cin >> w1 >> w2;
    string s;
    cin >> s;
    int n = s.length();

    vector<pair<long long, long long>> dp(n + 1, {INF, INF});

    if (s[0] == '0' || s[0] == '?') dp[1].first = 0;
    if (s[0] == '1' || s[0] == '?') dp[1].second = 0;
    
    for (int i = 2; i <= n; i++) {
        if (s[i - 1] == '0' || s[i - 1] == '?') dp[i].first = min(dp[i - 1].first, dp[i - 1].second + w2);
        if (s[i - 1] == '1' || s[i - 1] == '?') dp[i].second = min(dp[i - 1].second, dp[i - 1].first + w1);
    }

    cout << min(dp[n].first, dp[n].second) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 0; i < 4; i++) {
        solve();
    }

    return 0;
}