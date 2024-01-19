# C++编译期编程

C++编译期编程是一种强大的技术，允许在编译时执行复杂的逻辑和计算。以下是这一主题的几个核心部分。

## 1. 编译期多态：泛型编程和模板

- **泛型编程**：使用模板编写代码，使其能够处理多种数据类型。这提高了代码的可重用性和灵活性。
- **函数模板**：允许编写可接受任何类型参数的函数。
- **类模板**：定义可用于多种类型的类。

### 示例：函数模板

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}

// 使用模板函数
int main() {
    std::cout << add<int>(5, 3) << std::endl;     // 对整数使用
    std::cout << add<double>(2.5, 3.5) << std::endl; // 对浮点数使用
}
```



## 2. 编译期能做什么

编译期编程在C++中主要体现在模板元编程和静态断言两个方面。

### 模板元编程

模板元编程（Template Metaprogramming, TMP）是一种使用模板来在编译时执行计算的技术。这可以用于生成高度优化的代码，或创建在编译时就能确定其属性的复杂数据结构。

#### 示例：编译时计算斐波那契数

```cpp
template<int N>
struct Fibonacci {
    static const int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template<>
struct Fibonacci<0> {
    static const int value = 0;
};

template<>
struct Fibonacci<1> {
    static const int value = 1;
};

// 使用模板元编程
int main() {
    std::cout << "Fibonacci of 5 is " << Fibonacci<5>::value << std::endl; // 输出 5 的斐波那契数
}
```

### 静态断言

静态断言（Static Assertion）是C++11引入的特性，允许在编译时进行条件检查。如果条件不满足，编译器将产生错误，从而防止生成不合适的代码。

#### 示例：确保模板参数是整数类型

```cpp
template <typename T>
void checkIsIntegral() {
    static_assert(std::is_integral<T>::value, "Type T must be an integral type.");
}

// 使用静态断言
int main() {
    checkIsIntegral<int>(); // 成功：int 是整数类型
    checkIsIntegral<double>(); // 失败：double 不是整数类型，编译时报错
}
```



## 3. SFINAE原则

### 定义

- **SFINAE**（Substitution Failure Is Not An Error）：类型替换失败不是错误，而是导致模板实例被丢弃。
- **应用**：用于模板特化和重载决议。

SFINAE（Substitution Failure Is Not An Error）是C++模板编程中一个重要的概念。它意味着在模板类型推导和替换过程中，如果出现了无法解析的类型或模板，这不会立即导致编译错误，而是使该模板实例被排除在候选之外。这个特性使得模板程序员可以编写只有在特定条件下才有效的模板代码，从而实现了一种编译期的条件选择。

### 应用

SFINAE常用于实现以下功能：
- **类型特化**：根据类型特征选择不同的模板实现。
- **函数重载决策**：在重载解析中使用类型特征以选择最合适的函数重载。
- **编译时错误检测**：在模板类型不满足特定条件时，阻止模板实例化。

### 示例：SFINAE

#### 代码解释

```cpp
template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type isIntegral(T) {
    return true;
}

template <typename T>
typename std::enable_if<!std::is_integral<T>::value, bool>::type isIntegral(T) {
    return false;
}
```

- 第一个 `isIntegral` 函数模板使用 `std::enable_if` 来检测 `T` 是否为整数类型（`std::is_integral<T>::value`）。如果是，它定义了一个有效的返回类型 `bool`，从而使得该版本的函数模板有效。
- 第二个 `isIntegral` 函数模板则恰恰相反，它在 `T` 不是整数类型时才有效。
- 当尝试使用这些函数时，编译器将根据传递给 `isIntegral` 的参数类型来决定哪个模板是有效的。

#### 使用示例

```cpp
int main() {
    std::cout << std::boolalpha << isIntegral(5) << std::endl;   // 输出：true
    std::cout << std::boolalpha << isIntegral(3.14) << std::endl; // 输出：false
}
```

在 `main` 函数中，当我们传入一个整数（如 `5`），第一个模板实例化并返回 `true`。而当我们传入一个非整数（如 `3.14`）时，第二个模板实例化并返回 `false`。

### 示例：用于构造函数

`std::enable_if` 可以用在构造函数中实现条件编译，特别是在创建模板类时需要根据类型特征来启用或禁用某些构造函数的情况。下面是一个详细的例子：

假设我们有一个模板类 `MyClass`，我们希望当模板参数是整数类型时，类具有一个特殊的构造函数。

#### 示例代码

```cpp
#include <iostream>
#include <type_traits>

template <typename T>
class MyClass {
public:
    // 普通构造函数
    MyClass() {
        std::cout << "Default constructor" << std::endl;
    }

