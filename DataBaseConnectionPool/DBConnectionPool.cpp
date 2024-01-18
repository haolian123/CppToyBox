#include"DBConnectionPool.h"

DBConnectionPool* DBConnectionPool::getInstance(){
    static DBConnectionPool connection;
    return &connection;
}

void DBConnectionPool::freeConnection(MYSQL* connection){
    assert(connection);
    std::lock_guard<std::mutex> locker(mutex);
    connectionQueue.push(connection);
    sem_post(&semId);
}
MYSQL* DBConnectionPool::getConnection(){
    MYSQL* sql=nullptr;
    if(connectionQueue.empty()){
        return nullptr;
    }
    sem_wait(&semId);
    {
        std::lock_guard<std::mutex> locker(mutex);
        sql=connectionQueue.front();
        connectionQueue.pop();
    }
    return sql;
}
void DBConnectionPool::Init(const char* host, int port,
                            const char* user, const char* passWord,
                            const char* DBName, int connectionSize
                        ){
    // 确保连接池大小大于0
    assert(connectionSize > 0);
    
    for(int i = 0; i < connectionSize; i++){
        MYSQL* sql = nullptr;
        sql = mysql_init(sql);
        
        // 检查是否成功初始化 MySQL 连接
        if(!sql){
            assert(sql);
        }
        
        // 连接到数据库
        sql = mysql_real_connect(sql, host, user, passWord, DBName, port, nullptr, 0);
        
        // 将连接添加到连接队列
        connectionQueue.emplace(sql);
    }
    
    // 设置最大连接数和初始化信号量
    maxConnection = connectionSize;
    sem_init(&semId, 0, maxConnection);
}

void DBConnectionPool::closePool(){
    std::lock_guard<std::mutex>locker(mutex);
    while(!connectionQueue.empty()){
        auto connection=connectionQueue.front();
        connectionQueue.pop();
        mysql_close(connection);
    }
    mysql_library_end();
}

int DBConnectionPool::getFreeConnectionNumber(){
    std::lock_guard<std::mutex> locker(mutex);
    return connectionQueue.size();
}

DBConnectionPool::DBConnectionPool(){
    this->useNumber=this->freeNumber=0;
}
DBConnectionPool::~DBConnectionPool(){
    closePool();
}