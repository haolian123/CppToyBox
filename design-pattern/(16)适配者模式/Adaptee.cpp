/*
适配器模式（Adapter Pattern）是一种结构性设计模式，
用于将一个类的接口转换成另一个类的接口，从而使不兼容的类能够相互协作。
这种模式允许两个不兼容的接口进行交互，而无需修改它们的源代码。
*/
#include<iostream>

//Adaptee类，需要被适配的类
class Adaptee{
public:
    void specificRequest(){
        std::cout << "适应者的具体要求。" << std::endl;
    }
};

//Target接口，客户端所期望的接口。
class Target{
public:
    virtual void request()=0;
};

//Adapter类，适配器，将Adaptee的接口转换成Target的接口
class Adapter:public Target{
private:
    Adaptee adaptee;
public:
    void request() override{
        adaptee.specificRequest();
    }
};


int main(){
    Target* target=new Adapter();
    // 调用Target接口的request方法，实际上会调用Adaptee的specificRequest方法
    target->request();
    return 0;
}