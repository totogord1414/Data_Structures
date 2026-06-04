#include <bits/stdc++.h>

using namespace std;

// Basic data packet
struct Edge {
    int u;
    int v;
    long long value;
    bool isTreeEdge = false;
};

// Disjoint Set Union (Capacity expanded to support 2n nodes)
class UnionFind {
public: // Set to public for easy modification of parent-child relationships during tree reconstruction
    vector<int> parent;
    int components; // Records the number of connected components in the original graph

    UnionFind(int max_nodes, int initial_components) {
        parent.resize(max_nodes + 1);
        for (int i = 1; i <= max_nodes; i++) {
            parent[i] = i;
        }
        components = initial_components;
    }

    int find(int m) {
        if (m != parent[m]) {
            parent[m] = find(parent[m]);
        }
        return parent[m];
    }
};

const int MAX_NODES = 1005; // Large enough to hold 2n-1 nodes

// ================= Global Variables =================
vector<int> treeAdj[MAX_NODES]; // Adjacency list for the reconstruction tree (only directed edges from parent to child)
long long nodeValue[MAX_NODES]; // Node values of the reconstruction tree (representing the edge weights)

// TODO 1: Declare a depth array named 'depth' (size MAX_NODES)
int depth[MAX_NODES];
// TODO 2: Declare the binary lifting array 'fa' (2D array, size MAX_NODES x 12 is sufficient since 2^11 > 1000)
int fa[MAX_NODES][12];
// ================= Core Algorithms =================

// Core 1: Binary Lifting Preprocessing
void dfs_lca(int curr, int parent) {
    // TODO 1: Record the depth of the current node (equals parent's depth + 1)
    
    // TODO 2: Initialize the ancestor for a 2^0 (1 step) jump, which is the 'parent' itself
    
    // TODO 3: Write a loop from 1 to 11 to fill the 'fa' array using the state transition equation
    // Hint: fa[curr][j] = fa[ fa[curr][j - 1] ][ j - 1 ];
    
    // TODO 4: Iterate through all child nodes in treeAdj[curr] and recursively call dfs_lca
}

// Core 2: Jump using Binary Lifting to find LCA
int get_lca(int u, int v) {
    // TODO 1: Ensure 'u' is the deeper node (if depth[u] < depth[v], swap(u, v))
    
    // TODO 2: Make 'u' jump upwards until it is at the same depth as 'v'
    // Hint: Use a for loop with 'j' decreasing from 11 to 0. If depth[fa[u][j]] >= depth[v], update u = fa[u][j]
    
    // If u and v are equal after aligning depths, one is the ancestor of the other, return u directly
    if (u == v) return u;

    // TODO 3: u and v jump upwards together
    // Hint: Similarly, use a loop with 'j' from 11 down to 0. If fa[u][j] != fa[v][j], it means they haven't met the LCA yet, update u = fa[u][j], v = fa[v][j]
    
    // TODO 4: After the loop, u and v are exactly one step below the LCA. Return the node 1 step above them (i.e., fa[u][0])
    return 0; // Remember to modify this return value
}

// Core 3: Merge components and build the Reconstruction Tree
long long buildKruskalTree(int n, UnionFind& uf, vector<Edge>& edgeSet) {
    long long totalValue = 0;
    int totNodes = n; // Track the total number of nodes created. Initially, there are 'n' leaf nodes

    for (int i = 0; i < edgeSet.size(); i++) {
        Edge& currEdge = edgeSet[i];
        
        // TODO 1: Use uf.find to get the current root nodes 'ru' and 'rv' for currEdge.u and currEdge.v
        
        // TODO 2: If they belong to different components (ru != rv)
            // Step A: Create a new component node (increment totNodes by 1)
            // Step B: Assign weight to the new node (nodeValue[totNodes] = current edge's value)
            // Step C: Set the new node as the parent of the original roots (uf.parent[ru] = totNodes, same for rv)
            // Step D: Add directed edges in treeAdj from the new node 'totNodes' to 'ru' and 'rv'
            
            // Step E: Basic MST maintenance (add to totalValue, set isTreeEdge to true, decrement uf.components by 1)
            // Step F: If uf.components == 1, the final tree is formed, break the loop early
    }
    
    // TODO 3: If the graph is connected (uf.components == 1), run dfs_lca starting from the highest root node (totNodes). Note: the root's parent can be set to 0.
    
    return totalValue;
}

// Core 4: Final judgment, query, and replacement
pair<bool, long long> findAnother(int n, vector<Edge>& edgeSet) {
    long long maxDiff = 1e18;
    bool changed = false;
    
    for (const auto& edge : edgeSet) {
        if (!edge.isTreeEdge) {
            int u = edge.u;
            int v = edge.v;
            long long weight = edge.value;
            
            if (u == v) continue;

            // TODO 1: Call get_lca to find the Lowest Common Ancestor (LCA) of u and v in the reconstruction tree
            
            // TODO 2: Retrieve the weight of this LCA node via the nodeValue array (this represents the maximum edge weight on the path)
            
            // TODO 3: Compare 'weight' with 'max_path_weight':
                // If equal, another MST with the exact same weight exists, return {true, 0};
                // If 'weight' is greater, update 'maxDiff', and set 'changed' to true
        }
    }

    if (changed) {
        return {false, maxDiff};
    }
    return {false, -1};
}

// ================= Main Function =================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    
    UnionFind uf(2 * n, n); 
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
    
    long long minValue = buildKruskalTree(n, uf, edgeSet);
    
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