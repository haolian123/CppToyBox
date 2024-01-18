/*
外观模式（Facade Pattern）是一种结构性设计模式，它提供了一个统一的接口，用于访问子系统中的一组接口，
从而简化复杂系统的使用。外观模式允许客户端通过与外观对象交互，而不必与子系统的每个组件直接交互，
从而降低了系统的复杂性，提高了客户端的可维护性和可用性。
这种模式类似于在现实生活中，你只需按下电视遥控器的按钮，而不必了解电视内部的复杂工作原理即可控制电视。
*/

#include<iostream>

class SubSystemOne{
public:
    void MethodOne(){
        printf("子系统方法一\n");
    }
};
class SubSystemTwo{
public:
    void MethodTwo(){
        printf("子系统方法二\n");
    }
};
class SubSystemThree{
public:
    void MethodThree(){
        printf("子系统方法三\n");
    }
};
class SubSystemFour{
public:
    void MethodFour(){
        printf("子系统方法四\n");
    }
};
class Facade{
    SubSystemOne one;
    SubSystemTwo two;
    SubSystemThree three;
    SubSystemFour four;
public:
    Facade(){}
    void MethodA(){
        printf("\n-------方法组A()------");
        one.MethodOne();
        two.MethodTwo();
        four.MethodFour();
    }

    void MethodB(){
        printf("\n-------方法组B()------");
        two.MethodTwo();
        three.MethodThree();
    }
};

int main(){
    Facade* facade=new Facade();
    facade->MethodA();
    facade->MethodB();
}