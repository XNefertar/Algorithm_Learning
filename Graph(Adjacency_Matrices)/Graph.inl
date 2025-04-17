template<typename V, typename W, int MAX_WEIGHT, bool Direction>
Graph<V, W, MAX_WEIGHT, Direction>::Graph() = default;

template<typename V, typename W, int MAX_WEIGHT, bool Direction>
Graph<V, W, MAX_WEIGHT, Direction>::Graph(const V* vertPtr, size_t n) {
    _vertSet.reserve(n);
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