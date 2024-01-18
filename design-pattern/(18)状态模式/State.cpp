#include <iostream>

/*

状态模式是一种行为型设计模式，它允许对象在内部状态发生变化时改变其行为，
使其看起来像是改变了类。这种模式将状态抽象为独立的类，并允许对象在不同状态下执行不同的操作。

*/


class Context; // 前向声明 Context 类

class State {
public:
    virtual void Handle(Context* context)=0;
};

class ConcreteStateB; // 前向声明 ConcreteStateB 类

class ConcreteStateA : public State {
public:
    void Handle(Context* context) override;
};

class Context {
private:
    State* state;

public:
    Context(State* state) {
        this->state = state;
    }

    State* getState() {
        return state;
    }

    void setState(State* value) {
        this->state = value;
    }

    void request() {
        state->Handle(this);
    }
};

class ConcreteStateB : public State {
public:
    void Handle(Context* context) override {
        context->setState(new ConcreteStateA());
        printf("B->A\n");
    }
};

void ConcreteStateA::Handle(Context* context) {
    context->setState(new ConcreteStateB());
    printf("A->B\n");
}

int main() {
    State* s = new ConcreteStateA();
    Context* c = new Context(s);
    c->request();
    c->request();
    c->request();
    c->request();
    
    delete c; // 清理内存
    return 0;
}