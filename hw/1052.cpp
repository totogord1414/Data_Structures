#include <bits/stdc++.h>

using namespace std;

struct Task{
    int next_event;
    int duration;
    int input_index;
};

struct CriticalActivity{
    int start_event;
    int end_event;
    int input_index;
};

bool judge(int n, const vector<vector<Task>>& Graph, vector<int>& earliest_time, vector<int>& in_degree, vector<int>& topological_order) {
    int completed_node = 0;
    queue<int> ready_evenets;

    for(int i = 1; i <= n; i++) {
        if(in_degree[i] == 0) {
            ready_evenets.push(i);
        }
    }

    while(!ready_evenets.empty()) {
        int current = ready_evenets.front();
        topological_order.push_back(current);
        ready_evenets.pop();
        completed_node++;

        for(const auto& v: Graph[current]) {
            int event = v.next_event;
            in_degree[event]--;
            if(in_degree[event] == 0) {
                ready_evenets.push(event);
            }

            earliest_time[event] = max(earliest_time[event], earliest_time[current] + v.duration);
        }
    }

    return completed_node == n;
}

void backward_pass(int n, vector<int>& topological_order, vector<int>& latest_time,const vector<vector<Task>>& Graph) {
    for(int i = n - 1; i >= 0; i--) {
        int current = topological_order[i];
        for(const auto& v: Graph[current]) {
            latest_time[current] = min(latest_time[current], latest_time[v.next_event] - v.duration);
        }
    }
}

bool cmp(const CriticalActivity& a, const CriticalActivity& b) {
    if(a.start_event == b.start_event) {
        return a.input_index > b.input_index;
    } else {
        return a.start_event < b.start_event;
    }
}

void find_path(int n, vector<int>& earliest_time, vector<int>& latest_time, vector<CriticalActivity>& CriticalPath, const vector<vector<Task>>& Graph) {
    for(int current = 1; current <= n; current++) {
        for(const auto& task: Graph[current]) {
            int event = task.next_event;
            int duration = task.duration;
            
            if(earliest_time[current] == latest_time[event] - duration) {
                CriticalPath.push_back({current, event, task.input_index});
            }
        }
    }

    sort(CriticalPath.begin(), CriticalPath.end(), cmp);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<Task>> Graph(n + 1);
    vector<int> in_degree(n + 1);

    vector<int> earliest_time(n + 1, 0);
    vector<int> topological_order;
    for(int i = 1; i <= m ; i++) {
        int start, end, duration;
        cin >> start >> end >> duration;

        Graph[start].push_back({end, duration, i});
        in_degree[end]++;
    }
    
    if(!judge(n, Graph, earliest_time, in_degree, topological_order)) {
        cout << 0 << "\n";
    } else {
        int total_time = 0;
        for(const auto& time: earliest_time) {
            total_time = max(time, total_time);
        }
        
        
        vector<int> latest_time(n + 1, total_time);
        backward_pass(n, topological_order, latest_time, Graph);
        vector<CriticalActivity> CriticalPath;

        find_path(n, earliest_time, latest_time, CriticalPath, Graph);

        cout << total_time << "\n";
        for(int i = 0; i < CriticalPath.size(); i++) {
            cout << CriticalPath[i].start_event << "->" << CriticalPath[i].end_event << "\n";
        }       
    }
    
    return 0;
}