#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

struct Edge{
    int to;
    int length;
    int cost;
};

struct State{
    int u;
    int length;
    int cost;
};

struct Comparator{
    bool operator()(const State& a, const State& b) {
        if(a.length != b.length) {
            return a.length > b.length;
        } else {
            return a.cost > b.cost;
        }
    }
};
pair<int, int> solve(vector<vector<Edge>>& Graph, int s, int d, int n) {
    priority_queue<State, vector<State>, Comparator> pq;
    vector<bool> hasVisited(n, false);
    vector<int> dist(n, INF);
    vector<int> fee(n, INF);

    pq.push({s, 0, 0});

    dist[s] = 0;
    fee[s] = 0;
    // you have to remember to initiate!!!!!

    while(!pq.empty()) {
        State curr = pq.top();
        pq.pop();
        int u = curr.u;
        int cost = curr.cost;
        int length = curr.length;

        if(hasVisited[u]) {
            continue;
        }   else {
            hasVisited[u] = true;

            if(u == d) {
                break;
            }

            for(const auto& edge: Graph[u]) {
                int to = edge.to;
                if(edge.length + length < dist[to]) {
                    dist[to] = edge.length + length;
                    fee[to] = edge.cost + cost;
                    pq.push({to, dist[to], fee[to]});
                } else if(edge.length + length == dist[to] && edge.cost + cost < fee[to]) {
                    fee[to] = edge.cost + cost;
                    pq.push({to, dist[to], fee[to]});
                }
            }
            
        }
    }

    return {dist[d], fee[d]};
};

int main() {
    int n, m, s, d;
    cin >> n >> m >> s >>d;

    vector<vector<Edge>> Graph(n);

    for(int i = 0; i < m; i++) {
        int u, v, length, cost;
        cin >> u >> v >> length >> cost;
        Graph[u].push_back({v, length, cost});
        Graph[v].push_back({u, length, cost});
    }

    pair<int, int> result = solve(Graph, s, d, n);

    cout << result.first << " " << result.second << "\n";

    return 0;
}