#include <bits/stdc++.h>

using namespace std;

// Basic data structure for an edge
struct Edge {
    int u;
    int v;
    long long value;
    bool isTreeEdge = false;
};

// Full-featured Disjoint Set Union (UnionFind)
// Route 1 utilizes Union by Size for maximum efficiency
class UnionFind {
private:
    vector<int> size;
    vector<int> parent;
    
public:
    int components; 

    UnionFind(int n) {
        size.resize(n + 1, 1);
        parent.resize(n + 1);
        for(int i = 1; i <= n; i++) {
            parent[i] = i;
        }
        components = n;
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
        
        if(uP == vP) return false; 
        
        if(size[uP] < size[vP]) {
            swap(uP, vP);
        }
        parent[vP] = uP;
        size[uP] += size[vP];
        components--; 
        
        return true; 
    }
};

const int MAX_NODES = 505;

// ================= Global Variables for Route 1 =================
// Standard Adjacency List for MST
vector<pair<int, long long>> mstAdj[MAX_NODES]; 

int depth[MAX_NODES];           
int fa[MAX_NODES][12];          

// 🌟 THE CORE ARRAY OF ROUTE 1: 
// max_w[i][j] records the MAXIMUM edge weight on the path from node 'i' jumping up 2^j steps
long long max_w[MAX_NODES][12]; 

// ================= Core Algorithms =================

// Preprocessing: Calculate depths, ancestor jumps, and max weights along the jumps
void dfs_lca(int curr, int parent, long long weight_to_parent) {
    // TODO 1: Initialize depth of 'curr' based on 'parent'
    
    // TODO 2: Initialize the 1-step jump (2^0) ancestor and its corresponding max_w
    // Hint: fa[curr][0] = ? ; max_w[curr][0] = ? ;
    
    // TODO 3: Dynamic Programming for Binary Lifting
    // Write a loop for j from 1 to 11 to populate fa[curr][j] and max_w[curr][j]
    // Hint for max_w: You need to find the max between the first half of the jump and the second half.
    
    // TODO 4: Recursively visit all children in mstAdj[curr]
    // Remember to avoid visiting the 'parent' again!
    depth[curr] = depth[parent] + 1;
    fa[curr][0] = parent;
    max_w[curr][0] = weight_to_parent;
    for(int j = 1; j < 12 && pow(2, j) <= depth[curr]; j++) {
        int anc = fa[curr][j - 1];
        fa[curr][j] = fa[anc][j - 1];
        max_w[curr][j] = max(max_w[curr][j - 1], max_w[anc][j - 1]);
    }

    for(const auto& p: mstAdj[curr]) {
        if(p.first != parent) {
            dfs_lca(p.first, curr, p.second);
        }
    }
}

// LCA Query + Dynamic Max Weight Tracking
long long get_max_weight(int u, int v) {
    long long path_max = 0; 
    
    // TODO 1: Ensure 'u' is the deeper node (swap if necessary)
    if(depth[u] < depth[v]) {
        swap(u, v);
    }
    
    // TODO 2: Align depths
    // Write a loop to make 'u' jump upwards until depth[u] == depth[v]
    // CRITICAL HINT: Before 'u' jumps to its new ancestor, you MUST update 'path_max' with the max_w of that jump!
    for(int j = 11; j >= 0; j--) {
        if (depth[fa[u][j]] >= depth[v]) {
            
            path_max = max(path_max, max_w[u][j]);

            u = fa[u][j];
        }
    }
    
    
    if (u == v) return path_max;

    // TODO 3: Jump upwards together
    // Write a loop from j = 11 down to 0. If fa[u][j] != fa[v][j], both nodes jump.

    for(int j = 11; j >= 0; j--) {
        if (depth[fa[u][j]] >= 0 && fa[u][j] != fa[v][j]) {
            path_max = max({path_max, max_w[u][j], max_w[v][j]});

            u = fa[u][j];
            v = fa[v][j];
        }
    }

    // CRITICAL HINT: Update 'path_max' considering BOTH max_w[u][j] and max_w[v][j] BEFORE making the jump.
    
    // TODO 4: The final 1-step jump
    // At this point, u and v are just 1 step below the LCA. 
    // Update 'path_max' one last time using max_w[u][0] and max_w[v][0].
    path_max = max(path_max, max_w[u][0], max_w[v][0]);
    return path_max;
}

// Build standard MST using Kruskal's Algorithm
long long buildStandardMST(int n, UnionFind& uf, vector<Edge>& edgeSet) {
    long long totalValue = 0;

    for (int i = 0; i < edgeSet.size(); i++) {
        Edge& currEdge = edgeSet[i];

        // TODO 1: Attempt to unite currEdge.u and currEdge.v using uf.unionSet()
        // If successful:
        //   - Add value to totalValue
        //   - Mark isTreeEdge = true
        //   - Add bidirectional edges to mstAdj
        //   - Check if the graph is fully connected (components == 1) and break early if so
        int u = currEdge.u;
        int v = currEdge.v;
        int weight = currEdge.value;
        if(uf.unionSet(u, v))
        {
            totalValue += currEdge.value;
            currEdge.isTreeEdge = true;
            mstAdj[u].push_back({v, weight});
            mstAdj[v].push_back({u, weight});
        }
        if(uf.components == 1) {
            break;
        }
    }
    
    // TODO 2: If the graph is connected, start the dfs_lca from node 1.
    // Hint: The parent of the root can be 0, and the weight to this non-existent parent is 0.
    depth[0] = -1;
    if(uf.components == 1) {
        dfs_lca(1, 0, 0);
    }
    
    return totalValue;
}

// Final check: Calculate differences using non-tree edges
pair<bool, long long> findAnother(int n, const vector<Edge>& edgeSet) {
    long long maxDiff = 1e18; 
    bool changed = false;
    
    for (const auto& edge : edgeSet) {
        if (!edge.isTreeEdge) {
            int u = edge.u;
            int v = edge.v;
            long long weight = edge.value;
            
            if (u == v) continue;

            // TODO 1: Call get_max_weight to find the bottleneck on the MST path between u and v
            long long max_path_weight = get_max_weight(u, v); // REPLACE THIS LINE with your function call
            
            // TODO 2: Compare the non-tree edge 'weight' with 'max_path_weight'
            // If they are equal, return {true, 0}
            // If 'weight' is greater, update 'maxDiff' and set 'changed' to true
            if(max_path_weight == weight) {
                return {true, 0};
            } else {
                changed = true;
                maxDiff = min(maxDiff, weight - max_path_weight);
            }
        }
    }

    if (changed) {
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
    
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edgeSet.push_back({u, v, w, false});
    }

    sort(edgeSet.begin(), edgeSet.end(), [](const Edge& a, const Edge& b) {
        return a.value < b.value;
    });
    
    long long minValue = buildStandardMST(n, uf, edgeSet);
    
    if (uf.components > 1) {
        cout << "NO MST\n" << uf.components << "\n";
    } else {
        pair<bool, long long> ans = findAnother(n, edgeSet);
        if (ans.first) {
            cout << "YES\n" << minValue << "\n";
        } else if (ans.second == -1) {
            cout << "NO\n" << minValue << " " << -1 << "\n";
        } else {
            cout << "NO\n" << minValue << " " << minValue + ans.second << "\n";
        }
    }

    return 0;
}