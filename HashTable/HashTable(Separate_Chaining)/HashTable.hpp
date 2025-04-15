#pragma once
#include <vector>
#include <string>
#include <utility>  // 添加std::pair
#include <list>


template<typename K, typename V>
struct HashNode {
    K _key;
    V _value;
    HashNode* _next;

    HashNode()
        : _key(0)
        , _value(0)
        , _next(nullptr)
    {
    }

    HashNode(const K& k, const V& v)
        : _key(k)
        , _value(v)
        , _next(nullptr)
    {
    }
};

template<typename K>
struct DefaultHasher {
    size_t operator()(const K& k) {
        return std::hash<K>{}(k);
    }
};

template<>
struct DefaultHasher<std::string> {
    size_t operator()(const std::string& item) const {
        int hash = 1;
        for (auto& c : item) {
            hash = hash * 131 + c;
        }
        return hash;
    }
};

template<typename K, typename V, class Hasher = DefaultHasher<K>>
class HashTable {
    using HashNode = HashNode<K, V>;
private:
    Hasher _hashFunc;
    size_t _elemCount;
    size_t _tableSize;
    std::vector<HashNode*> _hashTable;

private:
    size_t _calcHashPos(const K& k) {
        return _hashFunc(k);
    }
public:
    HashTable(size_t tableSize = 10)
        : _elemCount(0)
        , _tableSize(tableSize)
        , _hashTable(tableSize, nullptr)
    {
    }

    bool addElement(const std::pair<K, V>& kv) {
        size_t pos = _hashFunc(kv.first) % _tableSize;
        auto it = _hashTable[pos];

        if (it == nullptr) {
            _hashTable[pos] = new HashNode(kv.first, kv.second);
        }
        else {
            HashNode* parent = nullptr;
            while (it->_key != kv.first) {
                parent = it;
                it = it->_next;
                if (it == nullptr) {
                    it = new HashNode(kv.first, kv.second);
                    parent->_next = it;
                }
            }
			it->_value = kv.second;
        }
        return true;
    }

    bool findElement(const std::pair<K, V>& kv) {
        size_t pos = _hashFunc(kv.first) % _tableSize;
        auto it = _hashTable[pos];
        if (it == nullptr) {
            return false;
        }
        else {
            while (it->_key != kv.first) {
                it = it->_next;
                if (it == nullptr) {
                    return false;
                }
            }
			kv.second = it->_value;
            return true;
        }
    }

    bool findElement(const K& k, V& v) {
        size_t pos = _hashFunc(k) % _tableSize;
        auto it = _hashTable[pos];
        if (it == nullptr) {
            return false;
        }
        else {
            while (it->_key != k) {
                it = it->_next;
                if (it == nullptr) {
                    return false;
                }
            }
            v = it->_value;
            return true;
        }
    }
};
