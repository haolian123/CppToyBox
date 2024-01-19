# C++内存模型和Atomic操作

## C++内存模型

C++内存模型定义了多线程程序中对象的行为。它涵盖了线程间的数据共享、同步操作以及内存顺序。

### 关键概念：

1. **顺序一致性**：理想化的内存模型，所有线程看到的操作顺序都是一致的。
2. **内存顺序**：实际的内存操作可能因编译器和处理器优化而有所不同，导致顺序一致性被打破。
3. **数据竞争**：当两个线程同时访问同一数据，并且至少有一个线程在写入时，就会发生数据竞争。

## Atomic操作

`atomic`操作是设计用来避免数据竞争的一种机制。`atomic`类型的对象保证了对它们的操作是不可分割的，即这些操作在多线程环境中是安全的。

### 关键特性：

1. **原子性**：保证操作的不可分割性，操作要么完全执行，要么完全不执行。
2. **内存顺序保证**：提供了不同级别的保证，从松散的到顺序一致的。

### 示例：Atomic整数

```cpp
#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> count(0);

void increment() {
    for (int i = 0; i < 1000; ++i) {
        count.fetch_add(1, std::memory_order_relaxed); // 原子地增加count
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Count: " << count << std::endl; // 输出最终结果
    return 0;
}
```

