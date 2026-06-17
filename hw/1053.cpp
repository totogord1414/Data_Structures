#include <bits/stdc++.h>

using namespace std;

int min_unbalanced_id = 1e9;

int judge_tree(int root, const vector<pair<int, int>>& tree) {
    if(root == 0) {
        return 0;
    }

    int left = judge_tree(tree[root].first, tree);
    int right = judge_tree(tree[root].second, tree);

    if(abs(left - right) > 1) {
        min_unbalanced_id = min(min_unbalanced_id, root);
    }

    return max(left, right) + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<pair<int, int>> tree(n + 1);

    for(int i = 1; i <= n; i++) {
        int left, right;
        cin >> left >> right;
        tree[i] = {left, right};
    }

    int height = judge_tree(1, tree);

    if(min_unbalanced_id == 1e9) {
        cout << "Yes\n" << height << "\n";
    } else {
        cout << "No\n" << min_unbalanced_id << "\n";
    }

    return 0;
}