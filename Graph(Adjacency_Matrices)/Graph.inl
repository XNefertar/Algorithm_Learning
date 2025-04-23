#include "Graph.hpp"
template<typename V, typename W, int MAX_WEIGHT, bool Direction>
Graph<V, W, MAX_WEIGHT, Direction>::Graph() = default;

template<typename V, typename W, int MAX_WEIGHT, bool Direction>
Graph<V, W, MAX_WEIGHT, Direction>::Graph(const V* vertPtr, size_t n) {
    _vertSet.reserve(n);
    _unionIndex.resize(n, -1);
    for (size_t i = 0; i < n; ++i) {
        _vertSet.push_back(vertPtr[i]);
        _mapVIndex[vertPtr[i]] = i;
    }
    _adjMatrix.resize(n);
    for (size_t i = 0; i < n; ++i) {
        _adjMatrix[i].resize(n, MAX_WEIGHT);
    }
}

template<typename V, typename W, int MAX_WEIGHT, bool Direction>
Graph<V, W, MAX_WEIGHT, Direction>::Graph(const std::vector<V>& vertSet, size_t n) {
    _vertSet.reserve(n);
    _unionIndex.resize(n, -1);
    for (size_t i = 0; i < n; ++i) {
        _vertSet.push_back(vertSet[i]);
        _mapVIndex[vertSet[i]] = i;
    }
    _adjMatrix.resize(n);
    for (size_t i = 0; i < n; ++i) {
        _adjMatrix[i].resize(n, MAX_WEIGHT);
    }
}

template<typename V, typename W, int MAX_WEIGHT, bool Direction>
size_t Graph<V, W, MAX_WEIGHT, Direction>::_getVertIndex(const V& vert) {
    auto it = _mapVIndex.find(vert);
    if (it == _mapVIndex.end()) {
        return -1;
    }
    else {
        return it->second;
    }
}


template<typename V, typename W, int MAX_WEIGHT, bool Direction>
void Graph<V, W, MAX_WEIGHT, Direction>::_addEdge(const size_t& startIndex, const size_t& endIndex, const W& weight) {
    _adjMatrix[startIndex][endIndex] = weight;
    if (Direction == false) {
        _adjMatrix[endIndex][startIndex] = weight;
    }
}


template<typename V, typename W, int MAX_WEIGHT, bool Direction>
bool Graph<V, W, MAX_WEIGHT, Direction>::addEdge(const V& start, const V& end, const W& weight) {
    size_t startIndex = _getVertIndex(start);
    size_t endIndex = _getVertIndex(end);
    if (startIndex != -1 && endIndex != -1) {
        _addEdge(startIndex, endIndex, weight);
        return true;
    }
    else {
        return false;
    }
}


template<typename V, typename W, int MAX_WEIGHT, bool Direction>
void Graph<V, W, MAX_WEIGHT, Direction>::_DFS(const size_t& curIndex, std::vector<bool>& isVisited){
    std::cout << _vertSet[curIndex] << " ";
    for(int i = 0; i < _adjMatrix[curIndex].size(); ++i){
        if(_adjMatrix[curIndex][i] != MAX_WEIGHT && !isVisited[i]){
            isVisited[i] = true;
            _DFS(i, isVisited);
            // isVisited[_getVertIndex(_vertSet[i])] = false;
        }
    }
}


template<typename V, typename W, int MAX_WEIGHT, bool Direction>
void Graph<V, W, MAX_WEIGHT, Direction>::DFS(const V& start){
    std::vector<bool> isVisited(_vertSet.size(), false);
    size_t startIndex = _getVertIndex(start);
    isVisited[startIndex] = true;
    _DFS(startIndex, isVisited);
}


template<typename V, typename W, int MAX_WEIGHT, bool Direction>
void Graph<V, W, MAX_WEIGHT, Direction>::BFS(const V& start) {
    std::queue<V>       _vQueue;
    std::vector<bool>   _isVisted(_vertSet.size(), false);
    size_t startIndex = _getVertIndex(start);
    _vQueue.push(start);
    _isVisted[startIndex] = true;
    std::cout << _vertSet[startIndex] << " ";
    int levelSize = 1;
    while (!_vQueue.empty()) {
        auto& it = _vQueue.front();
        size_t curIndex = _getVertIndex(it);
        _vQueue.pop();
        for (int i = 0; i < levelSize; ++i) {
            int n = _adjMatrix[curIndex].size();
            for (int index = 0; index < n; ++index) {
                if (_adjMatrix[curIndex][index] != MAX_WEIGHT && _isVisted[index] == false) {
                    _vQueue.push(_vertSet[index]);
                    _isVisted[index] = true;
                    std::cout << _vertSet[index] << " ";
                }
            }
        }
        levelSize = _vQueue.size();
    }
}


