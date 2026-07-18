#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> W(n);
    int sum = 0;

    for (int i = 0; i < n; i++) {
        cin >> W[i];
        sum +=  W[i];
    }

    vector<bool> dp(sum + 1, false);
    //rotate and find the egability of the first n items;
    dp[0] = true;
    
    for (int w: W) {
        vector<bool> next_dp = dp;

        for (int i = 0; i <= sum; i++) {
            if (dp[i]) {
                if (i + w <= sum) {
                    next_dp[i + w] = true;
                }
                next_dp[abs(i - w)] = true;
            }
        }
        dp = next_dp;
    }

    //finalize the string s

    string s;
    for (int i = 1; i <= sum; i++) {
        s += dp[i] ? "1" : "0";
    }

    cout << s << "\n";

    return 0;
}