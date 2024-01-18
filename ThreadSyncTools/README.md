# 介绍

一个linux系统下的线程同步和并发控制工具。

## 信号量类（Semaphore）

### 概述
信号量是一种用于线程或进程之间同步的机制，主要用来控制对共享资源的访问。这个信号量类提供了基本的信号量操作，包括初始化、等待（wait）和发送（post）信号量。

### 使用方法
```cpp
// 创建信号量对象，初始值为0
Semaphore sem;

// 等待信号量
if (sem.wait()) {
    // 获得信号量后的操作
}

// 发送信号量，将信号量值加1
if (sem.post()) {
    // 释放信号量后的操作
}
```

## 互斥锁类（Locker）

### 概述
互斥锁是一种用于确保在同一时刻只有一个线程可以访问共享资源的机制。这个互斥锁类提供了基本的互斥锁操作，包括锁的初始化、加锁（lock）和解锁（unlock）。

### 使用方法
```cpp
// 创建互斥锁对象
Locker lock;

// 加锁
if (lock.lock()) {
    // 获得互斥锁后的操作

    // 解锁
    lock.unlock();
}
```

## 条件变量类（Condition）

### 概述
条件变量是一种用于在线程之间传递信号的机制，通常用于线程等待某个特定条件的发生。这个条件变量类提供了基本的条件变量操作，包括等待（wait）和通知（signal）。

### 使用方法
```cpp
// 创建条件变量对象
Condition condition;

// 创建互斥锁
Locker mutexLock;
pthread_mutex_t mutex = *mutexLock.getMutex();

// 在互斥锁的保护下等待条件满足
if (condition.wait(&mutex)) {
    // 条件满足后的操作
}

// 在指定时间内等待条件满足
struct timespec time;
// 设置时间
if (condition.timewait(&mutex, time)) {
    // 条件满足后的操作
}

// 发送广播，唤醒所有等待该条件变量的线程
if (condition.signal()) {
    // 广播操作
}
```

### 注意事项
- 在使用这些类时，请确保正确地处理异常。初始化和操作失败时，类中的构造函数和成员函数会抛出异常（例如 `std::runtime_error`）。
- 为了避免资源泄漏，请确保在不需要使用这些对象时进行适当的销毁操作（调用析构函数或者使用 RAII）。
