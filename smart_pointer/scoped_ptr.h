#ifndef SCOPED_PTR_H
#define SCOPED_PTR_H
#include<iostream>

template<typename T>
class scoped_ptr{
private:
    T* ptr;
public:
    scoped_ptr(const scoped_ptr& other) = delete;

    scoped_ptr& operator=(const scoped_ptr& other)=delete;
    
    ~scoped_ptr(){
        delete ptr;
    }

    explicit scoped_ptr(T* ptr=nullptr): ptr(ptr){}

    T* operator ->() const noexcept{
        return ptr;
    }

    T &operator*() const noexcept{
        return *ptr;
    }

    T* get() const {
        return ptr;
    }

    void swap(scoped_ptr &rhs) noexcept{
        std::swap(ptr,rhs.ptr);
    }

    void reset(T* p=nullptr){
        scoped_ptr(p).swap(*this);
    }

};

template<typename T>
void swap(scoped_ptr<T> & lhs,scoped_ptr<T> & rhs){
    lhs.swap(rhs);
}


#endif