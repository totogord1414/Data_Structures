#include <bits/stdc++.h>

using namespace std;

int bfs(int startNode, vector<bool>& visited, vector<vector<int>>& side)
{
    int visitedNode = 1;
    visited[startNode] = true;
    queue<int> nodeLevel;
    queue<int> Node;
    Node.push(startNode);
    nodeLevel.push(0);

    while(!Node.empty())
    {
        int currNode = Node.front();
        int currLevel = nodeLevel.front();
        Node.pop();
        nodeLevel.pop();

        for(int i: side[currNode])
        {
            if(!visited[i])
            {
                visited[i] = true;
                visitedNode++;
                if(currLevel < 5)
                {
                    Node.push(i);
                    nodeLevel.push(currLevel + 1);
                }
            }
        }
    }

    return visitedNode;
}




int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> side(N + 1);
    for(int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        side[u].push_back(v);
        side[v].push_back(u);
    }

    for(int i = 1; i <= N; i++)
    {
        int level = 6;
        vector<bool> visited(N + 1, false);
        int visitedNode = bfs(i, visited, side);
        double rate = (visitedNode * 100.0) / N ;
        printf("%d: %.2f%%\n", i, rate);
    }

    return 0;
}
