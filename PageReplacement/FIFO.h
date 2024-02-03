#ifndef FIFO_H
#define FIFO_H

#include <unordered_map>
#include <list>
#include <iostream>

template<typename K, typename V>
class FIFOCache {
private:
    int capacity;
    std::list<K> keys; 
    std::unordered_map<K, V> cache;

public:
    FIFOCache(int capacity) : capacity(capacity) {}

    V get(K key) {
        auto it = cache.find(key);
        if (it == cache.end()) {
            return V(); // 返回V类型的默认值
        }
        return it->second;
    }

    void put(K key, V value) {
        if (capacity == 0) return;
        auto it = cache.find(key);
        if (it != cache.end()) {
            // 如果键已存在，更新其值
            it->second = value;
            return;
        }

        if (keys.size() == capacity) {
            // 如果缓存已满，移除最先进入缓存的键
            K old_key = keys.front();
            keys.pop_front();
            cache.erase(old_key);
        }
        keys.push_back(key);
        cache[key] = value;
    }
};


#endif