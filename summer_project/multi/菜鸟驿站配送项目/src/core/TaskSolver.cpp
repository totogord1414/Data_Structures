#include "../../include/core/TaskSolver.h"
#include "models/Package.h"
#include <iostream>
#include <algorithm>

const int INF = 1e9;

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
        
        std::vector<models::Package> pending = packages;
        
        std::sort(pending.begin(), pending.end(), [](const models::Package& a, const models::Package& b) {
            return a.arrive_time < b.arrive_time;
        });

        double totalDissatisfaction = 0.0;
        double currentTime = 0.0;

        while (!pending.empty()) {
            std::vector<models::Package> currCarLoad;
            double currLoadWeight = 0.0;
            double max_time = 0.0;

            while (!pending.empty() && currLoadWeight + pending.front().weight <= car.capacity) {
                currLoadWeight += pending.front().weight;
                max_time = pending.front().arrive_time;
                currCarLoad.push_back(pending.front());
                pending.erase(pending.begin());

            }

            currentTime = std::max(max_time, currentTime);

            int currPos = 0;

            while (!currCarLoad.empty()) {
                int bestIndex = -1;
                double shortestDist = INF;
                for (int i = 0; i < currCarLoad.size(); i++) {
                    double dist = router.getShortestPath(currPos, currCarLoad[i].dest).distance;

                    if (dist < shortestDist) {
                        shortestDist = dist;
                        bestIndex = i;
                    }
                }

                models::Package targetPackage = currCarLoad[bestIndex];

                currentTime += shortestDist / car.speed;

                totalDissatisfaction += (currentTime - targetPackage.arrive_time);
                currPos = targetPackage.dest;
                currCarLoad.erase(currCarLoad.begin() + bestIndex);
            }

            double dist = router.getShortestPath(currPos, 0).distance;

            currentTime += dist / car.speed;
        }

        std::cout << "The total dissatisfactio through T2's algorithm is: " << totalDissatisfaction << std::endl;
    }

    void TaskSolver::solveT3() {
        // TODO: Implement T3 logic
        std::cout << "T3 not implemented yet." << std::endl;
    }

}
