#include <iostream>
#include <string>
#include <vector>
#include <windows.h>  // 控制台编码设置
#include "Graph.hpp"

// 辅助函数：打印图结构
template<typename V, typename W, bool Direction>
void printGraph(const Graph<V, W, Direction>& g) {
    std::cout << "图结构：" << (Direction ? "有向图" : "无向图") << std::endl;
    
    std::cout << "顶点数量: " << g.vertexCount() << std::endl;
    std::cout << "边数量: " << g.edgeCount() << std::endl;
    
    std::cout << "邻接表：" << std::endl;
    g.printAdjList();
    
    std::cout << std::endl;
}

// 测试整数顶点的有向图
void testIntDirectedGraph() {
    std::cout << "===== 测试整数顶点的有向图 =====" << std::endl;
    
    // 创建有向图
    int vertices[] = {1, 2, 3, 4, 5};
    Graph<int, double, true> g(vertices, 5);
    
    // 添加边
    g.addEdge(1, 2, 0.5);
    g.addEdge(1, 3, 1.0);
    g.addEdge(2, 4, 2.0);
    g.addEdge(3, 5, 1.5);
    g.addEdge(4, 5, 0.7);
    
    // 打印图结构
    printGraph(g);
    
    // 验证边是否存在
    std::cout << "边验证：" << std::endl;
    std::cout << "1->2 存在: " << (g.hasEdge(1, 2) ? "是" : "否") << std::endl;
    std::cout << "2->1 存在: " << (g.hasEdge(2, 1) ? "是" : "否") << " (有向图，应为否)" << std::endl;
    std::cout << "2->4 存在: " << (g.hasEdge(2, 4) ? "是" : "否") << std::endl;
    std::cout << "1->5 存在: " << (g.hasEdge(1, 5) ? "是" : "否") << " (应为否)" << std::endl;
    
    // 测试获取边权重
    double weight;
    if (g.getEdgeWeight(1, 2, weight)) {
        std::cout << "边1->2的权重为: " << weight << std::endl;
    }
    
    // 测试更新边权重
    g.addEdge(1, 2, 10.0);  // 更新已存在的边
    if (g.getEdgeWeight(1, 2, weight)) {
        std::cout << "更新后边1->2的权重为: " << weight << std::endl;
    }
}

// 测试字符串顶点的无向图
void testStringUndirectedGraph() {
    std::cout << "\n===== 测试字符串顶点的无向图 =====" << std::endl;
    
    // 创建无向图
    std::string vertices[] = {"北京", "上海", "广州", "深圳", "杭州"};
    Graph<std::string, int, false> g(vertices, 5);
    
    // 添加边
    g.addEdge("北京", "上海", 1200);
    g.addEdge("上海", "杭州", 180);
    g.addEdge("广州", "深圳", 140);
    g.addEdge("北京", "广州", 1900);
    
    // 打印图结构
    printGraph(g);
    
    // 验证边是否存在 (无向图应该是双向的)
    std::cout << "边验证：" << std::endl;
    std::cout << "北京->上海 存在: " << (g.hasEdge("北京", "上海") ? "是" : "否") << std::endl;
    std::cout << "上海->北京 存在: " << (g.hasEdge("上海", "北京") ? "是" : "否") << " (无向图，应为是)" << std::endl;
    std::cout << "上海->广州 存在: " << (g.hasEdge("上海", "广州") ? "是" : "否") << " (应为否)" << std::endl;
    
    // 测试获取边权重
    int weight;
    if (g.getEdgeWeight("广州", "深圳", weight)) {
        std::cout << "边广州->深圳的权重为: " << weight << std::endl;
    }
    
    if (g.getEdgeWeight("深圳", "广州", weight)) {
        std::cout << "边深圳->广州的权重为: " << weight << " (无向图，应该与反向一致)" << std::endl;
    }
}

// 测试动态添加顶点
void testDynamicVertexAddition() {
    std::cout << "\n===== 测试动态添加顶点 =====" << std::endl;
    
    // 创建空图
    Graph<char, float, false> g({}, 0);
    
    // 通过添加边动态添加顶点
    g.addEdge('A', 'B', 1.5f);
    g.addEdge('B', 'C', 2.3f);
    g.addEdge('C', 'D', 0.7f);
    g.addEdge('A', 'D', 3.1f);
    
    // 打印图结构
    printGraph(g);
    
    // 验证顶点数量
    std::cout << "顶点数应该为4: " << (g.vertexCount() == 4 ? "通过" : "失败") << std::endl;
    
    // 测试边
    std::cout << "验证边A->C: " << (g.hasEdge('A', 'C') ? "存在(错误)" : "不存在(正确)") << std::endl;
    std::cout << "验证边C->B: " << (g.hasEdge('C', 'B') ? "存在(正确)" : "不存在(错误)") << " (无向图)" << std::endl;
}

int main() {
    // 设置控制台编码为UTF-8
    SetConsoleOutputCP(65001);
    
    std::cout << "图结构测试程序\n" << std::endl;
    
    testIntDirectedGraph();
    testStringUndirectedGraph();
    testDynamicVertexAddition();
    
    std::cout << "\n所有测试完成!" << std::endl;
    return 0;
}