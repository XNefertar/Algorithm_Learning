#pragma once
#include <map>
#include <queue>
#include <vector>
#include <climits>
#include <iostream>

template<typename V, typename W, int MAX_WEIGHT = INT_MAX, bool Direction = false>
class Graph {
private:
    std::vector<std::vector<W>> _adjMatrix;
    std::map<V, size_t> _mapVIndex;
    std::vector<V> _vertSet;
public:
    Graph();
    Graph(const V* vertPtr, size_t n);
    Graph(const std::vector<V>& vertSet, size_t n);
private:

    size_t _getVertIndex(const V& vert);
    void _addEdge(const size_t& startIndex, const size_t& endIndex, const W& weight);

public:

    bool addEdge(const V& start, const V& end, const W& weight);
    void _DFS(const size_t& curIndex, std::vector<bool>& isVisted);

public:

    void DFS(const V& start);
    void BFS(const V& start);

    void graphPrint();
};

#include "Graph.inl"