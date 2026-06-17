#include <bits/stdc++.h>

using namespace std;

struct MinHeap {
    vector<int> heap;

    MinHeap() {
        heap.push_back(0);
    }

    void shift_up(int pos) {
        while(pos> 1 && heap[pos / 2] > heap[pos]) {
            swap(heap[pos / 2], heap[pos]);
            pos = pos / 2;
        }
    }

    void shift_down(int pos) {
        int size = heap.size() - 1;

        while(pos * 2 <= size) {
            int child = pos * 2;
            
            if(pos * 2 + 1 <= size && heap[child + 1] < heap[child]) {
                child++;
            }

            if(heap[pos] > heap[child]) {
                swap(heap[pos], heap[child]);
                pos = child;
            } else {
                break;
            }
        }
    }

    bool empty() {
        return heap.size() == 1;
    }

    void push(int num) {
        heap.push_back(num);
        shift_up(heap.size() - 1);
    }

    void pop() {
        if(empty()) {
            return;
        } else {
            swap(heap[1], heap[heap.size() - 1]);
            heap.pop_back();

            if(!empty()) {
                shift_down(1);
            }
        }
    }

    int top() {
        return heap[1];
    }

};




int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;

    cin >> n >> m ;

    int actual_m = min(m, n);
    MinHeap mh;

    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if(i < actual_m) {
            mh.push(x);
        } else {
            if(x > mh.top()) {
                mh.pop();
                mh.push(x);
            }
        }
    }

    vector<int> result(actual_m);

    for(int i = actual_m - 1; i >= 0; i--) {
        result[i] = mh.top();
        mh.pop();
    }

    for(int i = 0; i < actual_m; i++) {
        cout << result[i] << (i == actual_m - 1 ? "\n" : " ");
    }

    return 0;
}