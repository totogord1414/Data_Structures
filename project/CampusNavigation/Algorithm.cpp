//
// 动态图上的校园路线规划与设施分析系统
// Algorithm.cpp - 图算法实现
//

#include "Algorithm.h"
#include <iostream>

namespace Graph {
    namespace Algorithm {


        //this is a helper function
        std::vector<int> GetComponentsCore(const LGraph &graph, 
                                           const std::string& ignore_node = "", 
                                           const std::string& ignore_u = "", 
                                           const std::string& ignore_v = "") {
            std::unordered_map<std::string, int> name_id;
            int curr_id = 0;
            
            for (const auto& place_id : graph.AllPlaceIds()) {
                if (place_id == ignore_node) continue; 
                //this makes sure that the ignore_node won't be added into the DSU,so no need to worry that there is one more extra space
                
                name_id[place_id] = curr_id;
                curr_id++;
            }

            DSU uf(curr_id);

            for(const auto& edge: graph.AllEdges(true)) {
                if (edge.from_id == ignore_node || edge.to_id == ignore_node) continue;
                
                if ((edge.from_id == ignore_u && edge.to_id == ignore_v) || 
                    (edge.from_id == ignore_v && edge.to_id == ignore_u)) {
                    continue;
                }

                int from = name_id[edge.from_id];
                int to = name_id[edge.to_id];
                uf.unite(from, to);
            }            

            return uf.get_sizes();
        }

        

        // ==================== A. 连通分量分析 ====================

        ComponentsResult GetConnectedComponents(const LGraph &graph) {
            (void)graph;
            // TODO: 计算图中（仅考虑 open 边）的连通分量个数和各分量规模
            // 提示：
            //   1. 使用 BFS 或 DFS 遍历图
            //   2. 只遍历 status == "open" 的边
            //   3. 从 graph.AllPlaceIds() 获取当前存在的顶点
            //   4. 每次从一个未访问的顶点出发，标记所有可达顶点为同一分量
            //   5. 统计每个分量的大小，最后按降序排列
            //initiate
            std::vector<int> sizes = GetComponentsCore(graph);            

            return {static_cast<int>(sizes.size()), sizes};
        }

        // ==================== B. 最短路径 ====================

        PathResult GetShortestPath(const LGraph &graph,
                                   const std::string &from_id,
                                   const std::string &to_id,
                                   PathMode mode) {
            (void)graph; (void)from_id; (void)to_id; (void)mode;
            // TODO: 使用 Dijkstra 算法计算最短路径
            // 提示：
            //   1. 根据 mode 选择边权：DIST 使用 distance，TIME 使用 walk_time
            //   2. 只走 status == "open" 的边
            //   3. 使用优先队列（小顶堆）优化
            //   4. 维护 prev 数组以回溯完整路径
            //   5. 若不可达，返回 reachable = false 的 PathResult
            //   6. 路径中存储的是 place_id 序列（不是内部索引）
            const int INF = 1e9;

            if (!graph.exist_vertex(from_id) || !graph.exist_vertex(to_id)) {
                throw GraphException("ERROR <place_not_found>");
            }

            std::unordered_map<std::string, std::string> prev;
            std::unordered_map<std::string, bool> confirmed;
            std::unordered_map<std::string, int> dist;

            for (const auto& place_id : graph.AllPlaceIds()) {
                dist[place_id] = INF;
                confirmed[place_id] = false;
            }
            
            std::priority_queue<NodeCost, std::vector<NodeCost>, CompareNodeCost> pq;

            dist[from_id] = 0;
            pq.push({0, from_id});

            while (!pq.empty()) {
                NodeCost current = pq.top();
                pq.pop();

                if(confirmed[current.place_id]) {
                    continue;
                }

                if(current.place_id == to_id) {
                    break;
                }

                confirmed[current.place_id] = true;

                for (const auto& edge : graph.GetAdjacentEdges(current.place_id)) {
                    if(edge.status != "open") {
                        continue;
                    }

                    std::string neighbor_id = (edge.from_id == current.place_id ? edge.to_id 
                        : edge.from_id);
                    
                    int weight = (mode == PathMode::DIST ? edge.distance : edge.walk_time);

                    if (dist[neighbor_id] > dist[current.place_id] + weight) {
                        dist[neighbor_id] = dist[current.place_id] + weight;
                        pq.push({dist[neighbor_id], neighbor_id});

                        prev[neighbor_id] = current.place_id;
                    }
                }
            }

            PathResult result;

            if (dist[to_id] == INF) {
                return result;
            }

            result.reachable = true;
            result.total_cost = dist[to_id];

            std::string curr = to_id;

            while (curr != from_id) {
                result.path.push_back(curr);
                curr = prev[curr];
            }

            result.path.push_back(curr);
            std::reverse(result.path.begin(), result.path.end());

            return result;
        }

        // ==================== B'. 时刻约束最短路径 ====================

