#include <bits/stdc++.h>

using namespace std;

void parseString(const string& s, string& int_part, string& frac_part) {
    size_t pos = s.find('.');
    if (pos == string::npos) {
        int_part = s;
        frac_part = "";
    } else {
        int_part = s.substr(0, pos);
        frac_part = s.substr(pos + 1);
    }
    if (int_part.empty()) {
        int_part = "0";
    }
}

void add(const string& a, const string& b, string& sum, int carry) {
    if (a.length() < b.length()) {
        add(b, a, sum, carry);
        return;
    }
    for (int i = 0; i < a.length(); i++) {
        int value = carry + a[i] - '0';
        if (i < b.length()) {
            value += b[i] - '0';
        }
        sum += to_string(value % 10);
        carry = value / 10;
    }
    if (carry) {
        sum += to_string(carry);
    }

    reverse(sum.begin(), sum.end());
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    

    string A, B;
    int N;
    cin >> A >> B >> N;

    string int1, int2, frac1, frac2;
    parseString(A, int1, frac1);
    parseString(B, int2, frac2);

    int max_len = max({N + 1, (int)frac1.size(), (int)frac2.size()});
    frac1.append(max_len - frac1.size(), '0');
    frac2.append(max_len - frac2.size(), '0');

    int carry = 0;
    string frac_sum = "";

    for (int i = max_len - 1; i >= 0; i--) {
        int value = carry + frac1[i] - '0' + frac2[i] - '0';
        carry = value / 10;        
        frac_sum += to_string(value % 10);
    }

    reverse(frac_sum.begin(), frac_sum.end());



    string int_sum = "";
    reverse(int1.begin(), int1.end());
    reverse(int2.begin(), int2.end());

    add(int1, int2, int_sum, carry);


    int round_carry = 0;
    string final_frac = frac_sum.substr(0, N);
    if (frac_sum[N] >= '5') {
        round_carry = 1;
        for (int i = N - 1; i >= 0; i--) {
            int value = frac_sum[i] - '0' + round_carry;
            final_frac[i] = value % 10 + '0';
            round_carry = value / 10;
        }

        if (round_carry) {
            for (int i = int_sum.length() - 1; i >= 0; i--) {
                int value = int_sum[i] - '0' + round_carry;
                int_sum[i] = value % 10 + '0';
                round_carry = value / 10;
            }

            if (round_carry) {
                int_sum.insert(0, to_string(round_carry));
            }
        }
    }

    int non_zero_idx = 0;
    while (non_zero_idx < int_sum.length() - 1 && int_sum[non_zero_idx] == '0') {
        non_zero_idx++;
    }
    int_sum = int_sum.substr(non_zero_idx);


    cout << int_sum << "." << final_frac << "\n";

    return 0;
}