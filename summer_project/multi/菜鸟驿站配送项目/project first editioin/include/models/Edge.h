#ifndef EDGE_H
#define EDGE_H

namespace models {

    struct Edge {
        int to;        
        double weight; 

        Edge() : to(-1), weight(0.0) {}
        Edge(int _to, double _weight) : to(_to), weight(_weight) {}
    };

}

#endif