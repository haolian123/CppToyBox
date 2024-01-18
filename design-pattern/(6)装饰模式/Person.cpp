/*
装饰模式是一种结构型设计模式，它允许动态地向对象添加额外的功能，而无需修改其原始类。
这通过创建装饰器类，它实现了与原始类相同的接口并包含对原始对象的引用来实现。
装饰器类可以嵌套，以实现多层功能叠加，同时保持对客户端代码的透明性，使得对象的行为可以灵活组合和扩展，
符合"对扩展开放，对修改关闭"的设计原则。
*/
#include<iostream>

class Person{
public:
    Person(){}
    Person(std::string&name):name(name){}
    Person(std::string&&name):name(name){}
    virtual void show(){
        printf("装扮的%s",name.c_str());
    }
private:
    std::string name;

};


//服装类
class Finery:public Person{
protected:
    Person* component;

public:
    //打扮
    void decorate(Person* component){
        this->component=component;
    }

    void show(){
        if(component){
            component->show();
        }
    }
};


//具体服饰类
class TShirts: public Finery{
public:
    void show(){
        printf("大T恤");
        Finery::show();
    }
};

class BigTrouser: public Finery{
public:
    void show(){
        printf("垮裤");
        Finery::show();
    }
};

int main(){
    Person* person=new Person("haolian");
    BigTrouser *BT=new BigTrouser();
    TShirts *TS=new TShirts();
    BT->decorate(person);
    TS->decorate((Person*)BT);
    TS->show();
}