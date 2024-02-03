#ifndef LRU_H
#define LRU_H
#include <unordered_map>
#include <iostream>

// 定义泛型的双向链表节点
template<typename K, typename V>
struct LRUNode {
    K key;
    V value;
    LRUNode* prev;
    LRUNode* next;
    LRUNode(K k, V v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

// 定义泛型的LRU缓存类
template<typename K, typename V>
class LRUCache {
private:
    int capacity; // 缓存的容量
    // 哈希表，用于O(1)时间内查找节点
    std::unordered_map<K, LRUNode<K, V>*> cache;
    LRUNode<K, V>* head; // 双向链表的伪头部
    LRUNode<K, V>* tail; // 双向链表的伪尾部

    // 移动节点到双向链表头部
    void moveToHead(LRUNode<K, V>* node) {
        removeNode(node);
        addToHead(node);
    }

    // 从双向链表中删除节点
    void removeNode(LRUNode<K, V>* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // 在双向链表头部添加节点
    void addToHead(LRUNode<K, V>* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    // 删除双向链表尾部节点，并返回该节点
    LRUNode<K, V>* removeTail() {
        LRUNode<K, V>* node = tail->prev;
        removeNode(node);
        return node;
    }

public:
    LRUCache(int capacity) : capacity(capacity) {
        head = new LRUNode<K, V>(K(), V());
        tail = new LRUNode<K, V>(K(), V());
        head->next = tail;
        tail->prev = head;
    }

    V get(K key) {
        if (cache.find(key) == cache.end()) {
            return V(); // 返回V类型的默认值
        }
        LRUNode<K, V>* node = cache[key];
        moveToHead(node);
        return node->value;
    }

    void put(K key, V value) {
        if (cache.find(key) != cache.end()) {
            LRUNode<K, V>* node = cache[key];
            node->value = value;
            moveToHead(node);
        } else {
            LRUNode<K, V>* newNode = new LRUNode<K, V>(key, value);
            cache[key] = newNode;
            addToHead(newNode);
            if (cache.size() > capacity) {
                LRUNode<K, V>* tail = removeTail();
                cache.erase(tail->key);
                delete tail; // 释放内存
            }
        }
    }

    ~LRUCache() {
        LRUNode<K, V>* node = head;
        while (node) {
            LRUNode<K, V>* next = node->next;
            delete node;
            node = next;
        }
    }
};
#endif