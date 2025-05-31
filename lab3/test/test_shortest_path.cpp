#include <gtest/gtest.h>
#include "../src/lab1.cpp"  // 包含源文件

// 声明这些结构和函数以避免重复定义，实际实现将从源文件中获取
struct Edge;
struct PathInfo;
class DirectedGraph;
std::string toLower(const std::string& word);

// 为测试创建一个夹具类
class ShortestPathTest : public ::testing::Test {
protected:
    DirectedGraph* graph;

    void SetUp() override {
        graph = new DirectedGraph();
        
        // 创建一个简单的测试图
        // A -> B -> C
        // |    |    ^
        // v    v    |
        // D -> E ---+
        graph->addEdge("a", "b");
        graph->addEdge("a", "d");
        graph->addEdge("b", "c");
        graph->addEdge("b", "e");
        graph->addEdge("d", "e");
        graph->addEdge("e", "c");

        // 添加一些带权重的边
        // F -> G (weight=5)
        // F -> H (weight=2)
        // H -> G (weight=1)
        graph->addEdge("f", "g"); // 默认权重1
        graph->addEdge("f", "g"); // 增加权重到2
        graph->addEdge("f", "g"); // 增加权重到3
        graph->addEdge("f", "g"); // 增加权重到4
        graph->addEdge("f", "g"); // 增加权重到5
        graph->addEdge("f", "h");
        graph->addEdge("f", "h"); // 增加权重到2
        graph->addEdge("h", "g");
    }

    void TearDown() override {
        delete graph;
    }
};

// 测试两个存在路径的节点之间的最短路径
TEST_F(ShortestPathTest, ExistingPath) {

    PathInfo result = graph->findShortestPath("a", "c");
    graph->printGraph(); // 打印图结构以便调试    
    EXPECT_NE(INT_MAX, result.distance);
    EXPECT_EQ(2, result.distance); // a->b->c 的距离应该是2


    // 验证路径是否正确
    std::vector<std::string> expectedPath = {"a", "b", "c"};
    EXPECT_EQ(expectedPath, result.path);
}

// 测试不同路径的情况 - a到e有两条路径
TEST_F(ShortestPathTest, MultiplePathsExist) {
    PathInfo result = graph->findShortestPath("a", "e");
    
    EXPECT_NE(INT_MAX, result.distance);
    EXPECT_EQ(2, result.distance); // a->d->e 和 a->b->e 都是2，但返回哪一条取决于实现
    
    // 验证路径长度是否正确
    EXPECT_EQ(3, result.path.size()); // 应该有3个节点
    
    // 检查起点和终点是否正确
    EXPECT_EQ("a", result.path.front());
    EXPECT_EQ("e", result.path.back());
}

// 测试不可达路径
TEST_F(ShortestPathTest, NoPathExists) {
    // 添加一个孤立节点
    graph->addEdge("isolated", "isolated"); // 自环
    
    PathInfo result = graph->findShortestPath("isolated", "a");
    
    EXPECT_EQ(INT_MAX, result.distance);
    EXPECT_TRUE(result.path.empty());
}

// 测试节点不在图中的情况
TEST_F(ShortestPathTest, NodeNotInGraph) {
    PathInfo result = graph->findShortestPath("nonexistent", "a");
    
    EXPECT_EQ(INT_MAX, result.distance);
    EXPECT_TRUE(result.path.empty());
    
    result = graph->findShortestPath("a", "nonexistent");
    
    EXPECT_EQ(INT_MAX, result.distance);
    EXPECT_TRUE(result.path.empty());
}

// 测试相同节点的最短路径
TEST_F(ShortestPathTest, SameNode) {
    PathInfo result = graph->findShortestPath("a", "a");
    
    EXPECT_EQ(0, result.distance); // 到自己的距离是0
    EXPECT_EQ(1, result.path.size()); // 路径中只有一个节点
    EXPECT_EQ("a", result.path[0]);
}


// 测试环路处理
TEST_F(ShortestPathTest, CycleHandling) {
    // 创建一个包含环的图
    graph->addEdge("p", "q");
    graph->addEdge("q", "r");
    graph->addEdge("r", "p"); // 创建环 p->q->r->p
    
    PathInfo result = graph->findShortestPath("p", "r");
    
    EXPECT_NE(INT_MAX, result.distance);
    EXPECT_EQ(2, result.distance); // p->q->r 距离为2
    
    // 验证路径是否正确（不应包含环）
    std::vector<std::string> expectedPath = {"p", "q", "r"};
    EXPECT_EQ(expectedPath, result.path);
}


// 主函数
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}