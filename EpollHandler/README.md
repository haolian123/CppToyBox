# 高效的IO事件监听管理器

## 简介

    这是一个使用`epoll` 实现的高效 IO 事件监听管理器。利用 Linux 下的 `epoll` 接口，提供了一种高效的方法来同时监听多个文件描述符上的 IO 事件。主要用于处理大量并发的 socket 连接，适用于高性能网络编程。

## 特性

- **高效的事件处理**：基于 `epoll`，比传统的 `poll` 或 `select` 更高效。
- **简洁的接口**：提供了添加、修改、删除文件描述符及其事件的简洁接口。
- **可配置的事件数量**：默认支持的最大事件数为 1024，但可以在构造时自定义。
- **灵活的等待机制**：支持指定超时时间的事件等待。

## 使用方法

### 初始化

创建一个 EpollManager 实例：

```cpp
EpollManager epollManager; // 使用默认的最大事件数
```

或者，使用自定义的最大事件数：

```cpp
EpollManager epollManager(2048); // 设置最大事件数为2048
```

### 基本操作

- **添加文件描述符**:
  ```cpp
  epollManager.addFd(fd, EPOLLIN | EPOLLET); // 添加文件描述符并设置事件
  ```
- **修改文件描述符事件**:
  ```cpp
  epollManager.modifyFd(fd, EPOLLOUT); // 修改文件描述符的关注事件
  ```
- **删除文件描述符**:
  ```cpp
  epollManager.deleteFd(fd); // 从 epoll 实例中删除文件描述符
  ```
- **等待事件发生**:
  ```cpp
  int eventCount = epollManager.wait(500); // 等待事件发生，超时时间为500毫秒
  ```

### 事件处理

在调用 `wait` 方法后，可以使用以下方法获取事件信息：

- **获取事件的文件描述符**:
  ```cpp
  int fd = epollManager.getEventFd(i); // 获取第 i 个事件的文件描述符
  ```
- **获取事件类型**:
  ```cpp
  uint32_t events = epollManager.getEvents(i); // 获取第 i 个事件的类型
  ```

## 环境要求

- Linux 操作系统。

## 测试

    需使用Google Test框架，运行test.cpp文件进行测试
