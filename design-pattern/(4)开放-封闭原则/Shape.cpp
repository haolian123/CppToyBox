/*
开放-封闭原则（Open-Closed Principle，OCP）是设计模式中的一个原则，它要求软件实体（例如类、模块、函数等）应该对扩展开放，对修改封闭。
这意味着当需要添加新功能时，我们应该通过扩展而不是修改现有代码来实现它，以减少代码的风险性和不稳定性。
下面是一个简单的C++示例来演示开放-封闭原则。
*/

#include <iostream>
#include <vector>

class Shape {
public:
    virtual void draw() const = 0;
};

class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Draw a circle." << std::endl;
    }
};

class Rectangle : public Shape {
public:
    void draw() const override {
        std::cout << "Draw a rectangle." << std::endl;
    }
};

int main() {
    std::vector<Shape*> shapes;

    shapes.push_back(new Circle());
    shapes.push_back(new Rectangle());

    for (const auto& shape : shapes) {
        shape->draw();
    }

    // 添加新的图形类型，不需要修改现有代码
    class Triangle : public Shape {
    public:
        void draw() const override {
            std::cout << "Draw a triangle." << std::endl;
        }
    };

    shapes.push_back(new Triangle());

    for (const auto& shape : shapes) {
        shape->draw();
    }

    // 释放内存
    for (const auto& shape : shapes) {
        delete shape;
    }

    return 0;
}