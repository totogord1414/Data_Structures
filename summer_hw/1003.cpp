#include <bits/stdc++.h>

using namespace std;


long long solve(string& s) {
    vector<int> cVal(128, -1);
    int distinctCount = 0;

    for (char c : s) {        

        if (cVal[c] == -1) {
            if (distinctCount == 0) {
                cVal[c] = 1;
            } else if (distinctCount == 1) {
                cVal[c] = 0;
            } else {
                cVal[c] = distinctCount;
            }

            distinctCount++;
        }
    }

    long long result = 0;

    int base = max(2, distinctCount);

    for (char c : s) {
        result *= base;
        result += cVal[c];
    }

    return result;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        long long result = solve(s);

        cout << "case #" << i << ":\n" << result << "\n";
    }
}