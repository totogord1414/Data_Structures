//
// 动态图上的校园路线规划与设施分析系统
// CommandProcessor.cpp - 命令解析与分发实现
//

#include "CommandProcessor.h"
#include <iostream>

namespace Graph {

    bool CommandProcessor::ProcessCommand(const std::string &line) {
        (void)graph;  // TODO: 各 cmd* 处理函数实现后会使用 graph。

        std::istringstream iss(line);
        std::string cmd;
        if (!(iss >> cmd)) {
            return true;  // 空行，跳过
        }

        if (cmd == "QUIT") {
            return false;
        } else if (cmd == "LOAD") {
            cmdLoad(iss);
        } else if (cmd == "SAVE") {
            cmdSave(iss);
        } else if (cmd == "QUERY_PLACE") {
            cmdQueryPlace(iss);
        } else if (cmd == "QUERY_CATEGORY") {
            cmdQueryCategory(iss);
        } else if (cmd == "ADJ") {
            cmdAdj(iss);
        } else if (cmd == "ADD_PLACE") {
            cmdAddPlace(iss);
        } else if (cmd == "DELETE_PLACE") {
            cmdDeletePlace(iss);
        } else if (cmd == "UPDATE_PLACE") {
            cmdUpdatePlace(iss);
        } else if (cmd == "ADD_ROAD") {
            cmdAddRoad(iss);
        } else if (cmd == "DELETE_ROAD") {
            cmdDeleteRoad(iss);
        } else if (cmd == "UPDATE_ROAD") {
            cmdUpdateRoad(iss);
        } else if (cmd == "CLOSE_ROAD") {
            cmdCloseRoad(iss);
        } else if (cmd == "OPEN_ROAD") {
            cmdOpenRoad(iss);
        } else if (cmd == "COMPONENTS") {
            cmdComponents();
        } else if (cmd == "SHORTEST") {
            cmdShortest(iss);
        } else if (cmd == "TIMED_SHORTEST") {
            cmdTimedShortest(iss);
        } else if (cmd == "SHORTEST_K") {
            cmdShortestK(iss);
        } else if (cmd == "MUST_PASS") {
            cmdMustPass(iss);
        } else if (cmd == "MST") {
            cmdMst();
        } else if (cmd == "CRITICAL") {
            cmdCritical();
        } else {
            std::cout << "ERROR unknown_command" << std::endl;
        }

        return true;
    }

    // ==================== LOAD ====================
    void CommandProcessor::cmdLoad(std::istringstream &args) {
        (void)args;
        // TODO: 实现 LOAD <places.csv> <roads.csv>
        // 提示：
        //   1. 从 args 读取两个文件路径
        //   2. 用 CsvIO::ReadPlaces 和 CsvIO::ReadRoads 读取数据
        //   3. 重建图（清空旧数据，插入新顶点和边）
        //   4. 成功输出 "OK"，失败输出 "ERROR <reason>"
        std::string places_file, roads_file;
        if (!(args >> places_file >> roads_file)) {
            std::cout << "ERROR invalid_arguments\n";
            return;
        }

        auto places = CsvIO::ReadPlaces(places_file);
        auto roads = CsvIO::ReadRoads(roads_file);

        graph = LGraph(false);

        try {

            for (const auto& place : places) {
                graph.InsertVertex(place);
            }

            for (const auto& road : roads) {
                graph.InsertEdge(road.from_id, road.to_id, road.distance, road.walk_time, road.status);
            }


            std::cout << "OK\n";
        } catch (const GraphException& e) {
            std::cout << e.what() << "\n";
        }

    }

    // ==================== SAVE ====================
    void CommandProcessor::cmdSave(std::istringstream &args) {
        (void)args;
        // TODO: 实现 SAVE <places_out.csv> <roads_out.csv>
        // 提示：
        //   1. 从 args 读取两个输出文件路径
        //   2. 调用 CsvIO::WritePlaces 和 CsvIO::WriteRoads
        //   3. 成功输出 "OK"
        std::string places_file, roads_file;
        if(!(args >> places_file >> roads_file)) {

            std::cout << "ERROR invalid_arguments\n";
            return;
        }

        CsvIO::WritePlaces(places_file, graph);
        CsvIO::WriteRoads(roads_file, graph);

        std::cout << "OK\n";
    }

