#include <bits/stdc++.h>

using namespace std;

struct ParsedString {
    string original;
    bool has_num;
    int num_val;

    ParsedString(const string& s) : original(s), has_num(false), num_val(0) {
        for (char c : s) {
            if (isdigit(c)) {
                has_num = true;
                num_val = num_val * 10 + c - '0';
            }
        }
    }
};

bool cmp(const ParsedString& a, const ParsedString& b) {
    if (a.has_num != b.has_num) {
        return b.has_num;
    } else if (a.has_num && a.num_val != b.num_val) {
        return a.num_val < b.num_val;
    } else {
        return a.original < b.original;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    vector<ParsedString> v;

    while(cin >> s) {
        v.push_back(ParsedString(s));
    }

    sort(v.begin(), v.end(), cmp);

    for (int i = 0; i < v.size(); i++) {
        cout << v[i].original << (i == v.size() - 1? "\n" : " ");
    }

    return 0;

}