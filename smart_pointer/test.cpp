#include"scoped_ptr.h"
#include"shared_ptr.h"
#include"unique_ptr.h"
#include<cassert>
class Base { public: virtual ~Base() {} };
class Derived : public Base {};

void test_scoped_ptr(){

    scoped_ptr<std::string> strPtr(new std::string("Hello, world!"));

    // 测试操作符*和->
    assert(*strPtr == "Hello, world!"); // 测试解引用操作符*
    assert(strPtr->size() == 13);       // 测试->操作符

    // 测试reset功能
    strPtr.reset(new std::string("Another string"));
    assert(*strPtr == "Another string");

    // 测试get方法
    assert(strPtr.get() != nullptr);

    std::cout<<"scoped_ptr测试通过！"<<std::endl;
}

void test_unique_ptr() {
    // 测试构造函数
    unique_ptr<std::string> strPtr(new std::string("Hello, world!"));
    assert(*strPtr == "Hello, world!");

    // 测试操作符*和->
    assert(strPtr->size() == 13);       // 测试->操作符

    // 测试移动构造函数
    unique_ptr<std::string> movedPtr(std::move(strPtr));
    assert(strPtr.get() == nullptr);    // 原智能指针应为空
    assert(*movedPtr == "Hello, world!");

    // 测试移动赋值操作符
    unique_ptr<std::string> anotherPtr(new std::string("Another string"));
    anotherPtr = std::move(movedPtr);
    assert(movedPtr.get() == nullptr);  // 移动源应为空
    assert(*anotherPtr == "Hello, world!");

    // 测试reset功能
    anotherPtr.reset(new std::string("Yet another string"));
    assert(*anotherPtr == "Yet another string");

    // 测试get方法
    assert(anotherPtr.get() != nullptr);

    std::cout<<"unique_ptr测试通过！"<<std::endl;
}

void test_shared_ptr() {
    // 测试参数化构造函数
    shared_ptr<std::string> strPtr(new std::string("Hello, world!"));
    assert(*strPtr == "Hello, world!");
    assert(strPtr->size() == 13);

    // 测试拷贝构造函数
    shared_ptr<std::string> copyPtr(strPtr);
    assert(*copyPtr == "Hello, world!");

    // 测试移动构造函数
    shared_ptr<std::string> movedPtr(std::move(strPtr));
    assert(*movedPtr == "Hello, world!");
    assert(strPtr.get() == nullptr);

    // 测试拷贝赋值操作符
    shared_ptr<std::string> anotherPtr(new std::string("Another"));
    anotherPtr = copyPtr;
    assert(*anotherPtr == "Hello, world!");

    // 测试移动赋值操作符
    shared_ptr<std::string> anotherMovedPtr(new std::string("Moved"));
    anotherMovedPtr = std::move(movedPtr);
    assert(*anotherMovedPtr == "Hello, world!");
    assert(movedPtr.get() == nullptr);

    // 测试reset功能
    anotherMovedPtr.reset(new std::string("Another string"));
    assert(*anotherMovedPtr == "Another string");

    // 测试get方法
    assert(anotherMovedPtr.get() != nullptr);

    // 测试swap功能
    shared_ptr<std::string> swapPtr(new std::string("Swap test"));
    anotherMovedPtr.swap(swapPtr);
    assert(*swapPtr == "Another string");
    assert(*anotherMovedPtr == "Swap test");

    // 测试多态和类型转换功能
    shared_ptr<Derived> derivedPtr(new Derived());
    shared_ptr<Base> basePtr = static_pointer_cast<Base>(derivedPtr);
    assert(basePtr.get() == derivedPtr.get());

    shared_ptr<Base> dynamicCastPtr = dynamic_pointer_cast<Base>(derivedPtr);
    assert(dynamicCastPtr.get() == derivedPtr.get());

    shared_ptr<const Base> constCastPtr = const_pointer_cast<const Base>(basePtr);
    assert(constCastPtr.get() == basePtr.get());

    std::cout << "shared_ptr测试通过！" << std::endl;
}

int main(){
    test_scoped_ptr();
    test_unique_ptr();
    test_shared_ptr();
}