    // ==================== QUERY_PLACE ====================
    void CommandProcessor::cmdQueryPlace(std::istringstream &args) {
        // TODO: 实现 QUERY_PLACE <place_id>
        // 输出格式：PLACE <place_id> <display_name> <category> <stay_time> <open_time> <close_time>
        // 若不存在：ERROR place_not_found
        std::string place_id;
        if (!(args >> place_id)) {
            std::cout << "ERROR invalid_arguments\n";
            return;
        }
        try {
            LocationInfo info = graph.GetVertex(place_id);
            std::cout << "PLACE " << info.place_id << " " << info.display_name << " " << info.category << " "
                      << info.stay_time << " " << info.open_time << " " << info.close_time << "\n";
        } catch (const GraphException& e) {
            std::cout << e.what() << "\n";
        }
    }

    // ==================== QUERY_CATEGORY ====================
    void CommandProcessor::cmdQueryCategory(std::istringstream &args) {
        // TODO: 实现 QUERY_CATEGORY <category>
        // 输出格式：CATEGORY <category> <count> <id1> <id2> ...
        // place_id 按字典序升序输出
        // 若无匹配：CATEGORY <category> 0
        std::string category;
        if (!(args >> category)) {
            std::cout << "ERROR invalid_arguments\n";
            return;
        }
        std::vector<std::string> ids = graph.GetPlacesByCategory(category);
        std::cout << "CATEGORY " << category << " " << ids.size();
        for (const auto& id : ids) {
            std::cout << " " << id;
        }
        std::cout << "\n";
    }

    // ==================== ADJ ====================
    void CommandProcessor::cmdAdj(std::istringstream &args) {
        // TODO: 实现 ADJ <place_id>
        // 输出格式：ADJ <place_id> <count> <neighbor1>:<distance>:<walk_time>:<status> ...
        // 邻接点按 place_id 字典序升序输出
        // 若顶点不存在：ERROR place_not_found
        std::string place_id;
        if (!(args >> place_id)) {
            std::cout << "ERROR invalid_arguments\n";
            return;
        }
        try {
            std::vector<EdgeNode> edges = graph.GetAdjacentEdges(place_id);
            // 虽然图里保证了顺序，但为了绝对满足邻接点 place_id 的字典序要求，这里统一排个序
            std::sort(edges.begin(), edges.end(), [&place_id](const EdgeNode& a, const EdgeNode& b) {
                std::string neighbor_a = (a.from_id == place_id) ? a.to_id : a.from_id;
                std::string neighbor_b = (b.from_id == place_id) ? b.to_id : b.from_id;
                return neighbor_a < neighbor_b;
            });

            std::cout << "ADJ " << place_id << " " << edges.size();
            for (const auto& edge : edges) {
                std::string neighbor = (edge.from_id == place_id) ? edge.to_id : edge.from_id;
                std::cout << " " << neighbor << ":" << edge.distance << ":" << edge.walk_time << ":" << edge.status;
            }
            std::cout << "\n";
        } catch (const GraphException& e) {
            std::cout << e.what() << "\n";
        }
    }

    // ==================== ADD_PLACE ====================
    void CommandProcessor::cmdAddPlace(std::istringstream &args) {
        // TODO: 实现 ADD_PLACE <place_id> <display_name> <category> <stay_time> <open_time> <close_time>
        // 成功输出 "OK"
        // 若 place_id 已存在：ERROR place_already_exists
        std::vector<std::string> params;
        std::string token;
        while (args >> token) params.push_back(token);
        if (params.size() != 6) {
            std::cout << "ERROR invalid_arguments\n";
            return;
        }
        
        LocationInfo info;
        info.place_id = params[0];
        info.display_name = params[1];
        info.category = params[2];
        try {
            info.stay_time = std::stoi(params[3]);
        } catch (...) {
            std::cout << "ERROR invalid_arguments\n";
            return;
        }
        info.open_time = params[4];
        info.close_time = params[5];

        try {
            graph.InsertVertex(info);
            std::cout << "OK\n";
        } catch (const GraphException& e) {
            std::cout << e.what() << "\n";
        }
    }

    // ==================== DELETE_PLACE ====================
    void CommandProcessor::cmdDeletePlace(std::istringstream &args) {
        // TODO: 实现 DELETE_PLACE <place_id>
        // 成功输出 "OK"
        // 若不存在：ERROR place_not_found
        std::string place_id;
        if (!(args >> place_id)) {
            std::cout << "ERROR invalid_arguments\n";
            return;
        }
        try {
            graph.DeleteVertex(place_id);
            std::cout << "OK\n";
        } catch (const GraphException& e) {
            std::cout << e.what() << "\n";
        }
    }

