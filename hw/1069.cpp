#include <bits/stdc++.h>

using namespace std;

struct Maxheap {
    vector<int> heap;

    Maxheap(int k) {
        heap.reserve(k + 2);
        heap.push_back(0);
    }

    void shift_up(int pos) {
        int val = heap[pos];
        while(pos > 1 && val > heap[pos / 2]) {
            heap[pos] = heap[pos / 2];
            pos = pos / 2;
        }
        heap[pos] = val;
    }

    void shift_down(int pos) {
        int size = heap.size() - 1;
        int val = heap[pos];

        while(pos * 2 <= size) {
            int child = pos * 2;

            if(child + 1 <= size && heap[child] < heap[child + 1]) {
                child++;
            }

            if(val < heap[child]) {
                heap[pos] = heap[child];
                pos = child;
            } else {
                break;
            }
        }
        heap[pos] = val;
    }

    void push(int n) {
        int pos = heap.size();
        heap.push_back(n);
        shift_up(pos);
    }

    bool empty() {
        return heap.size() == 1;
    }

    void pop() {
        if(empty()) {
            return;
        }
        int last_pos = heap.size() - 1;
        swap(heap[1], heap[last_pos]);

        heap.pop_back();
        shift_down(1);
    }

    int top() {
        return heap[1];
    }
};

int main()  {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);    


    int n, k;
    cin >> n >> k;
    Maxheap pq(k);


    for(int i = 0; i < k; i++) {
        int val;
        cin >> val;
        pq.push(val);
    }
    for(int i = k; i < n; i++) {
        int val;
        cin >> val;
        if(pq.top() > val) {
            pq.pop();
            pq.push(val);
        }
    }

    cout << pq.top() << "\n";
    return 0;
}