        PathResult GetTimedShortestPath(const LGraph &graph,
                                        const std::string &from_id,
                                        const std::string &to_id,
                                        const std::string &time,
                                        PathMode mode) {
            (void)graph; (void)from_id; (void)to_id; (void)time; (void)mode;
            // TODO: 在给定时刻 time（HH:MM）下求最短路径
            // 提示：
            //   1. 判断某地点在 time 时是否开放：open_time <= time <= close_time（字符串比较即可）
            //   2. 只允许使用"此时开放"的地点作为路径上的节点（包括起点和终点）
            //   3. 只走 status == "open" 的边
            //   4. 余下和普通 Dijkstra 相同；可以复用 GetShortestPath 的实现思路
            //   5. 若起点或终点此时未开放，直接返回不可达
            const int INF = 1e9;


            if (!graph.exist_vertex(from_id) || !graph.exist_vertex(to_id)) {
                throw GraphException("ERROR <place_not_found>");
            }
            
            LocationInfo from_info = graph.GetVertex(from_id);
            LocationInfo to_info = graph.GetVertex(to_id);

            if(time < from_info.open_time || time > from_info.close_time ||
                time < to_info.open_time || time > to_info.close_time) {
                    PathResult result;
                    return result;
                }

            std::unordered_map<std::string, std::string> prev;
            std::unordered_map<std::string, bool> confirmed;
            std::unordered_map<std::string, int> dist;

            for (const auto& place_id : graph.AllPlaceIds()) {
                dist[place_id] = INF;
                
                LocationInfo info = graph.GetVertex(place_id);
                //optimization rather than judging it below
                if (time < info.open_time || time > info.close_time) {
                    confirmed[place_id] = true;
                } else {
                    confirmed[place_id] = false;
                }
            }
            
            std::priority_queue<NodeCost, std::vector<NodeCost>, CompareNodeCost> pq;

            dist[from_id] = 0;
            pq.push({0, from_id});

            while (!pq.empty()) {
                NodeCost current = pq.top();
                pq.pop();

                if(confirmed[current.place_id]) {
                    continue;
                }

                if(current.place_id == to_id) {
                    break;
                }

                confirmed[current.place_id] = true;

                for (const auto& edge : graph.GetAdjacentEdges(current.place_id)) {
                    if(edge.status != "open") {
                        continue;
                    }

                    std::string neighbor_id = (edge.from_id == current.place_id ? edge.to_id 
                        : edge.from_id);
                    
                    
                    int weight = (mode == PathMode::DIST ? edge.distance : edge.walk_time);

                    if (dist[neighbor_id] > dist[current.place_id] + weight) {
                        dist[neighbor_id] = dist[current.place_id] + weight;
                        pq.push({dist[neighbor_id], neighbor_id});

                        prev[neighbor_id] = current.place_id;
                    }
                }
            }

            PathResult result;

            if (dist[to_id] == INF) {
                return result;
            }

            result.reachable = true;
            result.total_cost = dist[to_id];

            std::string curr = to_id;

            while (curr != from_id) {
                result.path.push_back(curr);
                curr = prev[curr];
            }

            result.path.push_back(curr);
            std::reverse(result.path.begin(), result.path.end());

            return result;

        }

        // ==================== C. 必经点路径规划 ====================

        PathResult GetMustPassPath(const LGraph &graph,
                                   const std::string &from_id,
                                   const std::string &to_id,
                                   PathMode mode,
                                   const std::vector<std::string> &waypoints) {
            (void)graph; (void)from_id; (void)to_id; (void)mode; (void)waypoints;
            // TODO: 计算必经点路径
            // 提示：
            //   1. 将路径拆分为多段：from -> w1 -> w2 -> ... -> wk -> to
            //   2. 对每段调用 GetShortestPath
            //   3. 如果任意一段不可达，则整条路径不可达
            //   4. 拼接所有段的路径（注意去掉重复的中间点）
            //   5. 累加所有段的代价作为总代价
            PathResult total_result;

            std::vector<std::string> all_stops;
            all_stops.push_back(from_id);

            for (const auto& id : waypoints) {
                all_stops.push_back(id);
            }
            all_stops.push_back(to_id);

            for (int i = 0; i < all_stops.size() - 1; i++) {
                PathResult result = GetShortestPath(graph, all_stops[i], all_stops[i + 1], mode);
                
                if (!result.reachable) {
                    total_result.reachable = false;
                    return total_result;
                }


                if (total_result.path.empty()) {
                    total_result.path = result.path;
                } else {
                    total_result.path.insert(total_result.path.end(), result.path.begin() + 1,
                    result.path.end());
                }

                total_result.total_cost += result.total_cost;
            }

            total_result.reachable = true;
            return total_result;
        }

        // ==================== D. 最小生成树 ====================

