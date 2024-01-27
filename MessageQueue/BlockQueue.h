#ifndef BLOCKQUEUE
#define BLOCKQUEUE

#include <mutex>
#include <deque>
#include <condition_variable>
#include <sys/time.h>

template<class T>
class BlockQueue {
private:
    std::deque<T> deque;                     // 队列容器
    size_t capacity;                         // 队列最大容量
    std::mutex mutex;                        // 互斥锁
    bool isClose;                            // 队列是否关闭
    std::condition_variable condConsumer;    // 消费者条件变量
    std::condition_variable condProducer;    // 生产者条件变量

public:
    explicit BlockQueue(size_t maxCapacity = 1000); // 构造函数，设置队列容量
    ~BlockQueue();                       // 析构函数
    void clear();                        // 清空队列
    bool empty();                        // 检查队列是否为空
    bool full();                         // 检查队列是否已满
    void close();                        // 关闭队列
    size_t size();                       // 获取队列当前大小
    size_t getCapacity();                // 获取队列容量
    T front();                           // 获取队列头部元素
    T back();                            // 获取队列尾部元素
    void push_back(const T& item);       // 向队列尾部添加元素
    void push_front(const T& item);      // 向队列头部添加元素
    bool pop(T& item);                   // 从队列头部弹出元素
    bool pop(T& item, int timeout);      // 带超时的从队列头部弹出元素
    void flush();                        // 唤醒等待中的消费者
};

template<class T>
BlockQueue<T>::BlockQueue(size_t maxCapacity) : capacity(maxCapacity) {
    assert(maxCapacity > 0);
    isClose = false;
}

template<class T>
BlockQueue<T>::~BlockQueue() {
    this->close();
}

template<class T>
void BlockQueue<T>::close() {
    {
        std::lock_guard<std::mutex> locker(mutex);
        deque.clear();
        isClose = true;
    }
    condProducer.notify_all();
    condConsumer.notify_all();
}

template<class T>
void BlockQueue<T>::flush() {
    condConsumer.notify_one();
}

template<class T>
void BlockQueue<T>::clear() {
    std::lock_guard<std::mutex> locker(mutex);
    deque.clear();
}

template<typename T>
T BlockQueue<T>::front(){
    std::unique_lock<std::mutex>lock(this->mutex);
    condConsumer.wait(lock,[&](){
        return deque.size()>0;
    });
    return deque.front();
}

template<typename T>
T BlockQueue<T>::back(){
    std::unique_lock<std::mutex>lock(this->mutex);
    condConsumer.wait(lock,[&](){
        return deque.size()>0;
    });
    return deque.back();
}
template<class T>
size_t BlockQueue<T>::size() {
    std::lock_guard<std::mutex> locker(mutex);
    return deque.size();
}

template<class T>
size_t BlockQueue<T>::getCapacity() {
    std::lock_guard<std::mutex> locker(mutex);
    return capacity;
}

template<class T>
void BlockQueue<T>::push_back(const T& item) {
    std::unique_lock<std::mutex> locker(mutex);
    while (deque.size() >= capacity) {
        condProducer.wait(locker);
    }
    deque.emplace_back(item);
    condConsumer.notify_one();
}

template<class T>
void BlockQueue<T>::push_front(const T& item) {
    std::unique_lock<std::mutex> locker(mutex);
    while (deque.size() >= capacity) {
        condProducer.wait(locker);
    }
    deque.emplace_front(item);
    condConsumer.notify_one();
}

template<class T>
bool BlockQueue<T>::empty() {
    std::lock_guard<std::mutex> locker(mutex);
    return deque.empty();
}

template<class T>
bool BlockQueue<T>::full() {
    std::lock_guard<std::mutex> locker(mutex);
    return deque.size() >= capacity;
}

template<class T>
bool BlockQueue<T>::pop(T& item) {
    std::unique_lock<std::mutex> locker(mutex);
    while (deque.empty() && !isClose) { // 检查队列是否为空且未关闭
        condConsumer.wait(locker);
    }
    if (isClose && deque.empty()) { // 如果队列已关闭且为空，则退出
        return false;
    }
    item = deque.front();
    deque.pop_front();
    condProducer.notify_one();
    return true;
}

template<class T>
bool BlockQueue<T>::pop(T& item, int timeout) {
    std::unique_lock<std::mutex> locker(mutex);
    while (deque.empty()) {
        if (condConsumer.wait_for(locker, std::chrono::seconds(timeout)) == std::cv_status::timeout) {
            return false;
        }
        if (isClose) {
            return false;
        }
    }
    item = deque.front();
    deque.pop_front();
    condProducer.notify_one();
    return true;
}

#endif