    // ==================== UPDATE_PLACE ====================
    void CommandProcessor::cmdUpdatePlace(std::istringstream &args) {
        // TODO: 实现 UPDATE_PLACE <place_id> <field> <value>
        // 成功输出 "OK"
        // 支持的字段：display_name, category, stay_time, open_time, close_time
        // 若顶点不存在：ERROR place_not_found
        // 若字段不支持：ERROR invalid_field
        std::string place_id, field, value;
        if (!(args >> place_id >> field >> value)) {
            std::cout << "ERROR invalid_arguments\n";
            return;
        }
        try {
            graph.UpdateVertex(place_id, field, value);
            std::cout << "OK\n";
        } catch (const GraphException& e) {
            std::cout << e.what() << "\n";
        }
    }

    // ==================== ADD_ROAD ====================
    void CommandProcessor::cmdAddRoad(std::istringstream &args) {
        // TODO: 实现 ADD_ROAD <from_id> <to_id> <distance> <walk_time> <status>
        // 成功输出 "OK"
        // 若顶点不存在：ERROR place_not_found
        // 若边已存在：ERROR road_already_exists
        std::vector<std::string> params;
        std::string token;
        while (args >> token) params.push_back(token);
        if (params.size() != 5) {
            std::cout << "ERROR invalid_arguments\n";
            return;
        }
        try {
            int distance = std::stoi(params[2]);
            int walk_time = std::stoi(params[3]);
            graph.InsertEdge(params[0], params[1], distance, walk_time, params[4]);
            std::cout << "OK\n";
        } catch (const GraphException& e) {
            std::cout << e.what() << "\n";
        } catch (...) {
            std::cout << "ERROR invalid_arguments\n";
        }
    }

    // ==================== DELETE_ROAD ====================
    void CommandProcessor::cmdDeleteRoad(std::istringstream &args) {
        // TODO: 实现 DELETE_ROAD <from_id> <to_id>
        // 成功输出 "OK"
        // 若边不存在：ERROR road_not_found
        std::string from_id, to_id;
        if (!(args >> from_id >> to_id)) {
            std::cout << "ERROR invalid_arguments\n";
            return;
        }
        try {
            graph.DeleteEdge(from_id, to_id);
            std::cout << "OK\n";
        } catch (const GraphException& e) {
            std::cout << e.what() << "\n";
        }
    }

    // ==================== UPDATE_ROAD ====================
    void CommandProcessor::cmdUpdateRoad(std::istringstream &args) {
        // TODO: 实现 UPDATE_ROAD <from_id> <to_id> <field> <value>
        // 成功输出 "OK"
        // 支持的字段：distance, walk_time, status
        // 若边不存在：ERROR road_not_found
        // 若字段不支持：ERROR invalid_field
        std::string from_id, to_id, field, value;
        if (!(args >> from_id >> to_id >> field >> value)) {
            std::cout << "ERROR invalid_arguments\n";
            return;
        }
        try {
            graph.UpdateEdge(from_id, to_id, field, value);
            std::cout << "OK\n";
        } catch (const GraphException& e) {
            std::cout << e.what() << "\n";
        }
    }

    // ==================== CLOSE_ROAD ====================
    void CommandProcessor::cmdCloseRoad(std::istringstream &args) {
        // TODO: 实现 CLOSE_ROAD <from_id> <to_id>
        // 成功输出 "OK"
        // 若边不存在：ERROR road_not_found
        std::string from_id, to_id;
        if (!(args >> from_id >> to_id)) {
            std::cout << "ERROR invalid_arguments\n";
            return;
        }
        try {
            graph.CloseRoad(from_id, to_id);
            std::cout << "OK\n";
        } catch (const GraphException& e) {
            std::cout << e.what() << "\n";
        }
    }

    // ==================== OPEN_ROAD ====================
    void CommandProcessor::cmdOpenRoad(std::istringstream &args) {
        // TODO: 实现 OPEN_ROAD <from_id> <to_id>
        // 成功输出 "OK"
        // 若边不存在：ERROR road_not_found
        std::string from_id, to_id;
        if (!(args >> from_id >> to_id)) {
            std::cout << "ERROR invalid_arguments\n";
            return;
        }
        try {
            graph.OpenRoad(from_id, to_id);
            std::cout << "OK\n";
        } catch (const GraphException& e) {
            std::cout << e.what() << "\n";
        }
    }

    // ==================== COMPONENTS ====================
    void CommandProcessor::cmdComponents() {
        // TODO: 实现 COMPONENTS
        // 输出格式：COMPONENTS <count> SIZES <s1> <s2> ...
        // 规模按降序输出
        auto result = Algorithm::GetConnectedComponents(graph);
        std::cout << "COMPONENTS " << result.count << " SIZES";
        for (int size : result.sizes) {
            std::cout << " " << size;
        }
        std::cout << "\n";
    }

