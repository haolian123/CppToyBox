# 一、初始化列表与赋值

### 类的初始化列表

- **const成员**：必须在构造函数的初始化列表中初始化，不能通过赋值进行。
- **引用成员**：与const成员类似，只能在构造函数的初始化列表中进行初始化。
- **对象成员**：如果对象成员的类没有默认构造函数，则其初始化也必须在构造函数的初始化列表中进行。

```c++
class Example {
public:
    Example(int a, const std::string& n) : age(a), name(n) {}

private:
    int age;
    const std::string& name;
};

int main() {
    std::string myName = "John Doe";
    Example example(30, myName);
    return 0;
}

```

在这个例子中，`Example` 类有两个成员：`age` 和 `name`。`name` 是对字符串的常量引用，它必须在构造函数的初始化列表中初始化。

### 类之间的嵌套

- **使用初始化列表**：当类中包含其他自定义类或结构体时，初始化列表可以用于创建对象并同时进行初始化。
- **构造函数赋值初始化**：等价于先定义对象，然后再进行赋值。这通常涉及默认构造函数的调用，然后是赋值操作符的调用。

```c++
class Inner {
public:
    Inner() { std::cout << "Inner default constructor\n"; }
};

class Outer {
public:
    Outer() : inner() { std::cout << "Outer constructor\n"; }

private:
    Inner inner;
};

int main() {
    Outer outer;
    return 0;
}
```

在这个例子中，`Outer` 类包含一个 `Inner` 类型的对象。`inner` 在 `Outer` 的构造函数的初始化列表中初始化。

### 无默认构造函数的继承关系

- 在继承关系中，如果基类没有默认构造函数，派生类必须通过初始化列表向基类的构造函数传递参数。
- 不使用初始化列表导致编译错误，因为编译器无法找到合适的基类构造函数来调用。

```c++
class Base {
public:
    Base(int x) : num(x) { std::cout << "Base constructor\n"; }

private:
    int num;
};

class Derived : public Base {
public:
    Derived(int x) : Base(x) { std::cout << "Derived constructor\n"; }
};

int main() {
    Derived derived(10);
    return 0;
}
```

在这个例子中，`Base` 类没有默认构造函数，因此 `Derived` 类在其构造函数中必须显式调用 `Base` 类的构造函数。

### 类中的const和引用数据成员

- 这些成员必须在初始化列表中初始化，不能通过赋值来初始化。
- 忽略这一点将导致编译错误，因为引用必须在定义时就被初始化，而const成员一旦定义后就不能更改。

```c++
class MyClass {
public:
    MyClass(int x, const std::string& str) : constInt(x), constRefStr(str) {}

private:
    const int constInt;          // const成员
    const std::string& constRefStr;  // 引用成员
};

int main() {
    std::string str = "Hello";
    MyClass obj(100, str);
    return 0;
}
```

这个例子中，`MyClass` 有两个成员：`constInt` 是一个 `const int` 类型的成员，`constRefStr` 是对 `std::string` 的常量引用。它们都必须在初始化列表中初始化。

___

# 二、enum class

在《Effective Modern C++》中，Item 10建议使用有作用域的 `enum class` 替代无作用域的 `enum`。

## 传统Enum的问题

### 1. 名称冲突

```cpp
enum Shape { circle, rectangle };
auto circle = 10;  // 错误：名称冲突
```

上述错误是因为两个 `circle` 在同一作用域中。这对于 `enum` 相当于定义了两个宏：

```cpp
#define circle 0
#define rectangle 1
```

因此，后面再定义 `circle` 会导致错误。

### 2. 成员名称冲突

即使枚举名称不同，只要成员有相同的名称，就会出现问题。

```cpp
enum A { a, b };
enum B { c, a };  // 错误：'a' 已在枚举 'A' 中定义
```

## 使用namespace作为解决方案

将枚举放在命名空间中，可以避免上述问题：

```cpp
namespace EntityType {
    enum Enum {
        Ground = 0,
        Human,
        Aerial,
        Total
    };
}

void foo(EntityType::Enum entityType) {
    if (entityType == EntityType::Ground) {
        // code
    }
}
```

命名空间提供了一种方式来避免名称冲突，但这种方式可能过于繁琐。

