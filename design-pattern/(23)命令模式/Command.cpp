#include<iostream>

/*

命令模式是一种行为型设计模式，它将请求封装为对象，
以便可以参数化客户端对象，排队请求，将请求记录到日志中，
支持可撤销操作等。

*/

class Receiver{
public:
    void Action(){
        printf("执行请求\n");
    }
};

class Command{
protected:
    Receiver* receiver;
public:
    Command(Receiver* receiver){
        this->receiver=receiver;
    }

    virtual void Execute()=0;

};

class ConcreteCommand: public Command{
public:
    ConcreteCommand(Receiver* receiver):Command(receiver){}

    void Execute() override{
        receiver->Action();
    }
};

class Invoker{
private:
    Command * command=nullptr;
public:
    void SetCommand(Command* command){
        this->command=command;
    }

    void ExecuteCommand(){
        command->Execute();
    }
};

int main(){
    Receiver* receiver=new Receiver();
    Command* command=new ConcreteCommand(receiver);
    Invoker* invoker=new Invoker();
    invoker->SetCommand(command);
    invoker->ExecuteCommand();
}