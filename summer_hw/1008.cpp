#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<long long> num(n);

    for (int i = 0; i < n; i++) {
        cin >> num[i];
    }

    sort(num.begin(), num.end());

    long long min_sum = 0;
    
    for (int i = 0; i < n; i += 2) {
        min_sum += num[i + 1] - num[i];
    }

    cout << min_sum << "\n";

    return 0;
}