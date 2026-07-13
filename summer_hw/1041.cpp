#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int max_len = 0;
    int curr_len = 1;
    int n = s.length();
    for (int i = 0; i < n - 1; i++) {
        if (s[i] != s[i + 1]) {
            curr_len++;
        } else {
            max_len = max(max_len, curr_len);
            curr_len = 1;
        }
    }
    max_len = max(max_len, curr_len);

    cout << max_len << '\n';
    return 0;
}