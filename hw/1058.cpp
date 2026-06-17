#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

void helper(const vector<int>& pre_order, vector<int>& result, int& pointer, int bound) {
    if(pointer >= pre_order.size() || pre_order[pointer] >= bound) {
        return;
    } else {
        int node_value = pre_order[pointer];
        pointer++;

        helper(pre_order, result, pointer, node_value); //visit left side
        helper(pre_order, result, pointer, bound); //visit right side

        result.push_back(node_value);
    }
}

void solve(const vector<int>& pre_order) {
    int pointer = 0;
    vector<int> result;
    result.reserve(pre_order.size());

    helper(pre_order, result, pointer, INF);

    for(const auto& v: result) {
        cout << v << "\n";
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);    

    vector<int> pre_order;

    int n;
    while(cin >> n) {
        pre_order.push_back(n);
    }

    solve(pre_order);

    return 0;
}