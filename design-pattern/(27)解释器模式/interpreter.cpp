#include <iostream>
#include <vector>


// 解释器模式是一种行为型设计模式，用于定义一个语言的文法规则，
// 并为该语言创建一个解释器。
// 这允许解释和执行特定语言的语句或表达式。
// 它通常用于构建编程语言解释器、
// 正则表达式解释器以及其他需要解释语言结构的应用中。


//抽象表达式
class Expression{
public:
    virtual int interpret()=0;
};

//终结符表达式
class NumberExpression: public Expression{
private:
    int number;
public:
    NumberExpression(int value) : number(value){}

    int interpret() override {
        return number;
    }
};

//非终结符表达式
class AdditionExpression: public Expression{
private:
    Expression* left;
    Expression* right;
public:
    AdditionExpression(Expression* l, Expression* r):left(l),right(r){}

    int interpret() override{
        return left->interpret() + right->interpret();
    }
};

int main(){
    //构建解释器
    Expression* expression=new AdditionExpression(
        new NumberExpression(5),
        new AdditionExpression(
            new NumberExpression(10),
            new NumberExpression(2)
        )
    );

    //解释并计算表达式结果
    int result=expression->interpret();
    std::cout<<"Result:" << result << std::endl;
    return 0;
}