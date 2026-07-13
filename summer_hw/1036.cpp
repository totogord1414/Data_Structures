#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    map<int, int> element_counts;
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        for (int j = 0; j < m; j++) {
            int val;
            cin >> val;
            element_counts[val]++;
        }
    }

    bool is_first = true;
    for (const auto& pair : element_counts) {
        if (pair.second == n) {
            if (!is_first) {
                cout << " ";
            }
            cout << pair.first;
            is_first = false;
        }
    }
    cout << "\n";

    return 0;
}