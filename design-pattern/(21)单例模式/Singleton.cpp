
#include<iostream>
/*
单例模式是一种创建型设计模式，它确保一个类只有一个实例，
并提供全局访问点以获取该实例。
这对于需要共享资源的情况非常有用。
*/
class Singleton{
private:
static Singleton* instance;
Singleton(){}

public:
    static Singleton* GetInstance(){
        if(instance==nullptr){
            instance=new Singleton();
        }
        return instance;
    }
};
Singleton* Singleton::instance=nullptr;


int main(){
    auto S1=Singleton::GetInstance();
    auto S2=Singleton::GetInstance();
    if(S1==S2){
        printf("S1和S2相同");

    }
}