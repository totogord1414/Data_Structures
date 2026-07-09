#include <bits/stdc++.h>

using namespace std;

void trim(vector<int>& v) {
    while (v.size() > 1 && v.back() == 0) {
        v.pop_back();
    }
}

int div(vector<int>& v) {
    int rem = 0;
    for (int i = v.size() - 1; i >= 0; i--) {
        int value = v[i] + rem * 10;
        v[i] = value / 2;
        rem = value % 2;
    }
    trim(v);
    return rem;
}

void mul(vector<int>& v, int bit) {
    int carry = bit;
    for (int i = 0; i < v.size(); i++) {
        int value = carry + v[i] * 2;
        v[i] = value % 10;
        carry = value / 10;
    }

    if (carry) {
        v.push_back(carry);
    }
}

void solve(const string& s, int case_num) {
    if (s == "0") {
        cout << "case #" << case_num << ":\n";
        cout << 0 << "\n";
        return;
    }

    vector<int> v;
    v.reserve(s.size());

    for (int i = s.size() - 1; i >= 0; i--) {
        v.push_back(s[i] - '0');
    }

    vector<int> ans;
    ans.push_back(0);

    while (!(v.size() == 1 && v[0] == 0)) {
        int bit = div(v);
        mul(ans, bit);
    }

    cout << "case #" << case_num << ":\n";
    for (int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i];
    }    
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        string s;
        cin >> s;

        solve(s, i);
    }

    return 0;
}