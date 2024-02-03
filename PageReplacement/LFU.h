#ifndef LFU_H
#define LFU_H
#include <unordered_map>
#include <list>
#include <iostream>

template<typename K, typename V>
struct LFUNode {
    K key;
    V value;
    int frequency;
    LFUNode(K key, V value, int frequency) : key(key), value(value), frequency(frequency) {}
};

template<typename K, typename V>
class LFUCache {
private:
    int minFrequency, capacity;
    std::unordered_map<K, typename std::list<LFUNode<K, V>>::iterator> keyTable;
    std::unordered_map<int, std::list<LFUNode<K, V>>> frequencyTable;

    // 移除最不经常使用的节点
    void evictNode() {
        auto& node_list = frequencyTable[minFrequency];
        auto least_freq_node = node_list.back();
        keyTable.erase(least_freq_node.key);
        node_list.pop_back();
        if (node_list.empty()) {
            frequencyTable.erase(minFrequency);
        }
    }

    // 更新节点频率
    void updateFrequency(typename std::list<LFUNode<K, V>>::iterator nodeIterator, V newValue) {
        int frequency = nodeIterator->frequency;
        K key = nodeIterator->key;
        frequencyTable[frequency].erase(nodeIterator);
        if (frequencyTable[frequency].empty()) {
            frequencyTable.erase(frequency);
            if (frequency == minFrequency) {
                minFrequency++;
            }
        }
        frequencyTable[frequency + 1].emplace_front(LFUNode<K, V>(key, newValue, frequency + 1));
        keyTable[key] = frequencyTable[frequency + 1].begin();
    }

public:
    LFUCache(int capacity) : capacity(capacity) {
        minFrequency = 0;
    }

    V get(K key) {
        if (capacity == 0) {
            return V(); // 返回V类型的默认值
        }
        auto it = keyTable.find(key);
        if (it == keyTable.end()) return V(); // 返回V类型的默认值
        V value = it->second->value;
        updateFrequency(it->second, value);
        return value;
    }

    void put(K key, V value) {
        if (capacity == 0) return;
        auto it = keyTable.find(key);
        if (it != keyTable.end()) {
            // 如果键已存在，更新其值和频率
            updateFrequency(it->second, value);
        } else {
            // 如果缓存已满，移除最不经常使用的节点
            if (keyTable.size() == capacity) {
                evictNode();
            }
            frequencyTable[1].emplace_front(LFUNode<K, V>(key, value, 1));
            keyTable[key] = frequencyTable[1].begin();
            minFrequency = 1;
        }
    }
};

#endif