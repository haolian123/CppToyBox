# 消息队列

## 简介
​	这是一个基于 C++ 实现的线程安全的阻塞消息队列。使用 `std::deque` 作为底层容器，提供了线程间安全的数据交换机制。适用于生产者-消费者模型，多个线程可能同时访问队列进行数据的生产和消费。

## 特性
- **线程安全**：通过内部的互斥锁 (`std::mutex`) 和条件变量 (`std::condition_variable`) 来保证线程安全。
- **自动阻塞与唤醒**：队列在空时自动阻塞消费者线程，在满时自动阻塞生产者线程。
- **灵活的容量设置**：允许在构造时设置队列的最大容量。
- **支持超时等待**：提供了带超时机制的 `pop` 函数。
- **优雅关闭**：允许安全地关闭队列，并唤醒所有等待的线程。

## 使用方法

### 初始化
创建一个指定容量的 BlockQueue 实例：
```cpp
BlockQueue<int> queue(1000); // 创建一个最大容量为1000的队列
```

### 基本操作
- **添加元素**:
  ```cpp
  queue.push_back(item); // 向队尾添加元素
  queue.push_front(item); // 向队头添加元素
  ```
- **移除元素**:
  ```cpp
  int item;
  queue.pop(item); // 从队头移除元素
  ```
- **超时移除**:
  ```cpp
  bool success = queue.pop(item, 10); // 等待10秒尝试从队头移除元素
  ```

### 状态检查
- **队列大小**:
  ```cpp
  size_t size = queue.size(); // 获取队列当前大小
  ```
- **队列容量**:
  ```cpp
  size_t capacity = queue.getCapacity(); // 获取队列容量
  ```
- **空/满 检查**:
  ```cpp
  bool isEmpty = queue.empty(); // 检查队列是否为空
  bool isFull = queue.full(); // 检查队列是否已满
  ```

### 其他操作
- **关闭队列**:
  ```cpp
  queue.close(); // 关闭队列
  ```
- **清空队列**:
  ```cpp
  queue.clear(); // 清空队列
  ```

## 测试

​	需使用Google Test框架，运行test.cpp文件进行测试