    // ==================== SHORTEST ====================
    void CommandProcessor::cmdShortest(std::istringstream &args) {
        // TODO: 实现 SHORTEST <from_id> <to_id> <DIST|TIME>
        // 成功输出格式：PATH <DIST|TIME> <total_cost> NODES <id1> <id2> ...
        // 不可达输出：NO_PATH
        // 若顶点不存在：ERROR place_not_found
        std::string from_id, to_id, mode;
        if (!(args >> from_id >> to_id >> mode)) {
            std::cout << "ERROR invalid_arguments\n";
            return;
        }

        if (mode != "DIST" && mode != "TIME") {
            std::cout << "ERROR invalid_arguments\n";
            return;
        }

        Algorithm::PathMode p_mode = (mode == "DIST") ? Algorithm::PathMode::DIST : Algorithm::PathMode::TIME;
        try {
            auto result = Algorithm::GetShortestPath(graph, from_id, to_id, p_mode);
            if (!result.reachable || result.path.empty()) {
                std::cout << "NO_PATH\n";
            } else {
                std::cout << "PATH " << mode << " " << result.total_cost << " NODES";
                for (const auto& node : result.path) {
                    std::cout << " " << node;
                }
                std::cout << "\n";
            }
        } catch (const GraphException& e) {
            std::cout << e.what() << "\n";
        }
    }

    // ==================== TIMED_SHORTEST ====================
    void CommandProcessor::cmdTimedShortest(std::istringstream &args) {
        // TODO: 实现 TIMED_SHORTEST <from_id> <to_id> <time> <DIST|TIME>
        // 含义：在给定时刻（HH:MM）下，找 from_id 到 to_id 的最短路径
        //   - 只走 status == "open" 的道路
        //   - 路径上（含起点、终点、中间点）所有地点必须在 time 时开放
        //     （即 open_time <= time <= close_time，字符串比较即可）
        // 成功输出格式：PATH <DIST|TIME> <total_cost> NODES <id1> <id2> ...
        // 不可达输出：NO_PATH
        // 若顶点不存在：ERROR place_not_found
        std::string from_id, to_id, time, mode;
        if (!(args >> from_id >> to_id >> time >> mode)) {
            std::cout << "ERROR invalid_arguments\n";
            return;
        }

        if (mode != "DIST" && mode != "TIME") {
            std::cout << "ERROR invalid_arguments\n";
            return;
        }

        Algorithm::PathMode p_mode = (mode == "DIST") ? Algorithm::PathMode::DIST : Algorithm::PathMode::TIME;
        try {
            auto result = Algorithm::GetTimedShortestPath(graph, from_id, to_id, time, p_mode);
            if (!result.reachable || result.path.empty()) {
                std::cout << "NO_PATH\n";
            } else {
                std::cout << "PATH " << mode << " " << result.total_cost << " NODES";
                for (const auto& node : result.path) {
                    std::cout << " " << node;
                }
                std::cout << "\n";
            }
        } catch (const GraphException& e) {
            std::cout << e.what() << "\n";
        }
    }

    // ==================== SHORTEST_K ====================
    void CommandProcessor::cmdShortestK(std::istringstream &args) {
        std::string from_id, to_id;
        int max_k;
        if (!(args >> from_id >> to_id >> max_k)) {
            std::cout << "ERROR invalid_arguments\n";
            return;
        }

        try {
            Algorithm::PathResultK result = Algorithm::GetShortestPathK(graph, from_id, to_id, max_k);
            if (!result.reachable) {
                std::cout << "NO_PATH\n";
            } else {
                std::cout << "PATH " << result.total_time << " K_USED " << result.k_used << " NODES";
                for (const auto& node : result.path) {
                    std::cout << " " << node;
                }
                
                if (result.fast_edges.empty()) {
                    std::cout << " FAST 0\n";
                } else {
                    std::cout << " FAST " << result.fast_edges.size();
                    for (const auto& edge : result.fast_edges) {
                        std::cout << " " << edge.first << "-" << edge.second;
                    }
                    std::cout << "\n";
                }
            }
        } catch (const GraphException& e) {
            std::cout << e.what() << "\n";
        }
    }

