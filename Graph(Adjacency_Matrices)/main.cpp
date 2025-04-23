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

// 测试添加重复边(应该更新权重)
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
    
    // 尝试在空图上添加边(应该返回false)
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


// 测试Kruskal最小生成树算法
void testKruskalAlgorithm() {
    printTestHeader("Kruskal最小生成树算法测试");
    
    // 创建一个无向图
    char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    Graph<char, int> g(vertices, 6);
    
    // 添加边 - 使用经典的MST测试图
    g.addEdge('A', 'B', 6);
    g.addEdge('A', 'C', 1);
    g.addEdge('A', 'D', 5);
    g.addEdge('B', 'C', 5);
    g.addEdge('B', 'E', 3);
    g.addEdge('C', 'D', 5);
    g.addEdge('C', 'E', 6);
    g.addEdge('C', 'F', 4);
    g.addEdge('D', 'F', 2);
    g.addEdge('E', 'F', 6);
    
    std::cout << "原图结构:" << std::endl;
    g.graphPrint();
    
    // 创建最小生成树
    Graph<char, int> mst;
    int totalWeight = g.KruskalAlgorithm(mst);
    
    std::cout << "\n最小生成树结构:" << std::endl;
    mst.graphPrint();
    
    std::cout << "最小生成树总权重: " << totalWeight << std::endl;
    
    // 验证结果
    int expectedWeight = 15;  // A-C(1) + D-F(2) + B-E(3) + C-F(4) + B-C(5) = 15
    std::cout << "验证: " << (totalWeight == expectedWeight ? "正确" : "错误") << std::endl;
}


// 测试Prim最小生成树算法
void testPrimAlgorithm() {
    printTestHeader("Prim最小生成树算法测试");
    
    // 创建一个无向图 - 使用与Kruskal测试相同的图
    char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    Graph<char, int> g(vertices, 6);
    
    g.addEdge('A', 'B', 6);
    g.addEdge('A', 'C', 1);
    g.addEdge('A', 'D', 5);
    g.addEdge('B', 'C', 5);
    g.addEdge('B', 'E', 3);
    g.addEdge('C', 'D', 5);
    g.addEdge('C', 'E', 6);
    g.addEdge('C', 'F', 4);
    g.addEdge('D', 'F', 2);
    g.addEdge('E', 'F', 6);
    
    std::cout << "原图结构:" << std::endl;
    g.graphPrint();
    
    // 创建最小生成树
    Graph<char, int> mst;
    int totalWeight = g.PrimAlgorithm(mst);
    
    std::cout << "\n最小生成树结构:" << std::endl;
    mst.graphPrint();
    
    std::cout << "最小生成树总权重: " << totalWeight << std::endl;
    
    // 验证结果
    int expectedWeight = 15; // 同Kruskal算法结果
    std::cout << "验证: " << (totalWeight == expectedWeight ? "正确" : "错误") << std::endl;
}


void testDijkstraAlgorithm() {
    printTestHeader("Dijkstra最短路径算法测试");
    
    // 创建有向图
    char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    Graph<char, int, INT_MAX, true> g(vertices, 6);
    
    // 添加有向边
    g.addEdge('A', 'B', 10);
    g.addEdge('A', 'C', 3);
    g.addEdge('B', 'D', 2);
    g.addEdge('C', 'B', 4);
    g.addEdge('C', 'D', 8);
    g.addEdge('C', 'E', 2);
    g.addEdge('D', 'E', 7);
    g.addEdge('D', 'F', 4);
    g.addEdge('E', 'F', 6);
    
    std::cout << "图结构:" << std::endl;
    g.graphPrint();
    
    // 打印从A到各顶点的最短路径
    g.printShortestPathDijkstra('A', 'D');  // 期望路径: A->C->B->D, 距离: 9
    g.printShortestPathDijkstra('A', 'F');  // 期望路径: A->C->B->D->F, 距离: 13
    
    // 测试不可达的情况
    g.printShortestPathDijkstra('F', 'A');  // 期望输出: 不存在路径
}

