/*
策略模式（Strategy Pattern）是一种行为型设计模式，它定义了一系列算法或行为，
并将它们封装成独立的策略类，使得这些策略可以相互替换，而不影响客户端代码。
客户端可以动态选择所需的策略，并在运行时切换策略，从而实现不同的行为。
这种模式有助于减少代码中的条件分支，提高代码的可扩展性和维护性。
*/

#include<iostream>

// 现金收费抽象类
class CashSuper{
public:
    virtual double acceptCash(double money)=0;
};

// 正常收费子类
class CashNormal:public CashSuper{
public:
    double acceptCash(double money){
        return money;
    }
};

//打折收费子类
class CashRebate:public CashSuper{
private:
    // 折扣 0.xx格式
    double moneyRebate=1.0;
public:
    CashRebate(double moneyRebate):moneyRebate(moneyRebate){}
    double acceptCash(double money){
        return money*moneyRebate;
    }
};

//返利收费子类
class CashReturn:public CashSuper{
private:
    double moneyCondition=0.0;
    double moneyReturn=0.0;
public:
    CashReturn(double moneyCondition,double moneyReturn):
    moneyCondition(moneyCondition),moneyReturn(moneyReturn){}

    double acceptCash(double money){
        double result=money;
        if(money>=moneyCondition){
            result=money-money/moneyCondition*moneyReturn;
        }
        return result;
    }
};

//CashContext类
class CashContext{
private:
    CashSuper *cs=nullptr;
public:
    CashContext(CashSuper* csuper){
        cs=csuper;
    }
public:
    double getResult(double money){
        return cs->acceptCash(money);
    }

};


//客户端代码
int main(){
    double total=0.0;
    double money=500;
    std::string pattern ="打8折";
    CashContext *cashContext=nullptr;
    if(pattern=="正常收费"){
        cashContext=new CashContext(new CashNormal());
    }else if(pattern=="满300减100"){
        cashContext=new CashContext(new CashReturn(300,100));
    }else if(pattern=="打8折"){
        cashContext=new CashContext(new CashRebate(0.8));
    }
    std::cout<<"total price= "<<cashContext->getResult(money)<<std::endl;
}   

/*这样有个问题：
    需要在客户端去判断要用哪个算法，可以和简单工厂模式结合起来。
    见CashFactory



*/
