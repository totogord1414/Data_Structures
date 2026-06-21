#include <bits/stdc++.h>

using namespace std;

int bfs(int s, int e) {
    if(s >= e) {
        return s - e;
    }

    vector<int> visited_time(e + 3, -1);
    queue<int> q;
    q.push(s);
    visited_time[s] = 0;

    while(!q.empty()) {
        int curr = q.front();
        q.pop();

        int next_pos[3] = {curr - 1, curr + 1, curr * 2};
        for(int p: next_pos) {
            if(p >= 0 && p <= e + 2 && visited_time[p] == -1) {
                q.push(p);
                visited_time[p] = visited_time[curr] + 1;
            }

            if(p == e) {
                return visited_time[p];
            }
        }
    }

    return -1;
}

int main() {
    int s, e;
    cin >> s >> e;

    cout << bfs(s, e) << "\n";

    return 0;
}
