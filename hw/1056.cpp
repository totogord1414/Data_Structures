#include <bits/stdc++.h>

using namespace std;

struct Project{
    long long cost;
    long long value;
};

bool cmp(const Project& a, const Project& b) {
    return a.cost < b.cost;
}



long long solve(vector<Project>& projects, const long long w, const long long k, const long long n) {
    priority_queue<long long> pq;

    int pointer = 0;
    long long wealth = w;

    for(int i = 0; i < k; i++) {
        while(pointer < n && projects[pointer].cost <= wealth) {
            pq.push(projects[pointer].value);
            pointer++;
        }

        if(pq.empty()) {
            break;
        }

        long long best = pq.top();
        pq.pop();
        wealth += best;
    }

    return wealth;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    long long n, w, k;
    cin >> n >> w >> k;

    vector<Project> projects(n);
    for(int i = 0; i < n; i++) {
        long long cost, value;
        cin >> cost >> value;
        projects[i] = {cost, value};
    }
    
    sort(projects.begin(), projects.end(), cmp);

    long long wealth = solve(projects, w, k, n);

    cout << wealth << "\n";

    return 0;
}