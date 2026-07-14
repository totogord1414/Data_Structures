#include <bits/stdc++.h>

using namespace std;

void solve() {
    int N, M;
    cin >> N >> M;
    vector<int> v(N + 1, 0);
    v[0] = 1;

    for (int i = 1; i <= M; i++) {
        for (int j = N; j >= 0; j--) {
            if (j >= i) {
                v[j] += v[j - i];
            }
        }
    }

    cout << v[N] << "\n";
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