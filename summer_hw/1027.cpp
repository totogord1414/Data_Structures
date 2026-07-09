#include <bits/stdc++.h>

using namespace std;

void solve(int t) {
    string line;
    getline(cin, line);
    for (char& c : line) {
        if (c == ',' || c == '.' || c == '!' || c == '?') c = ' ';
    }

    stringstream ss(line);

    set<string> word_set;
    string word;
    while (ss >> word) {
        word_set.insert(word);
    }

    bool is_first = true;

    cout << "case #" << t << ":" << "\n";

    for (const string& word : word_set) {
        if (!is_first) {
            cout << " ";
        }
        cout << word;
        is_first = false;
    }

    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    string dummy;
    getline(cin, dummy);

    for (int t = 0; t < T; t++) {
        solve(t);
    }

    return 0;
}