/*
职责链模式是一种行为型设计模式，它允许将请求传递沿着处理者链，
直到其中一个处理者能够处理请求。
这减少了发送者和接收者之间的耦合。
*/

#include<iostream>
#include<vector>
class Handler{
protected:
    Handler* successor;

public:
    void setSuccessor(Handler* successor){
        this->successor=successor;
    }

    virtual void HandleRequest(int request)=0;
};


class ConcreteHandler1:public Handler{
public:
    void HandleRequest(int request) override{
        if(request>=0&&request<10){
            printf("ConcreteHandler1处理%d\n",request);
        }else if(successor!=nullptr){
            successor->HandleRequest(request);
        }
    }
};

class ConcreteHandler2: public Handler{
public:
    void HandleRequest(int request) override{
        if(request>=10&&request<20){
            printf("ConcreteHandler2处理%d\n",request);
        }else if(successor!=nullptr){
            successor->HandleRequest(request);
        }
    }
};

class ConcreteHandler3: public Handler{
public:
    void HandleRequest(int request) override{
        if(request>=20&&request<=30){
            printf("ConcreteHandler3处理%d\n",request);
        }else if(successor!=nullptr){
            successor->HandleRequest(request);
        }
    }
};

int main(){
    Handler* h1=new ConcreteHandler1();
    Handler* h2=new ConcreteHandler2();
    Handler* h3=new ConcreteHandler3();
    h1->setSuccessor(h2);
    h2->setSuccessor(h3);
    std::vector<int>requests={1,4,17,25,3,12,26};
    for(auto it:requests){
        h1->HandleRequest(it);
    }

}