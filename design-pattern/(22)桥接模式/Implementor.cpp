/*
桥接模式是一种结构型设计模式，它将抽象部分与其实现部分分离，
使它们可以独立地变化。
这允许系统更灵活地适应变化。
*/

#include<iostream>

//手机软件
class HandsetSoft{
public:
    virtual void run()=0;
};

//手机游戏
class HandsetGame: public HandsetSoft{
public:
    void run() override{
        printf("运行手机游戏\n");
    }
};

//手机通讯录
class HandsetAddressList: public HandsetSoft{
public:
    void run() override{
        printf("运行手机通讯录\n");
    }
};

//手机品牌类
class HandsetBrand{
protected:
    HandsetSoft *soft=nullptr;
public:
    //设置手机软件
    void SetHandsetSoft(HandsetSoft* soft){
        this->soft=soft;
    }

    virtual void run()=0;

};

//手机品牌N
class HandsetBrandN: public HandsetBrand{
public:
    void run(){
        printf("品牌N\n");
        soft->run();
    }
};

//手机品牌M
class HandsetBrandM : public HandsetBrand{
public:
    void run(){
        printf("品牌M\n");
        soft->run();
    }
};

int main(){
    HandsetBrand* ab=new HandsetBrandN();
    ab->SetHandsetSoft(new HandsetGame());
    ab->run();

    ab=new HandsetBrandM();
    ab->SetHandsetSoft(new HandsetAddressList());
    ab->run();
}