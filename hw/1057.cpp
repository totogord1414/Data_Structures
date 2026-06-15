#include <bits/stdc++.h>

using namespace std;

void helper(vector<int>& in_order, const vector<int>& array, int pos) {
    if(pos < array.size()) {
        helper(in_order, array, pos * 2);
        in_order.push_back(array[pos]);
        helper(in_order, array, pos * 2 + 1);
    }
}


void judge(const vector<int>& array) {
    vector<int> in_order;
    helper(in_order, array, 1);

    for(int i = 0; i < in_order.size() - 1; i++) {
        if(in_order[i] >= in_order[i + 1]) {
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int m;
        cin >> m;
        vector<int> array(m + 1);

        for(int j = 1; j <= m; j++) {
            cin >> array[j];
        }

        judge(array);
    }

    return 0;
}