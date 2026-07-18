#include <bits/stdc++.h>

using namespace std;

void get_num(string& A, vector<int>& a) {
    int i = 0;
    int sign = 1;
    int value = 0;
    int exp = 0;
    bool calc_exp = false;
    bool has_value = false;

    while (i < A.length()) {
        char c = A[i];
        if (c == '+' || c == '-') {
            if (calc_exp || has_value) {
                if (calc_exp && exp == 0) exp = 1;
                if (!has_value) value = 1;
                a[exp] += sign * value;
            }

            sign = (c == '-') ? - 1 : 1;
            calc_exp = false;
            has_value = false;
            exp = 0;
            value = 0;
        } else if (c == 'x') {
            calc_exp = true;
        } else if (isdigit(c)) {
            if (!calc_exp) {
                has_value = true;
                value *= 10;
                value += c - '0';
            } else {
                exp *= 10;
                exp += c - '0';
            }
        }

        i++;
    }

    if (has_value || calc_exp) {
        if (!has_value) value = 1;
        if (calc_exp && exp == 0) exp = 1;
        a[exp] += sign * value;
    }
}

void mul(const vector<int>& a, const vector<int>& b) {
    vector<long long> result(106, 0);

    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            result[i + j] += a[i] * b[j];
        }
    }
    bool is_first = true;
    for (int i = result.size() - 1; i >= 0; i--) {
        long long n = result[i];
        if (n != 0) {
            if (!is_first) {
                cout << " ";
            }
            cout << n;
            is_first = false;
        }
    }

    cout << "\n";
}


int main() {
    string A, B;
    while (cin >> A >> B) {
        vector<int> a(52, 0);
        vector<int> b(52, 0);
        get_num(A, a);
        get_num(B, b);

        mul(a, b);
    }

    return 0;
}