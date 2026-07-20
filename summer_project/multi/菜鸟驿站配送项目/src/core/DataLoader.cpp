#include "../../include/core/DataLoader.h"

#include <fstream>
#include <iostream>

namespace core {
    void DataLoader::loadGraph(const std::string &directory, data_structures::Graph &graph) {
        
        std::string filePath = directory + "/map.txt";

        std::ifstream inFile(filePath);

        if (!inFile) {
            std::cerr << "ERROR: fail to open the file: " << filePath << std::endl;
            return;
        }

        int n, m;
        inFile >> n >> m;

        graph.init(n);

        for (int i = 0; i < n; i++) {
            int id;
            double x, y;
            bool is_station;

            inFile >> id >> x >> y >> is_station;

            graph.setNode(id, x, y, is_station);
        }


        for (int i = 0; i < m; i++) {
            int u, v;
            double weight;

            inFile >> u >> v >> weight;

            graph.addEdge(u, v, weight);
        }


        inFile.close();
    }


    void DataLoader::loadPackages(const std::string &directory, std::vector<models::Package> &packages) {

        std::string filePath = directory + "/packages.txt";
        
        std::ifstream inFile(filePath);

        if (!inFile) {
            std::cerr << "ERROR: fail to open the file:" << filePath << std::endl;
            return;
        }
        int k;

        inFile >> k;

        for (int i = 0; i < k; ++i) {
            int id, dest;
            double weight, arrive_time, deadline;
            
            inFile >> id >> weight >> dest >> arrive_time >> deadline;
            
            packages.push_back(models::Package(id, weight, dest, arrive_time, deadline));
        }

        inFile.close();
    }


    void DataLoader::loadCar(const std::string &directory, models::Car &car) {
        std::string filepath = directory + "/car.txt";

        std::ifstream inFile(filepath);
        if (!inFile.is_open()) {
            std::cerr << "ERROR: fail to open the file: " << filepath << std::endl;
            return;
        }
        double speed, car_weight, capacity;
        

        inFile >> speed >> car_weight >> capacity;
        
        car = models::Car(speed, car_weight, capacity);
        inFile.close();
    }
}