#include <iostream>
#include <pthread.h>
#include <cassert>
#include "ThreadSyncTools.h" // 替换为您的头文件名
#include <unistd.h>

// 用于Semaphore测试的线程函数
void* semaphoreTestThread(void* arg) {
    Semaphore* sem = (Semaphore*)arg;
    sem->post();
    return nullptr;
}

// 用于Condition测试的线程函数
void* conditionTestThread(void* arg) {
    Condition* cond = (Condition*)arg;
    cond->signal();
    return nullptr;
}

void testConcurrencyTools() {
    // 测试Semaphore
    Semaphore sem;
    pthread_t semThread;
    pthread_create(&semThread, nullptr, semaphoreTestThread, (void*)&sem);
    assert(sem.wait()); // 等待信号量，确保线程已经post
    pthread_join(semThread, nullptr);

    // 测试Locker
    Locker locker;
    locker.lock();
    locker.unlock(); // 简单测试锁的功能，但不涉及多线程竞争

    // 测试Condition
    Condition cond;
    pthread_t condThread;
    Locker condLocker;
    condLocker.lock();
    pthread_create(&condThread, nullptr, conditionTestThread, (void*)&cond);
    assert(cond.wait(condLocker.getMutex())); // 等待条件变量
    condLocker.unlock();
    pthread_join(condThread, nullptr);

    std::cout << "测试通过！" << std::endl;
}

int main() {
    testConcurrencyTools();
    return 0;
}
