#ifndef DB_CONNECTION_POOL
#define DB_CONNECTION_POOL

#include<mysql/mysql.h>
#include<string>
#include<queue>
#include<mutex>
#include<semaphore.h>
#include<memory>
#include<thread>
#include<cassert>
class DBConnectionPool {
public:
    // 获取连接池实例的静态方法
    static DBConnectionPool* getInstance();

    // 释放数据库连接
    void freeConnection(MYSQL* connection);

    // 获取数据库连接
    MYSQL* getConnection();

    // 初始化连接池
    void Init(const char* host, int port,
              const char* user, const char* pwd,
              const char* dbName, int connectionSize);

    // 关闭连接池
    void closePool();

    // 获取空闲连接数
    int getFreeConnectionNumber();

private:
    // 构造函数和析构函数私有化，确保单例模式
    DBConnectionPool();
    ~DBConnectionPool();

    int maxConnection;     // 连接池最大连接数
    int useNumber;         // 已使用的连接数
    int freeNumber;        // 空闲的连接数

    std::queue<MYSQL*> connectionQueue;  // 存放连接的队列
    std::mutex mutex;                   // 用于多线程同步访问连接池
    sem_t semId;                        // 信号量，用于控制连接的分配和释放
};




#endif