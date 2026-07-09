#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    string s = "0";

    for (int i = 0; i < n; i++) {
        string anti_s = "";
        for (char c : s) {
            if (c == '1') {
                anti_s += "0";
            } else {
                anti_s += "1";
            }
        }

        s += anti_s;
    }

    cout << s << "\n";

    return 0;
}