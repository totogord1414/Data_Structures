#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, p, m, t;
    cin >> n >> p >> m >> t;
    vector<int> v(n + 2, 0);
    vector<int> temp(n + 2, 0);
    v[p] = 1;
    while (m > 0) {
        fill(temp.begin(), temp.end(), 0);
        for (int i = 1; i <= n; i++) {
            temp[i] = v[i - 1] + v[i + 1];
        }

        swap(v, temp);
        m--;
    }

    cout << v[t] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int cas;
    cin >> cas;
    for (int t = 0; t < cas; t++) {
        solve();
    }

    return 0;
}