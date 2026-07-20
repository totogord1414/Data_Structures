#ifndef TASKSOLVER_H
#define TASKSOLVER_H

#include "../data_structures/Graph.h"
#include "../models/Package.h"
#include "../models/Car.h"
#include "Router.h"
#include <vector>

namespace core {

    class TaskSolver {
    private:
        const data_structures::Graph& graph;
        const std::vector<models::Package>& packages;
        const models::Car& car;
        Router router;

    public:
        TaskSolver(const data_structures::Graph& g, 
                   const std::vector<models::Package>& p, 
                   const models::Car& c);

        void solveT1(int startNode, int endNode);
        
        void solveT2();
        
        void solveT3();
    };

}

#endif
