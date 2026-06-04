#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

struct Edge {
    int to;
    int weight;
};

struct Node {
    int id;
    int dist;
};

struct nodeComparator {
    bool operator()(const Node& a, const Node&b) {
        return a.dist > b.dist;
    }
};

void solve(int s, vector<int>& dist, vector<long long>& count, vector<vector<Edge>>& edgeSet) {
    priority_queue<Node, vector<Node>, nodeComparator> pq;

    dist[s] = 0;
    count[s] = 1;

    pq.push({s, 0});

    while(!pq.empty()) {
        Node curr = pq.top();
        pq.pop();
        int id = curr.id;
        int currdist = curr.dist;
        if(currdist > dist[id]) { // normally it should be currdist == dist[id]
            continue;
        }

        for(const auto& edge: edgeSet[id]) {
            int v = edge.to;
            int w = edge.weight;

            if(dist[v] > dist[id] + w) {
                dist[v] = dist[id] + w;
                count[v] = count[id];
                pq.push({v, dist[v]});
            } else if(dist[v] == dist[id] + w) {
                count[v] += count[id];
            }
        }

    }
}

int main() {
    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<Edge>> edgeSet(n + 1);

    for(int i = 0; i < m; i++) {
        int u, v ,w;
        cin >> u >> v >> w;
        edgeSet[u].push_back({v, w});
    }
    
    vector<int> dist(n + 1, INF);
    
    vector<long long> count(n + 1, 0);

    solve(s, dist, count, edgeSet);

    for(int i = 1; i <= n; i++) {
        if(i == s) {
            continue;
        }
        cout << dist[i] << " " << count[i] << "\n";
    }

    return 0;
}