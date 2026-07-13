#include <bits/stdc++.h>

using namespace std;

void solve() {
    int r, c, n, k;
    cin >> r >> c >> n >> k;
    vector<pair<int, int>> pos(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        pos[i] = {x, y};
    }
    int count = 0;

    for (int i = 1; i <= r; i++) {
        for (int j = i; j <= r; j++) {
            for (int p = 1; p <= c; p++) {
                for (int q = p; q <= c; q++) {
                    int one_count = 0;
                    for (const auto& pa: pos) {
                        if (i <= pa.first && pa.first <= j && p <= pa.second && pa.second <= q) {
                            one_count++;
                        }
                    }

                    if(one_count >= k) {
                        count++;
                    }
                }
            }
        }
    }

    cout << count << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        cout << "case #" << t << ":\n";
        solve();
    }
    return 0;
}