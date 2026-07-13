#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int max_len = 0;
    int curr_len = 0;
    bool is_front = true;
    for (char c: s) {
        if (isdigit(c)) {
            if (c == '0' && is_front) {
                continue;
            }
            is_front = false;
            curr_len++;
        } else {
            is_front = true;
            curr_len = 0;
            max_len = max(max_len, curr_len);
        }
    }
    max_len = max(max_len, curr_len);

    cout << max_len << "\n";

    return 0;
}