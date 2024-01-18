/*
代理模式是一种结构型设计模式，它允许一个对象（代理）充当另一个对象（真实对象）的接口，
以控制对这个真实对象的访问。代理可以用于实现延迟加载、访问控制、日志记录等功能，
而无需改变真实对象的代码，提供了更灵活和可维护的代码结构。在Java中，代理模式通常使用接口实现，
允许代理类实现与真实对象相同的接口，并在必要时委托真实对象执行操作。
*/
#include<iostream>

class Subject{
public:
    virtual void Request()=0;
};


class RealSubject:public Subject{
public:
    void Request(){
        printf("真实的请求");
    }
};


class Proxy:Subject{
    RealSubject * realSubject=nullptr;
public:
    void Request(){
        if(!realSubject){
            realSubject=new RealSubject();
        }
        realSubject->Request();
    }
};

int main(){
    Proxy* proxy=new Proxy();
    proxy->Request();
}