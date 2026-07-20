#include <iostream>
#include <vector>
#include <string>

// Include headers
#include "../include/models/Package.h"
#include "../include/models/Car.h"
#include "../include/data_structures/Graph.h"
#include "../include/core/DataLoader.h"
#include "../include/core/TaskSolver.h"

int main() {
    std::cout << "--- Cainiao Delivery System Initialization ---" << std::endl;

    data_structures::Graph graph;
    std::vector<models::Package> packages;
    models::Car car;

    std::string data_dir = "test_data/example";

    core::DataLoader::loadGraph(data_dir, graph);
    core::DataLoader::loadPackages(data_dir, packages);
    core::DataLoader::loadCar(data_dir, car);

    core::TaskSolver solver(graph, packages, car);

    std::cout << "\n========== Task 1: Shortest Path ==========" << std::endl;
    solver.solveT1(0, 4);

    std::cout << "\n========== Task 2: Minimize Dissatisfaction ==========" << std::endl;
    solver.solveT2();

    std::cout << "\n========== Task 3: Transport Cost Optimization ==========" << std::endl;
    solver.solveT3();

    std::cout << "\n========== Task 4: TSP Return Logistics ==========" << std::endl;
    //decide yourself all the return Nodes
    std::vector<int> returnNodes = {1, 2, 4, 5}; 
    solver.solveT4(returnNodes);

    return 0;
}