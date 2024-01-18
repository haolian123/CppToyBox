#include <iostream>

// 抽象产品A
class AbstractProductA {
public:
    virtual void use() = 0;
};

// 具体产品A1
class ConcreteProductA1 : public AbstractProductA {
public:
    void use() override {
        std::cout << "Using Product A1" << std::endl;
    }
};

// 具体产品A2
class ConcreteProductA2 : public AbstractProductA {
public:
    void use() override {
        std::cout << "Using Product A2" << std::endl;
    }
};

// 抽象产品B
class AbstractProductB {
public:
    virtual void operate() = 0;
};

// 具体产品B1
class ConcreteProductB1 : public AbstractProductB {
public:
    void operate() override {
        std::cout << "Operating Product B1" << std::endl;
    }
};

// 具体产品B2
class ConcreteProductB2 : public AbstractProductB {
public:
    void operate() override {
        std::cout << "Operating Product B2" << std::endl;
    }
};

// 抽象工厂接口
class AbstractFactory {
public:
    virtual AbstractProductA* createProductA() = 0;
    virtual AbstractProductB* createProductB() = 0;
};

// 具体工厂1
class ConcreteFactory1 : public AbstractFactory {
public:
    AbstractProductA* createProductA() override {
        return new ConcreteProductA1();
    }

    AbstractProductB* createProductB() override {
        return new ConcreteProductB1();
    }
};

// 具体工厂2
class ConcreteFactory2 : public AbstractFactory {
public:
    AbstractProductA* createProductA() override {
        return new ConcreteProductA2();
    }

    AbstractProductB* createProductB() override {
        return new ConcreteProductB2();
    }
};
// 具体工厂3
class ConcreteFactory3 : public AbstractFactory {
public:
    AbstractProductA* createProductA() override {
        return new ConcreteProductA1();
    }

    AbstractProductB* createProductB() override {
        return new ConcreteProductB2();
    }
};

int main() {
    // 使用具体工厂1创建产品
    AbstractFactory* factory1 = new ConcreteFactory1();
    AbstractProductA* productA1 = factory1->createProductA();
    AbstractProductB* productB1 = factory1->createProductB();

    productA1->use();
    productB1->operate();

    // 使用具体工厂2创建产品
    AbstractFactory* factory2 = new ConcreteFactory2();
    AbstractProductA* productA2 = factory2->createProductA();
    AbstractProductB* productB2 = factory2->createProductB();

    productA2->use();
    productB2->operate();
    // 使用具体工厂3创建产品
    AbstractFactory* factory3 = new ConcreteFactory3();
    AbstractProductA* productA3 = factory3->createProductA();
    AbstractProductB* productB3 = factory3->createProductB();

    productA3->use();
    productB3->operate();

    delete productA1;
    delete productB1;
    delete productA2;
    delete productB2;
    delete productA3;
    delete productB3;

    return 0;
}