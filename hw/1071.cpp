#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int solve(int n, const vector<vector<int>>& graph) {
    vector<int> dist(n + 1, INF);
    vector<bool> visited(n + 1, false);
    dist[1] = 0;
    int cost = 0;

    for(int i = 0; i < n; i++) {
        int min_city = -1;
        int lowest_cost = INF;
        for(int j = 1; j <= n; j++) {
            if(!visited[j] && dist[j] < lowest_cost) {
                lowest_cost = dist[j];
                min_city = j;
            }

        }

        if(min_city == -1) {
            return -1;
        }

        visited[min_city] = true;
        cost += lowest_cost;

        for(int v = 1; v <= n; v++) {
            if(!visited[v] && graph[v][min_city] < dist[v]) {
                dist[v] = graph[v][min_city];
            }
        }

    }


    return cost;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);   

    int n;
    cin >> n;

    int m = n * (n - 1) / 2;
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, INF));

    for(int i = 0; i < m; i++) {
        int u, v, c, b;
        cin >> u >> v >> c >> b;

        if(b == 1) {
            c = 0;
        }

        graph[u][v] = c;
        graph[v][u] = c;
    }

    int cost = solve(n, graph);

    cout << cost << "\n";
}