/*
观察者模式是一种行为型设计模式，用于在对象之间建立一种一对多的依赖关系。当一个对象的状态发生变化时
，所有依赖于它的其他对象都会自动收到通知并进行相应的更新操作。
这种模式适用于以下情景：
当存在一个对象（称为主题或目标），并且多个对象（观察者）需要根据主题的状态变化而自动更新。
当不希望主题与观察者之间紧密耦合，即希望它们之间保持松散的关系，以便更容易扩展和维护。
当需要确保在系统中的多个部分之间保持一致性，而不需要将这些部分相互了解或直接通信。
*/
#include<iostream>
#include<vector>

class Observer{
public:
    virtual void Update()=0;
};

//抽象通知者
class Subject{
private:
    std::vector<Observer*> observers;
public:
    //增加观察者
    void attach(Observer* observer){
        observers.emplace_back(observer);
    }

    //移除观察者
    void detach(Observer* observer){
        for(int i=0;i<observers.size();i++){
            if(observers[i]==observer)
                observers.erase(i+observers.begin());
                break;
        }
    }

    //通知
    void notify(){
        for(auto it : observers){
            it->Update();
        }
    }
};


class ConcreteSubject: public Subject{
private:
    std::string subjectState;
public:
    std::string getSubjectState(){
        return this->subjectState;
    }
    void setSubjectState(std::string subjectState){
        this->subjectState=subjectState;
    }
};


class ConcreteObserver: public Observer{
private:
    std::string name;
    std::string observerState;
    ConcreteSubject * subject;

public:
    ConcreteObserver(ConcreteSubject* subject, std::string name){
        this->subject=subject;
        this->name=name;
    }

    void Update() override{
        observerState=subject->getSubjectState();
        printf("观察者%s的新状态是%s\n",name.c_str(),observerState.c_str());
    }

    ConcreteSubject* getSubject(){
        return this->subject;
    }

    void setSubject(ConcreteSubject* subject){
        this->subject=subject;
    }
}; 


//客户端代码
int main(){
    ConcreteSubject* s=new ConcreteSubject();

    s->attach(new ConcreteObserver(s,"X"));
    s->attach(new ConcreteObserver(s,"Y"));
    s->attach(new ConcreteObserver(s,"Z"));
    s->setSubjectState(std::string("ABC"));
    s->notify();

}