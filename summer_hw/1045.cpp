#include <bits/stdc++.h>

using namespace std;

const int divisor = 10007;

int power(int a, int n) {
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return a % divisor;
    }
    int v = power(a, n / 2) % divisor;
    long long value = v * v % divisor;
    if (n % 2) {
        value = value * a % divisor;
    }
    return value;
}

int comb(int k, int m) {
    vector<int> v(k + 1, 0);
    v[0] = 1;
    for (int i = 1; i <= k; i++) {
        for (int n = i; n > 0; n--) {
            v[n] = (v[n] + v[n - 1]) % divisor;
        }
    }

    return v[m];
}

void solve() {
    int a, b, k, n, m;
    cin >> a >> b >> k >> n >> m;

    a = a % divisor;
    b = b % divisor;
    int a_p = power(a, n);
    int b_p = power(b, m);

    int c = comb(k, m);

    int result = (a_p * b_p) % divisor;
    result = (result * c) % divisor;

    cout << result << "\n";
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