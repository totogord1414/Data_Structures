#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

#include "../models/Node.h"
#include "../models/Edge.h"

 namespace data_structures {
    
    class Graph {
    private:
        std::vector<models::Node> nodes;
        
        std::vector<std::vector<models::Edge>> adj;

    public:

        Graph() {}

        void init(int n) {
            nodes.resize(n);
            adj.resize(n);
        }

        void setNode(int id, double x, double y, bool is_station) {
            if (id >= 0 && id < nodes.size()) {
                nodes[id] = models::Node(id, x, y, is_station);
            }
        }

        void addEdge(int u, int v, double weight) {

            adj[u].push_back(models::Edge(v, weight));
            adj[v].push_back(models::Edge(u, weight));
        }

        int getNodeCount() const {
            return nodes.size();
        }

        std::vector<models::Edge> getNeightors(int u) const {
            return adj[u];
        }
    };
 }

#endif
