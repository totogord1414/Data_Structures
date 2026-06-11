#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

// 'v' represents the destination node of this specific edge
struct Edge {
    int v;
    int length;
};

// 'u' represents the current node in the priority queue
struct State {
    int u;
    int dist;
    int teams;
};

class Comparator {
public:
    bool operator()(const State& a, const State& b) {
        // First priority: shorter distance
        // Second priority: more rescue teams (note the '<' for max-heap behavior on teams)
        if (a.dist == b.dist) {
            return a.teams < b.teams;
        } else {
            return a.dist > b.dist;
        }
    }
};

void solve(int n, int s, int d, const vector<int>& teams, vector<int>& parent,
    vector<int>& dist, vector<int>& maxTeams, vector<int>& pathCount, const vector<vector<Edge>>& graph) {

    // Initialize the starting node 's'
    dist[s] = 0;
    maxTeams[s] = teams[s];
    pathCount[s] = 1;

    priority_queue<State, vector<State>, Comparator> pq;
    vector<bool> hasVisited(n + 1, false);
    
    pq.push({s, 0, teams[s]});

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();

        int u = curr.u; // Standard naming: 'u' is the current node

        if (hasVisited[u]) {
            continue;
        } 
        
        hasVisited[u] = true;
        
        // Early exit: we have found the optimal path to the destination
        if (u == d) {
            break;
        }

        // Standard naming: 'v' is the neighbor node
        for (const auto& edge : graph[u]) {
            int v = edge.v;
            int vTeam = teams[v];
            int length = edge.length;

            // Case 1: A strictly shorter path is found
            if (dist[v] > dist[u] + length) {
                dist[v] = dist[u] + length;
                maxTeams[v] = maxTeams[u] + vTeam;
                pathCount[v] = pathCount[u]; // FIXED TYPO: Inherit path count from 'u'
                parent[v] = u;
                
                pq.push({v, dist[v], maxTeams[v]});
            } 
            // Case 2: An alternative path with the exact same distance is found
            else if (dist[v] == dist[u] + length) {
                pathCount[v] += pathCount[u]; // Unconditionally add the number of paths
                
                // Only update teams, parent, and push to queue if it yields more rescue teams
                if (maxTeams[v] < maxTeams[u] + vTeam) {
                    maxTeams[v] = maxTeams[u] + vTeam;
                    parent[v] = u;
                    pq.push({v, dist[v], maxTeams[v]});
                }
            }
        }
    }
}

int main() {
    // Optimize standard I/O operations for performance
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s, d;
    if (!(cin >> n >> m >> s >> d)) return 0;

    vector<int> teams(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> teams[i];
    }

    vector<vector<Edge>> graph(n + 1);
    vector<int> parent(n + 1, -1);
    vector<int> pathCount(n + 1, 0);
    vector<int> dist(n + 1, INF);
    vector<int> maxTeams(n + 1, 0);  

    for (int i = 0; i < m; i++) {
        int u, v, length;
        cin >> u >> v >> length;
        // The graph is undirected
        graph[u].push_back({v, length});
        graph[v].push_back({u, length});
    }

    solve(n, s, d, teams, parent, dist, maxTeams, pathCount, graph);

    // Output 1: Total number of shortest paths and the maximum teams gathered
    cout << pathCount[d] << " " << maxTeams[d] << "\n";

    // Trace back the optimal path using the parent array
    vector<int> path;
    int curr = d;
    while (curr != -1) {
        path.push_back(curr);
        curr = parent[curr];
    }

    // Reverse to get the path from source to destination
    reverse(path.begin(), path.end());

    // Output 2: The actual path sequence
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i] << (i == path.size() - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}