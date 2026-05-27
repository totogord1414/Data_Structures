#include <bits/stdc++.h>

using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};//direction vector

int dfs(int x, int y, vector<vector<bool>>& visited, vector<string>& graph)
{
    visited[x][y] = true;
    int currentSize = 1;
    int H = graph.size();
    int W = visited[0].size();
    for(int i = 0; i < 4; i++)
    {
        int px = x + dx[i];
        int py = y + dy[i];
        if(px >= 0 && px < H && py >= 0 && py < W && !visited[px][py] && graph[px][py] == '*')
        {
            currentSize += dfs(px, py, visited, graph);
        }
    }

    return currentSize;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int W, H;
    cin >> W >> H;
    vector<vector<bool>> visited(H, vector<bool>(W, false));
    
    vector<string> graph(H);

    for(int i = 0; i < H; i++)
    {
        cin >> graph[i];
    }

    int max_area = 0;
    
    
    for(int i = 0; i < H; i++)
    {
        for(int j = 0; j < W; j++)
        {
            if(!visited[i][j] && graph[i][j] == '*')
            {
                max_area = max(max_area, dfs(i, j, visited, graph));
            }
        }
    }

    cout << max_area << endl;

    return 0;
}
