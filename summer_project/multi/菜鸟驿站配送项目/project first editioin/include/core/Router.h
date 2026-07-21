#ifndef ROUTER_H
#define ROUTER_H

#include "../data_structures/Graph.h"
#include <vector>

namespace core {

    class Router {
    private:
        const data_structures::Graph& graph;

    public:
        struct PathResult {
            double distance;           
            std::vector<int> path;  
        };

        Router(const data_structures::Graph& g) : graph(g) {}

        // Calculate shortest path to a specific end node
        PathResult getShortestPath(int start, int end);
        
        // Calculate shortest distances from start to ALL nodes
        std::vector<double> getAllShortestDistances(int start);
    };

}

#endif
