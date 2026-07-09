#include <bits/stdc++.h>

using namespace std;

const int Primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};


vector<int> parseAndReverse(const string& s) {
    vector<int> res;
    stringstream ss(s);
    string token;
    while (getline(ss, token, ',')) {
        res.push_back(stoi(token));
    }

    reverse(res.begin(), res.end());

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (int k = 0; k < t; k++) {
        string s1, s2;

        cin >> s1 >> s2;

        vector<int> a = parseAndReverse(s1);
        vector<int> b = parseAndReverse(s2);

        vector<int> result;
        int carry = 0;
        int maxLen = max(a.size(), b.size());

        for (int i = 0; i < maxLen || carry != 0; i++) {
            int valA = i < a.size() ? a[i] : 0;
            int valB = i < b.size() ? b[i] : 0;

            int sum = valA + valB + carry;
            int base = Primes[i];

            result.push_back(sum % base);
            carry = sum / base;
        }

        reverse(result.begin(), result.end());

        cout << "case #" << k << ":\n";
    
        for (int j = 0; j < result.size() - 1; j++) {
            cout << result[j] << ",";
        }
        cout << result.back() << "\n";
    }

    return 0;
}