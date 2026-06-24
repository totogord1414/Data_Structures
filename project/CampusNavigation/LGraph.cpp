//
// 动态图上的校园路线规划与设施分析系统
// LGraph.cpp - 图 ADT 实现（内部存储结构由你自行设计）
//

#include "LGraph.h"

namespace Graph {

    LGraph::LGraph(bool directed) {
        // TODO: 初始化你自己设计的数据结构。
        //       directed 参数表示是否为有向图（本项目默认无向图）。
        this->is_directed = directed;
    }

    // ==================== 基础信息 ====================

    int LGraph::VertexCount() const {
        // TODO: 返回当前图中存在的顶点数
        return this->vertices.size();
    }

    int LGraph::EdgesCount() const {
        // TODO: 返回当前图中存在的边数（无向图中每条边算一次）
        int count = 0;
        for(const auto& pair: this->adj) {
            count += pair.second.size();
        }

        if(!is_directed) {
            count /= 2;
        }

        return count;
    }

    bool LGraph::exist_vertex(const std::string &place_id) const {
        // TODO: 判断 place_id 对应的顶点是否存在
        return vertices.find(place_id) != vertices.end();
    }

    bool LGraph::exist_edge(const std::string &from_id, const std::string &to_id) const {
        // TODO: 判断 from_id 与 to_id 之间是否有边
        auto it = adj.find(from_id);
        if(it != adj.end()) {
            return it->second.find(to_id) != it->second.end();
        }

        return false;
    }

    // ==================== 顶点操作 ====================

    void LGraph::InsertVertex(const LocationInfo &vertex_info) {
        // TODO: 插入顶点
        //   - 若 place_id 已存在，抛出 GraphException
        //   - 否则将其加入你的存储结构
        if(exist_vertex(vertex_info.place_id)) {
            throw GraphException("ERROR place_already_exists");
        } else {
            vertices[vertex_info.place_id] = vertex_info;
        }
    }

    void LGraph::DeleteVertex(const std::string &place_id) {
        // TODO: 删除顶点，并同步删除所有与该顶点相关的边
        //   - 若 place_id 不存在，抛出 GraphException
        //   - 无向图中对端的邻接信息也要同步清理
        if(!exist_vertex(place_id)) {
        throw GraphException("ERROR place_not_found");
        } else {
            if(is_directed) {
                for(auto& pair: adj) {
                    pair.second.erase(place_id);
                }
            } else {
                for(const auto& pair: adj[place_id]) {
                    const std::string& target = pair.first;
                    adj[target].erase(place_id);
                }
            }        

            adj.erase(place_id);
            vertices.erase(place_id);
        }
    }

    void LGraph::UpdateVertex(const std::string &place_id,
                              const std::string &field, const std::string &value) {
        // TODO: 按字段名更新顶点信息
        //   支持的字段：display_name, category, stay_time, open_time, close_time
        //   - stay_time 需要将 value 转为 int
        //   - place_id 不存在 → GraphException
        //   - field 不支持 → GraphException
        if(!exist_vertex(place_id)) {
            throw GraphException("ERROR place_not_found");
        } else {
            if(field == "display_name") {
                vertices[place_id].display_name = value;
            } else if (field == "category") {
                vertices[place_id].category = value;
            } else if (field == "stay_time") {
                int i_value = std::stoi(value);
                vertices[place_id].stay_time = i_value;
            } else if (field == "open_time") {
                vertices[place_id].open_time = value;
            } else if (field == "close_time") {
                vertices[place_id].close_time = value;
            } else {

                throw GraphException("ERROR invalid_field");

            }
        }
    }

    LocationInfo LGraph::GetVertex(const std::string &place_id) const {
        // TODO: 返回 place_id 对应的顶点完整信息
        //   不存在 → GraphException
        //doesn't call the get_vertex function for the sake of efficency
        auto it = vertices.find(place_id); 
        if (it == vertices.end()) {
            throw GraphException("ERROR place_not_found");
        } else {
            return it->second;
        }
    }

    // ==================== 边操作 ====================

    void LGraph::InsertEdge(const std::string &from_id, const std::string &to_id,
                            int distance, int walk_time, const std::string &status) {
        // TODO: 插入边
        //   - 两端顶点必须都存在，否则抛异常
        //   - 边已存在则抛 GraphException
        //   - 无向图中注意反向关联
        if (!exist_vertex(from_id) || !exist_vertex(to_id)) {
            throw GraphException("ERROR place_not_found");
        }
        if(exist_edge(from_id, to_id)) {
            throw GraphException("ERROR road_already_exists");
        } else {
            adj[from_id][to_id] = EdgeNode(from_id, to_id, distance, walk_time, status);
            if(!is_directed) {
                adj[to_id][from_id] = EdgeNode(to_id, from_id, distance, walk_time, status);
            }
        }
    }

    void LGraph::DeleteEdge(const std::string &from_id, const std::string &to_id) {
        // TODO: 删除边
        //   - 边不存在 → GraphException
        //   - 无向图中反向边同步删除
        if(!exist_edge(from_id, to_id)) {
            throw GraphException("ERROR road_not_found");
        } else {
            adj[from_id].erase(to_id);
            if(!is_directed) {
                adj[to_id].erase(from_id);
            }
        }
    }

