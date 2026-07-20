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

        // 懒汉缓存表：保存算过的两点距离
        std::vector<std::vector<double>> distCache;

        // 带缓存的距离查询接口
        double getDistance(int u, int v);

    public:
        TaskSolver(const data_structures::Graph& g, 
                   const std::vector<models::Package>& p, 
                   const models::Car& c);

        void solveT1(int startNode, int endNode);
        
        void solveT2();
        
        void solveT3();
        
        void solveT4(const std::vector<int>& returnNodes);
    };

}

#endif
