/*
建造者模式（Builder Pattern）是一种创建型设计模式，旨在将复杂对象的构建过程分离出来，
使用户能够通过指定对象的类型和内容来构建它们，而无需了解内部的具体构建细节。
该模式允许逐步创建复杂对象，将对象的构建过程封装在一个独立的建造者类中。
建造者模式通常由以下几个角色组成：
产品（Product）、具体建造者（Concrete Builder）、指挥者（Director）和建造者接口（Builder）。
它在实际应用中用于创建复杂的对象，
如文档、电子商务订单、图形用户界面等，以提供更灵活的对象构建方式和降低对象构建的复杂性。
*/
#include<iostream>
#include<vector>
class Product{
    std::vector<std::string> parts;
public:
    void Add(const std::string& part){
        parts.emplace_back(part);
    }
    void Show(){
        printf("\n-------产品 创建------\n");
        for(auto part : parts){
            std::cout<<part<<std::endl;
        }
    }
};

//Builder类——抽象建造者类，确定产品由两个部件PartA和PartB组成，并声明一个得到产品建造后结果的方法getResult。
class Builder{
public:
    virtual void BuildPartA()=0;
    virtual void BuildPartB()=0;
    virtual Product* getResult()=0;

};

//具体建造者类1
class ConcreteBuilder1: public Builder{
private:
    Product* product=new Product();
public:
    void BuildPartA() override{
        product->Add("部件A");
    }

    void BuildPartB() override{
        product->Add("部件B");
    }

    Product* getResult() override{
        return product;
    }
};

//具体建造者类2
class ConcreteBuilder2: public Builder{
private:
    Product* product=new Product();
public:
    void BuildPartA() override{
        product->Add("部件X");
    }

    void BuildPartB() override{
        product->Add("部件Y");
    }

    Product* getResult() override{
        return product;
    }
};

//指挥者类
class Director{
public:
    void Construct(Builder* builder){
        builder->BuildPartA();
        builder->BuildPartB();
    }
};

int main(){
    Director* dir=new Director();
    Builder* b1=new ConcreteBuilder1();
    Builder* b2=new ConcreteBuilder2();

    dir->Construct(b1);
    Product *p1=b1->getResult();
    p1->Show();
    dir->Construct(b2);
    Product *p2=b2->getResult();
    p2->Show();
}