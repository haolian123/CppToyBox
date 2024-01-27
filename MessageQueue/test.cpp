#include <gtest/gtest.h>
#include "BlockQueue.h" 

// 测试 BlockQueue 类的功能
class BlockQueueTest : public ::testing::Test {
protected:
    BlockQueue<int> queue; 

    void SetUp() override {
        queue.clear(); 
    }

    void TearDown() override {

    }
};

// 测试构造函数
TEST_F(BlockQueueTest, Constructor) {
    EXPECT_EQ(queue.size(), 0);
    EXPECT_EQ(queue.getCapacity(), 1000); 
}

// 测试 clear 方法
TEST_F(BlockQueueTest, Clear) {
    queue.push_back(1);
    queue.clear();
    EXPECT_TRUE(queue.empty());
}

// 测试 empty 和 full 方法
TEST_F(BlockQueueTest, EmptyAndFull) {
    EXPECT_TRUE(queue.empty());
    EXPECT_FALSE(queue.full());
    for (int i = 0; i < 1000; ++i) { 
        queue.push_back(i);
    }
    EXPECT_TRUE(queue.full());
}

// 测试 push_back 和 front 方法
TEST_F(BlockQueueTest, PushBackAndFront) {
    queue.push_back(1);
    EXPECT_EQ(queue.front(), 1);
}

// 测试 push_front 和 back 方法
TEST_F(BlockQueueTest, PushFrontAndBack) {
    queue.push_front(1);
    EXPECT_EQ(queue.back(), 1);
}

// 测试 pop 方法
TEST_F(BlockQueueTest, Pop) {
    queue.push_back(1);
    queue.push_back(2);
    int item;
    EXPECT_TRUE(queue.pop(item));
    EXPECT_EQ(item, 1);
    EXPECT_TRUE(queue.pop(item));
    EXPECT_EQ(item, 2);
}

// 测试 pop 方法的超时行为
TEST_F(BlockQueueTest, PopWithTimeout) {
    int item;
    EXPECT_FALSE(queue.pop(item, 1)); // 1 秒超时
}

// 测试 close 方法
TEST_F(BlockQueueTest, Close) {
    queue.push_back(1);
    queue.close();
    int item;
    EXPECT_FALSE(queue.pop(item));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
