#include <bits/stdc++.h>

using namespace std;


void dfs(int node, vector<vector<int>>& side, vector<bool>& visited, vector<int>& ans, int& nodeCount)
{
    visited[node] = true;
    nodeCount++;
    ans.push_back(node);
    for(int i: side[node])
    {
        if(!visited[i])
        {
            dfs(i, side, visited, ans, nodeCount);
            ans.push_back(node);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> ans;
    int N, M, startNode;
    cin >> N >> M >> startNode;

    vector<vector<int>> side(N + 1 );
    vector<bool> visited(N + 1, false);

    for(int i = 0 ; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        side[u].push_back(v);
        side[v].push_back(u);
    }
    int nodeCount = 0;
    for(int i = 1; i <= N; i++)
    {
        sort(side[i].begin(), side[i].end());
    }

    dfs(startNode, side, visited, ans, nodeCount);
    
    for(int i: ans)
    {
        cout << i << " ";
    }

    if(nodeCount != N)
    {
        cout << 0 << "\n";
    }


    return 0;
}