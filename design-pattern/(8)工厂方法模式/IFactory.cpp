/*
简单工厂模式和工厂方法模式都是创建型设计模式，但它们有一些关键的区别：
创建对象的方式：
简单工厂模式： 由一个工厂类负责创建多个不同类型的对象。客户端通过传递不同的参数给工厂类，获得所需的对象。
工厂方法模式： 定义一个创建对象的接口，但让子类决定实例化哪个类。每个具体的工厂子类都负责创建特定类型的对象。
类的数量：
简单工厂模式： 通常只有一个工厂类，负责创建多个产品类的实例。
工厂方法模式： 每个产品类都有一个对应的工厂类，从而形成了一组工厂类，每个工厂类只负责创建一个特定类型的对象。
灵活性：
简单工厂模式： 不够灵活，因为所有的产品都由同一个工厂创建，如果需要添加新产品，可能需要修改工厂类。
工厂方法模式： 更灵活，因为每个产品都有对应的工厂类，新增产品时只需要添加一个新的工厂类，不需要修改已有代码。
扩展性：
简单工厂模式： 不够易扩展，因为所有的创建逻辑都封装在一个工厂类中，新增产品或修改创建逻辑可能导致工厂类的修改。
工厂方法模式： 更易扩展，每个产品都有独立的工厂类，新增产品时只需要添加新的工厂类，不会影响已有代码。
总的来说，简单工厂模式适用于工厂类负责创建的对象较少且不太变化的情况，而工厂方法模式适用于有多个产品系列、需要灵活扩展的情况。
*/
#include<iostream>
class LeiFeng{
public:
    void work(){
        printf("做好事");
    }
};

class Undergraduate: public LeiFeng{

};

class Volunteer: public LeiFeng{

};

//雷锋工厂
class IFactory{
public:
    virtual LeiFeng* createLeiFeng()=0;
};

class UndergraduateFactory: IFactory{
public:
    LeiFeng* createLeiFeng() override{
        return new Undergraduate();
    }
};

class VolunteerFactory: IFactory{
public:
    LeiFeng* createLeiFeng() override{
        return new Volunteer();
    }
};

int main(){
    IFactory * factory=(IFactory *)new UndergraduateFactory();
    LeiFeng* student=factory->createLeiFeng();
    student->work();
}