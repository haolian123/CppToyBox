/*
简单工厂模式（Simple Factory Pattern）是一种创建型设计模式，它提供一个单一的工厂类，
根据客户端的请求，动态创建不同类型的对象，隐藏了对象的创建逻辑。
这种模式使得客户端无需关心具体对象的实例化过程，只需向工厂类请求所需的对象即可，增强了代码的灵活性和可维护性。
*/

#include<iostream>
#include<stdexcept>
class Operation{
private:
    double numberA=0;
    double numberB=0;

public:
    double getNumberA(){return numberA;}
    double getNumberB(){return numberB;}
    void setNumberA(double n){numberA=n;}
    void setNumberB(double n){numberB=n;}

public:
    virtual double getResult(){
        double result=0;
        return result;
    }
};


// 加减乘除类
class OperationAdd:public Operation{
public:
    double getResult(){
        return getNumberA()+getNumberB();
    }

};

class OperationSub:public Operation{
public:
    double getResult(){
        return getNumberA()-getNumberB();
    }

};

class OperationMul:public Operation{
public:
    double getResult(){
        return getNumberA()*getNumberB();
    }

};

class OperationDiv:public Operation{
public:
    double getResult(){
        if(getNumberB()==0.0){
            /*抛出异常*/
            throw std::runtime_error("Division by zero is not allowed.");
        }
        return getNumberA()/getNumberB();
    }

};

// 简单工厂
class OperationFactory{
public:
    static Operation* createOperation(char operate){
        Operation *oper=nullptr;
        switch (operate){
            case '+':
            oper=new OperationAdd();
            break;
            case '-':
            oper=new OperationSub();
            break;
            case '/':
            oper=new OperationDiv();
            break;
            case '*':
            oper=new OperationMul();
            break;
        }
        return oper;
    }
};

int main(){
    Operation *oper=OperationFactory::createOperation('+');
    oper->setNumberA(5);
    oper->setNumberB(6);
    double result=oper->getResult();
    std::cout<<"result="<<result<<std::endl;

}