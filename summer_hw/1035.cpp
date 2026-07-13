#include <bits/stdc++.h>

using namespace std;

void print_set(const set<int>& s) {
    cout << "{";
    bool is_first = true;
    for (int n : s) {
        if (!is_first) {
            cout << ", ";
        }
        cout << n;
        is_first = false;
    }
    cout << "}\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);


    int a, b;
    cin >> a >> b;
    set<int> A;
    set<int> B;
    for (int i = 0; i < a; i++) {
        int temp;
        cin >> temp;
        A.insert(temp);
    }

    for (int i = 0; i < b; i++) {
        int temp;
        cin >> temp;
        B.insert(temp);
    }

    set<int> C;
    for (int num : A) {
        if (B.count(num)) {
            C.insert(num);
        }
    }
    print_set(C);

    set<int> D = A;
    for (int num : B) {
        D.insert(num);
    }
    print_set(D);

    set<int> E;
    for (int num: A) {
        if (B.count(num) == 0) {
            E.insert(num);
        }
    }
    print_set(E);
}