#ifndef LOCKER_H
#define LOCKER_H 

#include <pthread.h>
#include <semaphore.h>
#include <stdexcept> 

// 信号量类
class Semaphore {
private:
    sem_t sem;

public:
    Semaphore() {
        if (sem_init(&sem, 0, 0) != 0) {
            throw std::runtime_error("Semaphore initialization failed");
        }
    }

    explicit Semaphore(int num) {
        if (sem_init(&sem, 0, num) != 0) {
            throw std::runtime_error("Semaphore initialization failed");
        }
    }

    ~Semaphore() {
        sem_destroy(&sem);
    }

    bool wait() {
        return sem_wait(&sem) == 0;
    }

    bool post() {
        return sem_post(&sem) == 0;
    }
};

// 互斥锁类
class Locker {
private:
    pthread_mutex_t mutex;

public:
    Locker() {
        if (pthread_mutex_init(&mutex, nullptr) != 0) {
            throw std::runtime_error("Mutex initialization failed");
        }
    }

    ~Locker() {
        pthread_mutex_destroy(&mutex);
    }

    bool lock() {
        return pthread_mutex_lock(&mutex) == 0;
    }

    bool unlock() {
        return pthread_mutex_unlock(&mutex) == 0;
    }

    pthread_mutex_t* getMutex() {
        return &mutex;
    }
};

// 条件变量类
class Condition {
private:
    pthread_cond_t cond;

public:
    Condition() {
        if (pthread_cond_init(&cond, nullptr) != 0) {
            throw std::runtime_error("Condition variable initialization failed");
        }
    }

    ~Condition() {
        pthread_cond_destroy(&cond);
    }

    bool wait(pthread_mutex_t* mutex) {
        return pthread_cond_wait(&cond, mutex) == 0;
    }

    bool timeWait(pthread_mutex_t* mutex, struct timespec t) {
        return pthread_cond_timedwait(&cond, mutex, &t) == 0;
    }

    bool signal() {
        return pthread_cond_broadcast(&cond) == 0;
    }
};

#endif
