
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <list>
#include <utility>
#include <functional>

template <typename Key, typename Value>
class HashTable {
private:
    static const int DEFAULT_CAPACITY = 101;
    std::vector<std::list<std::pair<Key, Value>>> table;
    int size;

public:
    int collisionCount = 0;
    int comparisonCount = 0;

    HashTable() : table(DEFAULT_CAPACITY), size(0) {}

    void insert(const Key& key, const Value& value) {
        int idx = hashFunc(key);
        auto& bucket = table[idx];
        if (!bucket.empty()) collisionCount++;
        for (auto& pair : bucket) {
            comparisonCount++;
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        bucket.emplace_back(key, value);
        size++;
    }

    bool find(const Key& key, Value& result) {
        int idx = hashFunc(key);
        for (auto& pair : table[idx]) {
            comparisonCount++;
            if (pair.first == key) {
                result = pair.second;
                return true;
            }
        }
        return false;
    }

    int hashFunc(const Key& key) const {
        return std::hash<Key>{}(key) % table.size();
    }
};

#endif
