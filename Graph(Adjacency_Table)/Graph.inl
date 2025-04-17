#include "Graph.hpp"

template<typename V, typename W, bool Direction>
size_t Graph<V, W, Direction>::_getVertToIndex(const V& vertex){
    auto it = _mapVIndex.find(vertex);
    if(it == _mapVIndex.end()){
        return -1;
    } else {
        return it->second;
    }
}

template<typename V, typename W, bool Direction >
bool Graph<V, W, Direction>::_addEdge(const V& start, const V& end, const W& weight){
    size_t startIndex = _getVertToIndex(start);
    size_t endIndex = _getVertToIndex(end);
    if(startIndex == -1){
        startIndex = _vertSet.size();
        _vertSet.push_back(start);
        _mapVIndex[start] = startIndex;
        _edgeTable.push_back(nullptr);
    }
    if(endIndex == -1){
        endIndex = _vertSet.size();
        _vertSet.push_back(end);
        _mapVIndex[end] = endIndex;
        _edgeTable.push_back(nullptr);
    }
    Edge* tmp = new Edge(endIndex, weight);
    if(_edgeTable[startIndex] == nullptr){
        _edgeTable[startIndex] = tmp;
    } else {
        // 遍历到链表末尾
        // 添加重复边检查
        Edge* current = _edgeTable[startIndex];
        while(current->_next != nullptr){
            if(current->_dsti == endIndex){
                current->_weight = weight;
                return true;
            }
            current = current->_next;
        }
        current->_next = tmp;
    }
    // 无向图添加反向边
    if(Direction == false){
        Edge* revTmp = new Edge(startIndex, weight);
        // 同样正确处理反向边
        if(_edgeTable[endIndex] == nullptr){
            _edgeTable[endIndex] = revTmp;
        } else {
            Edge* current = _edgeTable[endIndex];
            while(current->_next != nullptr){
                if(current->_dsti == startIndex){
                    current->_weight = weight;
                    return true;
                }
                current = current->_next;
            }
            current->_next = revTmp;
        }
    }
    return true;
}


template<typename V, typename W, bool Direction>
bool Graph<V, W, Direction>::_hasEdge(const V& start, const V& end){
    size_t startIndex = _getVertToIndex(start);
    size_t endIndex = _getVertToIndex(end);
    if(startIndex == -1 || endIndex == -1) return false;
    else{
        Edge* current = _edgeTable[startIndex];
        while(current){
            if(current->_dsti == endIndex){
                return true;
            }
            current = current->_next;
        }
        return false;
    }
}



template<typename V, typename W, bool Direction>
bool Graph<V, W, Direction>::_getEdgeWeight(const V& start, const V& end, const W& weight){
    size_t startIndex = _getVertToIndex(start);
    size_t endIndex = _getVertToIndex(end);
    
    if (startIndex == -1 || endIndex == -1) 
        return false;
    
    Edge* current = _edgeTable[startIndex];
    while (current) {
        if (current->_dsti == endIndex) {
            return weight == current->_weight;
        }
        current = current->_next;
    }
    return false;
}


// 通过顶点集合初始化图结构
template<typename V, typename W, bool Direction>
Graph<V, W, Direction>::Graph(const V* vertSet, size_t n){
    _vertSet.reserve(n);
    for(size_t i = 0; i < n; ++i){
        _vertSet.push_back(vertSet[i]);
        _mapVIndex[vertSet[i]] = i;
    }
    _edgeTable.resize(n, nullptr);
}


template<typename V, typename W, bool Direction>
Graph<V, W, Direction>::~Graph(){
    for(auto& head : _edgeTable){
        Edge* current = head;
        while(current){
            Edge* tmp = current;
            current = current->_next;
            delete tmp;
        }
    }
}


template<typename V, typename W, bool Direction>
bool Graph<V, W, Direction>::addEdge(const V& start, const V& end, const W& weight){
    return _addEdge(start, end, weight);
}

template<typename V, typename W, bool Direction>
bool Graph<V, W, Direction>::hasEdge(const V& start, const V& end){
    return _hasEdge(start, end);
}

template<typename V, typename W, bool Direction>
bool Graph<V, W, Direction>::getEdgeWeight(const V& start, const V& end, const W& weight){
    return _getEdgeWeight(start, end, weight);
}

template<typename V, typename W, bool Direction>
const int Graph<V, W, Direction>::vertexCount() const {
    return _vertSet.size();
}


// 添加到Graph类的public部分
template<typename V, typename W, bool Direction>
void Graph<V, W, Direction>::printAdjList() const {
    std::cout << "  顶点   |   邻接节点(权重)" << std::endl;
    std::cout << "------------------------------" << std::endl;
    for (size_t i = 0; i < _vertSet.size(); ++i) {
        std::cout << "  " << _vertSet[i] << "\t|  ";
        Edge* current = _edgeTable[i];
        if (!current) {
            std::cout << "无邻接节点";
        }
        while (current) {
            std::cout << _vertSet[current->_dsti] << "(" << current->_weight << ") ";
            current = current->_next;
        }
        std::cout << std::endl;
    }
}


template<typename V, typename W, bool Direction>
size_t Graph<V, W, Direction>::edgeCount() const {
    size_t count = 0;
    for (size_t i = 0; i < _edgeTable.size(); ++i) {
        Edge* current = _edgeTable[i];
        while (current) {
            ++count;
            current = current->_next;
        }
    }
    // 如果是无向图，边被计算了两次，需要除以2
    return Direction ? count : count / 2;
}