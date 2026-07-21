#include <iostream>
#include <vector>
#include <string>

// Include headers
#include "../include/models/Package.h"
#include "../include/models/Car.h"
#include "../include/data_structures/Graph.h"
#include "../include/core/DataLoader.h"
#include "../include/core/TaskSolver.h"

void runT6Experiment(const std::string& dataset_path, const std::string& title) {
    std::cout << "\n========== Task 6: " << title << " ==========" << std::endl;
    data_structures::Graph graph;
    std::vector<models::Package> packages;
    models::Car car;
    core::DataLoader::loadGraph(dataset_path, graph);
    core::DataLoader::loadPackages(dataset_path, packages);
    core::DataLoader::loadCar(dataset_path, car);
    core::TaskSolver solver(graph, packages, car);
    solver.solveT6();

}

int main() {
    std::cout << "--- Cainiao Delivery System Initialization ---" << std::endl;

    data_structures::Graph graph;
    std::vector<models::Package> packages;
    models::Car car;

    std::string data_dir = "test_data/test2";

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

    std::cout << "\n[Info] Exporting visualization data to trace.js..." << std::endl;
    solver.exportVisualization("trace.js");

    std::cout << "\n========== Task 4: TSP Return Logistics ==========" << std::endl;
    std::vector<int> returnNodes = {1, 2, 4, 5}; 
    solver.solveT4(returnNodes);

    std::cout << "========== Task 5: Two-Car Coordination ==========" << std::endl;
    solver.solveT5();

    if (true) {
        runT6Experiment("test_data/t6/dataset1", "Dataset 1 (Anti-NN)");
        runT6Experiment("test_data/t6/dataset2", "Dataset 2 (Anti-Heavy)");
        runT6Experiment("test_data/t6/dataset3", "Dataset 3 (Anti-Composite)");
    }

    return 0;
}