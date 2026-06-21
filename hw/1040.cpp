#include <bits/stdc++.h>

using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> setSize;

public:
    UnionFind(int n) {
        parent.resize(n + 1);
        setSize.resize(n + 1, 1);

        iota(parent.begin(), parent.end(), 0);
    }

    int Find(int k) {
        if (parent[k] != k) {
            parent[k] = Find(parent[k]);
        }
        return parent[k];
    }

    void Union(int x, int y) {
        int rootX = Find(x);
        int rootY = Find(y);
        if (rootX != rootY) {
            if (setSize[rootX] < setSize[rootY]) {
                swap(rootX, rootY);
            }
            parent[rootY] = rootX;
            setSize[rootX] += setSize[rootY];
        }
    }
};

int main() {
    // 优化 I/O
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    UnionFind uf(n);
    vector<int> degree(n + 1, 0); 

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        degree[u]++;
        degree[v]++;
        uf.Union(u, v);
    }

    for (int i = 1; i <= n; i++) {
        if (degree[i] % 2 != 0) {
            cout << 0 << "\n";
            return 0;
        }
    }

    int rootCount = 0;
    for (int i = 1; i <= n; i++) {

        if (degree[i] > 0 && uf.Find(i) == i) {
            rootCount++;
        }
    }

    if (rootCount > 1) {
        cout << 0 << "\n";
    } else {
        cout << 1 << "\n";
    }

    return 0;
}