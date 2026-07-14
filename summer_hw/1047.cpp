#include <bits/stdc++.h>

using namespace std;

vector<int> v;
int total_sum = 0;
int max_sp = 0;

void dfs(int index, int s, int p) {
    if (p > total_sum) {
        return;
    }
    if (index == v.size()) {
        if (s == p) {
            max_sp = max(max_sp, s);
        }

        return;
    }

    dfs(index + 1, s, p * v[index]);
    dfs(index + 1, s + v[index], p);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, i;
    while (cin >> n >> i) {
        for (i; i > 0; i--) {
            v.push_back(n);
            total_sum += n;
        }
    }

    dfs(0, 0, 1);

    cout << v.size() << " " << max_sp << "\n";



    return 0;
}