    void LGraph::UpdateEdge(const std::string &from_id, const std::string &to_id,
                            const std::string &field, const std::string &value) {
        // TODO: 按字段名更新边
        //   支持字段：distance, walk_time, status
        //   - distance / walk_time 需要转为 int
        //   - status 只能是 "open" 或 "closed"
        //   - 无向图中两个方向需同时更新
        if(!exist_edge(from_id, to_id)) {
            throw GraphException("ERROR road_not_found");
        } else {
            auto& edge = adj[from_id][to_id];

            if(field == "distance") {
                int i_value = std::stoi(value);
                edge.distance = i_value;
            } else if (field == "walk_time") {
                int i_value = std::stoi(value);
                edge.walk_time = i_value;
            } else if (field == "status") {
                if(value == "closed" || value == "open") {
                    edge.status = value;
                } else {
                    throw GraphException("ERROR invalid_field");
                }
            } else {
                throw GraphException("ERROR invalid_field");
            }

            if(!is_directed) {
                auto& r_edge = adj[to_id][from_id];
                r_edge.distance = edge.distance;
                r_edge.walk_time = edge.walk_time;
                r_edge.status = edge.status;
            }
        }
    }

    EdgeNode LGraph::GetEdge(const std::string &from_id, const std::string &to_id) const {
        // TODO: 返回边的完整信息
        //   不存在 → GraphException
        auto from_it = adj.find(from_id);
        if(from_it == adj.end()) {
            throw GraphException("ERROR road_not_found");
        } else {
            auto to_it = from_it->second.find(to_id);
            if(to_it == from_it->second.end()) {
                throw GraphException("ERROR road_not_found");
            }
            return to_it->second;
        }
    }

    // ==================== 道路状态 ====================

    void LGraph::CloseRoad(const std::string &from_id, const std::string &to_id) {
        // TODO: 将边 status 设为 "closed"（可复用 UpdateEdge）
        UpdateEdge(from_id, to_id, "status", "closed");
    }

    void LGraph::OpenRoad(const std::string &from_id, const std::string &to_id) {
        // TODO: 将边 status 设为 "open"（可复用 UpdateEdge）
        UpdateEdge(from_id, to_id, "status", "open");
    }

    // ==================== 遍历 / 高级查询 ====================

    std::vector<std::string> LGraph::AllPlaceIds() const {
        // TODO: 返回当前图中所有存在的地点 id
        //   顺序由你决定（是否排序、按什么排序，请在报告中说明）
        std::vector<std::string> result;
        for(const auto& pair: vertices) {
            result.push_back(pair.first);
        }
        std::sort(result.begin(), result.end());

        return result;
    }

    std::vector<EdgeNode> LGraph::AllEdges(bool only_open) const {
        // TODO: 返回当前图中所有边
        //   - 无向图中每条边只出现一次
        //   - only_open = true 时仅返回 status == "open" 的边
        //   - 返回顺序由你决定
        std::vector<EdgeNode> result;
        for(const auto& vertex: adj) {
            for(const auto& pair: vertex.second) {
                if((!only_open || pair.second.status == "open") 
                    && (is_directed || vertex.first < pair.first)) {
                    result.push_back(pair.second);
                }
            }
        }

        std::sort(result.begin(), result.end(), [](const EdgeNode& a, const EdgeNode& b){
            if(a.from_id == b.from_id) {
                return a.to_id < b.to_id;
            }

            return a.from_id < b.from_id;
        });

        return result;
    }

    std::vector<EdgeNode> LGraph::GetAdjacentEdges(const std::string &place_id) const {
        // TODO: 返回某地点的所有邻接边完整信息
        //   place_id 不存在 → GraphException
        //   返回顺序由你决定
        if (!exist_vertex(place_id)) {
            throw GraphException("ERROR place_not_found");
        }
        std::vector<EdgeNode> result;
        const auto vertex = adj.find(place_id);
        if(vertex == adj.end()) {
            return result;  // 孤立节点，没有邻接边
        } else {
            for(const auto& neighbor: vertex->second) {
                if(neighbor.first < place_id && !is_directed) {//如果是无向边的话要取出发节点更小的边
                    
                    EdgeNode temp = neighbor.second;
                    temp.from_id = neighbor.first;
                    temp.to_id = place_id;
                    result.push_back(temp);

                } else {
                    result.push_back(neighbor.second);
                }
            }

            if(is_directed) {
                for(const auto& node: adj) {
                    if(node.first == place_id) {
                        continue;
                    }                    


                    const auto& pair = node.second.find(place_id);
                    if(pair != node.second.end()) {
                        result.push_back(pair->second);
                    }
                }
            }

            std::sort(result.begin(), result.end(), [](const EdgeNode& a, const EdgeNode& b){
                if(a.from_id == b.from_id) {
                    return a.to_id < b.to_id;
                } else {
                    return a.from_id < b.from_id;
                }
            });

        }

        return result;
    }

    std::vector<std::string> LGraph::GetPlacesByCategory(const std::string &category) const {
        // TODO: 返回某类别下所有地点 id
        //   返回顺序由你决定
        std::vector<std::string> result;
        for(const auto& pair: vertices) {
            if(pair.second.category == category) {
                result.push_back(pair.first);
            }
        }

        std::sort(result.begin(), result.end());

        return result;
    }

}
