#pragma once
#include <vector>
#include <iostream>
#include <map>
template<typename W>
struct Edge{
    size_t _dsti;
    W _weight;
    Edge<W>* _next;

    Edge(size_t dsti, const W& weight)
        : _dsti(dsti)
        , _weight(weight)
        , _next(nullptr)
    {}
};

template<typename V, typename W, bool Direction = false>
class Graph{
    using Edge = Edge<W>;
private:
    std::map<V, size_t> _mapVIndex;
    // 顶点集合
    std::vector<V> _vertSet;
    //  邻接表
    std::vector<Edge*> _edgeTable;

private:
    size_t _getVertToIndex(const V& vertex);

    bool _addEdge(const V& start, const V& end, const W& weight);

    bool _hasEdge(const V& start, const V& end);

    bool _getEdgeWeight(const V& start, const V& end, const W& weight);

public:
    // 通过顶点集合初始化图结构
    Graph(const V* vertSet, size_t n);
    ~Graph();

    bool addEdge(const V& start, const V& end, const W& weight);

    bool hasEdge(const V& start, const V& end);

    bool getEdgeWeight(const V& start, const V& end, const W& weight);

    const int vertexCount() const;

    // 添加到Graph类的public部分
    void printAdjList() const;


    size_t edgeCount() const;
};

#include "Graph.inl"