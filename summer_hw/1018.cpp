#include <bits/stdc++.h>

using namespace std;

int main() {
    long long n = 0;
    long long m = 1;
    int T;
    cin >> T;
    for (int t = 0 ; t < T; t++) {
        int curr_n, curr_m;
        char slash;
        cin >> curr_n >> slash >> curr_m;
        n = n * curr_m + m * curr_n;
        m = m * curr_m;
        int common_divisor = gcd(n, m);
        n = n / common_divisor;
        m = m / common_divisor;
    }

    cout << n << "/" << m << "\n";

    return 0;
}