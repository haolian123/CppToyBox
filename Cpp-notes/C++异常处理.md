# 异常处理

___

## 1. 基本概念

### 抛出异常（Throwing Exceptions）
- 使用`throw`关键字抛出异常。
- 可以抛出任何类型的对象（通常抛出派生自`std::exception`的类）。

### 捕获异常（Catching Exceptions）
- 使用`try`和`catch`块来捕获和处理异常。
- `try`块包含可能抛出异常的代码。
- `catch`块定义了当特定类型的异常被抛出时执行的代码。

### 异常对象（Exception Objects）
- 当异常被抛出时，会创建一个异常对象。
- 异常对象通常包含关于异常的信息，如错误消息。

## 2. 异常类型

### 标准异常（Standard Exceptions）

C++ 标准库中的异常类大多定义在 `<stdexcept>`、`<new>` 和 `<typeinfo>` 等头文件中，它们提供了一组用于报告标准异常情况的类。

#### 常见的标准异常类

1. **`std::exception`**
   - 所有标准异常类的基类。
   - 提供了一个虚函数 `what()`，用于返回异常描述。

2. **`std::runtime_error` 和 `std::logic_error`**
   - 逻辑错误（`std::logic_error`）：程序中的逻辑错误，如无效参数或错误的数据。
   - 运行时错误（`std::runtime_error`）：运行时发生的错误，如资源耗尽或文件无法打开。
   - 这两个类都有多个派生类来表示更具体的错误情况。

3. **`std::out_of_range`**
   - 用于报告范围错误，通常是访问超出有效范围的数组或容器元素时抛出。

4. **`std::invalid_argument`**
   - 当函数接收到无效的参数时抛出。

5. **`std::bad_alloc`**
   - 当内存分配失败时抛出，通常与 `new` 操作符相关。

#### 示例
```cpp
#include <stdexcept>
#include <iostream>

void testFunction(int value) {
    if (value < 0) {
        throw std::invalid_argument("Negative value provided");
    }
}

int main() {
    try {
        testFunction(-1);
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
```

### 自定义异常（Custom Exceptions）

#### 定义自定义异常
- 自定义异常通常继承自 `std::exception` 或其子类。
- 可以提供更多的上下文信息，比如错误代码或复杂的错误消息。

#### 实现
1. 继承自 `std::exception` 或其他标准异常类。
2. 重写 `what()` 方法，提供详细的错误信息。

#### 示例
```cpp
#include <exception>
#include <string>

class MyException : public std::exception {
private:
    std::string message;
public:
    MyException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

void someFunction() {
    throw MyException("Custom error occurred");
}

int main() {
    try {
        someFunction();
    } catch (const MyException& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
```

## 3.异常处理流程

### try-catch块

#### 定义
- `try` 块包含可能抛出异常的代码。
- `catch` 块定义了如何处理特定类型的异常。

#### 使用
- 将可能引发异常的代码放在 `try` 块中。
- 捕获异常的 `catch` 块紧随 `try` 块之后。

#### 示例
```cpp
try {
    // 可能抛出异常的代码
} catch (const std::exception& e) {
    // 处理标准异常
} catch (...) {
    // 处理所有未捕获的异常
}
```

### 多个catch块

#### 定义
- 一个 `try` 块可以有多个 `catch` 块来捕获和处理不同类型的异常。

#### 匹配规则
- 异常会被第一个能够匹配其类型的 `catch` 块捕获。
- 一旦某个 `catch` 块捕获了异常，后续的 `catch` 块不会再被检查或执行。

#### 示例
```cpp
try {
    // 代码可能抛出多种类型的异常
} catch (const std::runtime_error& e) {
    // 处理运行时错误
} catch (const std::exception& e) {
    // 处理其他标准异常
} catch (...) {
    // 处理所有未捕获的异常
}
```

### 堆栈展开（Stack Unwinding）

#### 定义
- 当函数因为异常而提前退出时，其局部对象需要被销毁。
- 堆栈展开是一个从异常抛出点回溯到 `catch` 块的过程，在这个过程中，所有的局部对象都会被按照其创建的逆序销毁（调用析构函数）。

#### 重要性
- 堆栈展开确保了即使在异常情况下，资源也能被正确释放，如关闭文件、释放内存等。

#### 示例
```cpp
class MyResource {
public:
    MyResource() { /* 资源分配 */ }
    ~MyResource() { /* 资源释放 */ }
};

void function() {
    MyResource res;
    // 更多代码
    if (/* 某个条件 */) {
        throw std::runtime_error("Error occurred");
    }
    // 更多代码
}

int main() {
    try {
        function();
    } catch (const std::runtime_error& e) {
        // 处理异常
    }
    return 0;
}
```

## 4. noexcept

### noexcept关键字
- `noexcept`是C++11中引入的一个关键字，用于指定一个函数不会抛出异常。
- 当一个函数被声明为`noexcept`时，编译器可以进行某些优化，因为它知道这个函数不会因为异常而退出。
- 但是，如果一个被标记为`noexcept`的函数实际抛出了异常，程序将调用`std::terminate()`，导致程序立即终止。

### **例子**：

```cpp
void noThrowFunction() noexcept {
    // 这个函数被保证不会抛出异常
}

void mayThrowFunction() {
    // 这个函数可能会抛出异常
}
```

## 5. 异常安全（Exception Safety）

### 异常安全保证
- **基本保证**：即使异常发生，程序的基本功能保持正常，不会发生诸如内存泄漏之类的资源问题。
- **强保证**：操作可能会失败并抛出异常，但如果发生这种情况，程序的状态将保持不变，就好像该操作从未被尝试过一样。
- **无保证**：一旦异常发生，程序的状态可能变得不可预测。

### RAII（Resource Acquisition Is Initialization）
- RAII是一种利用对象生命周期来管理资源（如内存、文件句柄等）的技术。
- 当对象被创建时，它会获取某种资源，当对象的生命周期结束时（例如，离开作用域时），它的析构函数会自动释放这些资源。
- 这确保了即使在异常情况下，资源也能被正确地释放。

### **例子**：

```cpp
class FileHandler {
public:
    FileHandler(const std::string& fileName) {
        // 打开文件
        file.open(fileName);
    }

    ~FileHandler() {
        // 析构函数关闭文件，确保资源被释放
        if (file.is_open()) {
            file.close();
        }
    }

    // ... 其他功能 ...

private:
    std::fstream file;
};

void useFile() {
    FileHandler fh("example.txt");
    // 如果在这里发生异常，FileHandler 的析构函数会自动关闭文件
}
```
## 6. 实例

### 抛出和捕获异常
```cpp
#include <stdexcept>
#include <iostream>

void mightGoWrong() {
    bool error = true;
    if (error) {
        throw std::runtime_error("Something went wrong");
    }
}

int main() {
    try {
        mightGoWrong();
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
```

