#include <bits/stdc++.h>

using namespace std;

const double INF = 1e9;

double solve(vector<double> p, vector<double> q) {
    int n = p.size() - 1;

    //initialize s
    vector<double> S(n + 1);

    S[0] = q[0];
    for(int i = 1; i <= n; i++) {
        S[i] = S[i - 1] + p[i] + q[i];
    }


    vector<vector<double>> dq(n + 2, vector<double>(n + 2));
    //record the best root
    vector<vector<int>> root(n + 1, vector<int>(n + 1));

    //when the len is 0
    for(int i = 0; i <= n; i++) {
        dq[i + 1][i] = q[i];
    }

    //when the len is 1,which means there is only one possible tree
    for(int i = 1; i <= n; i++) {
        dq[i][i] = dq[i + 1][i] + dq[i][i - 1] + S[i] - S[i - 1] + q[i - 1];
        root[i][i] = i;
    }

    for(int len = 2; len <= n; len++) {
        for(int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            dq[i][j] = INF;
            double cost = S[j] - S[i - 1] + q[i - 1];
            for(int k = root[i][j - 1]; k <= root[i + 1][j]; k++) {

                double total_cost = dq[i][k - 1] + dq[k + 1][j] + cost;

                if(total_cost < dq[i][j]) {
                    dq[i][j] = total_cost;
                    root[i][j] = k;
                }
            }
        }
    }

    return dq[1][n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<double> p(n + 1);
    vector<double> q(n + 1);

    for(int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    for(int i = 0; i <= n; i++) {
        cin >> q[i];
    }

    double result = solve(p, q);

    cout << fixed << setprecision(6) << result << "\n";

    return 0;

}