## 引入enum class

C++11引入了 `enum class`，解决了传统 `enum` 的多个问题：

- **为enum成员定义类型**
- **类型安全**
- **约束**

### 示例：使用enum class

```cpp
enum class EntityType {
    Ground = 0,
    Human,
    Aerial,
    Total
};

void foo(EntityType entityType) {
    if (entityType == EntityType::Ground) {
        // code
    }
}
```

---

# 三、RAII（资源获取即初始化）

RAII(Resource Acquisition Is Initialization)是一种在C++中管理资源的编程惯用法，利用了对象生命周期来管理资源的获取和释放。

## 基本概念

RAII的核心理念是将资源的生命周期与对象的生命周期绑定。当对象被创建时，资源被获取（如分配内存），当对象的生命周期结束时（如对象被销毁），资源被释放。

### 优点

1. **异常安全**：资源自动释放，即使发生异常也能保证资源正确释放。
2. **内存管理**：减少内存泄漏和资源泄漏的风险。
3. **代码清晰**：资源的管理逻辑封装在类中，使得代码更加清晰和易于维护。

### 应用场景

- 管理动态分配的内存。
- 文件句柄和网络连接的管理。
- 任何需要在构造时获取并在析构时释放的资源。

## RAII的实现

RAII的实现依赖于C++的构造函数和析构函数。

1. 构造函数：在构造函数中获取资源。这可能包括分配内存、打开文件、获取网络资源等。
2. 析构函数：在析构函数中释放资源。无论对象如何结束生命周期（正常结束或异常），析构函数都会被调用，从而确保资源被正确释放。

## RAII类的设计

设计一个RAII类需要注意以下几点：

1. ### 确保资源唯一性

   - 确保每个资源只由一个RAII对象管理，避免资源的重复释放。

2. ### 禁止复制

   - 通过删除复制构造函数和复制赋值运算符，防止对象被不正确地复制。
   - 可以实现移动构造函数和移动赋值运算符以支持资源的转移。

3. ### 异常安全

   - 确保在资源获取过程中如果发生异常，已经获取的资源能够被正确释放。

4. ### 资源的延迟获取

   - 在必要时才获取资源，避免不必要的资源占用。

## RAII的示例

### 示例1：管理动态内存

```cpp
class MemoryRAII {
public:
    MemoryRAII(size_t size) : data_(new int[size]) {}
    ~MemoryRAII() { delete[] data_; }

    // 禁止复制
    MemoryRAII(const MemoryRAII&) = delete;
    MemoryRAII& operator=(const MemoryRAII&) = delete;

    // 允许移动
    MemoryRAII(MemoryRAII&& other) noexcept : data_(other.data_) {
        other.data_ = nullptr;
    }
    MemoryRAII& operator=(MemoryRAII&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            other.data_ = nullptr;
        }
        return *this;
    }

private:
    int* data_;
};
```

### 示例2：文件资源管理

```cpp
#include <fstream>
#include <string>

class FileRAII {
public:
    FileRAII(const std::string& fileName) : file_(fileName) {}
    ~FileRAII() {
        if (file_.is_open()) {
            file_.close();
        }
    }

    // 禁止复制
    FileRAII(const FileRAII&) = delete;
    FileRAII& operator=(const FileRAII&) = delete;

    // 允许移动
    FileRAII(FileRAII&& other) noexcept : file_(std::move(other.file_)) {}
    FileRAII& operator=(FileRAII&& other) noexcept {
        if (this != &other) {
            file_ = std::move(other.file_);
        }
        return *this;
    }

    std::fstream& getStream() { return file_; }

private:
    std::fstream file_;
};

```

在这个例子中，`FileRAII` 类负责打开一个文件，并在其析构函数中关闭该文件。这样，无论由于什么原因（正常结束或异常）结束其作用域，文件都会被安全关闭。

# 四、Copy-and-Swap

___

## 为什么需要Copy-and-Swap?

#### 管理资源的类
任何管理资源的类（例如智能指针）都需要实现拷贝构造函数、析构函数和拷贝赋值运算符。拷贝赋值运算符是实现中最微妙和复杂的部分。

