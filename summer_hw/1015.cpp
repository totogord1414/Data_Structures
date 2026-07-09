#include <bits/stdc++.h>

using namespace std;

void parseString(const string& s, string& i, string& f) {
    size_t pos = s.find('.');
    if (pos == string::npos) {
        i = s;
        f = "";
    } else {
        i = s.substr(0, pos);
        f = s.substr(pos + 1);
    }

    if (i.empty()) {
        i = "0";
    }
}

bool compare(const string& int1, const string& int2, const string& frac1, const string& frac2) {
        if (int1 == int2) {
            return frac1 < frac2;
        }
        return int1 < int2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //sepreate and initialize the int and fic
    string A, B;
    int N;
    cin >> A >> B >> N;

    string int1, int2, frac1, frac2;

    parseString(A, int1, frac1);
    parseString(B, int2, frac2);

    int max_len = max({N + 1, (int) frac1.length(), (int) frac2.length()});

    frac1.append(max_len - frac1.length(), '0');
    frac2.append(max_len - frac2.length(), '0');

    int max_int_len = max(int1.length(), int2.length());
    int1 = string(max_int_len - int1.length(), '0') + int1;
    int2 = string(max_int_len - int2.length(), '0') + int2;

    //compare the larger one of a and b, and confirm the sign

    bool is_negative = compare(int1, int2, frac1, frac2);

    if (is_negative) {
        swap(int1, int2);
        swap(frac1, frac2);
    }
    //seperately minus the int part and the frac part
    
    A = int1 + frac1;
    B = int2 + frac2;
    string result = "";
    int borrow = 0;
    for (int i = A.length() - 1; i >= 0; i--) {
        int value = A[i] - B[i] - borrow;
        if (value < 0) {
            value += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result += to_string(value);
    }

    reverse(result.begin(), result.end());
    //confirm the round_carry and minus again

    string result_int = result.substr(0, max_int_len);
    string result_frac = result.substr(max_int_len);

    int carry = 0;
    if (result_frac[N] >= '5') {
        carry = 1;
    }
    
    result_frac = result_frac.substr(0, N);

    if (carry == 1) {
        for (int i = N - 1; i >= 0; i--) {
            int value = result_frac[i] - '0' + carry;
            result_frac[i] = value % 10 + '0';
            carry = value / 10;
            if (carry == 0) break;
        }

        if (carry == 1) {
            for (int i = result_int.length() - 1; i >= 0; i--) {
                int value = result_int[i] - '0' + carry;
                result_int[i] = value % 10 + '0';
                carry = value / 10;
                if (carry == 0) break;
            }
            if (carry == 1) {
                result_int = "1" + result_int;
            }
        }
    }

    //output with the sign at first

    int idx = 0;
    while (idx < result_int.length() && result_int[idx] == '0') {
        idx++;
    }

    result_int = result_int.substr(idx);
    if(result_int.empty()) {
        result_int = "0";
    }

    bool is_zero = true;
    for (char c : result_int) if (c != '0') {
        is_zero = false;
        break;
    } 
    for (char c : result_frac) if (c != '0') {
        is_zero = false;
        break;
    } 

    if (!is_zero && is_negative) {
        cout << "-";
    }

    cout << result_int << "." << result_frac << "\n";

    return 0;
}