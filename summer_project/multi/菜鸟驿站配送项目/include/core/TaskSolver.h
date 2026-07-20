#ifndef TASKSOLVER_H
#define TASKSOLVER_H

#include "../data_structures/Graph.h"
#include "../models/Package.h"
#include "../models/Car.h"
#include "Router.h"
#include <vector>

namespace core {

    enum class Strategy {
        NEAREST_NEIGHBOR, // Baseline 1: Distance only
        HEAVIEST_FIRST,   // Baseline 2: Weight only
        COMPOSITE         // Improved: Weight / Distance
    };

    class TaskSolver {
    private:
        data_structures::Graph graph;
        std::vector<models::Package> packages;
        models::Car car;
        Router router;

        std::vector<std::vector<double>> distCache;

    public:
        TaskSolver(const data_structures::Graph& g, const std::vector<models::Package>& p, const models::Car& c);

        double getDistance(int u, int v);

        void solveT1(int startNode, int endNode);
        
        void solveT2();
        
        void solveT3();
        
        void solveT4(const std::vector<int>& returnNodes);

        void solveT5();

        void solveT6();

    private:
        double simulateSingleCar(const std::vector<models::Package>& p, int& timeoutCount, Strategy strategy = Strategy::COMPOSITE);
    };

}

#endif
