#include <gtest/gtest.h>
#include "../src/lab1.cpp"  // 包含源文件

// 定义一个测试夹具类，用于设置不同图结构的测试
class BridgeWordsTest : public ::testing::Test {
protected:
    // 空图，用于测试边界情况
    DirectedGraph emptyGraph;
    
    // 简单图，仅包含几个单词和边
    DirectedGraph simpleGraph;
    
    // 复杂图，包含多个潜在的桥接词
    DirectedGraph complexGraph;
    
    // 环形图，包含循环引用
    DirectedGraph cyclicGraph;
    
    void SetUp() override {
        // 设置简单图: word1 -> word2 -> word3
        simpleGraph.addEdge("word1", "word2");
        simpleGraph.addEdge("word2", "word3");
        
        
        // 设置复杂图:
        // A -> B -> C
        // |    |    ^
        // v    v    |
        // D -> E ---+
        complexGraph.addEdge("a", "b");
        complexGraph.addEdge("a", "d");
        complexGraph.addEdge("b", "c");
        complexGraph.addEdge("b", "e");
        complexGraph.addEdge("d", "e");
        complexGraph.addEdge("e", "c");
        
        // 设置环形图:
        // X -> Y -> Z
        // ^         |
        // |         v
        // W <- V <- U
        cyclicGraph.addEdge("x", "y");
        cyclicGraph.addEdge("y", "z");
        cyclicGraph.addEdge("z", "u");
        cyclicGraph.addEdge("u", "v");
        cyclicGraph.addEdge("v", "w");
        cyclicGraph.addEdge("w", "x");
    }
};




// 测试用例1: 在空图中查找桥接词
TEST_F(BridgeWordsTest, EmptyGraph) {
    std::vector<std::string> result = emptyGraph.findBridgeWords("any", "word");
    EXPECT_TRUE(result.empty()) << "空图中不应该有桥接词";
}

// 测试用例2: 在简单图中查找存在的桥接词
TEST_F(BridgeWordsTest, SimpleGraphExistingBridge) {
    DirectedGraph simpleGraph;

    // 设置简单图: word1 -> word2 -> word3
    simpleGraph.addEdge("word1", "word2");
    simpleGraph.addEdge("word2", "word3");
    simpleGraph.addEdge("word3", "word4");
    std::string word1 = "word1";
    std::string word2 = "word3";
    std::vector<std::string> result = simpleGraph.findBridgeWords(word1, word2);
    EXPECT_EQ(result.size(), 1) << "应该找到一个桥接词";
    if (!result.empty()) {
        EXPECT_EQ(result[0], "word2") << "桥接词应该是word2";
    }
}

// 测试用例3: 在简单图中查找不存在的桥接词
TEST_F(BridgeWordsTest, SimpleGraphNonExistingBridge) {
    DirectedGraph simpleGraph;

            // 设置简单图: word1 -> word2 -> word3
        simpleGraph.addEdge("word1", "word2");
        simpleGraph.addEdge("word2", "word3");
    std::vector<std::string> result = simpleGraph.findBridgeWords("word1", "word1");
    EXPECT_TRUE(result.empty()) << "word1和word1之间不应该有桥接词";
}

// 测试用例4: 查找词本身不在图中的情况
TEST_F(BridgeWordsTest, WordNotInGraph) {
    DirectedGraph simpleGraph;

            // 设置简单图: word1 -> word2 -> word3
        simpleGraph.addEdge("word1", "word2");
        simpleGraph.addEdge("word2", "word3");
    // 第一个词不在图中
    std::vector<std::string> result1 = simpleGraph.findBridgeWords("unknown", "word2");
    EXPECT_TRUE(result1.empty()) << "第一个词不在图中时不应该有桥接词";
    
    // 第二个词不在图中
    std::vector<std::string> result2 = simpleGraph.findBridgeWords("word1", "unknown");
    EXPECT_TRUE(result2.empty()) << "第二个词不在图中时不应该有桥接词";
    
    // 两个词都不在图中
    std::vector<std::string> result3 = simpleGraph.findBridgeWords("unknown1", "unknown2");
    EXPECT_TRUE(result3.empty()) << "两个词都不在图中时不应该有桥接词";
}

// 测试用例7: 环形图中的桥接词
TEST_F(BridgeWordsTest, CyclicGraphBridges) {
    DirectedGraph cyclicGraph;
            cyclicGraph.addEdge("x", "y");
        cyclicGraph.addEdge("y", "z");
        cyclicGraph.addEdge("z", "u");
        cyclicGraph.addEdge("u", "v");
        cyclicGraph.addEdge("v", "w");
        cyclicGraph.addEdge("w", "x");
    // 测试在环形结构中是否可以找到正确的桥接词
    std::vector<std::string> result = cyclicGraph.findBridgeWords("x", "z");
    EXPECT_EQ(result.size(), 1) << "环形图中x到z的桥接词应该只有y";
    if (!result.empty()) {
        EXPECT_EQ(result[0], "y") << "环形图中x到z的桥接词应该是y";
    }
}

// 测试用例8: 测试相同单词的桥接词查询
TEST_F(BridgeWordsTest, SameWordNoDirectLoop) {
    DirectedGraph complexGraph;
            complexGraph.addEdge("a", "b");
        complexGraph.addEdge("a", "d");
        complexGraph.addEdge("b", "c");
        complexGraph.addEdge("b", "e");
        complexGraph.addEdge("d", "e");
        complexGraph.addEdge("e", "c");
    // 对于没有直接自循环的单词
    std::vector<std::string> result = complexGraph.findBridgeWords("a", "a");
    EXPECT_TRUE(result.empty()) << "没有直接自循环的单词不应该有桥接词";
}

// 测试用例9: 测试权重对桥接词查找的影响
TEST_F(BridgeWordsTest, EdgeWeightImpact) {
    // 创建一个有权重的图
    DirectedGraph weightedGraph;
    weightedGraph.addEdge("start", "middle");  // 权重为1
    weightedGraph.addEdge("middle", "end");    // 权重为1
    
    // 增加同一条边的权重
    weightedGraph.addEdge("start", "middle");  // 权重增加到2
    
    // 查找桥接词
    weightedGraph.addEdge("end","test");
    std::vector<std::string> result = weightedGraph.findBridgeWords("start", "end");
    EXPECT_EQ(result.size(), 1) << "增加边权重不应该改变桥接词的存在";
    if (!result.empty()) {
        EXPECT_EQ(result[0], "middle") << "桥接词应该是middle";
    }
}


// 主函数
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}