// 测试Bellman-Ford算法
void testBellmanFordAlgorithm() {
    printTestHeader("Bellman-Ford最短路径算法测试");
    
    // 测试1: 带负权边但无负权回路的有向图
    std::cout << "测试1: 带负权边但无负权回路的有向图" << std::endl;
    char vertices1[] = {'A', 'B', 'C', 'D', 'E'};
    Graph<char, int, INT_MAX, true> g1(vertices1, 5);
    
    g1.addEdge('A', 'B', 6);
    g1.addEdge('A', 'C', 7);
    g1.addEdge('B', 'C', 8);
    g1.addEdge('B', 'D', -4);  // 负权边
    g1.addEdge('B', 'E', 5);
    g1.addEdge('C', 'D', 9);
    g1.addEdge('C', 'E', -3);  // 负权边
    g1.addEdge('D', 'E', 7);
    g1.addEdge('D', 'A', 2);
    g1.addEdge('E', 'B', -2);  // 负权边
    
    std::cout << "图结构:" << std::endl;
    g1.graphPrint();
    
    // 打印从A出发到各顶点的最短路径
    std::cout << "A到各顶点的最短路径: " << std::endl;
    g1.printShortestPathBellmanFord('A', 'A');  // 自身到自身
    g1.printShortestPathBellmanFord('A', 'B');
    g1.printShortestPathBellmanFord('A', 'C');
    g1.printShortestPathBellmanFord('A', 'D');
    g1.printShortestPathBellmanFord('A', 'E');
    
    // 测试2: 带负权回路的有向图
    std::cout << "\n测试2: 带负权回路的有向图" << std::endl;
    char vertices2[] = {'A', 'B', 'C', 'D'};
    Graph<char, int, INT_MAX, true> g2(vertices2, 4);
    
    g2.addEdge('A', 'B', 1);
    g2.addEdge('B', 'C', 2);
    g2.addEdge('C', 'D', 3);
    g2.addEdge('D', 'A', -7);  // 形成负权回路: A->B->C->D->A总权重为-1
    
    std::cout << "图结构:" << std::endl;
    g2.graphPrint();
    
    // 尝试计算最短路径，应该检测到负权回路
    g2.printShortestPathBellmanFord('A', 'C');
    
    // 测试3: 与Dijkstra算法比较(无负权边的图)
    std::cout << "\n测试3: 与Dijkstra算法比较(无负权边的图)" << std::endl;
    char vertices3[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    Graph<char, int, INT_MAX, true> g3(vertices3, 6);
    
    // 使用与Dijkstra测试相同的图
    g3.addEdge('A', 'B', 10);
    g3.addEdge('A', 'C', 3);
    g3.addEdge('B', 'D', 2);
    g3.addEdge('C', 'B', 4);
    g3.addEdge('C', 'D', 8);
    g3.addEdge('C', 'E', 2);
    g3.addEdge('D', 'E', 7);
    g3.addEdge('D', 'F', 4);
    g3.addEdge('E', 'F', 6);
    
    std::cout << "图结构:" << std::endl;
    g3.graphPrint();
    
    std::cout << "Dijkstra算法结果:" << std::endl;
    g3.printShortestPathDijkstra('A', 'F');
    
    std::cout << "Bellman-Ford算法结果:" << std::endl;
    g3.printShortestPathBellmanFord('A', 'F');
}


void testFloydWarshallAlgorithm() {
    printTestHeader("Floyd-Warshall最短路径算法测试");
    
    // 测试1: 基本有向图
    std::cout << "\n测试1: 基本有向图" << std::endl;
    char vertices1[] = {'A', 'B', 'C', 'D'};
    Graph<char, int, INT_MAX, true> g1(vertices1, 4);
    
    g1.addEdge('A', 'B', 5);
    g1.addEdge('A', 'C', 3);
    g1.addEdge('B', 'C', 2);
    g1.addEdge('B', 'D', 1);
    g1.addEdge('C', 'D', 6);
    
    std::cout << "图结构:" << std::endl;
    g1.graphPrint();
    
    // 打印所有点对最短路径
    g1.printShortestPathFloydWarshall('A', 'D');  // 期望: A->B->D, 距离6
    g1.printShortestPathFloydWarshall('A', 'C');  // 期望: A->C, 距离3
    g1.printShortestPathFloydWarshall('C', 'B');  // 期望: 不存在路径
    
    // 测试2: 带负权边的图
    std::cout << "\n测试2: 带负权边的图" << std::endl;
    char vertices2[] = {'A', 'B', 'C', 'D', 'E'};
    Graph<char, int, INT_MAX, true> g2(vertices2, 5);
    
    g2.addEdge('A', 'B', 3);
    g2.addEdge('A', 'C', 8);
    g2.addEdge('A', 'E', -4);
    g2.addEdge('B', 'D', 1);
    g2.addEdge('B', 'E', 7);
    g2.addEdge('C', 'B', 4);
    g2.addEdge('D', 'C', -5);
    g2.addEdge('D', 'A', 2);
    g2.addEdge('E', 'D', 6);
    
    std::cout << "图结构:" << std::endl;
    g2.graphPrint();
    
    g2.printShortestPathFloydWarshall('A', 'C');  // 期望: A->E->D->C, 距离-3
    g2.printShortestPathFloydWarshall('B', 'A');  // 期望: B->D->A, 距离3
    g2.printShortestPathFloydWarshall('E', 'B');  // 期望: E->D->C->B, 距离5
    
    // 测试3: 与其他算法比较
    std::cout << "\n测试3: 与Dijkstra算法比较" << std::endl;
    char vertices3[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    Graph<char, int, INT_MAX, true> g3(vertices3, 6);
    
    // 使用与Dijkstra测试相同的图
    g3.addEdge('A', 'B', 10);
    g3.addEdge('A', 'C', 3);
    g3.addEdge('B', 'D', 2);
    g3.addEdge('C', 'B', 4);
    g3.addEdge('C', 'D', 8);
    g3.addEdge('C', 'E', 2);
    g3.addEdge('D', 'E', 7);
    g3.addEdge('D', 'F', 4);
    g3.addEdge('E', 'F', 6);
    
    std::cout << "图结构:" << std::endl;
    g3.graphPrint();
    
    std::cout << "Dijkstra算法结果:" << std::endl;
    g3.printShortestPathDijkstra('A', 'F');
    
    std::cout << "Floyd-Warshall算法结果:" << std::endl;
    g3.printShortestPathFloydWarshall('A', 'F');
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
    testKruskalAlgorithm();
    testPrimAlgorithm();
    testDijkstraAlgorithm();
    testBellmanFordAlgorithm();
    testFloydWarshallAlgorithm();
    
    std::cout << "\n所有测试完成!" << std::endl;
    return 0;
}