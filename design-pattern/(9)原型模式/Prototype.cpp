/*
原型模式是一种创建型设计模式，它用于创建对象的新实例，而这些新实例是通过复制现有对象而得到的。
这个模式通过允许客户端复制已经存在的对象来创建新的对象，而不是从头开始创建，从而降低了对象创建的复杂性，同时保持了灵活性。
*/

#include<iostream>
//抽象原型类
class Prototype{
public:
    virtual Prototype* clone() const=0;
    virtual void display() const=0 ;
};

//具体原型类，实现clone方法
class ConcretePrototype: public Prototype{
private:
    std::string data;
public:
    ConcretePrototype(const std::string&data):data(data){

    }
    Prototype* clone() const override{
        /*需要注意深拷贝的问题*/
        return new ConcretePrototype(data);
    }

    void display() const override{
        printf("Data: %s\n",data.c_str());
    }
};


int main(){
     // 创建一个原型对象
    Prototype* original = new ConcretePrototype("Original Data");
    
    // 使用原型对象的clone方法创建新对象
    Prototype* copy1 = original->clone();
    Prototype* copy2 = original->clone();
    
    // 验证对象是否被成功克隆
    original->display();
    copy1->display();
    copy2->display();

    // 释放内存
    delete original;
    delete copy1;
    delete copy2;

    return 0;
}