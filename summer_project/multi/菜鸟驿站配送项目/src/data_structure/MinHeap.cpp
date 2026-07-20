#include "../../include/data_structures/MinHeap.h"
#include <algorithm>
#include <utility>

namespace data_structures {

    MinHeap::MinHeap(int n) {
    heap_size = 0;
    heap.reserve(n + 1);
    heap.push_back({-1, 0.0});

    pos.resize(n, -1);
    }

    bool MinHeap::empty() const { return heap_size == 0; }

    void MinHeap::swapElements(int i, int j) {
    std::swap(heap[i], heap[j]);
    pos[heap[i].id] = i;
    pos[heap[j].id] = j;
    }

    void MinHeap::shiftUp(int index) {
    while (index > 1) {
        int p_index = index / 2;
        if (heap[index].dist < heap[p_index].dist) {
        swapElements(index, p_index);
        index = p_index;
        } else {
        break;
        }
    }
    }

    void MinHeap::shiftDown(int index) {
    int size = heap.size();

    while (2 * index < size) {
        int lchild = 2 * index;
        int rchild = 2 * index + 1;
        if (rchild >= size)
        rchild--;

        int minChild;
        if (heap[lchild].dist < heap[rchild].dist) {
        minChild = lchild;
        } else {
        minChild = rchild;
        }

        if (heap[minChild].dist < heap[index].dist) {
        swapElements(minChild, index);
        index = minChild;
        } else {
        break;
        }
    }
    }

    void MinHeap::pushOrUpdate(int id, double dist) {
    if (pos[id] == -1) {
        heap.push_back({id, dist});
        heap_size++;
        pos[id] = heap_size;
        shiftUp(heap_size);
    } else {
        int currPos = pos[id];
        if (heap[currPos].dist > dist) {
        heap[currPos].dist = dist;
        shiftUp(currPos);
        }
    }
    }

    int MinHeap::pop() {
    int res = heap[1].id;
    pos[res] = -1;

    if (heap_size > 1) {
        heap[1] = heap[heap_size];
        pos[heap[1].id] = 1;
    }

    heap.pop_back();

    heap_size--;

    if (heap_size > 0) {
        shiftDown(1);
    }

    return res;
    }
} // namespace data_structures
