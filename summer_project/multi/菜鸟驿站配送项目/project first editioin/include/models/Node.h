#ifndef NODE_H
#define NODE_H

namespace models {
    
    struct Node {
        int id;
        double x;
        double y;
        bool is_station;
        

        Node() : id(-1), x(0.0), y(0.0), is_station(false) {}
        Node(int i, double cx, double cy, bool s) {
            id = i;
            x = cx;
            y = cy;
            is_station = s;
        }
    };


}

#endif