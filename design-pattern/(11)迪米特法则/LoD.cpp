
/*
迪米特法则，也被称为最少知识原则，
强调一个对象应当对其他对象尽可能少了解，
减少类之间的耦合，从而提高系统的可维护性和灵活性。
具体实现时，一个对象只应该与其直接朋友（关联最密切的类）通信，
而不应该暴露过多的细节给其他对象。
*/

#include<iostream>
#include<vector>

//房子类
class House{
public:
    std::string getLocation(){
        return location;
    }

    void setLocation(const std::string&loc){
        location=loc;
    }

private:
    std::string location;
};

//客户类
class Customer{
public:
    Customer(const std::string&name) :name(name){}
    void rentHouse(House* house){
        std::cout<<name<<"租了位于"<<house->getLocation()<<"的房子"<<std::endl;
    }
private:
    std::string name;
};

//定义房屋中介类，充当“朋友”的角色
class HouseMediator{
public:
    HouseMediator(){
        //中介类创建了房子对象
        availableHouse->setLocation("城市中心");
    }

    House* getHouse(){
        return availableHouse;
    }

private:
    House* availableHouse=new House();
};

int main(){
    HouseMediator * mediator=new HouseMediator();

    Customer customer1("小明");
    Customer customer2("小红");

    customer1.rentHouse(mediator->getHouse());
    customer2.rentHouse(mediator->getHouse());
}