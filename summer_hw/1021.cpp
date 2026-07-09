#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    string dummy;
    getline(cin, dummy);

    unordered_set<string> ignored_words = {"the", "a", "an", "of", "for", "and"};

    for (int t = 0; t < T; t++) {
        string line;
        getline(cin, line);
        
        stringstream ss(line);
        string word;

        int count = 0;
        while(ss >> word) {
            if (ignored_words.find(word) == ignored_words.end()) {
                count ++;
            }
        }

        cout << "case #" << t << ":" << endl;
        cout << count << endl;
    }

    return 0;
}