template<typename V, typename W, int MAX_WEIGHT, bool Direction>
void Graph<V, W, MAX_WEIGHT, Direction>::graphPrint() {
    for (size_t i = 0; i < _vertSet.size(); ++i) {
        std::cout << _vertSet[i] << ": ";
        for (size_t j = 0; j < _adjMatrix[i].size(); ++j) {
            if (_adjMatrix[i][j] != MAX_WEIGHT) {
                std::cout << "(" << _vertSet[j] << ", " << _adjMatrix[i][j] << ") ";
            }
        }
        std::cout << std::endl;
    }
}


template<typename V, typename W, int MAX_WEIGHT, bool Direction>
W Graph<V, W, MAX_WEIGHT, Direction>::KruskalAlgorithm(GraphSelf& minTree){
    // initialize
    size_t n = _vertSet.size();
    minTree._mapVIndex = this->_mapVIndex;
    minTree._vertSet = this->_vertSet;
    // minTree._unionIndex = this->_unionIndex;
    minTree._unionIndex.resize(n, -1);
    minTree._adjMatrix.resize(n);
    for(int i = 0; i < n; ++i){
        minTree._adjMatrix[i].resize(n, MAX_WEIGHT);
    }

    std::priority_queue<Edge<W>, std::vector<Edge<W>>, std::greater<Edge<W>>> _priEdge;
    for(size_t i = 0; i < n; ++i){
        for(size_t j = 0; j < n; ++j){
            if(i < j && _adjMatrix[i][j] != MAX_WEIGHT){
                _priEdge.push(Edge<W>{i, j, _adjMatrix[i][j]});
            }
        }
    }

    // 选出 n - 1 条边
    int size = 0;
    W totalWeight{};

    while(!_priEdge.empty()){
        Edge<W> tmp = _priEdge.top();
        _priEdge.pop();
        size_t startIndex = tmp._startIndex;
        size_t endIndex = tmp._endIndex;
        if(_findRoot(startIndex) != _findRoot(endIndex)){
            _unionVert(startIndex, endIndex);

            minTree._addEdge(startIndex, endIndex, tmp._weight);
            ++size;
            totalWeight += tmp._weight;
            
        } else {
            std::cout << "不加入最小生成树, 构成环: ";
            std::cout << _vertSet[tmp._startIndex] << " -> " << _vertSet[tmp._endIndex] \
            << ": " << tmp._weight << std::endl;
        }
    }
    if(size == n - 1){
        std::cout << "克鲁斯卡尔算法可以生成对应的最小生成树..." << std::endl;
    } else{
        std::cout << "无法生成最小生成树..." << std::endl;
    }
    return totalWeight;
}


template<typename V, typename W, int MAX_WEIGHT, bool Direction>
W Graph<V, W, MAX_WEIGHT, Direction>::PrimAlgorithm(GraphSelf& minTree) {
    size_t n = _vertSet.size();
    minTree._vertSet = this->_vertSet;
    minTree._mapVIndex = this->_mapVIndex;
    minTree._adjMatrix.resize(n);
    for(int i = 0; i < n; ++i){
        minTree._adjMatrix[i].resize(n, MAX_WEIGHT);
    }

    std::vector<bool> _inTree(n, false);
    std::vector<int> _parent(n, -1);
    std::vector<int> _minDist(n, MAX_WEIGHT);

    W totalWeight{};
    _minDist[0] = 0;

    for(size_t i = 0; i < n; ++i){
        W minWeight = MAX_WEIGHT;
        size_t u = -1;
        
        // 找出最小权值
        for(size_t j = 0; j < n; ++j){
            if(!_inTree[j] && _minDist[j] < minWeight){
                u = j;
                minWeight = _minDist[j];
            }
        }

        if(u == -1){
            std::cout << "存在独立节点, 无法构成完整的最小生成树..." << std::endl;
            break;
        }

        _inTree[u] = true;
        totalWeight += minWeight;

        // 如果不是第一个顶点，添加连接边
        if (_parent[u] != -1){
            minTree._addEdge(_parent[u], u, _minDist[u]);
            std::cout << "添加边: " << _vertSet[_parent[u]] << " -> "
                      << _vertSet[u] << " 权重: " << _minDist[u] << std::endl;
        }

        // 更新每个点的最小权值
        for(size_t v = 0; v < n; ++v){
            if(!_inTree[v] && _adjMatrix[u][v] != MAX_WEIGHT && _adjMatrix[u][v] < _minDist[v]){
                _minDist[v] = _adjMatrix[u][v];
                _parent[v] = u;
            }
        }
    }

    if(totalWeight < MAX_WEIGHT){
        std::cout << "Prim算法构建最小生成树成功..." << std::endl;
    } else {
        std::cout << "Prim算法构建最小生成树失败..." << std::endl;
    }

    return totalWeight;
}


