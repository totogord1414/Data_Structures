#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>

namespace data_structures {
    class MinHeap {
    
    private:
        struct Element {
            int id;
            double dist;

            Element(int _id, double _dist) {
                id = _id;
                dist = _dist;
            }
        };

        int heap_size;

        std::vector<Element> heap;
        //the pos of each id 
        std::vector<int> pos;

        void shiftUp(int index);

        void shiftDown(int index);

        void swapElements(int i, int j);

    public:
        
        MinHeap(int n);

        bool empty() const;

        void pushOrUpdate(int id, double dist);

        int pop();
    };
}


#endif
