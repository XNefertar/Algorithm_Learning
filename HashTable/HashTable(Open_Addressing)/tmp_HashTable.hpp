#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
enum HASH_STATUS {
    EMPTY = 0,
    OCCUPIED,
    DELETED
};

template<typename K, typename V>
struct HashEntry {
    K           _key;
    V           _value;
    HASH_STATUS _status;

    HashEntry() : _status(EMPTY) {}
};

template<typename K, typename V>
class HashTable {
	typedef HashEntry<K, V> HashEntry;
private:
    int _count;
    std::vector<HashEntry> _hashTable;
private:
    K calcHash(const K& key) {
        return key % _hashTable.size();
    }

    bool expandMemory() {
        HashTable<K, V> tmp((int)_hashTable.size() * 2);

        for (auto& it : _hashTable) {
            if (it._status == OCCUPIED) {
                int index = calcHash(it._key);
                tmp.insertEntry(std::make_pair(it._key, it._value));
            }
        }
        _hashTable.swap(tmp._hashTable);
        return true;
    }

public:
    HashTable(int size = 10)
        : _count(0)
        , _hashTable(size)
    {
    }

    bool insertEntry(const std::pair<K, V>& kv) {
        // 计算负载因子
        double loadFactor = (double)_count / _hashTable.size();
        // 负载因子大于等于 0.7 触发扩容
        if (loadFactor >= 0.7) {
            if (!expandMemory()) return false;
        }
        int index = calcHash(kv.first);
        while (_hashTable[index]._status == OCCUPIED) {
            // _hashTable[index]._value = kv.second;
            index = (index + 1) % _hashTable.size();
        }

        _hashTable[index]._key = kv.first;
        _hashTable[index]._value = kv.second;
        _hashTable[index]._status = OCCUPIED;

        ++_count;
        return true;
    }

    HashEntry* findEntry(const K& k) {
        int index = calcHash(k);
        while (_hashTable[index]._status != EMPTY) {
            if (_hashTable[index]._key == k) {
                return &_hashTable[index];
            }
            index = (index + 1) % _hashTable.size();
        }
        return nullptr;
    }

    bool eraseEntry(const K& k) {
        HashEntry* target = findEntry(k);
        if (target != nullptr) {
            target->_status = DELETED;
            --_count;
            return true;
        }
        return false;
    }
};

