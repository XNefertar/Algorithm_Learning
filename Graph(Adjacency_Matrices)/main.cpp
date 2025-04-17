#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <windows.h>  // 用于控制台编码设置
#include "Graph.hpp"

// 辅助函数: 打印测试标题
void printTestHeader(const std::string& title) {
    std::cout << "\n===== " << title << " =====\n" << std::endl;
}

// 测试有向图
void testDirectedGraph() {
    printTestHeader("有向图测试");
    
    // 创建有向图
    int vertices[] = {1, 2, 3, 4, 5};
    Graph<int, double, INT_MAX, true> g(vertices, 5);
    
    // 添加边
    std::cout << "添加边: " << std::endl;
    bool success = g.addEdge(1, 2, 0.5);
    std::cout << "  添加边1->2: " << (success ? "成功" : "失败") << std::endl;
    
    g.addEdge(1, 3, 1.0);
    g.addEdge(2, 4, 2.0);
    g.addEdge(3, 5, 1.5);
    g.addEdge(4, 5, 0.7);
    
    // 打印图结构
    std::cout << "\n有向图结构: " << std::endl;
    g.graphPrint();
}

// 测试无向图
void testUndirectedGraph() {
    printTestHeader("无向图测试");
    
    // 创建无向图
    std::string vertices[] = {"北京", "上海", "广州", "深圳", "杭州"};
    Graph<std::string, int> g(vertices, 5);
    
    // 添加边
    std::cout << "添加边: " << std::endl;
    g.addEdge("北京", "上海", 1200);
    g.addEdge("上海", "杭州", 180);
    g.addEdge("广州", "深圳", 140);
    g.addEdge("北京", "广州", 1900);
    
    // 打印图结构
    std::cout << "\n无向图结构: " << std::endl;
    g.graphPrint();
}

// 测试添加非法边的情况
void testInvalidEdges() {
    printTestHeader("非法边测试");
    
    // 创建一个小图
    char vertices[] = {'A', 'B', 'C'};
    Graph<char, float> g(vertices, 3);
    
    // 尝试添加包含不存在顶点的边
    std::cout << "尝试添加含不存在顶点的边: " << std::endl;
    bool success = g.addEdge('A', 'D', 1.5f);
    std::cout << "  添加边A->D: " << (success ? "成功(错误)" : "失败(正确)") << std::endl;
    
    // 添加合法边作为对比
    success = g.addEdge('A', 'B', 2.0f);
    std::cout << "  添加边A->B: " << (success ? "成功(正确)" : "失败(错误)") << std::endl;
    
    // 查看图结构
    std::cout << "\n图结构: " << std::endl;
    g.graphPrint();
}

// 测试从向量构造
void testVectorConstruction() {
    printTestHeader("从向量构造测试");
    
    std::vector<double> vertices = {1.1, 2.2, 3.3, 4.4};
    Graph<double, int> g(vertices, vertices.size());
    
    // 添加一些边
    g.addEdge(1.1, 2.2, 10);
    g.addEdge(2.2, 3.3, 20);
    g.addEdge(3.3, 4.4, 30);
    g.addEdge(4.4, 1.1, 40);
    
    // 打印图结构
    std::cout << "从向量构造的图: " << std::endl;
    g.graphPrint();
}

// 测试添加重复边（应该更新权重）
void testDuplicateEdges() {
    printTestHeader("重复边测试");
    
    int vertices[] = {1, 2, 3};
    Graph<int, int> g(vertices, 3);
    
    // 添加一条边
    std::cout << "添加边1->2, 权重10" << std::endl;
    g.addEdge(1, 2, 10);
    
    // 打印图
    std::cout << "\n初始图结构: " << std::endl;
    g.graphPrint();
    
    // 添加同一条边但权重不同
    std::cout << "\n添加相同边1->2, 权重变为20" << std::endl;
    g.addEdge(1, 2, 20);
    
    // 打印更新后的图
    std::cout << "\n更新后图结构: " << std::endl;
    g.graphPrint();
}

// 测试空图
void testEmptyGraph() {
    printTestHeader("空图测试");
    
    // 创建默认空图
    Graph<int, int> g;
    std::cout << "空图构造成功" << std::endl;
    
    // 尝试在空图上添加边（应该返回false）
    bool success = g.addEdge(1, 2, 10);
    std::cout << "尝试在空图上添加边1->2: " << (success ? "成功(不应该)" : "失败(正确)") << std::endl;
    
    // 尝试打印空图
    std::cout << "\n空图结构: " << std::endl;
    g.graphPrint();
}

