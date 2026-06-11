#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int total_tasks;
    if (!(cin >> total_tasks)) return 0;

    // task_graph[u] stores all tasks that directly depend on task 'u'
    vector<vector<int>> task_graph(total_tasks + 1);
    
    // in_degree[u] represents the number of uncompleted prerequisites for task 'u'
    vector<int> in_degree(total_tasks + 1, 0);

    // Queue to store tasks that are ready to be executed (in-degree == 0)
    queue<int> ready_tasks;

    // 1. Build the graph and initialize in-degrees
    for (int task_id = 1; task_id <= total_tasks; ++task_id) {
        int num_dependencies;
        cin >> num_dependencies;
        
        in_degree[task_id] = num_dependencies;
        
        // If a task has no dependencies, it can be executed immediately
        if (num_dependencies == 0) {
            ready_tasks.push(task_id);
        }

        for (int j = 0; j < num_dependencies; ++j) {
            int pre_task;
            cin >> pre_task;
            
            // Directed edge: pre_task -> task_id
            // Indicates that completing 'pre_task' unlocks 'task_id'
            task_graph[pre_task].push_back(task_id);
        }
    }

    int completed_task_count = 0;

    // 2. Process tasks using BFS (Kahn's Algorithm)
    while (!ready_tasks.empty()) {
        int current_task = ready_tasks.front();
        ready_tasks.pop();
        
        completed_task_count++;

        // Iterate through all subsequent tasks that depend on the current task
        for (int next_task : task_graph[current_task]) {
            // Remove one prerequisite "lock" from the dependent task
            in_degree[next_task]--;
            
            // If all prerequisites are met, add the task to the ready queue
            if (in_degree[next_task] == 0) {
                ready_tasks.push(next_task);
            }
        }
    }

    // 3. Cycle Detection / Feasibility Check
    // If completed tasks equal total tasks, the schedule is feasible (no cycles)
    if (completed_task_count == total_tasks) {
        cout << 1 << "\n";
    } else {
        cout << 0 << "\n";
    }

    return 0;
}