#include <bits/stdc++.h>

using namespace std;

//initiate the offset

const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[8] = {0, 1, -1, 1, -1, 0, 1, -1};

void solve(const pair<int, int>& start, const pair<int, int>& end, const vector<string>& maze, int n) {
    if(maze[start.first][start.second] == '1' || maze[end.first][end.second] == '1') {
        cout << "no\n";
        return;
    }


    queue<pair<int, int>> node_set;
    vector<vector<bool>> visited(n, vector<bool>(n, false));

    node_set.push(start);
    visited[start.first][start.second] = true;

    while(!node_set.empty()) {
        pair<int, int> curr = node_set.front();
        node_set.pop();
        if(curr == end) {
            cout << "yes\n";
            return;
        }

        for(int i = 0; i < 8; i++) {
            int x = curr.first + dx[i];
            int y = curr.second + dy[i];

            if(x >= 0 && x < n && y >= 0 && y < n && !visited[x][y] && maze[x][y] == '0') {
                visited[x][y] = true;
                node_set.push({x, y});
            }
        }
    }

    cout << "no\n";
}

int main() {
    int n;
    cin >> n;
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    pair<int, int> start = {x1, y1};
    pair<int, int> end = {x2, y2};

    vector<string> maze(n);
    for(int i = 0; i < n; i++) {
        cin >> maze[i];
    }
    
    solve(start, end, maze, n);

    return 0;
}