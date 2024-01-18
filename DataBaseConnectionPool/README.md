# Linux MySQL数据库连接池

## 概述
​	这个项目为一个MySQL数据库的连接池，用于提高数据库操作的效率和性能。适用于Linux环境。

## 特性
- **单例模式**: 保证全局只有一个数据库连接池实例。
- **线程安全**: 使用互斥锁(mutex)和信号量(semaphore)来保证多线程环境下的安全访问。
- **RAII管理**: 资源获取即初始化，确保资源的有效管理和异常安全。
- **动态管理连接**: 根据需求动态地获取和释放数据库连接。

## 使用方法

### 初始化
在使用连接池前，需要先进行初始化。通过调用`Init`方法，设置数据库的主机地址、端口、用户名、密码、数据库名和连接池的大小。

```cpp
DBConnectionPool::getInstance()->Init("host", port, "user", "password", "dbName", connectionSize);
```

### 获取和释放连接
获取数据库连接时，调用`getConnection`方法。使用完毕后，通过`freeConnection`方法将连接返回给连接池。

```cpp
MYSQL* connection = DBConnectionPool::getInstance()->getConnection();
// 使用连接进行数据库操作
...
// 操作完成后释放连接
DBConnectionPool::getInstance()->freeConnection(connection);
```

### 关闭连接池
当不再需要连接池时，可以调用`closePool`方法来关闭连接池，释放资源。

```cpp
DBConnectionPool::getInstance()->closePool();
```

## 构建和依赖
本项目依赖于MySQL的C API。请确保在编译前已正确安装MySQL库。
