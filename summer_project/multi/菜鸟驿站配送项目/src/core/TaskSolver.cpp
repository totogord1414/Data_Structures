#include "../../include/core/TaskSolver.h"
#include <iostream>

namespace core {

    TaskSolver::TaskSolver(const data_structures::Graph& g, 
                           const std::vector<models::Package>& p, 
                           const models::Car& c) 
        : graph(g), packages(p), car(c), router(g) {
    }

    void TaskSolver::solveT1(int startNode, int endNode) {
        Router::PathResult result = router.getShortestPath(startNode, endNode);
        
        std::cout << "Shortest distance from " << startNode << " to " << endNode << ": " 
                  << result.distance << std::endl;
        
        std::cout << "Path: ";
        for (size_t i = 0; i < result.path.size(); ++i) {
            std::cout << result.path[i];
            if (i < result.path.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }

    void TaskSolver::solveT2() {
        // TODO: Implement T2 logic
        std::cout << "T2 not implemented yet." << std::endl;
    }

    void TaskSolver::solveT3() {
        // TODO: Implement T3 logic
        std::cout << "T3 not implemented yet." << std::endl;
    }

}