    // ==================== MUST_PASS ====================
    void CommandProcessor::cmdMustPass(std::istringstream &args) {
        // TODO: 实现 MUST_PASS <from_id> <to_id> <DIST|TIME> <k> <p1> <p2> ... <pk>
        // 成功输出格式：PATH <DIST|TIME> <total_cost> NODES <id1> <id2> ...
        // 不可达输出：NO_PATH
        // 若顶点不存在：ERROR place_not_found
        std::string from_id, to_id, mode;
        int k;
        if (!(args >> from_id >> to_id >> mode >> k)) {
            std::cout << "ERROR invalid_arguments\n";
            return;
        }

        if (mode != "DIST" && mode != "TIME") {
            std::cout << "ERROR invalid_arguments\n";
            return;
        }

        std::vector<std::string> must_pass;
        for (int i = 0; i < k; ++i) {
            std::string p;
            if (!(args >> p)) {
                std::cout << "ERROR invalid_arguments\n";
                return;
            }
            must_pass.push_back(p);
        }

        std::vector<std::string> waypoints;
        waypoints.push_back(from_id);
        for (const auto& p : must_pass) waypoints.push_back(p);
        waypoints.push_back(to_id);

        int total_cost = 0;
        std::vector<std::string> final_nodes;

        Algorithm::PathMode p_mode = (mode == "DIST") ? Algorithm::PathMode::DIST : Algorithm::PathMode::TIME;
        try {
            for (size_t i = 0; i < waypoints.size() - 1; ++i) {
                auto result = Algorithm::GetShortestPath(graph, waypoints[i], waypoints[i+1], p_mode);
                if (!result.reachable || result.path.empty()) {
                    std::cout << "NO_PATH\n";
                    return;
                }
                
                total_cost += result.total_cost;
                
                if (final_nodes.empty()) {
                    final_nodes = result.path;
                } else {
                    final_nodes.insert(final_nodes.end(), result.path.begin() + 1, result.path.end());
                }
            }

            std::cout << "PATH " << mode << " " << total_cost << " NODES";
            for (const auto& node : final_nodes) {
                std::cout << " " << node;
            }
            std::cout << "\n";
        } catch (const GraphException& e) {
            std::cout << e.what() << "\n";
        }
    }

    // ==================== MST ====================
    void CommandProcessor::cmdMst() {
        // TODO: 实现 MST
        // 成功输出格式：MST <total_distance> EDGES <u1>-<v1>:<w1> <u2>-<v2>:<w2> ...
        // 边按 (min(u,v), max(u,v)) 字典序排序输出
        // 图不连通输出：DISCONNECTED
        auto mst = Algorithm::MinimumSpanningTree(graph);
        if (mst.empty()) {
            std::cout << "DISCONNECTED\n";
            return;
        }

        int total_distance = 0;
        for (const auto& edge : mst) {
            total_distance += edge.distance;
        }

        std::sort(mst.begin(), mst.end(), [](const EdgeNode& a, const EdgeNode& b) {
            std::string a_u = std::min(a.from_id, a.to_id);
            std::string a_v = std::max(a.from_id, a.to_id);
            std::string b_u = std::min(b.from_id, b.to_id);
            std::string b_v = std::max(b.from_id, b.to_id);
            if (a_u != b_u) return a_u < b_u;
            return a_v < b_v;
        });

        std::cout << "MST " << total_distance << " EDGES";
        for (const auto& edge : mst) {
            std::string u = std::min(edge.from_id, edge.to_id);
            std::string v = std::max(edge.from_id, edge.to_id);
            std::cout << " " << u << "-" << v << ":" << edge.distance;
        }
        std::cout << "\n";
    }

    // ==================== CRITICAL ====================
    void CommandProcessor::cmdCritical() {
        // TODO: 实现 CRITICAL —— 输出关键节点与关键边
        // 输出格式：CRITICAL NODES <count> <id1> <id2> ... EDGES <count> <u1>-<v1> <u2>-<v2> ...
        //   - 关键节点（删去后连通分量数增加的顶点）按 place_id 字典序输出
        //   - 关键边（删去后连通分量数增加的边）按 (min(u,v), max(u,v)) 字典序输出
        // 实现可调用 Algorithm::FindCriticalNodesAndEdges(graph)
        auto result = Algorithm::FindCriticalNodesAndEdges(graph);

        std::cout << "CRITICAL NODES " << result.critical_nodes.size();
        for (const auto& node : result.critical_nodes) {
            std::cout << " " << node;
        }

        std::cout << " EDGES " << result.critical_edges.size();
        for (const auto& edge : result.critical_edges) {
            std::cout << " " << edge.first << "-" << edge.second;
        }
        std::cout << "\n";
    }

}
