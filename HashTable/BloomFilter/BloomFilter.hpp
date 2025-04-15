#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

template<typename T>
struct DefaultHasher{
    size_t operator()(const T& item, size_t seed) const {
        return std::hash<T>{}(item) ^ seed;
    }
};

// string 的特化
template<>
struct DefaultHasher<std::string> {
    size_t operator()(const std::string& item, size_t seed) const {
        size_t hash = seed;
        for(auto& c : item){
            hash = hash * 131 + c;
        }
        return hash;
    }
};

template<typename T, typename Hasher = DefaultHasher<T>>
class BloomFilter{
private:
    // 整数数组表示位图
    std::vector<int> _bitArray;
    size_t _bitSize;
    // 哈希函数生成器
    Hasher _hashFunc;
    size_t _hashFuncCount;
    size_t _elemCount;
    static const int INT_BITS = 32;

    std::vector<size_t> _calcHashPositions(const T& item) const {
        std::vector<size_t> positions(_hashFuncCount);
        for(int i = 0; i < _hashFuncCount; ++i){
            positions[i] = _hashFunc(item, i) % _bitSize;
        }
        return positions;
    }

    void _setBit(size_t pos){
        size_t arrayIndex = pos / INT_BITS;
        size_t bitOffset = pos % INT_BITS;
        // _bitArray[arrayIndex] |= (1 << bitOffset);
        _bitArray[arrayIndex] |= (1 << bitOffset);
    }

    bool _getBit(size_t pos){
        size_t arrayIndex = pos / INT_BITS;
        size_t bitOffset = pos % INT_BITS;

        return (_bitArray[arrayIndex] & (1 << bitOffset));
    }

public:

    BloomFilter(size_t bitSize = 10000, size_t hashFuncCount = 3)
        : _bitSize(bitSize)
        , _hashFuncCount(hashFuncCount)
        , _elemCount(0)
    {
        // 向上取整的常用操作
        // 避免了使用 std::ceil 函数的浮点数运算
        size_t arraySize = (bitSize + INT_BITS - 1) / INT_BITS;
        _bitArray.resize(arraySize, 0);
    }

    void addElement(const T& item){
        std::vector<size_t> positions = _calcHashPositions(item);
        for(size_t pos : positions){
            _setBit(pos);
        }
        ++_elemCount;
    }

    bool isContains(const T& item){
        if(_elemCount == 0) return false;
        std::vector<size_t> positions = _calcHashPositions(item);
        for(size_t pos : positions){
            if(_getBit(pos) == false) return false;
        }
        return true;
    }

    void printStats() const {
        std::cout << "布隆过滤器统计信息：" << std::endl;
        std::cout << "  位图大小: " << _bitSize << " bits" << std::endl;
        std::cout << "  存储数组大小: " << _bitArray.size() << " ints" << std::endl;
        std::cout << "  哈希函数数量: " << _hashFuncCount << std::endl;
        std::cout << "  已添加元素数量: " << _elemCount << std::endl;
    }

    void clearElement(){
        std::fill(_bitArray.begin(), _bitArray.end(), 0);
        _elemCount = 0;
    }

    // 获取位图总大小（位数）
    size_t size() const {
        return _bitSize;
    }

    // 获取哈希函数数量
    size_t hashFunctionCount() const {
        return _hashFuncCount;
    }

    // 获取已添加元素数量
    size_t elementCount() const {
        return _elemCount;
    }

};