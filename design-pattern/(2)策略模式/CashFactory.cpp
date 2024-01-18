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

//改进后的CashContext
class CashContext{
    CashSuper* cashContext=nullptr;
public:
    CashContext(std::string& pattern){
        if(pattern=="正常收费"){
            cashContext=new CashNormal();
        }else if(pattern=="满300减100"){
            cashContext=new CashReturn(300,100);
        }else if(pattern=="打8折"){
            cashContext=new CashRebate(0.8);
        }
    }
    double getResult(double money){
        return cashContext->acceptCash(money);
    }
};

int main(){
     std::string pattern ="打8折";
     CashContext* cashContext=new CashContext(pattern);
     double money=500;
     std::cout<<"total price= "<<cashContext->getResult(money)<<std::endl;
}