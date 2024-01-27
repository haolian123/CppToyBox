#include"DBConnectionPool.h"

DBConnectionPool* DBConnectionPool::getInstance(){
    static DBConnectionPool instance;
    return &instance;
}

void DBConnectionPool::freeConnection(MYSQL* connection){
    assert(connection);
    std::lock_guard<std::mutex> lock(mutex);
    connectionQueue.push(connection);
    condition.notify_one();
}

MYSQL* DBConnectionPool::getConnection(){
    MYSQL* sql = nullptr;
    std::unique_lock<std::mutex>lock(mutex);
    
    condition.wait(lock,[&](){
        return connectionQueue.size()>0;
    });

    sql = connectionQueue.front();
    connectionQueue.pop();
    
    return sql;
}

void DBConnectionPool::Init(const char* host, int port,
            const char* user, const char* passWord,
            const char* dbName, int connectionSize){

    assert(connectionSize>0);
    for(int i=0;i<connectionSize;i++){
        MYSQL* sql = nullptr;
        sql = mysql_init(sql);
        assert(sql);
        sql = mysql_real_connect(sql, host, user, passWord, dbName, port, nullptr, 0);

        connectionQueue.emplace(sql);
    }

    maxConnection = connectionSize;
}

void DBConnectionPool::closePool(){
    std::lock_guard<std::mutex>lock(mutex);
    while(!connectionQueue.empty()){
        auto connection = connectionQueue.front();
        connectionQueue.pop();
        mysql_close(connection);
    }
    mysql_library_end();
}

int DBConnectionPool::getFreeConnectionNumber(){
    std::lock_guard<std::mutex>lock(mutex);
    return connectionQueue.size();
}

DBConnectionPool::DBConnectionPool(){
    this->useNumber=this->freeNumber=0;
}
DBConnectionPool::~DBConnectionPool(){
    closePool();
}