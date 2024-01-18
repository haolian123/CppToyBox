#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include<iostream>
template<typename T>
class unique_ptr{
private:
    T* ptr;
public:
    explicit unique_ptr(T* p =nullptr)noexcept: ptr(p){}
    ~unique_ptr() noexcept{
        delete ptr;
    }

    unique_ptr(const unique_ptr& rhs)=delete;

    unique_ptr& operator=(const unique_ptr& rhs)= delete;

    unique_ptr& operator=(unique_ptr&& rhs){
        if (this != &rhs) {
            unique_ptr(std::move(rhs)).swap(*this);
        }
        return *this;
    }

    unique_ptr(unique_ptr&& rhs)noexcept : ptr(rhs.ptr) {
        rhs.ptr = nullptr;
    }

    template <typename U> unique_ptr(unique_ptr<U> &&other) noexcept :ptr(other.ptr){
        other.ptr=nullptr;
    }

    void swap(unique_ptr& rhs){
        std::swap(ptr,rhs.ptr);
    }

    T* operator->(){
        return ptr;
    }
    T& operator*(){
        return *ptr;
    }

    T* get(){
        return ptr;
    }

    void reset(T* p=nullptr){
        unique_ptr(p).swap(*this);
    }
    
};

template<typename T>
void swap(unique_ptr<T>& lhs,unique_ptr<T>& rhs){
    lhs.swap(rhs);
}

#endif