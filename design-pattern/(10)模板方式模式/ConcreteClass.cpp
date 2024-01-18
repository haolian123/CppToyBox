/*
模板方法模式是一种行为型设计模式，它在一个抽象类中定义了一个算法的骨架，
然后将某些具体步骤延迟到子类中实现。这允许子类在不改变算法结构的情况下，重定义算法的特定步骤，
提供了一种模板化的方法来设计和实现算法，促进了代码重用和扩展性。
*/

#include<iostream>

class AbstractClass{
public:
    virtual void PrimitiveOperation1()=0;
    virtual void PrimitiveOperation2()=0;

    void TemplateMethod(){
        PrimitiveOperation1();
        PrimitiveOperation2();
    }
};

class ConcreteClassA: public AbstractClass{
public:
    void PrimitiveOperation1() override{
        printf("具体类A方法1实现\n");
    }
    void PrimitiveOperation2() override{
        printf("具体类A方法2实现\n");
    }
};

class ConcreteClassB: public AbstractClass{
public:
    void PrimitiveOperation1() override{
        printf("具体类B方法1实现\n");
    }
    void PrimitiveOperation2() override{
        printf("具体类B方法2实现\n");
    }
};

int main(){
    AbstractClass* c=nullptr;
    c=new ConcreteClassA();
    c->TemplateMethod();
    c=new ConcreteClassB();
    c->TemplateMethod();
}