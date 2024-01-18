#include<iostream>
#include<map>
// 享元模式是一种结构性设计模式，旨在最大程度地减少内存或计算开销，
// 通过共享尽可能多的可复用对象来提高系统的性能。
// 这种模式适用于具有大量相似对象的情况，
// 其中每个对象的一部分状态可以被共享。

//抽象享元类
class Flyweight{
public:
    virtual void operation()=0;
};


//具体享元类
class ConcreteFlyweight: public Flyweight{
public:
    void operation() override{
        std::cout<<"Concrete Flyweight"<<std::endl;
    }
};

//享元工厂，用于创建和管理享元对象
class FlyweightFactory{
private:
    std::map<char,Flyweight*> flyweights;

public:
    Flyweight* getFlyweight(char key){
        if(flyweights.find(key)==flyweights.end()){
            flyweights[key]=new ConcreteFlyweight();
        }
        return flyweights[key];
    }
};

int main(){
    FlyweightFactory* factory=new FlyweightFactory();

    Flyweight* fw1=factory->getFlyweight('A');
    Flyweight* fw2=factory->getFlyweight('B');

    fw1->operation();
    fw2->operation();

    return 0;
}