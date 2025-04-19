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
W Graph<V, W, MAX_WEIGHT, Direction>::kruskalAlgorithm(GraphSelf& minTree){
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
W Graph<V, W, MAX_WEIGHT, Direction>::primAlgorithm(GraphSelf& minTree) {
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
        int u = -1;
        
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