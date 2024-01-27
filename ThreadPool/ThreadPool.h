#ifndef THREADPOOL
#define THREADPOOL

#include<mutex>
#include<condition_variable>
#include<queue>
#include<functional>
#include<memory>
#include<cassert>
#include<thread>
struct Pool{
    std::mutex mutex;
    std::condition_variable condition;
    bool isClose;
    std::queue<std::function<void()>>tasks;
};

class ThreadPool{
private:
    std::shared_ptr<Pool>pool;
public:
    ThreadPool(size_t threadNumber=8):pool(std::make_shared<Pool>()){
        assert(threadNumber>0);
        for(int i=0;i<threadNumber;i++){
            std::thread(
                [pool = this->pool]{
                    while(true){
                        std::unique_lock<std::mutex>lock(pool->mutex);
                        pool->condition.wait(lock,[&](){
                            return !pool->tasks.empty()||pool->isClose;
                        });
                        if(pool->isClose)
                            break;
                        auto task = std::move(pool->tasks.front());
                        pool->tasks.pop();
                        lock.unlock();
                        task();
                        lock.lock();
                    }
                    

                }
            ).detach();
        }
    }

    ThreadPool(ThreadPool&&) = default;

    ~ThreadPool(){
        if(pool!=nullptr){
            std::lock_guard<std::mutex>lock(pool->mutex);
            pool->isClose=true;
        }
        pool->condition.notify_all();
    }

    template<typename T>
    void addTask(T&& task){
        {
            std::lock_guard<std::mutex>lock(pool->mutex);
            pool->tasks.emplace(std::forward<T>(task));
        }
        pool->condition.notify_one();
    }
};

#endif 