#pragma once
#include <map>
#include <queue>
#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
#include <functional>

template<typename W>
struct Edge{
    size_t _startIndex;
    size_t _endIndex;
    W _weight;

    Edge(const size_t& startIndex, const size_t& endIndex, const W& weight)
        : _startIndex(startIndex)
        , _endIndex(endIndex)
        , _weight(weight)
    {}

    bool operator<(const Edge& edge) const {
        return this->_weight < edge._weight;
    }
    bool operator>(const Edge& edge) const {
        return this->_weight > edge._weight;
    }
};


template<typename V, typename W, int MAX_WEIGHT = INT_MAX, bool Direction = false>
class Graph {
    using GraphSelf = Graph<V, W, MAX_WEIGHT, Direction>;
private:
    std::vector<std::vector<W>> _adjMatrix;
    std::map<V, size_t> _mapVIndex;
    std::vector<V> _vertSet;
    std::vector<int> _unionIndex;
public:
    Graph();
    Graph(const V* vertPtr, size_t n);
    Graph(const std::vector<V>& vertSet, size_t n);
private:

    size_t _getVertIndex(const V& vert);
    void _addEdge(const size_t& startIndex, const size_t& endIndex, const W& weight);

private:
    // 查找并返回顶点所在的集合的根的下标
    std::function< size_t (size_t)> _findRoot = [this](size_t vertIndex) -> size_t {
        while(_unionIndex[vertIndex] >= 0){
            vertIndex = _unionIndex[vertIndex];
        }
        return vertIndex;
    };

    // 合并两个顶点所在的集合
    std::function< void (size_t, size_t)> _unionVert = [this](size_t vert1Index, size_t vert2Index) -> void {
        size_t root1 = this->_findRoot(vert1Index);
        size_t root2 = this->_findRoot(vert2Index);
        
        if(root1 != root2){
            if(std::abs(_unionIndex[root1]) > std::abs(_unionIndex[root2])){
                _unionIndex[root2] = root1;
            } else {
                _unionIndex[root1] = root2;
            }
        }
    };

public:

    bool addEdge(const V& start, const V& end, const W& weight);
    void _DFS(const size_t& curIndex, std::vector<bool>& isVisted);

public:

    void DFS(const V& start); 
    void BFS(const V& start);
    W kruskalAlgorithm(GraphSelf& minTree);
    W primAlgorithm(GraphSelf& minTree);
    void dijkstraAlgorithm(const V& start, std::vector<W>& distance, std::vector<int>& path);
    bool BellmanFordAlgorithm(const V& start, std::vector<W>& distance, std::vector<int>& path);
    void printShortestPathDijkstra(const V& start, const V& end);
    void printShortestPathBellmanFord(const V& start, const V& end);

    void graphPrint();
};

#include "Graph.inl"