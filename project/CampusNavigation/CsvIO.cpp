//
// 动态图上的校园路线规划与设施分析系统
// CsvIO.cpp - CSV 文件读写实现
//

#include "CsvIO.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace Graph {
    namespace CsvIO {

        std::vector<LocationInfo> ReadPlaces(const std::string &path) {
            std::vector<LocationInfo> result;
            // TODO: 从 CSV 读取地点信息
            // 提示：
            //   1. 打开文件，若失败则输出错误信息并返回空 vector
            //   2. 逐行读取，将逗号替换为空格后使用 istringstream 解析
            //   3. 若首行以 "place_id" 开头，则跳过（表头行）
            //   4. 跳过空行
            //   5. 每行解析为：place_id, display_name, category, stay_time, open_time, close_time
            //   6. 将解析结果加入 vector 并返回
            std::ifstream file(path);
            if(!file.is_open()) {
                std::cerr << "fail to open the file" << path << std::endl;
                return result;
            } 

            std::string line;

            while(std::getline(file, line)) {

                if(line.empty()) {
                    continue;
                }

                if(line.find("place_id") == 0) {
                    continue;
                }

                if (!line.empty() && line.back() == '\r') {
                    line.pop_back();
                }

                for(char& c : line) {
                    if(c == ',') {
                        c = ' ';
                    }
                }

                std::istringstream iss(line);
                LocationInfo info;
                iss >> info.place_id >> info.display_name >> info.category >> info.stay_time
                    >> info.open_time >> info.close_time;

                result.push_back(info);
            }

            file.close();
            return result;
        }

        std::vector<RoadRecord> ReadRoads(const std::string &path) {
            // TODO: 从 CSV 读取道路信息
            // 提示：
            //   1. 打开文件，若失败则输出错误信息并返回空 vector
            //   2. 逐行读取，将逗号替换为空格后使用 istringstream 解析
            //   3. 若首行以 "from_id" 开头，则跳过（表头行）
            //   4. 跳过空行
            //   5. 每行解析为：from_id, to_id, distance, walk_time, status
            //   6. 将解析结果加入 vector 并返回
            std::vector<RoadRecord> result;
            
            std::ifstream file(path);
            if (!file.is_open()) {
                std::cerr << "fail to open the file: " << path << std::endl;
                return result;
            }

            std::string line;

            while (std::getline(file, line)) {

                if (line.empty()) {
                    continue;
                }

                if (line.find("from_id") == 0) {
                    continue;
                }

                if (!line.empty() && line.back() == '\r') {
                    line.pop_back();
                }

                for (char& c : line) {
                    if (c == ',') {
                        c = ' ';
                    }
                }

                std:: istringstream iss(line);
                
                RoadRecord record;
                
                iss >> record.from_id >> record.to_id >> record.distance >> record.walk_time
                    >> record.status;

                result.push_back(record);
            }
            

            return result;
        }

        void WritePlaces(const std::string &path, const LGraph &graph) {
            // TODO: 将地点信息写回 CSV
            // 提示：
            //   1. 打开文件输出流
            //   2. 写入表头行：place_id,display_name,category,stay_time,open_time,close_time
            //   3. 通过 graph.AllPlaceIds() 获取所有地点 id，逐个调用 graph.GetVertex(id) 取完整信息
            //   4. 每行输出一个地点的完整信息，字段间用逗号分隔
            //   5. 关闭文件
            std::ofstream file(path);
            if(!file.is_open()) {
                std::cerr << "fail to open the file" << path << std::endl;
            }

            file << "place_id,display_name,category,stay_time,open_time,close_time\n";

            std::vector<std::string> ids = graph.AllPlaceIds();
            for (const auto& id : ids) {
                LocationInfo info = graph.GetVertex(id);

                file << info.place_id << "," 
                     << info.display_name << ","
                     << info.category << "," 
                     << info.stay_time << ","
                     << info.open_time << "," 
                     << info.close_time << "\n";

            }

            file.close();
        }

        void WriteRoads(const std::string &path, const LGraph &graph) {
            // TODO: 将道路信息写回 CSV
            // 提示：
            //   1. 打开文件输出流
            //   2. 写入表头行：from_id,to_id,distance,walk_time,status
            //   3. 使用 graph.AllEdges(false) 获取所有边（包括 closed）
            //   4. 输出每条边的 from_id, to_id, distance, walk_time, status
            //   5. 关闭文件
            
            std::ofstream file(path);
            if(!file.is_open()) {
                std::cerr << "fail to open the file: " << path << std::endl;
                return;
            }

            file << "from_id,to_id,distance,walk_time,status\n";

            std::vector<EdgeNode> edges = graph.AllEdges(false);
            for (const auto& edge : edges) {
                file << edge.from_id << "," 
                     << edge.to_id << ","
                     << edge.distance << "," 
                     << edge.walk_time << ","
                     << edge.status << "\n";
            }

            file.close();
        }
    }
}
