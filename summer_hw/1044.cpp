#include <bits/stdc++.h>

using namespace std;

void add(string& s) {
    int carry = 1;
    reverse(s.begin(), s.end());
    int len = s.length();

    for (int i = 0; i < len; i++) {
        int value = s[i] - '0' + carry;
        s[i] = value % 10 + '0';
        carry = value / 10;
    }

    if (carry) {
        s += carry + '0';
    }

    reverse(s.begin(), s.end());
}

void spe_add(string& s, int pos) {
    int carry = 1;
    int len = s.length();
    pos = len - pos - 1;

    reverse(s.begin(), s.end());

    for (int i = pos; i < len; i++) {
        int value = s[i] - '0' + carry;
        s[i] = value % 10 + '0';
        carry = value / 10;
    }
    
    if (carry) {
        s += carry + '0';
    }

    for (int j = pos - 1; j >= 0; j--) {
        s[j] = (s[j + 1] == '0') ? '1' : '0';
    }

    reverse(s.begin(), s.end());
}

int check(string& s) {
    int len = s.length();
    for (int i = 0; i < len - 1; i++) {
        if (s[i] == s[i + 1]) {
            return i;
        }
    }
    return len;
}

void solve(string& s) {
    int pos;
    while((pos = check(s)) != s.length()) {
        spe_add(s, pos + 1);
    }

    cout << s << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        cout << "case #" << t << ":\n";
        string s;
        cin >> s;
        add(s);

        solve(s);
    }


    return 0;
}