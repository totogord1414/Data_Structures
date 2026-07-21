#include "../../include/core/Router.h"
#include "../../include/data_structures/MinHeap.h"
#include <algorithm> // 用来 reverse 数组

const int INF = 1e9;


namespace core {
    Router::PathResult Router::getShortestPath(int start, int end) {
        int n = graph.getNodeCount();
        
        std::vector<double> dist(n, INF);

        std::vector<int> prev(n, -1);

        data_structures::MinHeap heap(n);

        dist[start] = 0.0;
        heap.pushOrUpdate(start, 0.0);

        while (!heap.empty()) {
            int u = heap.pop();

            if (u == end) {
                break;
            }

            for (const auto& edge : graph.getNeightors(u)) {
                int v = edge.to;
                double weight = edge.weight;

                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;

                    heap.pushOrUpdate(v, dist[v]);
                }
            }
        }

        PathResult result;
        result.distance = dist[end];
        if (dist[end] == INF) {
            return result;
        }

        std::vector<int> path;
        int currID = end;
        while (currID != -1) {
            path.push_back(currID);
            currID = prev[currID];
        }

        reverse(path.begin(), path.end());

        result.path = path;
        return result;
    }

    std::vector<double> Router::getAllShortestDistances(int start) {
        int n = graph.getNodeCount();
        std::vector<double> dist(n, INF);
        data_structures::MinHeap heap(n);

        dist[start] = 0.0;
        heap.pushOrUpdate(start, 0.0);

        while (!heap.empty()) {
            int u = heap.pop();

            for (const auto& edge : graph.getNeightors(u)) {
                int v = edge.to;
                double weight = edge.weight;

                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    heap.pushOrUpdate(v, dist[v]);
                }
            }
        }

        return dist;
    }

}