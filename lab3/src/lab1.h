// 定义有向图的数据结构
struct Edge {
    std::string to;
    int weight;
    
    Edge(const std::string& to, int weight) : to(to), weight(weight) {}
};
// 定义用于Dijkstra算法的路径结构
struct PathInfo {
    int distance;
    std::vector<std::string> path;
    
    PathInfo() : distance(INT_MAX) {} // 初始化为无穷大
    
    PathInfo(int d, const std::vector<std::string>& p) : distance(d), path(p) {}
};
