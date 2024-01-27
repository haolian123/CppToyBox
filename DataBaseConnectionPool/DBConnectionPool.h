#ifndef DB_CONNECTION_POOL
#define DB_CONNECTION_POOL

#include <mysql/mysql.h>
#include <string>
#include <queue>
#include <mutex>
#include <memory>
#include <thread>
#include <cassert>
#include <condition_variable>

class DBConnectionPool {
public:
    // 获取单例对象的静态方法
    static DBConnectionPool* getInstance();

    // 释放连接回连接池
    void freeConnection(MYSQL* connection);

    // 从连接池获取一个连接
    MYSQL* getConnection();

    // 初始化连接池
    void Init(const char* host, int port,
              const char* user, const char* pwd,
              const char* dbName, int connectionSize);

    // 关闭连接池
    void closePool();

    // 获取空闲连接数
    int getFreeConnectionNumber();

    // 删除拷贝构造函数
    DBConnectionPool(const DBConnectionPool& other) = delete;
    // 删除拷贝赋值运算符
    DBConnectionPool& operator=(const DBConnectionPool& other) = delete;
    // 删除移动构造函数
    DBConnectionPool(DBConnectionPool&& other) = delete;
    // 删除移动赋值运算符
    DBConnectionPool& operator=(DBConnectionPool&& other) = delete;

private:
    // 私有构造函数
    DBConnectionPool();
    // 析构函数
    ~DBConnectionPool();
    // 最大连接数
    int maxConnection;
    // 使用中的连接数
    int useNumber;
    // 空闲的连接数
    int freeNumber;
    // 连接队列
    std::queue<MYSQL*> connectionQueue;
    // 互斥锁
    std::mutex mutex;
    // 条件变量，用于线程同步
    std::condition_variable condition;
};

#endif
