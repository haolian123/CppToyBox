#include <cassert>
#include <iostream>
#include "BTree.h"
#include "SkipList.h"

void testBTree() {
    // 初始化B树实例，最小度数设置为3
    BTree<int> bTree(3);

    // 插入元素
    bTree.insert(10);
    bTree.insert(20);
    bTree.insert(5);
    bTree.insert(6);
    bTree.insert(12);
    bTree.insert(30);
    bTree.insert(7);
    bTree.insert(17);

    // 测试用例计数器
    int testsPassed = 0;

    // 遍历B树
    std::cout << "BTree traversal: ";
    bTree.traverse();
    std::cout << std::endl;
    testsPassed++;

    // 测试搜索存在的元素
    assert(bTree.search(6) != nullptr);
    testsPassed++;
    assert(bTree.search(12) != nullptr);
    testsPassed++;

    // 测试搜索不存在的元素
    assert(bTree.search(100) == nullptr);
    testsPassed++;

    std::cout << "BTree tests passed: " << testsPassed << " tests." << std::endl;
}

void testSkipList() {
    // 初始化跳表实例
    SkipList<std::string, std::string> skipList;

    // 测试用例计数器
    int testsPassed = 0;

    // 测试添加元素
    assert(skipList.addItem("key1", "value1") == true);
    testsPassed++;

    // 测试搜索元素
    auto searchResult = skipList.searchItem("key1");
    assert(searchResult != nullptr && searchResult->value == "value1");
    testsPassed++;

    // 测试修改元素
    assert(skipList.modifyItem("key1", "valueModified") == true);
    searchResult = skipList.searchItem("key1");
    assert(searchResult != nullptr && searchResult->value == "valueModified");
    testsPassed++;

    // 测试删除元素
    assert(skipList.deleteItem("key1") == true);
    searchResult = skipList.searchItem("key1");
    assert(searchResult == nullptr);
    testsPassed++;

    // 测试列表大小
    assert(skipList.size() == 0);
    testsPassed++;

    std::cout << "SkipList tests passed: " << testsPassed << " tests." << std::endl;
}

int main() {

    testSkipList();

    testBTree();

    return 0;
}
