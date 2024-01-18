#include<iostream>
#include<vector>

/*
迭代器模式是一种行为型设计模式，
它提供一种方法来顺序访问一个聚合对象中的元素，
而不需要暴露该对象的内部结构。这简化了遍历集合的过程。

*/
class Iterator{
public:
    virtual int First()=0;
    virtual int Next()=0;
    virtual bool isDone()=0;
    virtual int currentItem()=0;
};

class Aggregate{
public:
    virtual Iterator* CreateIterator()=0;

};

class ConcreteAggregate:public  Aggregate{
private:
    std::vector<int>items;
public:
    ConcreteAggregate(){
        items.resize(10,0);
    }
    Iterator* CreateIterator() override;

    int size(){
        return items.size();
    }
    

    int& operator[](int index){
        return items[index];
    }


};

class ConcreteIterator: public Iterator{
private:
    ConcreteAggregate* aggregate;
private:
    int current=0;
public:
    ConcreteIterator (ConcreteAggregate* aggregate){
        this->aggregate=aggregate;
    }

    int First() override{
        return (*aggregate)[0];
    }

    int Next() override{
        return (*aggregate)[current++];
    }

    bool isDone() override{
        return current>=aggregate->size()?true:false;
    }

    int currentItem() override{
        return (*aggregate)[current];
    }

};
Iterator* ConcreteAggregate::CreateIterator(){
        return (new ConcreteIterator(this));
    }
int main(){
    std::cout<<"OK"<<std::endl;
    ConcreteAggregate* a=new ConcreteAggregate();
    for(int i=0;i<10;i++){
        (*a)[i]=i;
    }
    
    Iterator* it=new ConcreteIterator(a);
    while(!it->isDone()){
        printf("%d\n",it->currentItem());
        it->Next();
    }
}