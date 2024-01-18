## 字面量（Literals）

### 定义
- 字面量是在源代码中直接表示值的表示法，如整数、浮点数、字符和字符串。

### 类型
1. **整数字面量**：如 `42`、`0xFF`（十六进制）、`042`（八进制）、`0b1010`（二进制）。
2. **浮点字面量**：如 `3.14`、`2.5e-3`。
3. **字符字面量**：如 `'a'`、`'\n'`。
4. **字符串字面量**：如 `"Hello, World!"`。
5. **布尔字面量**：`true` 和 `false`。
6. **空指针字面量**：`nullptr`。

### 自定义字面量

#### 定义
- 通过定义特殊的函数或者用户定义的字面量运算符，来实现对原始数据类型（如整数、浮点数、字符等）的包装，使之表示更具体的概念或类型。

#### 实现方式
1. **运算符""定义**：使用`operator""`后缀来定义一个自定义字面量。
2. **函数形式**：自定义字面量函数接收原始数据类型的值，并返回一个转换后的值，通常是一个用户定义的类型。

#### 例子
```cpp
#include <iostream>

// 定义一个用于表示距离的类
class Distance {
public:
    explicit Distance(long double km) : km_(km) {}

    long double toKilometers() const { return km_; }

private:
    long double km_;
};

// 自定义字面量运算符，用于创建Distance对象
Distance operator"" _km(long double km) {
    return Distance(km);
}

int main() {
    Distance d = 42.5_km; // 使用自定义字面量
    std::cout << "距离是: " << d.toKilometers() << " 公里" << std::endl;

    return 0;
}
```

​	这个运算符允许我们直接用 `42.5_km` 这样的字面量来创建 `Distance` 对象。这种方式使得代码更加直观和易于理解，同时也提供了类型安全的好处。

## 静态断言（Static Assertions）

### 定义
静态断言是一种编译时检查机制，用于验证程序中的某些属性。如果断言的条件为`false`，则会产生编译错误。

### 用法
使用`static_assert`关键字，语法为：`static_assert(条件, "错误消息");`。这个断言在编译时被检查，如果条件不成立，编译器会显示指定的错误消息。

### 应用场景
- **检查类型大小**：确保类型的大小符合特定的期望。例如，使用`static_assert(sizeof(int) == 4, "Int must be 4 bytes");`来验证`int`类型是否是4字节。
- **验证模板参数**：在模板编程中，可以使用静态断言来确保模板参数满足特定的条件或特性。

### 示例
```cpp
#include <iostream>
#include <type_traits> // 用于类型特性检查

template <typename T>
void func() {
    // 验证T是整数类型
    static_assert(std::is_integral<T>::value, "Function only supports integral types");
    // ...函数实现...
}

int main() {
    func<int>(); // 正确，int是整数类型
    // func<double>(); // 错误，编译时失败，因为double不是整数类型
    return 0;
}
```

### `static_assert` 与 `assert` 的区别
- **运行时 vs 编译时**：
  - `static_assert`在编译时进行检查，如果条件失败则阻止程序编译。
  - `assert`在运行时进行检查，如果条件失败则可能导致程序崩溃或终止。
- **错误处理**：
  - `static_assert`的失败会导致编译错误。
  - `assert`的失败通常导致程序崩溃或终止执行。
- **应用场景**：
  - `static_assert`用于编译时可以确定的属性，如类型属性或编译环境。
  - `assert`用于运行时条件，如算法的状态或函数参数的有效性。
- **开销**：
  - `static_assert`不增加运行时开销。
  - `assert`可能增加运行时开销。

## 成员函数说明符（Member Function Specifiers）

### 常见说明符
1. **const**：表示该成员函数不会修改对象的状态。
2. **noexcept**：表示该成员函数不会抛出异常。
3. **override**：指明该成员函数覆盖了基类中的虚函数。
4. **final**：表示该成员函数不能在派生类中被进一步覆盖。
5. **virtual**：表示函数可以在派生类中被覆盖。
6. **= delete**：显示禁用该函数。
7. **= default**：让编译器生成默认的函数实现。

### 使用示例
```cpp
class MyClass {
public:
    virtual void doSomething() const noexcept = 0; // 纯虚函数
    void doAnotherThing() const noexcept final;    // 最终函数
    MyClass() = default;                          // 默认构造函数
    MyClass(const MyClass&) = delete;             // 禁止拷贝构造
};
```

在这个示例中：
- `doSomething` 是一个纯虚函数，且不会修改类状态或抛出异常。
- `doAnotherThing` 不能在子类中被覆盖，也不会修改类状态或抛出异常。
- 默认构造函数由编译器生成。
- 拷贝构造函数被显式禁用。

### 重要性
- 成员函数说明符用于提高代码的安全性和清晰度。
- 它们使得函数的行为和限制更加明确。
