#include <iostream>
#include <string>


/*
备忘录模式是一种行为型设计模式，
它用于捕获一个对象的内部状态，
以便之后可以将对象恢复到这个状态。
这允许在不破坏封装的情况下保存和还原对象的状态。

*/

//备忘录类，用于存储对象的内部状态
class Memento{
private:
    std::string state;
public:
    Memento(const std::string& state):state(state){}
    Memento(){}
    std::string getState() const {
        return state;
    }
};

//发起人类，负责创建备忘录和恢复状态
class Originator{
private:
    std::string state;

public:
    void setState(const std::string& newState){
        state=newState;
    }

    std::string getState() const{
        return state;
    }

    Memento createMemento() const{
        return Memento(state);
    }

    void restoreFromMemento(const Memento& memento){
        state=memento.getState();
    }
};

//管理者类，负责保存和管理备忘录
class Caretaker{
private:
    Memento memento;

public:
    Caretaker(){}
    void saveMemento(const Memento& m){
        memento=m;
    }

    Memento getMemento() const{
        return memento;
    }
};

int main(){
    Originator originator;
    Caretaker caretaker;

    // 设置初始状态
    originator.setState("State 1");
    std::cout << "Current state: " << originator.getState() << std::endl;

    // 保存状态
    caretaker.saveMemento(originator.createMemento());

    // 修改状态
    originator.setState("State 2");
    std::cout << "Current state: " << originator.getState() << std::endl;

    // 恢复到之前的状态
    originator.restoreFromMemento(caretaker.getMemento());
    std::cout << "Restored state: " << originator.getState() << std::endl;

    return 0;
}
