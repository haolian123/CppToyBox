#include<vector>
#include<iostream>
#include<string>
#include"LFU.h"
#include"LRU.h"
#include"FIFO.h"


void testFIFO(const std::vector<int>& pageRequests) {
    std::cout << "======Testing FIFO Cache======" << std::endl;
    FIFOCache<int, std::string> memory(3);
    int hitCount = 0;
    int missCount = 0;

    for (int page : pageRequests) {
        if (memory.get(page) != "") {
            std::cout << "Page " << page << " hit." << std::endl;
            hitCount++;
        } else {
            std::cout << "Page " << page << " missed. Loading into memory." << std::endl;
            memory.put(page, "PageData");
            missCount++;
        }
    }

    float hitRate = (float)hitCount / pageRequests.size();
    float missRate = (float)missCount / pageRequests.size();
    std::cout << "Hit rate: " << hitRate << ", Miss rate: " << missRate << std::endl << std::endl;
}

void testLRU(const std::vector<int>& pageRequests) {
    std::cout << "======Testing LRU Cache======" << std::endl;
    LRUCache<int, std::string> memory(3);
    int hitCount = 0;
    int missCount = 0;

    for (int page : pageRequests) {
        if (memory.get(page) != "") {
            std::cout << "Page " << page << " hit." << std::endl;
            hitCount++;
        } else {
            std::cout << "Page " << page << " missed. Loading into memory." << std::endl;
            memory.put(page, "PageData");
            missCount++;
        }
    }

    float hitRate = (float)hitCount / pageRequests.size();
    float missRate = (float)missCount / pageRequests.size();
    std::cout << "Hit rate: " << hitRate << ", Miss rate: " << missRate << std::endl << std::endl;
}

void testLFU(const std::vector<int>& pageRequests) {
    std::cout << "======Testing LFU Cache======" << std::endl;
    LFUCache<int, std::string> memory(3);
    int hitCount = 0;
    int missCount = 0;

    for (int page : pageRequests) {
        if (memory.get(page) != "") {
            std::cout << "Page " << page << " hit." << std::endl;
            hitCount++;
        } else {
            std::cout << "Page " << page << " missed. Loading into memory." << std::endl;
            memory.put(page, "PageData");
            missCount++;
        }
    }

    float hitRate = (float)hitCount / pageRequests.size();
    float missRate = (float)missCount / pageRequests.size();
    std::cout << "Hit rate: " << hitRate << ", Miss rate: " << missRate << std::endl << std::endl;
}
int main() {
    std::vector<int> pageRequests = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};

    testFIFO(pageRequests);
    testLRU(pageRequests);
    testLFU(pageRequests);

    return 0;
}
