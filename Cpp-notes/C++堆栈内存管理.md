# 栈

___

## 栈内存管理分析

### 栈的工作原理

1. **自动分配和销毁**：栈内存是由编译器自动管理的。当你在函数内创建一个局部变量时，如 `Obj obj;`，它会被分配在栈上。当该变量的作用域（即函数或代码块）结束时，这个变量会自动被销毁。
2. **后进先出（LIFO）原则**：栈遵循后进先出的原则。最后创建的变量会首先被销毁。

### 示例

```c++
#include <iostream>
class Obj {
public:
  Obj() { puts("Obj()"); }
  ~Obj() { puts("~Obj()"); }
};
void foo(int n) {
  Obj obj;
  if (n == 42)
    throw "life, the universe and everything";
}
// 不管是否发生了异常，obj 的析构函数都会得到执行。
int main() {
  try {
    foo(41);
    foo(42);
  } catch (const char *s) {
    puts(s);
  }
}
```

代码分析

```c++
void foo(int n) {
  Obj obj;
  if (n == 42)
    throw "life, the universe and everything";
}
```

在这个函数中，当调用 `foo` 时，局部变量 `obj` 会在栈上创建。

- 如果 `n` 不等于 42，函数正常结束，`obj` 的作用域结束，它的析构函数会被调用，然后 `obj` 被销毁。

- 如果 `n` 等于 42，将抛出一个异常。这时，C++ 的异常处理机制确保所有栈上的局部变量（在这个例子中是 `obj`）都会被适当地销毁。这意味着即使在异常发生的情况下，`obj` 的析构函数也会被调用，从而释放相关的资源。

# 堆

___

## 基本概念
- **动态内存分配**：使用 `new` 关键字在堆上动态分配内存。
- **手动内存释放**：使用 `delete` 关键字显式释放分配的内存。
- **内存泄漏风险**：忘记释放内存可能导致内存泄漏。
- **异常安全**：确保在异常发生时适当地清理资源。

## 示例

### 直接在函数中分配和释放
- **功能**：在同一函数中进行内存的分配和释放。
- **代码示例**：
    ```c++
    void exampleFunction() {
        MyClass *obj = new MyClass();
        delete obj;
    }
    ```
- **注意点**：确保每次 `new` 后都跟随一个 `delete`。

###  使用函数封装内存分配与异常处理
- **功能**：将内存分配和释放分离，增强异常安全性。
- **代码示例**：
    ```c++
    MyClass* createMyClass() {
        MyClass *obj = nullptr;
        try {
            obj = new MyClass();
        } catch (...) {
            delete obj;
            throw;
        }
        return obj;
    }
    void exampleFunctionSafe() {
        MyClass *obj = createMyClass();
        delete obj;
    }
    ```
- **注意点**：使用封装函数来处理内存分配和异常，避免内存泄漏。

## 总结
- **重要性**：正确管理堆内存是避免内存泄漏和保证程序稳定性的关键。
- **最佳实践**：
  - 总是确保对于每个 `new` 都有一个对应的 `delete`。
  - 在可能抛出异常的代码周围使用 `try...catch` 块，并在 `catch` 块中进行适当的资源清理。
  - 考虑使用智能指针（如 `std::unique_ptr` 或 `std::shared_ptr`）自动管理内存。









