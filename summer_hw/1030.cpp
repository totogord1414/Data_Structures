#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, M;
    cin >> n >> M;

    vector<int> W(n + 1);
    vector<int> P(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> W[i] >> P[i];
    }

    vector<int> dp(M + 1, 0);
    
    for (int i = 1; i <= n; i++) {
        for (int j = M; j >= W[i]; j--) {
            dp[j] = max(dp[j - W[i]] + P[i], dp[j]);
        }
    }

    cout << dp[M] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }

    return 0;
}