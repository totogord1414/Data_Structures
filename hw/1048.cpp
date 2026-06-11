#include <bits/stdc++.h>

const int INF = 1e8;

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);    


    int N, M;
    cin >> N >> M;
    vector<vector<int>> dist(N + 1, vector<int>(N + 1, INF));

    for(int i = 1; i <= N; i++) {
        dist[i][i] = 0;
    }

    for(int i = 0; i < M; i++) {
        int a, b, l;
        cin >> a >> b >> l;
        dist[a][b] = min(dist[a][b], l);
        dist[b][a] = dist[a][b];
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            for(int k = 1; k <= N; k++) {
                dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
            }
        }
    }

    int bestAnimal = 0;
    int minAllLength = INF;

    for(int i = 1; i <= N; i++) {
        int maxLength = 0;
        for(int j = 1; j <= N; j++) {
            maxLength = max(maxLength, dist[i][j]);
        }

        if(maxLength >= INF) {
            continue;
        }

        if(maxLength < minAllLength) {
            bestAnimal = i;
            minAllLength = maxLength;
        }
    }

    if(bestAnimal == 0) {
        cout << 0 << "\n";
    } else {
        cout << bestAnimal << " " << minAllLength << "\n";
    }
    
}