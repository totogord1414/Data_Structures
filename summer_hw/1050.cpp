#include <bits/stdc++.h>

using namespace std;

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

void solve(long long n) {
    long long root = sqrt(n) / 2;
    while (4 * root * root <= n) {
        root++;
    }
    root--;

    long long step = n - 4 * root * root;
    long long x;
    long long y;

    if (step < 2 * root) {
        x = -root + step;
        y = -root;
    } else if (step < 4 * root + 1) {
        x = root;
        y = -root + step - 2 * root;
    } else if (step < 6 * root + 2) {
        x = root - (step - (4 * root + 1));
        y = root + 1;
    } else if (step < 8 * root + 4) {
        x = -root - 1;
        y = root + 1 - (step - (6 * root + 2));
    }

    cout << "(" << x << "," << y << ")\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    cin >> n;
    solve(n);    

    return 0;
}