template<typename V, typename W, int MAX_WEIGHT, bool Direction>
void Graph<V, W, MAX_WEIGHT, Direction>::DijkstraAlgorithm(const V& start, std::vector<W>& _distance, std::vector<int>& _path){
    size_t n = _vertSet.size();
    size_t startIndex = _getVertIndex(start);

    if(startIndex == -1) {
        std::cout << "起点不存在..." << std::endl;
        return;
    }

    std::vector<bool> _isVisited(n, false);
    _distance.resize(n, MAX_WEIGHT);
    _path.resize(n, -1);

    _distance[startIndex] = 0;

    for(size_t i = 0; i < n; ++i){
        size_t u = -1;
        W minDist = MAX_WEIGHT;

        for(size_t j = 0; j < n; ++j){
            if(!_isVisited[j] && _distance[j] < minDist){
                minDist = _distance[j];
                u = j;
            }
        }

        if(u == -1) break;

        _isVisited[u] = true;
        for(size_t v = 0; v < n; ++v){
            if(!_isVisited[v] && _adjMatrix[u][v] != MAX_WEIGHT
            && _distance[u] + _adjMatrix[u][v] < _distance[v]){
                _distance[v] = _distance[u] + _adjMatrix[u][v];
                _path[v] = u;
            }
        }

    }
}


template<typename V, typename W, int MAX_WEIGHT, bool Direction>
bool Graph<V, W, MAX_WEIGHT, Direction>::BellmanFordAlgorithm(const V& start, std::vector<W>& _distance, std::vector<int>& _path){
    size_t n = _vertSet.size();
    size_t startIndex = _getVertIndex(start);
    if(startIndex == -1){
        std::cout << "起点不存在..." << std::endl;
        return false;
    }

    _distance.resize(n, MAX_WEIGHT);
    _distance[startIndex] = W{};

    _path.resize(n, -1);

    for(size_t k = 1; k <= n; ++k){
        bool update = false;
        // std::cout << "更新第 " << k << " 轮: " << std::endl;
        for(size_t i = 0; i < n; ++i){
            for(size_t j = 0; j < n; ++j){
                if(_adjMatrix[i][j] != MAX_WEIGHT && _distance[i] != MAX_WEIGHT && _adjMatrix[i][j] + _distance[i] < _distance[j]){
                    _distance[j] = _adjMatrix[i][j] + _distance[i];
                    update = true;
                    _path[j] = i; 
                }
            }
        }
        if(!update){
            break;
        }
    }

    for(size_t i = 0; i < n; ++i){
        for(size_t j = 0; j < n; ++j){
            if(_adjMatrix[i][j] != MAX_WEIGHT && _distance[i] != MAX_WEIGHT && _adjMatrix[i][j] + _distance[i] < _distance[j]){
                std::cout << "存在负权回路, 更新中断..." << std::endl;
                return false;
            }
        }
    }
    return true;
}


template<typename V, typename W, int MAX_WEIGHT, bool Direction>
void Graph<V, W, MAX_WEIGHT, Direction>::FloydWarshallAlgorithm(std::vector<std::vector<W>>& _distance, std::vector<std::vector<int>>& _path){
    size_t n = _vertSet.size();
    _distance.resize(n);
    _path.resize(n);

    for(size_t i = 0; i < n; ++i){
        _distance[i].resize(n, MAX_WEIGHT);
        _path[i].resize(n, -1);
    }
    
    for(size_t i = 0; i < n; ++i){
        for(size_t j = 0; j < n; ++j){
            if(_adjMatrix[i][j] != MAX_WEIGHT){
                _distance[i][j] = _adjMatrix[i][j];
                _path[i][j] = i;
            }
        }
        _distance[i][i] = W{};
    }

    for(size_t k = 0; k < n; ++k){
        for(size_t i = 0; i < n; ++i){
            for(size_t j = 0; j < n; ++j){
                if(_distance[i][k] != MAX_WEIGHT && _distance[k][j] != MAX_WEIGHT && _distance[i][j] > _distance[i][k] + _distance[k][j]){
                    _distance[i][j] = _distance[i][k] + _distance[k][j];
                    _path[i][j] = _path[k][j];
                }
            }
        }
    }

    for(size_t i = 0; i < n; ++i){
        if(_distance[i][i] < W{}){
            std::cout << "图中存在负权环!" << std::endl;
            break;
        }
    }
}


