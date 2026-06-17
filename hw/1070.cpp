#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

struct Edge {
    int to;
    int weight;
};

struct State {
    int id;
    int dist_from_start;
    
    bool operator>(const State& other) const {
        return dist_from_start > other.dist_from_start;
    }
};

int solve(const vector<vector<Edge>>& graph, int n) {
    vector<int> shortest_path(n + 1, INF);
    vector<bool> checked(n + 1, false);

    priority_queue<State, vector<State>, greater<State>> pq;
    
    pq.push({1, 0});
    shortest_path[1] = 0;
    
    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();
        
        int u = curr.id;
        
        if (u == n) break; 

        if (checked[u]) continue;
        checked[u] = true;
        
        for (const auto& edge : graph[u]) {
            int v = edge.to;
            int w = edge.weight;
            
            if (!checked[v] && shortest_path[v] > shortest_path[u] + w) {
                shortest_path[v] = shortest_path[u] + w;
                pq.push({v, shortest_path[v]});
            }
        }
    }

    return shortest_path[n] == INF ? -1 : shortest_path[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<Edge>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    cout << solve(graph, n) << "\n";

    return 0;
}