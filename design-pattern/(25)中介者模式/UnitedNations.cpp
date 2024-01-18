/*
中介者模式是一种行为型设计模式，它定义了一个中介者对象，
用于协调多个对象之间的通信，而不需要让这些对象相互引用。
这降低了系统中对象之间的耦合度。
*/
#include<iostream>
class Colleague;
class Mediator{
public:
    virtual void send(std::string message, Colleague* colleague)=0;
};

class Colleague{
protected:
    Mediator * mediator=nullptr;

public:
    Colleague(Mediator* mediator){
        this->mediator=mediator;
    }
};

class ConcreteColleague1: public Colleague{
public:
    ConcreteColleague1(Mediator* mediator): Colleague(mediator){

    }

    void send(std::string message){
        mediator->send(message,(Colleague*)this);
    }

    void notify(std::string& message){
        printf("同事1得到信息:%s\n",message.c_str());
    }
};

class ConcreteColleague2: public Colleague{
public:
    ConcreteColleague2(Mediator* mediator): Colleague(mediator){

    }

    void send(std::string message){
        mediator->send(message,(Colleague*)this);
    }

    void notify(std::string& message){
        printf("同事2得到信息:%s\n",message.c_str());
    }
};

class ConcreteMediator: public Mediator{
private:
    ConcreteColleague1* colleague1;
    ConcreteColleague2* colleague2;
public:
    void setColleague1(ConcreteColleague1* concreteColleague1){
        colleague1=concreteColleague1;
    }
    void setColleague2(ConcreteColleague2* concreteColleague2){
        colleague2=concreteColleague2;
    }
    void send(std::string message, Colleague* colleague){
        if(colleague==colleague1){
            colleague2->notify(message);
        }else{
            colleague1->notify(message);
        }
    }

};

int main(){
    ConcreteMediator * m=new ConcreteMediator();
    ConcreteColleague1 *c1=new ConcreteColleague1(m);
    ConcreteColleague2 *c2=new ConcreteColleague2(m);

    m->setColleague1(c1);
    m->setColleague2(c2);

    c1->send("吃饭了吗?");
    c2->send("没有！");
}