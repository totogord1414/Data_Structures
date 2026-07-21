#include "../../include/core/TaskSolver.h"
#include "models/Package.h"
#include <iostream>
#include <algorithm>
#include <vector>

const int INF = 1e9;

namespace core {

    TaskSolver::TaskSolver(const data_structures::Graph& g, 
                           const std::vector<models::Package>& p, 
                           const models::Car& c) 
        : graph(g), packages(p), car(c), router(g) {
        
        // Initialize cache table with size n x n, default value -1.0
        int n = graph.getNodeCount();
        distCache.resize(n, std::vector<double>(n, -1.0));
    }





    double TaskSolver::getDistance(int u, int v) {
        if (u == v) return 0.0;
        
        // If not calculated yet, run Dijkstra once and cache the entire row
        if (distCache[u][v] < 0) {
            std::vector<double> allDists = router.getAllShortestDistances(u);
            for (size_t i = 0; i < allDists.size(); ++i) {
                distCache[u][i] = allDists[i];
                distCache[i][u] = allDists[i]; // Graph is undirected
            }
        }
        return distCache[u][v];
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
                    double dist = getDistance(currPos, currCarLoad[i].dest);

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

            double dist = getDistance(currPos, 0);

            currentTime += dist / car.speed;
        }

        std::cout << "The total dissatisfactio through T2's algorithm is: " << totalDissatisfaction << std::endl;
    }




    


    double TaskSolver::simulateSingleCar(const std::vector<models::Package>& p, int& timeOutCount, Strategy strategy) {
        std::vector<models::Package> pending = p;

        std::sort(pending.begin(), pending.end(), [](const models::Package& a, const models::Package& b) {
            return a.deadline < b.deadline;
        });

        double totalCost = 0.0;
        timeOutCount = 0;
        double currentTime = 0;

        while (!pending.empty()) {
            std::vector<models::Package> currCarLoad;
            double currLoadWeight = 0.0;

            while (!pending.empty() && currLoadWeight + pending.front().weight < car.capacity) {
                currCarLoad.push_back(pending.front());
                currLoadWeight += pending.front().weight;
                pending.erase(pending.begin());
            }

            int currPos = 0;

            while (!currCarLoad.empty()) {
                int bestIndex = -1;
                double bestScore = -1.0;
                double chosenDist = 0.0;

                for (int i = 0; i < currCarLoad.size(); i++) {
                    double dist = getDistance(currPos, currCarLoad[i].dest);

                    double score = 0.0;
                    if (strategy == Strategy::NEAREST_NEIGHBOR) {
                        score = 1.0 / (dist + 0.00001); // Distance only (Nearest first)
                    } else if (strategy == Strategy::HEAVIEST_FIRST) {
                        score = currCarLoad[i].weight; // Weight only (Heaviest first)
                    } else if (strategy == Strategy::COMPOSITE) {
                        score = currCarLoad[i].weight / (dist + 0.00001); // Combined strategy
                    }
                    
                    if (score > bestScore) {
                        bestScore = score;
                        chosenDist = dist;
                        bestIndex = i;
                    }
                }

                models::Package targetPackage = currCarLoad[bestIndex];

                totalCost += chosenDist * (car.car_weight + currLoadWeight);

                currentTime += chosenDist / car.speed;
                currPos = targetPackage.dest;
                currLoadWeight -= targetPackage.weight;

                if (currentTime > targetPackage.deadline) {
                    timeOutCount++;
                }

                currCarLoad.erase(currCarLoad.begin() + bestIndex);
            }

            double returnDist = getDistance(currPos, 0);

            totalCost += returnDist * car.car_weight;
            currentTime += returnDist / car.speed;
        }
        
        return totalCost;
    }







    void TaskSolver::solveT3() {
        int timeOutCount = 0;
        double totalCost = simulateSingleCar(packages, timeOutCount);

        std::cout << "T3 whole cost: " << totalCost << std::endl;
        std::cout << "T3 time out packages count: " << timeOutCount << std::endl;
    }








    void TaskSolver::solveT4(const std::vector<int>& inputNodes) {
        std::vector<int> returnNodes; 
        int maxNode = graph.getNodeCount() - 1;

        for (int node : inputNodes) {
            if (node <= 0 || node > maxNode) {
                std::cout << "Warning!!! Node " << node << " is out of bounds or invalid (station). Ignored." << std::endl;
            } else {
                returnNodes.push_back(node);
            }
        }

        if (returnNodes.empty()) {
            std::cout << "No valid return nodes provided." << std::endl;
            return;
        }

        if (returnNodes.size() <= 10) {
            //brute force
            //at first we use dfs here, but AI advise us to use this next_permutation function so that the code is easier to read and less errors might be made
            
            std::sort(returnNodes.begin(), returnNodes.end());
            
            double minTotalDist = 1e9;
            std::vector<int> bestRoute;

            do {
                double currentDist = 0.0;
                int currPos = 0; 
                
                for (int dest : returnNodes) {
                    currentDist += getDistance(currPos, dest);
                    currPos = dest;
                }

                currentDist += getDistance(currPos, 0);

                if (currentDist < minTotalDist) {
                    minTotalDist = currentDist;
                    bestRoute = returnNodes;
                }
            } while (std::next_permutation(returnNodes.begin(), returnNodes.end()));

            std::cout << "[Exact Solver] T4 Min Return Dist: " << minTotalDist << std::endl;
            std::cout << "Best Route: 0 -> ";
            for (int node : bestRoute) std::cout << node << " -> ";
            std::cout << "0" << std::endl;

        } else {
            //Greedy
            
            double totalDist = 0.0;
            int currPos = 0;
            std::vector<int> route;

            while (!returnNodes.empty()) {
                int bestIndex = -1;
                double shortestDist = 1e9;
                
                for (int i = 0; i < returnNodes.size(); ++i) {
                    double d = getDistance(currPos, returnNodes[i]);

                    if (d < shortestDist) {
                        shortestDist = d;
                        bestIndex = i;
                    }
                }
                
                currPos = returnNodes[bestIndex];
                route.push_back(currPos);
                totalDist += shortestDist;
                
                returnNodes.erase(returnNodes.begin() + bestIndex);
            }
            
            // Build the full cycle starting and ending at 0
            std::vector<int> fullRoute = {0};
            fullRoute.insert(fullRoute.end(), route.begin(), route.end());
            fullRoute.push_back(0);

            bool improved = true;
            int max_iters = 2000;
            while (improved && max_iters-- > 0) {
                improved = false;
                // Try swapping every possible pair of edges (i-1 to i) and (j to j+1)
                for (int i = 1; i < fullRoute.size() - 2; ++i) {
                    for (int j = i + 1; j < fullRoute.size() - 1; ++j) {
                        int A = fullRoute[i - 1];
                        int B = fullRoute[i];
                        int C = fullRoute[j];
                        int D = fullRoute[j + 1];

                        double oldDist = getDistance(A, B) + getDistance(C, D);
                        double newDist = getDistance(A, C) + getDistance(B, D); 

                        if (newDist < oldDist - 1e-6) { 

                            // Reversing the subroute effectively swaps the edges
                            std::reverse(fullRoute.begin() + i, fullRoute.begin() + j + 1);
                            improved = true;
                        }
                    }
                }
            }

            totalDist = 0.0;
            for (int i = 0; i < fullRoute.size() - 1; ++i) {
                totalDist += getDistance(fullRoute[i], fullRoute[i+1]);
            }

            std::cout << "[Not So Exact Solver with 2-Opt] T4 Return Dist: " << totalDist << std::endl;
            std::cout << "Route: ";
            for (int i = 0; i < fullRoute.size(); ++i) {
                std::cout << fullRoute[i] << (i == fullRoute.size() - 1 ? "" : " -> ");
            }
            std::cout << std::endl;
        }
    }







    void TaskSolver::solveT5() {
        if (packages.size() < 2) {
            std::cout << "Not enough packages for two cars." << std::endl;
            return;
        }

        // 1. Find Anchor Points
        int anchor1_idx = 0;
        int anchor2_idx = 1;
        double max_dist = -1.0;

        for (int i = 0; i < packages.size(); ++i) {
            for (int j = i + 1; j < packages.size(); ++j) {
                double d = getDistance(packages[i].dest, packages[j].dest);
                if (d > max_dist) {
                    max_dist = d;
                    anchor1_idx = i;
                    anchor2_idx = j;
                }
            }
        }

        int anchor1 = packages[anchor1_idx].dest;
        int anchor2 = packages[anchor2_idx].dest;

        // 2. Cluster Packages
        std::vector<models::Package> packagesCar1;
        std::vector<models::Package> packagesCar2;

        for (const auto& pkg : packages) {
            double dist1 = getDistance(pkg.dest, anchor1);
            double dist2 = getDistance(pkg.dest, anchor2);
            if (dist1 < dist2) {
                packagesCar1.push_back(pkg);
            } else {
                packagesCar2.push_back(pkg);
            }
        }

        // 3. Route & Evaluate
        int timeout1 = 0;
        int timeout2 = 0;
        double cost1 = simulateSingleCar(packagesCar1, timeout1);
        double cost2 = simulateSingleCar(packagesCar2, timeout2);

        std::cout << "Car 1 took " << packagesCar1.size() << " packages. Cost: " << cost1 << " | Timeouts: " << timeout1 << std::endl;
        std::cout << "Car 2 took " << packagesCar2.size() << " packages. Cost: " << cost2 << " | Timeouts: " << timeout2 << std::endl;
        std::cout << "T5 Total Cost: " << (cost1 + cost2) << std::endl;
        std::cout << "T5 Total Timeouts: " << (timeout1 + timeout2) << std::endl;
    }

    void TaskSolver::solveT6() {
        int t_nn = 0, t_heavy = 0, t_comp = 0;
        double cost_nn = simulateSingleCar(packages, t_nn, Strategy::NEAREST_NEIGHBOR);
        double cost_heavy = simulateSingleCar(packages, t_heavy, Strategy::HEAVIEST_FIRST);
        double cost_comp = simulateSingleCar(packages, t_comp, Strategy::COMPOSITE);

        std::cout << "  [Nearest Neighbor] Cost: " << cost_nn    << ", Timeouts: " << t_nn << std::endl;
        std::cout << "  [Heaviest First]   Cost: " << cost_heavy << ", Timeouts: " << t_heavy << std::endl;
        std::cout << "  [Composite]        Cost: " << cost_comp  << ", Timeouts: " << t_comp << std::endl;
        std::cout << std::endl;
    }

}
