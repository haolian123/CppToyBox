#include <iostream>
#include <vector>

/*
访问者模式是一种行为设计模式，它允许你在不改变元素类的前提下定义新的操作。
该模式的核心思想是将操作从元素类中分离出来，
这样可以在不修改现有元素类的情况下，通过不同的访问者类实现对元素的不同操作。
*/


// 前向声明访问者类
class Visitor;

// 元素类
class Element {
public:
    virtual void accept(Visitor* visitor) = 0;
    virtual ~Element() {}
    virtual void operation()=0;
};

// 具体元素类A
class ElementA : public Element {
public:
    void accept(Visitor* visitor) override;
    void operation() {
        std::cout << "ElementA operation" << std::endl;
    }
};

// 具体元素类B
class ElementB : public Element {
public:
    void accept(Visitor* visitor) override;
    void operation() {
        std::cout << "ElementB operation" << std::endl;
    }
};

// 访问者类
class Visitor {
public:
    virtual void visit(Element* element) = 0;

    virtual ~Visitor() {}
};

// 具体访问者类
class ConcreteVisitor : public Visitor {
public:
    void visit(Element* element) override {
        element->operation();
    }

};

// 实现元素类的accept方法
void ElementA::accept(Visitor* visitor) {
    visitor->visit(this);
}

void ElementB::accept(Visitor* visitor) {
    visitor->visit(this);
}

int main() {
    // 创建元素对象
    Element* elementA = new ElementA();
    Element* elementB = new ElementB();

    // 创建访问者对象
    Visitor* visitor = new ConcreteVisitor();

    // 对元素进行操作
    elementA->accept(visitor);
    elementB->accept(visitor);

    // 释放内存
    delete elementA;
    delete elementB;
    delete visitor;

    return 0;
}