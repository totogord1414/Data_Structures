#include <bits/stdc++.h>

using namespace std;

int query(const vector<vector<int>>& sum, int r1, int c1, int r2, int c2) {
    return sum[r2][c2] - sum[r1 - 1][c2] - sum[r2][c1 - 1] + sum[r1 - 1][c1 - 1];
}

void solve() {
    int r, c, n, k;
    cin >> r >> c >> n >> k;

    vector<vector<int>> matrix(r + 1, vector<int>(c + 1, 0));
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        matrix[x][y] = 1;
    }

    //initialize
    vector<vector<int>> sum(r + 1, vector<int>(c + 1, 0));
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] + matrix[i][j] - sum[i - 1][j - 1];
        }
    }

    long long count = 0;    

    for (int i = 1; i <= r; i++) {
        for (int j = i; j <= r; j++) {
            int left = 1;
            int right = 1;
            int one_count = 0;
            for (right = 1; right <= c; right++) {
                one_count += query(sum, i, right, j, right);
                while (one_count >= k) {
                    count += c - right + 1;

                    one_count -= query(sum,i, left, j, left);
                    left++;
                }
            }
        }
    }

    cout << count << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    
    for (int t = 0; t < T; t++) {
        cout << "case #" << t << ":\n";
        solve();
    }

    return 0;
}