// 测试BFS遍历
void testBFS() {
    printTestHeader("BFS遍历测试");
    
    // 创建有向图
    std::cout << "有向图BFS测试:" << std::endl;
    int verts1[] = {1, 2, 3, 4, 5, 6};
    Graph<int, int, INT_MAX, true> dg(verts1, 6);
    
    // 构建有向图 (用 -> 表示方向)
    // 1 -> 2 -> 5
    // |    |
    // v    v
    // 3 -> 4 -> 6
    dg.addEdge(1, 2, 1);
    dg.addEdge(1, 3, 1);
    dg.addEdge(2, 4, 1);
    dg.addEdge(2, 5, 1);
    dg.addEdge(3, 4, 1);
    dg.addEdge(4, 6, 1);
    
    std::cout << "有向图结构:" << std::endl;
    dg.graphPrint();
    
    std::cout << "\n从顶点1开始BFS:" << std::endl;
    dg.BFS(1);  // 预期输出: 1 2 3 4 5 6
    
    std::cout << "\n从顶点3开始BFS:" << std::endl;
    dg.BFS(3);  // 预期输出: 3 4 6
    
    // 创建无向图
    std::cout << "\n无向图BFS测试:" << std::endl;
    char verts2[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    Graph<char, int> ug(verts2, 6);
    
    // 构建无向图 (用 - 表示边)
    // A - B - C
    // |   |   |
    // D - E - F
    ug.addEdge('A', 'B', 1);
    ug.addEdge('A', 'D', 1);
    ug.addEdge('B', 'C', 1);
    ug.addEdge('B', 'E', 1);
    ug.addEdge('C', 'F', 1);
    ug.addEdge('D', 'E', 1);
    ug.addEdge('E', 'F', 1);
    
    std::cout << "无向图结构:" << std::endl;
    ug.graphPrint();
    
    std::cout << "\n从顶点A开始BFS:" << std::endl;
    ug.BFS('A');  // 预期输出类似: A B D C E F
    
    std::cout << "\n从顶点F开始BFS:" << std::endl;
    ug.BFS('F');  // 预期输出类似: F C E B A D
}

// 测试DFS遍历
void testDFS() {
    printTestHeader("DFS遍历测试");
    
    // 创建有向图
    std::cout << "有向图DFS测试:" << std::endl;
    int verts1[] = {1, 2, 3, 4, 5, 6};
    Graph<int, int, INT_MAX, true> dg(verts1, 6);
    
    // 构建有向图 (用 -> 表示方向)
    // 1 -> 2 -> 5
    // |    |
    // v    v
    // 3 -> 4 -> 6
    dg.addEdge(1, 2, 1);
    dg.addEdge(1, 3, 1);
    dg.addEdge(2, 4, 1);
    dg.addEdge(2, 5, 1);
    dg.addEdge(3, 4, 1);
    dg.addEdge(4, 6, 1);
    
    std::cout << "有向图结构:" << std::endl;
    dg.graphPrint();
    
    std::cout << "\n从顶点1开始DFS: ";
    dg.DFS(1);  // 可能输出: 1 2 4 6 5 3
    std::cout << std::endl;
    
    std::cout << "从顶点3开始DFS: ";
    dg.DFS(3);  // 可能输出: 3 4 6
    std::cout << std::endl;
    
    // 创建无向图
    std::cout << "\n无向图DFS测试:" << std::endl;
    char verts2[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    Graph<char, int> ug(verts2, 6);
    
    // 构建无向图 (用 - 表示边)
    // A - B - C
    // |   |   |
    // D - E - F
    ug.addEdge('A', 'B', 1);
    ug.addEdge('A', 'D', 1);
    ug.addEdge('B', 'C', 1);
    ug.addEdge('B', 'E', 1);
    ug.addEdge('C', 'F', 1);
    ug.addEdge('D', 'E', 1);
    ug.addEdge('E', 'F', 1);
    
    std::cout << "无向图结构:" << std::endl;
    ug.graphPrint();
    
    std::cout << "\n从顶点A开始DFS: ";
    ug.DFS('A');  // 可能输出: A B C F E D 或其他变体
    std::cout << std::endl;
    
    std::cout << "从顶点F开始DFS: ";
    ug.DFS('F');  // 可能输出: F C B A D E 或其他变体
    std::cout << std::endl;
}

int main() {
    // 设置控制台编码为UTF-8以显示中文
    SetConsoleOutputCP(65001);
    
    std::cout << "邻接矩阵图结构测试程序\n" << std::endl;
    
    testDirectedGraph();
    testUndirectedGraph();
    testInvalidEdges();
    testVectorConstruction();
    testDuplicateEdges();
    testEmptyGraph();
    testBFS();
    testDFS();
    
    std::cout << "\n所有测试完成!" << std::endl;
    return 0;
}