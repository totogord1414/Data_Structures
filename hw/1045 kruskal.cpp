#include <bits/stdc++.h>

using namespace std;

struct side{
    int u;
    int v;
    int value;
};

struct UnionFind{
    vector<int> size;
    vector<int> parent;

    UnionFind(int N) {
        size.resize(N + 1, 1);
        parent.resize(N + 1);
        for(int i = 0; i <= N; i++) {
            parent[i] = i;
        }
    }

    int Find(int u) {
        if(u != parent[u]) {
            parent[u] = Find(parent[u]);
        }
        return parent[u];
    }

    void Union(int u, int v) {
        int uParent = Find(u);
        int vParent = Find(v);

        if(uParent != vParent) {
            if(size[uParent] < size[vParent]) {
                swap(uParent, vParent);
            }
            parent[vParent] = uParent;
            size[uParent] += size[vParent];
        }
    }

    bool inSameSet(int u, int v)
    {
        int a = Find(u);
        int b = Find(v);
        
        return a == b;
    }
};

bool cmp(const side a, const side b) {
    return a.value <  b.value;
}

int solve(int n, UnionFind& uf, vector<side>& sideSet) {
    int lowestCost = 0;
    int roadRequired = n;
    int roadPointer = 0;
    while(roadRequired > 0 && roadPointer < sideSet.size()) {
        side currRoad = sideSet[roadPointer];
        roadPointer++;
        
        if(!uf.inSameSet(currRoad.u, currRoad.v)) {
            uf.Union(currRoad.u, currRoad.v);
            roadRequired--;
            lowestCost += currRoad.value;
        }
    }

    return lowestCost;
}

int main()
{
    int n, m, c;
    cin >> n >> m >> c;
    UnionFind uf(n);

    vector<side> sideSet;
    for(int i = 1; i <= n; i++) {
        int buildCost;
        cin >> buildCost;
        sideSet.push_back({0, i, buildCost});
    }

    for(int i = 0; i < m; i++) {
        int u, v, roadLength;
        cin >> u >> v >> roadLength;
        int roadCost = roadLength * c;
        sideSet.push_back({u, v, roadCost});
    }

    sort(sideSet.begin(), sideSet.end(), cmp);

    int lowestCost = solve(n, uf, sideSet);

    cout << lowestCost << "\n";

    return 0;
}