#### 避免的陷阱
在实现赋值运算符时，需要避免代码重复并提供强大的异常安全保证。正确实现可以避免许多常见的编程错误。

## 基本概念
### Copy-and-Swap技巧
Copy-and-swap是一种优雅地处理赋值操作的方法，通过创建一个局部副本（使用拷贝构造函数），然后交换副本和原始数据（使用swap函数）来工作。

### 异常安全和自赋值安全
这种方法提供了强异常安全保证，同时也天然地解决了自赋值的问题。

## 实现步骤
### 拷贝构造函数
必须有一个有效的拷贝构造函数来创建对象的副本。

### 析构函数
需要一个有效的析构函数来正确地释放资源。

### 交换函数
实现一个交换函数，它是一个不抛出异常的函数，用于交换两个对象或成员的资源。

### 赋值操作符
在赋值操作符中，使用拷贝构造函数和swap函数来实现资源的正确管理。

### swap函数的实现
#### 使用std::swap
虽然可能想使用`std::swap`，但在实现中，`std::swap`使用了拷贝构造函数和拷贝赋值运算符，这可能导致循环定义。

#### 自定义swap
因此，通常需要提供自定义的swap方法。这种方法避免了使用标准库`std::swap`可能导致的不必要的对象构造和析构。

### 示例
```cpp
class MyClass {
public:
    MyClass(const MyClass& other); // 拷贝构造函数
    ~MyClass(); // 析构函数
    friend void swap(MyClass& first, MyClass& second); // swap函数

    MyClass& operator=(MyClass other) {
        swap(*this, other);
        return *this;
    }
};

void swap(MyClass& first, MyClass& second) {
    // 实现两个对象的资源交换
}
```
在这个示例中，赋值操作通过创建一个临时对象（拷贝构造函数）和交换临时对象与当前对象的资源（swap函数）来完成。当临

时对象离开作用域时，原始对象的资源随之被正确地释放。

## 注意事项
- 确保所有资源管理操作都被正确实现，尤其是在拷贝构造函数和swap函数中。
- 对于不需要管理资源的简单类，使用默认的赋值操作符可能更为高效。
- 自定义的swap函数应该高效且不抛出异常，以保证赋值操作的安全性和效率。

## 示例：智能指针

```c++
#include <iostream>
#include <string>

namespace SmartPointerNamespace {
    template<typename T>
    class SmartPtr {
    public:
        // 默认构造函数
        SmartPtr() noexcept : ptr_(new T()) {}

        // 指针型构造函数
        explicit SmartPtr(T* ptr) noexcept : ptr_(ptr) {}

        // 拷贝构造函数
        SmartPtr(const SmartPtr &rhs) noexcept : ptr_(new T(*rhs.ptr_)) {}

        // 拷贝赋值运算符
        SmartPtr &operator=(SmartPtr rhs) noexcept {
            swap(rhs);
            return *this;
        }

        //移动构造函数
        SmartPtr(SmartPtr&& rhs) : ptr(rhs.ptr) {
        	rhs.ptr = nullptr;
    	}

        // 移动赋值运算符
        SmartPtr &operator=(SmartPtr &&rhs) noexcept {
            if (this != &rhs) {
                SmartPtr(std::move(rhs)).swap(*this);
            }
            return *this;
        }

        // 析构函数
        ~SmartPtr() {
            delete ptr_;
        }

        // 交换函数
        void swap(SmartPtr &rhs) noexcept {
            using std::swap;
            swap(ptr_, rhs.ptr_);
        }

        // 获取原始指针
        T* get() const noexcept {
            return ptr_;
        }

    private:
        T *ptr_;
    };

    // 非成员swap函数
    template<typename T>
    void swap(SmartPtr<T> &lhs, SmartPtr<T> &rhs) noexcept {
        lhs.swap(rhs);
    }
}

int main() {
    using SmartPointerNamespace::SmartPtr;
    using std::string;

    SmartPtr<string> smartStr1(new string("hello")), smartStr2(new string("world"));

    // 交换前
    std::cout << *smartStr1.get() << " " << *smartStr2.get() << std::endl;

    swap(smartStr1, smartStr2); // 利用ADL进行swap

    // 交换后
    std::cout << *smartStr1.get() << " " << *smartStr2.get() << std::endl;

    // 使用赋值运算符进行拷贝
    SmartPtr<string> smartStr3;
    smartStr3 = smartStr1;

    // 输出拷贝后的结果
    std::cout << "After copying: " << *smartStr3.get() << std::endl;

    return 0;
}

```

