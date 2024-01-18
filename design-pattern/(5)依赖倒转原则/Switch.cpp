/*
依赖倒转原则（Dependency Inversion Principle，DIP）是设计模式中的一个关键原则，
它要求高层模块不应该依赖于低层模块，两者都应该依赖于抽象。
这可以通过使用接口或抽象类来实现。
*/
#include<iostream>
class Switchable{
public:
    virtual void turnOn()=0;
    virtual void turnOff()=0;
};

class Light:public Switchable{
public:
    void turnOn(){
        std::cout<<"Light turns on!"<<std::endl;
    }
    void turnOff(){
        std::cout<<"Light turns off!"<<std::endl;
    }
};

class Switch{
private:
    Switchable* device=nullptr;
public:
    Switch(Switchable*device):device(device){}
    void turnOn(){
        device->turnOn();
    }
    void turnOff(){
        device->turnOff();
    }
};


int main() {
    Light light;  // 创建电灯对象
    Switch switch1(&light);  // 创建开关对象，并传入电灯对象

    // 开关控制电灯
    switch1.turnOn();
    switch1.turnOff();

    return 0;
}