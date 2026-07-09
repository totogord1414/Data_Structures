#include <bits/stdc++.h>

using namespace std;


int ctonum(char c) {
    if (c == '0') {
        return 0;
    } else if ( c == '1') {
        return 1;
    } else if ( c == '2') {
        return -1;
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    long long N = 0;
    long long D = 1;
    int frac_len = 0;
    bool has_dot = false;

    for (char c : s) {
        if (c == '.') {
            has_dot = true;
            continue;
        }

        if (has_dot) {
            frac_len++;
        }

        N = N * 3 + ctonum(c);
    }

    for (int i = 0; i < frac_len; i++) {
        D *= 3;
    }

    if (N == 0) {
        cout << 0 << "\n";
        return 0;
    }

    bool is_neg = false;
    if (N < 0) {
        is_neg = true;
        N = -N;
    }    

    long long common_divisor = gcd(N, D);
    N = N / common_divisor;
    D = D / common_divisor;

    if (is_neg) {
        cout << '-';
    }

    if (D == 1) {
        cout << N << "\n";
    } else if (N < D) {
        cout << N << " " << D << "\n";
    } else {
        cout << N / D << " " << N % D << " " << D << "\n";
    }

    return 0;
    
}