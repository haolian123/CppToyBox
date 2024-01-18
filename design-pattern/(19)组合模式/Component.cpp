#include<iostream>
#include<vector>

/*
组合模式是一种结构型设计模式，它允许将对象组合成树状结构以表示部分-整体层次结构。
这使得客户端可以统一对待单个对象和对象组合，而不需要区分它们。

*/
class Component{
protected:
    std::string name;
public:
    Component(const std::string& name){
        this->name=name;
    }

    virtual void add(Component* c)=0;
    virtual void remove(Component* c)=0;
    virtual void display(int depth)=0;
};

//叶子节点
class Leaf: Component{
public:
    Leaf(const std::string& name):Component(name){

    }

    void add(Component* c) override{
        printf("Cannot add to a leaf");
    }

    void remove(Component* c) override{
        printf("Cannot remove from a leaf");
    }

    void display(int depth){
        std::string out=std::string(depth,'-');
        std::cout<<out<<name<<std::endl;
        // printf("%s%s",out.c_str(),name.c_str());
    }
};

//有枝节点
class Composite: Component{
private:
    std::vector<Component*>children;
public:
    Composite(const std::string &name):Component(name){

    }
     void add(Component* c) override{
        children.emplace_back(c);
    }

    void remove(Component* c) override{
        // printf("Cannot remove from a leaf");
        children.emplace_back(c);
    }

    void display(int depth){
        std::string out=std::string(depth,'-');
        std::cout<<out<<name<<std::endl;
        for(auto it:children){
            it->display(depth+2);
        }
    }
};

int main(){
    Composite* root=new Composite("root");
    root->add((Component*)(new Leaf("LeafA")));
    root->add((Component*)(new Leaf("LeafB")));

    Composite* comp=new Composite("Composite X");
    comp->add((Component*)(new Leaf("Leaf XA")));
    comp->add((Component*)(new Leaf("Leaf XB")));
    
    root->add((Component*)comp);

    root->display(1);

}