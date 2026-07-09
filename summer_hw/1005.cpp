#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);


    int n;
    cin >> n;
    string buffer;
    getline(cin, buffer);

    while (n--) {
        string s;
        getline(cin, s);

        int total_length = s.size() * 8;
        int one_count = 0;

        for (char c : s) {
            unsigned char uc = static_cast<unsigned char>(c);

            for (int i = 0; i < 8; i++) {
                if (uc & (1 << i)) {
                    one_count++;
                }
            }
        }

        int common_divisor = gcd(total_length, one_count);

        cout << one_count / common_divisor << "/" << total_length / common_divisor << "\n";
    }

    return 0;
}