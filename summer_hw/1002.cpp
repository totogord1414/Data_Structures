#include <iostream>
#include <string>

using namespace std;

struct Num {
    long long a;
    long long b;
    long long c;
    bool isNegative; 
};

int charToVal(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

long long getGcd(long long a, long long b) {
    return b == 0 ? a : getGcd(b, a % b);
}

Num StoF(long long r, string Snum) {
    long long A = 0;
    long long B = 0;
    long long C = 1;
    bool isNegative = false;

    long long pointer = 0;
    
    if (Snum[pointer] == '-') {
        isNegative = true;
        pointer++; 
    }

    // 解析整数部分
    while (pointer < Snum.size() && Snum[pointer] != '.') {
        char c = Snum[pointer];
        A *= r;
        A += charToVal(c);
        pointer++;
    }
    
    if (pointer < Snum.size()) {
        pointer++;

        while (pointer < Snum.size()) {
            char c = Snum[pointer];
            B *= r;
            C *= r;
            B += charToVal(c);
            pointer++; 
        }

        if (B > 0) { 
            long long val = getGcd(B, C);
            B /= val;
            C /= val;
        }
    }

    return {A, B, C, isNegative};
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long r;
    string Snum;

    if (!(cin >> r >> Snum)) return 0;

    Num result = StoF(r, Snum);

    if (result.a == 0 && result.b == 0) {
        cout << 0 << "\n";
        return 0;
    }

    if (result.isNegative) {
        cout << "-";
    }

    if (result.b == 0) {
        cout << result.a << "\n";
    } else if (result.a == 0) {
        cout << result.b << " " << result.c << "\n";
    } else {
        cout << result.a << " " << result.b << " " << result.c << "\n";
    }

    return 0;
}