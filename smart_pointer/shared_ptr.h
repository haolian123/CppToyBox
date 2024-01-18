#ifndef SHARED_PTR_H
#define SHARED_PTR_H
#include <iostream>
#include <mutex>

class shared_count {
private:
    std::mutex mutex;
    long count;

public:
    shared_count(int count=1) noexcept : count(count) {}

    void increaseRefCount() {
        std::lock_guard<std::mutex> lock(mutex);
        ++count;
    }

    void reduceRefCount() {
        std::lock_guard<std::mutex> lock(mutex);
        --count;
    }

    long getCount() {
        std::lock_guard<std::mutex> lock(mutex);
        return count;
    }
};

template<typename T>
class shared_ptr {
private:
    T* ptr;
    shared_count* sharedCount;

public:
    explicit shared_ptr(T* p = nullptr) noexcept : ptr(p), sharedCount(nullptr) {
        if(p) {
            sharedCount = new shared_count();
        }
    }

    shared_ptr(const shared_ptr & rhs) : ptr(rhs.ptr), sharedCount(rhs.sharedCount) {
        if (sharedCount) {
            sharedCount->increaseRefCount();
        }
    }

    shared_ptr(shared_ptr && rhs) noexcept : ptr(rhs.ptr), sharedCount(rhs.sharedCount) {
        rhs.ptr = nullptr;
        rhs.sharedCount = nullptr;
    }

    // 强制类型转换需要的构造函数
    template <typename U>
    shared_ptr(const shared_ptr<U> &other, T *ptr) noexcept:ptr(ptr) {
        if (ptr) {
        other.sharedCount->increaseRefCount();
        sharedCount = other.sharedCount;
        }
    }
    ~shared_ptr() {
        if(sharedCount) {
            sharedCount->reduceRefCount();
            if(ptr != nullptr && sharedCount->getCount() == 0) {
                delete ptr;
                delete sharedCount;
            }
        }
    }
    template <typename U> friend class shared_ptr;
    
    template<typename U> shared_ptr(const shared_ptr<U>&other) noexcept{
        ptr = other.ptr;
        if(ptr){
            other.sharedCount->increaseRefCount();
            sharedCount = other.sharedCount;
        }
    }
    template<typename U> shared_ptr(shared_ptr<U>&&other) noexcept{
        ptr = other.ptr;
        if(ptr){
            sharedCount = other.sharedCount;
            other.ptr = nullptr;
            other.sharedCount = nullptr;
        }
    }


    shared_ptr<T>& operator=(const shared_ptr & rhs) {
        if(this != &rhs) {
            shared_ptr<T>(rhs).swap(*this);
        }
        return *this;
    }

    shared_ptr<T>& operator=(shared_ptr && rhs) noexcept {
        if(this != &rhs) {
            shared_ptr<T>(std::move(rhs)).swap(*this);
        }
        return *this;
    }

    void swap(shared_ptr & rhs) noexcept {
        std::swap(ptr, rhs.ptr);
        std::swap(sharedCount, rhs.sharedCount);
    }

    T* operator->() const {
        return ptr;
    }

    T& operator*() const {
        return *ptr;
    }

    T* get() const {
        return ptr;
    }

    void reset(T* p = nullptr) {
        shared_ptr(p).swap(*this);
    }
};

template<typename T>
void swap(shared_ptr<T>& lhs, shared_ptr<T>& rhs) {
    lhs.swap(rhs);
}

template<typename T,typename U>
shared_ptr<T> dynamic_pointer_cast(const shared_ptr<U>& other) noexcept{
    T * ptr = dynamic_cast<T*>(other.get());
    return shared_ptr<T>(other,ptr);
}

template <typename T, typename U>
shared_ptr<T> static_pointer_cast(const shared_ptr<U> &other) noexcept {
  T *ptr = static_cast<T *>(other.get());
  return shared_ptr<T>(other, ptr);
}

template <typename T, typename U>
shared_ptr<T> const_pointer_cast(const shared_ptr<U> &other) noexcept {
  T *ptr = const_cast<T *>(other.get());
  return shared_ptr<T>(other, ptr);
}

template <typename T, typename U>
shared_ptr<T> reinterpret_pointer_cast(const shared_ptr<U> &other) noexcept {
  T *ptr = reinterpret_cast<T *>(other.get());
  return shared_ptr<T>(other, ptr);
}

#endif