# 五、pImpl (Pointer to Implementation)

## 定义

“指向实现的指针”（pImpl）是一种 C++ 编程技巧，通过将类的实现细节从其接口中分离出来，并将其放置在一个独立的、不透明的指针后面来隐藏这些细节。

## **基本用法：**

- **传统类实现：**
  ```cpp
  class X {
  private:
    C c;
    D d;
  };
  ```
- **使用 pImpl 的实现：**
  
  ```cpp
  class X {
  private:
    struct XImpl;
    XImpl* pImpl;
  };
  ```
```
  
  **在 CPP 文件中定义：**
  
  ```cpp
  struct X::XImpl {
    C c;
    D d;
  };
```

## 优势

1. **二进制兼容性：**
   - 在开发库时，可以在不破坏与客户端的二进制兼容性的情况下向 `XImpl` 添加或修改字段。因为 `X` 类的二进制布局不会更改，所以可以在库的次要版本更新中安全地添加新功能。

2. **数据隐藏：**
   - 对于特别是专有库的开发，隐藏实现细节是很重要的。pImpl 提供了一种方式来隐藏那些实现库公共接口所使用的其他库或实现技术。这可以避免用户对实现做出不安全的假设或破坏封装。

3. **编译时间：**
   - 使用 pImpl 可以减少编译时间。修改 `XImpl` 类时，只需重建 `X` 的源文件，而不是整个项目。在标准头文件/实现技术（不使用 pImpl）中，对 `X` 添加新字段会要求所有使用 `X` 的客户端重新编译，以调整分配的大小。

## 应用场景

- pImpl 特别适用于库开发，尤其是在需要频繁更新和维护而又不想影响到已有客户端代码的情况下。

## 示例

1. **声明类和隐藏实现（头文件）**

   假设有一个类 `MyClass`，在头文件 `MyClass.h` 中，声明这个类，但不直接在类中声明其数据成员。

    ```cpp
    // MyClass.h
    class MyClass {
    public:
        MyClass();
        ~MyClass();
        MyClass(const MyClass& other); // 拷贝构造函数
        MyClass(MyClass&& other);      // 移动构造函数
        MyClass& operator=(MyClass other); // 赋值操作符

        void doSomething();

    private:
        struct Impl;           // 声明一个私有的内部结构体
        Impl* pImpl;           // 指向实现的指针
    };
    ```

2. **定义实现（源文件）**

   在源文件 `MyClass.cpp` 中，定义 `Impl` 结构体，包含实际的数据成员和实现。

    ```cpp
    // MyClass.cpp
    #include "MyClass.h"

    struct MyClass::Impl {
        // 实际的数据成员
        int data;

        // 实际的方法实现
        void doInternalWork() {
            // ... 实现细节 ...
        }
    };

    MyClass::MyClass() : pImpl(new Impl()) {
    }

    MyClass::~MyClass() {
        delete pImpl;
    }

    MyClass::MyClass(const MyClass& other) : pImpl(new Impl(*other.pImpl)) {
    }

    MyClass::MyClass(MyClass&& other) : pImpl(other.pImpl) {
        other.pImpl = nullptr;
    }

    MyClass& MyClass::operator=(MyClass other) {
        std::swap(pImpl, other.pImpl);
        return *this;
    }

    void MyClass::doSomething() {
        pImpl->doInternalWork();
    }
    ```

3. **使用类**

   当使用 `MyClass` 时，不需要关心其内部实现细节。

    ```cpp
    // main.cpp
    #include "MyClass.h"

    int main() {
        MyClass obj;
        obj.doSomething();
        return 0;
    }
    ```

## 注意事项

- 确保在析构函数、拷贝构造函数、移动构造函数和赋值操作符中正确管理 `pImpl` 指针。
- 使用 pImpl 可以减少头文件依赖，从而减少编译时间。
- pImpl 隐藏了类的实现细节，有利于维护和二进制兼容性。