        std::vector<EdgeNode> MinimumSpanningTree(const LGraph &graph) {
            (void)graph;
            // TODO: 计算最小生成树（在 Kruskal 与 Prim 中任选其一实现）
            //
            // 选项一：Kruskal + DSU
            //   1. 获取所有 status == "open" 的边，按 distance 升序排序
            //   2. 使用并查集 DSU 维护连通性
            //   3. 依次尝试加入边，若两端不在同一集合则加入 MST
            //
            // 选项二：Prim
            //   1. 从任一顶点出发，维护"已加入 MST 的顶点集合 U"
            //   2. 每次从 U 与剩余顶点之间的边中选距离最小的加入 MST
            //   3. 重复直至 U 包含所有顶点
            //
            // 共同收尾：若最终 MST 边数 != 顶点数 - 1（图不连通），返回空 vector
            //
            // 报告中需说明你选了哪种、为什么、复杂度是多少。
            std::unordered_map<std::string, int> id_num;

            int curr_id = 0;
            for (const auto& place_id : graph.AllPlaceIds()) {
                id_num[place_id] = curr_id;
                curr_id++;
            }

            if (curr_id <= 1) {
                return {};
            }
            
            DSU uf(curr_id);

            std::vector<EdgeNode> edges;
            edges = graph.AllEdges(true);

            std::sort(edges.begin(), edges.end(), [](const EdgeNode& a, const EdgeNode& b){
                if (a.distance != b.distance) {
                    return a.distance < b.distance;
                }
                std::string a_min = std::min(a.from_id, a.to_id);
                std::string a_max = std::max(a.from_id, a.to_id);
                std::string b_min = std::min(b.from_id, b.to_id);
                std::string b_max = std::max(b.from_id, b.to_id);
                
                if (a_min != b_min) {
                    return a_min < b_min;
                }
                return a_max < b_max;
            });

            std::vector<EdgeNode> mst_edges;

            for (const auto& edge : edges) {
                int u = id_num[edge.from_id];
                int v = id_num[edge.to_id];

                if (!uf.same(u, v)) {
                    uf.unite(u, v);
                    mst_edges.push_back(edge);
                    
                    if (mst_edges.size() == curr_id - 1) {
                        break;
                    }
                }
            }

            if (mst_edges.size() == curr_id - 1) {
                return mst_edges;
            } else {
                return {};
            }

        }

        // ==================== E. 关键节点 / 关键边分析 ====================

        CriticalResult FindCriticalNodesAndEdges(const LGraph &graph) {
            (void)graph;
            // TODO: 找出"删去后会让图的连通分量数增加"的顶点和边
            //
            // 推荐方法（基于 PPT 第 3 章讲过的 BFS / DFS）：
            //   1. 先调用 GetConnectedComponents 算出原图的分量数 baseline
            //   2. 关键节点：对每个顶点 v
            //        a. 临时把 v 视作"被删除"（连同其所有相邻边一起忽略）
            //        b. 对剩余子图重新 BFS / DFS 计算连通分量数
            //        c. 若分量数 > baseline，则 v 是关键节点
            //   3. 关键边：对每条 status=="open" 的边 e
            //        a. 临时把 e 视作"closed"
            //        b. 重新计算连通分量数
            //        c. 若分量数 > baseline，则 e 是关键边
            //
            // 注意事项：
            //   - 仅考虑 status == "open" 的边和当前存在的顶点
            //   - 这种"临时删除"通常用一个"被屏蔽集合"参数控制 BFS/DFS 即可，
            //     不必真的修改图
            //   - 复杂度：O(V·(V+E)) + O(E·(V+E))
            //   - 千节点规模可接受；想优化的同学请看加分项中的 Tarjan 版本
            //
            // 加分提示：用 Tarjan 一遍 DFS 同时找全部关键节点和关键边
            //          （维护 dfn[] 和 low[]），可把复杂度降到 O(V+E)。
            //          若实现 Tarjan 版本请放在加分项里，**不要**替换本必做版本。
            
            
            CriticalResult result;
            int baseline = GetComponentsCore(graph).size();

            for (const auto& place_id : graph.AllPlaceIds()) {
                if (GetComponentsCore(graph, place_id).size() > baseline) {
                    result.critical_nodes.push_back(place_id);
                }
            }

            for (const auto& edge :graph.AllEdges(true)) {
                if (GetComponentsCore(graph, "" , edge.from_id, edge.to_id).size() > baseline) {
                    std::string from = std::min(edge.from_id, edge.to_id);
                    std::string to = std::max(edge.from_id, edge.to_id);
                    result.critical_edges.push_back({from, to});
                }
            }

            std::sort(result.critical_nodes.begin(), result.critical_nodes.end());

            std::sort(result.critical_edges.begin(), result.critical_edges.end(), []
            (const std::pair<std::string, std::string>& a, const std::pair<std::string, std::string>& b) {

                if (a.first == b.first) {
                    return a.second < b.second;
                }
                return a.first < b.first;
            });

            return result;
        }
    }
}