// 打印从起点到终点的最短路径
template<typename V, typename W, int MAX_WEIGHT, bool Direction>
void Graph<V, W, MAX_WEIGHT, Direction>::printShortestPathDijkstra(const V& start, const V& end) {
    std::vector<W> distance;
    std::vector<int> path;
    
    DijkstraAlgorithm(start, distance, path);
    
    size_t endIdx = _getVertIndex(end);
    if(endIdx == -1) {
        std::cout << "终点不存在!" << std::endl;
        return;
    }
    
    if(distance[endIdx] == MAX_WEIGHT) {
        std::cout << "从 " << start << " 到 " << end << " 不存在路径!" << std::endl;
        return;
    }
    
    std::cout << "从 " << start << " 到 " << end << " 的最短距离为: " << distance[endIdx] << std::endl;
    std::cout << "路径: ";
    
    // 重建路径
    std::vector<V> shortestPath;
    size_t current = endIdx;
    
    while(current != -1) {
        shortestPath.push_back(_vertSet[current]);
        current = path[current];
    }
    
    // 反向输出路径
    for(int i = shortestPath.size() - 1; i >= 0; --i) {
        std::cout << shortestPath[i];
        if(i > 0) std::cout << " -> ";
    }
    std::cout << std::endl;
}


// 打印从起点到终点的最短路径
template<typename V, typename W, int MAX_WEIGHT, bool Direction>
void Graph<V, W, MAX_WEIGHT, Direction>::printShortestPathBellmanFord(const V& start, const V& end) {
    std::vector<W> distance;
    std::vector<int> path;
    
    if (!BellmanFordAlgorithm(start, distance, path)) {
        return;
    }
    
    size_t endIdx = _getVertIndex(end);
    if(endIdx == -1) {
        std::cout << "终点不存在!" << std::endl;
        return;
    }
    
    if(distance[endIdx] == MAX_WEIGHT) {
        std::cout << "从 " << start << " 到 " << end << " 不存在路径!" << std::endl;
        return;
    }
    
    std::cout << "从 " << start << " 到 " << end << " 的最短距离为: " << distance[endIdx] << std::endl;
    std::cout << "路径: ";
    
    // 重建路径
    std::vector<V> shortestPath;
    size_t current = endIdx;
    
    while(current != -1) {
        shortestPath.push_back(_vertSet[current]);
        current = path[current];
    }
    
    // 反向输出路径
    for(int i = shortestPath.size() - 1; i >= 0; --i) {
        std::cout << shortestPath[i];
        if(i > 0) std::cout << " -> ";
    }
    std::cout << std::endl;
}

template<typename V, typename W, int MAX_WEIGHT, bool Direction>
void Graph<V, W, MAX_WEIGHT, Direction>::printShortestPathFloydWarshall(const V& start, const V& end) {
    std::vector<std::vector<W>> distance;
    std::vector<std::vector<int>> path;
    
    FloydWarshallAlgorithm(distance, path);
    
    size_t startIdx = _getVertIndex(start);
    size_t endIdx = _getVertIndex(end);
    
    if(startIdx == -1 || endIdx == -1) {
        std::cout << "起点或终点不存在!" << std::endl;
        return;
    }
    
    if(distance[startIdx][endIdx] == MAX_WEIGHT) {
        std::cout << "从 " << start << " 到 " << end << " 不存在路径!" << std::endl;
        return;
    }
    
    std::cout << "从 " << start << " 到 " << end << " 的最短距离为: " << distance[startIdx][endIdx] << std::endl;
    std::cout << "路径: ";
    
    std::vector<V> fullPath;
    std::function<void(size_t, size_t)> buildPath = [&](size_t u, size_t v) {
        if (u == v) {
            fullPath.push_back(_vertSet[u]);
            return;
        }
        
        if (path[u][v] == -1) {
            // 直接连接
            fullPath.push_back(_vertSet[u]);
            fullPath.push_back(_vertSet[v]);
        } else {
            size_t mid = path[u][v];
            if (mid == u || mid == v) {
                // 直接连接
                fullPath.push_back(_vertSet[u]);
                fullPath.push_back(_vertSet[v]);
            } else {
                // 通过中间节点
                buildPath(u, mid);
                // 避免重复
                fullPath.pop_back();  
                buildPath(mid, v);
            }
        }
    };
    
    buildPath(startIdx, endIdx);
    
    // 输出路径
    for (size_t i = 0; i < fullPath.size(); ++i) {
        std::cout << fullPath[i];
        if (i < fullPath.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
}