    // 当 T 是整数类型时，启用这个构造函数
    template <typename U = T>
    MyClass(typename std::enable_if<std::is_integral<U>::value, U>::type x) {
        std::cout << "Integral type constructor with value: " << x << std::endl;
    }

    // 当 T 不是整数类型时，启用这个构造函数
    template <typename U = T>
    MyClass(typename std::enable_if<!std::is_integral<U>::value, U>::type x) {
        std::cout << "Non-integral type constructor with value: " << x << std::endl;
    }
};

int main() {
    MyClass<int> obj1(10);        // 使用整数类型的构造函数
    MyClass<double> obj2(3.14);   // 使用非整数类型的构造函数
    MyClass<int> obj3;            // 使用默认构造函数
    return 0;
}
```

#### 代码解释

1. **类模板 `MyClass`**：这个模板类有三个构造函数。
2. **普通构造函数**：这是一个默认构造函数，用于没有提供参数的情况。
3. **基于 `std::enable_if` 的构造函数**：这里有两个基于条件的构造函数。一个用于 `T` 是整数类型时，另一个用于 `T` 不是整数类型时。
   - 使用 `std::enable_if<std::is_integral<U>::value, U>::type` 来判断 `T` 是否是整数类型。如果是，这个构造函数被启用。
   - 使用 `std::enable_if<!std::is_integral<U>::value, U>::type` 来判断 `T` 是否不是整数类型。如果不是，另一个构造函数被启用。
4. **在 `main` 函数中的使用**：根据 `MyClass` 的实例化类型（`int` 或 `double`），将调用相应的构造函数。

#### 注意事项

- 在这个例子中，构造函数的启用依赖于模板参数 `T` 的类型特征。
- `std::enable_if` 的使用使得构造函数仅在特定条件下有效，这是一种编译时的条件编译技术。
- 这种技术非常有用，尤其是在创建需要根据类型不同而表现不同行为的泛型类时。

## 4. constexpr

`constexpr` 是 C++11 引入的一个关键字，用于定义在编译时就能确定其值的表达式、变量、函数或对象构造器。这使得 C++ 程序能够在编译期执行更复杂的计算，同时保证了类型安全和更好的性能。

### 详细解释

1. **constexpr 变量**：一个被 `constexpr` 修饰的变量必须在编译时就有确定的值。它通常用于定义编译时的常量。
   
2. **constexpr 函数**：可以在编译时对其进行求值，只要给定的参数是编译时常量。这样的函数可以用在任何需要常量表达式的地方，例如数组大小或模板参数。

3. **constexpr 构造器**：允许对象在编译时被创建和初始化。这对于创建编译时数据结构非常有用。

### 示例扩展

```cpp
constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

int main() {
    constexpr int val = factorial(5); // 编译时计算
    std::cout << val << std::endl; // 输出：120
}
```

在这个示例中，`factorial` 函数被定义为 `constexpr`。这意味着，如果它的参数在编译时是已知的（如 `factorial(5)`），那么它的返回值（在这里是 `120`）也会**在编译时被计算出来**。因此，`val` 是一个编译时常量。

### constexpr 与 const 的区别

虽然 `constexpr` 和 `const` 都用于定义常量，但它们的用途和含义有所不同：

1. **const**：用于定义常量，表示一旦初始化后值不能改变。`const` 可以用于运行时和编译时的常量。例如，一个 `const` 变量可以在运行时从文件读取其值。

2. **constexpr**：更强调在编译时就能确定值的表达式。所有 `constexpr` 表达式都必须在编译时有确定的值，这使得它们非常适合用于需要编译时常量的场合，如数组大小、模板参数等。

