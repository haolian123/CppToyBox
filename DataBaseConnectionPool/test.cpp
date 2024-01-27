#include <gtest/gtest.h>
#include "DBConnectionPool.h"
#include <thread>

class DBConnectionPoolTest : public ::testing::Test {
protected:
    DBConnectionPool* pool;

    void SetUp() override {
        pool = DBConnectionPool::getInstance();
        pool->Init("localhost", 3306, "hao", "hao", "webserver", 10);
    }

    void TearDown() override {
        pool->closePool();
    }
};

// 测试初始化连接池
TEST_F(DBConnectionPoolTest, InitPool) {
    int freeConnections = pool->getFreeConnectionNumber();
    EXPECT_EQ(freeConnections, 10); // 假设连接池大小为 10
}

// 测试获取和释放连接
TEST_F(DBConnectionPoolTest, GetAndReleaseConnection) {
    MYSQL* connection = pool->getConnection();
    EXPECT_NE(connection, nullptr);

    pool->freeConnection(connection);
    int freeConnections = pool->getFreeConnectionNumber();
    EXPECT_EQ(freeConnections, 10); // 释放后，空闲连接数应该恢复为 10
}

// 测试并发获取和释放连接
TEST_F(DBConnectionPoolTest, ConcurrentGetAndRelease) {
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([this]() {
            MYSQL* connection = pool->getConnection();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            pool->freeConnection(connection);
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    int freeConnections = pool->getFreeConnectionNumber();
    EXPECT_EQ(freeConnections, 10); // 所有线程结束后，空闲连接数应该为 10
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
