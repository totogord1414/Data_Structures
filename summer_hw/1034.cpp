#include <bits/stdc++.h>

using namespace std;

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

void solve(int n) {
    vector<vector<int>> sq(n, (vector<int>(n, -1)));
    int dir = 0;
    int curr = 1;
    int max = n * n;
    int x = 0; 
    int y = 0;
    while (curr <= max) {
        sq[x][y] = curr;
        curr++;
        int next_x = x + dx[dir];
        int next_y = y + dy[dir];
        if (next_x < 0 || next_x >= n || next_y < 0 || next_y >= n || sq[next_x][next_y] != -1) {
            dir = (dir + 1) % 4;
            next_x = x + dx[dir];
            next_y = y + dy[dir];
        }

        x = next_x;
        y = next_y;
    }

    for (vector<int> v: sq) {
        int is_first = true;
        for (int k: v) {
            if (!is_first) {
                cout << " ";
            }
            cout << k;
            is_first = false;
        }
        cout << "\n";
    }
}

int main() {
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int n;
        cin >> n;
        cout << "case #" << t << ":\n";
        solve(n);
    }

    return 0;
}