#include "EpollManager.h"
#include <gtest/gtest.h>
#include <sys/socket.h>

class EpollManagerTest : public ::testing::Test {
protected:
    EpollManager* epollManager;

    void SetUp() override {
        epollManager = new EpollManager();
    }

    void TearDown() override {
        delete epollManager;
    }

    // Helper function to create a dummy file descriptor
    int createDummyFd() {
        int pipefd[2];
        if (pipe(pipefd) == -1) {
            return -1;
        }
        return pipefd[0];
    }
};

TEST_F(EpollManagerTest, ConstructorDestructor) {
    ASSERT_TRUE(epollManager != nullptr);
}

TEST_F(EpollManagerTest, AddFdValidFd) {
    int fd = createDummyFd();
    ASSERT_NE(fd, -1);
    ASSERT_TRUE(epollManager->addFd(fd, EPOLLIN));
    close(fd);
}

TEST_F(EpollManagerTest, AddFdInvalidFd) {
    ASSERT_FALSE(epollManager->addFd(-1, EPOLLIN));
}

TEST_F(EpollManagerTest, ModifyFdValidFd) {
    int fd = createDummyFd();
    ASSERT_NE(fd, -1);
    epollManager->addFd(fd, EPOLLIN);
    ASSERT_TRUE(epollManager->modifyFd(fd, EPOLLOUT));
    close(fd);
}

TEST_F(EpollManagerTest, ModifyFdInvalidFd) {
    ASSERT_FALSE(epollManager->modifyFd(-1, EPOLLIN));
}

TEST_F(EpollManagerTest, DeleteFdValidFd) {
    int fd = createDummyFd();
    ASSERT_NE(fd, -1);
    epollManager->addFd(fd, EPOLLIN);
    ASSERT_TRUE(epollManager->deleteFd(fd));
    close(fd);
}

TEST_F(EpollManagerTest, DeleteFdInvalidFd) {
    ASSERT_FALSE(epollManager->deleteFd(-1));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
