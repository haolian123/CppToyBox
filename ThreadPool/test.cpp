#include <gtest/gtest.h>
#include "ThreadPool.h" 
#include <atomic>
#include <chrono>

class ThreadPoolTest : public ::testing::Test {
protected:
    ThreadPool pool;

    ThreadPoolTest() : pool(8) {
    }

    void TearDown() override {
        
    }
};

// 测试线程池是否可以启动并执行单个任务
TEST_F(ThreadPoolTest, SingleTask) {
    std::atomic<bool> taskExecuted = false;
    pool.addTask([&taskExecuted]() {
        taskExecuted = true;
    });

    // 等待足够的时间确保任务被执行
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_TRUE(taskExecuted);
}

// 测试线程池处理多个任务
TEST_F(ThreadPoolTest, MultipleTasks) {
    std::atomic<int> counter = 0;
    const int numberOfTasks = 10;
    
    for (int i = 0; i < numberOfTasks; ++i) {
        pool.addTask([&counter]() {
            counter++;
        });
    }

    // 等待足够的时间确保所有任务被执行
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    EXPECT_EQ(counter, numberOfTasks);
}

// 测试线程池析构时是否正确关闭
TEST_F(ThreadPoolTest, DestructorClosesPool) {
    {
        ThreadPool localPool(8);
        localPool.addTask([]() {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        });
    } // localPool 在这里析构

    // 如果线程池的析构函数没有正确关闭，这里可能会出现挂起或其他问题
    EXPECT_TRUE(true); // 仅作为基本的检查
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}