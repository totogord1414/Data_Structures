#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    if (cin >> t) {
        vector<long long> count(51);
        count[0] = 1;
        count[1] = 1;
        count[2] = 2;
        count[3] = 4;
        for (int i = 4; i <= 50; i++) {
            count[i] = count[i - 1] + count[i - 2] + count[i - 3] + count[i - 4];
        }

        for (int j = 0; j < t; j++) {
            int n;
            cin >> n;
            cout << "case #" << j << ":\n";
            cout << count[n] << "\n";
        }
    }

    return 0;
}