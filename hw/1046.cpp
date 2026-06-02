#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int u;
    int v;
    long long value; 
    bool isTreeEdge = false;
};

//using class instead of struct
class UnionFind {
private:
    int setSize;
    vector<int> size;
    vector<int> parent;
    
public:
    UnionFind(int n) {
        setSize = n;
        size.resize(n + 1, 1);
        parent.resize(n + 1);
        for(int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find(int m) {
        if(m != parent[m]) {
            parent[m] = find(parent[m]);
        }
        return parent[m];
    }

    bool unionSet(int u, int v) {
        int uP = find(u);
        int vP = find(v);
        
        if(uP == vP) return false; //already in the same set, fail 
        
        if(size[uP] < size[vP]) {
            swap(uP, vP);
        }
        parent[vP] = uP;
        size[uP] += size[vP];
        setSize--;
        
        return true; // succeed
    }

    int getSize() const {
        return setSize;
    }
};

void dfs(int root, int parent, int curr, const vector<vector<pair<int, long long>>>& mstAdj, vector<vector<long long>>& longestPath, long long currMax) {
    longestPath[root][curr] = currMax;

    for(const auto& edge : mstAdj[curr]) {
        int nextNode = edge.first;
        long long weight = edge.second;

        if(nextNode != parent) {
            dfs(root, curr, nextNode, mstAdj, longestPath, max(currMax, weight));
        }
    }
}

long long findMinValue(UnionFind& uf, vector<Edge>& edgeSet, vector<vector<pair<int, long long>>>& mstAdj) {
    long long totalValue = 0;
    int edgePointer = 0;
    
    while(edgePointer < edgeSet.size()) {
        Edge& currEdge = edgeSet[edgePointer];
        int u = currEdge.u;
        int v = currEdge.v;
        long long value = currEdge.value;
        
        if(uf.unionSet(u, v)) {
            totalValue += value;
            currEdge.isTreeEdge = true;
            mstAdj[u].push_back({v, value});
            mstAdj[v].push_back({u, value});
        }
        edgePointer++;
    }

    return totalValue;
}

pair<bool, long long> findAnother(int n, long long minValue, const vector<Edge>& edgeSet, const vector<vector<pair<int, long long>>>& mstAdj) {
    vector<vector<long long>> longestPath(n + 1, vector<long long>(n + 1, 0));
    
    for(int i = 1; i <= n; i++) {
        dfs(i, -1, i, mstAdj, longestPath, 0);
    }

    long long maxDiff = 1e18; // 对应 long long 的无穷大
    bool changed = false;
    
    for(const auto& edge : edgeSet) {
        if(!edge.isTreeEdge) {
            int u = edge.u;
            int v = edge.v;
            long long weight = edge.value;
            
            if(weight == longestPath[u][v]) {
                return {true, 0};
            } else {
                maxDiff = min(maxDiff, weight - longestPath[u][v]);
                changed = true;
            }
        }
    }

    if(changed) {
        return {false, maxDiff};
    }
    return {false, -1};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    
    UnionFind uf(n);
    vector<Edge> edgeSet;
    for(int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edgeSet.push_back({u, v, w, false});
    }
//using the lambda  function
    sort(edgeSet.begin(), edgeSet.end(), [](const Edge& a, const Edge& b) {
        return a.value < b.value;
    });
    
    vector<vector<pair<int, long long>>> mstAdj(n + 1);

    long long minValue = findMinValue(uf, edgeSet, mstAdj);
    
    if(uf.getSize() > 1) {
        cout << "NO MST\n" << uf.getSize() << "\n";
    } else {
        pair<bool, long long> ans = findAnother(n, minValue, edgeSet, mstAdj);
        if(ans.first) {
            cout << "YES\n" << minValue << "\n";
        } else if(ans.second == -1) {
            cout << "NO\n" << minValue << " " << -1 << "\n";
        } else {
            cout << "NO\n" << minValue << " " << minValue + ans.second << "\n";
        }
    }

    return 0;
}