#include <bits/stdc++.h>

using namespace std;

struct Edge
{
    int to;
    int cost;

    Edge(int t, int c)
    {
        to = t;
        cost = c;
    }
};

struct Comparator
{
    bool operator()(const Edge& a,const Edge& b)
    {
        return a.cost > b.cost;
    }
};

int solve(int N, vector<vector<Edge>>& graph)
{
    priority_queue<Edge, vector<Edge>, Comparator> pq;
    int currCount = 1;
    vector<bool> visited(N + 1, false);
    visited[1] = true;
    int minCost = 0;
    for(Edge e: graph[1])
    {
        pq.push(e);
    }
    
    while(currCount < N && !pq.empty())
    {
        Edge e = pq.top();
        pq.pop();
        if(!visited[e.to])
        {
            visited[e.to] = true;
            minCost += e.cost;
            currCount++;
            for(Edge ed: graph[e.to])
            {
                if(!visited[ed.to])
                {
                    pq.push(ed);
                }
            }
        }
    }

    if(currCount < N)
    {
        return -1;
    }
    else
    {
        return minCost;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;
    vector<vector<Edge>> graph(N + 1);
    for(int i = 0; i < M; i++)
    {
        int u, v, cost;
        cin >> u >> v >> cost;
        graph[u].push_back({v, cost});
        graph[v].push_back({u, cost});
    }

    int ans = solve(N, graph);

    cout << ans << "\n";

    return 0;
}