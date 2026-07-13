#include <bits/stdc++.h>

using namespace std;

void print_cube(int n) {
    vector<vector<int>> cube(n, vector<int>(n, -1));

    int x = n - 1;
    int y = n / 2;
    int curr = 1;
    int square = n* n;
    while (curr <= square) {
        cube[x][y] =curr;
        curr++;
        int next_x = (x + 1) % n;
        int next_y = (y - 1 + n) % n;

        if((x == n - 1 && y == 0) || cube[next_x][next_y] != -1) {
            next_x = (x - 1 + n) % n;
            next_y = y;
        }

        x = next_x;
        y = next_y;
    }

    for (const vector<int>& v: cube) {
        bool is_first = true;
        for (int n: v) {
            if (!is_first) {
                cout << " ";
            }
            cout << n;
            is_first = false;
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        print_cube(n);
    }

    return 0;
}