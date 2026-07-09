#include <bits/stdc++.h>

using namespace std;

struct Email {
    string prefix;
    string suffix; 

    Email(const string& s): prefix(""), suffix("") {
        size_t pos = s.find('@');
        if (pos == string::npos) {
            prefix = s;
        } else {
            prefix = s.substr(0, pos);
            suffix = s.substr(pos + 1);
        }
    }
};

bool cmp(const Email& a, const Email& b) {
    if (a.suffix == b.suffix) {
        return a.prefix > b.prefix;
    } else {
        return a.suffix < b.suffix;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);   

    int n;
    cin >> n;
    vector<Email> v;
    v.reserve(n);

    for (int k = 0; k < n; k++) {
        string s;
        cin >> s;
        v.push_back(Email(s));
    }

    sort(v.begin(), v.end(), cmp);

    for (const Email& e: v) {
        cout << e.prefix << '@' << e.suffix << "\n";
    }

    return 0;
}