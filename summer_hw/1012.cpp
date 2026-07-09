#include <bits/stdc++.h>

using namespace std;

vector<int> add(vector<int>& a, vector<int>& b) {
    if (a.size() < b.size()) {
        return add(b, a);
    }

    vector<int> c;
    c.reserve(a.size());
    int carry = 0;
    for (int i = 0; i < a.size(); i++) {
        carry += a[i];
        if (i < b.size()) {
            carry += b[i];
        }

        c.push_back(carry % 10);
        carry = carry / 10;
    }

    if (carry) {
        c.push_back(carry);
    }

    return c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string a, b;

    while (cin >> a >> b) {
        vector<int> A, B;
        for (int i = a.size() - 1; i >= 0; i--) {
            A.push_back(a[i] - '0');
        }

        for (int i = b.size() - 1; i >= 0; i--) {
            B.push_back(b[i] - '0');

        }
        vector<int> C = add(A, B);
        for (int i = C.size() - 1; i >= 0; i--) {
            cout << C[i];
        }
        cout << "\n";
    }

    return 0;
}