#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    vector<int> letter_pos(128, -1);
    cin >> s;
    int L = 0;
    int R;
    int min_L = 0;
    int longest_length = 0;
    string result = "";
    
    for (R = 0; R < s.length(); R++) {
        if (L <= letter_pos[s[R]]) {
            L = letter_pos[s[R]] + 1;
        }

        letter_pos[s[R]] = R;

        if ((R - L + 1) > longest_length) {
            longest_length = R - L + 1;
            min_L = L;
        }
    }

    cout << s.substr(min_L, longest_length) << "\n";

    return 0;
}