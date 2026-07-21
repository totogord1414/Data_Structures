#ifndef DATALOADER_H
#define DATALOADER_H

#include <string>
#include <vector>
#include "../models/Package.h"
#include "../models/Car.h"
#include "../data_structures/Graph.h"

namespace core {

    class DataLoader {
    public:
        // 传入包含这三个 txt 的文件夹路径（比如 "测试数据/示例/"）
        // 然后在函数内部使用 std::ifstream 去读取它们
        static void loadGraph(const std::string& directory, data_structures::Graph& graph);

        static void loadPackages(const std::string& directory, std::vector<models::Package>& packages);

        static void loadCar(const std::string& directory, models::Car& car);
    };

}

#endif
