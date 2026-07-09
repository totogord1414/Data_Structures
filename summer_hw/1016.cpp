#include <bits/stdc++.h>

using namespace std;

int mod(int a, int b, int c) {
    if (b == 0) {
        return 1 % c;
    }

    int half = mod(a, b / 2, c);
    int half_sq = (half * half) % c;

    if (b % 2 == 1) {
        return (a * half_sq) % c;
    } else {
        return half_sq;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int A, B, C;
    while (cin >> A >> B >> C && (A != 0 || B != 0 || C != 0)) {
        int result = mod(A, B, C);

        cout << result << "\n";
    }

    return 0;
}