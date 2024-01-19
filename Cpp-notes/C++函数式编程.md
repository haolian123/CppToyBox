# 函数式编程

C++的函数式编程特性主要通过函数对象（functors）和Lambda表达式实现。这些特性使得C++编程更灵活、表达力更强。

## 函数对象（Functors）

函数对象（也称为“functors”）在C++中是非常有用的，尽管它们的功能看似可以被普通函数所替代。函数对象的存在和使用主要有以下几个原因：

### 1. 状态保持：
   - **普通函数**：无法保持状态，每次调用都是无状态的。
   - **函数对象**：可以保持状态。由于它们是对象，可以拥有成员变量来存储状态信息。

### 2. 内联优化：
   - **普通函数**：编译器可能不总是能够内联，特别是对于指向函数的指针或引用。
   - **函数对象**：编译器更容易进行内联优化，因为它们通常包含在使用它们的模板代码中。

### 3. 泛型编程：
   - **函数对象**：在模板编程中尤为有用，特别是与STL算法一起使用时。模板可以接受任何类型，只要它支持特定的操作，这使得函数对象可以与算法模板无缝配合。

### 4. 可定制性：
   - **函数对象**：可以携带更多信息和行为。例如，你可以为排序算法定义一个函数对象，其中包含复杂的比较逻辑。

### 5. 与Lambda表达式的关系：
   - 在C++11之前，Lambda表达式不可用，函数对象是实现类似功能的唯一方法。
   - 即使在C++11及以后，Lambda表达式在实现上实际上是以函数对象的形式存在。

### 示例：函数对象保持状态

```cpp
class Counter {
    int count;
public:
    Counter() : count(0) {}

    int operator()() {
        return ++count; // 每次调用，计数增加
    }
};

int main() {
    Counter c;
    std::cout << c() << std::endl; // 输出 1
    std::cout << c() << std::endl; // 输出 2
}
```

在这个例子中，`Counter` 是一个函数对象，它保持了一个内部状态（`count`），这是普通函数无法做到的。

## Lambda表达式

Lambda表达式提供了定义匿名函数对象的简洁方式。它们非常有用于短期使用的小型函数，特别是在需要作为参数传递给算法的情况下。

### 基本语法

```cpp
[ capture_clause ] ( parameters ) -> return_type {
    // function body
}
```

- **capture_clause**：捕获外部变量。
- **parameters**：与普通函数相同的参数列表。
- **return_type**：返回类型（可选，如果省略，编译器会自动推导）。
- **function body**：函数体。

### 示例：Lambda表达式

#### 1. 基本Lambda

```cpp
int main() {
    auto add = [](int a, int b) { return a + b; };
    std::cout << "Result: " << add(10, 5) << std::endl; // 输出：15
}
```

#### 2. 带捕获列表的Lambda

```cpp
int main() {
    int x = 10;
    auto addX = [x](int a) { return a + x; };
    std::cout << "Result: " << addX(5) << std::endl; // 输出：15
}
```

#### 3. Lambda作为函数参数

```cpp
void applyFunction(int a, int b, const std::function<int(int, int)>& func) {
    std::cout << "Result: " << func(a, b) << std::endl;
}

int main() {
    applyFunction(10, 5, [](int a, int b) { return a - b; }); // 输出：5
}
```

#### 4. Lambda返回类型推导

```cpp
int main() {
    auto multiply = [](int a, int b) { return a * b; };
    std::cout << "Result: " << multiply(10, 5) << std::endl; // 输出：50
}
```

### 总结

Lambda表达式和函数对象为C++添加了强大的函数式编程能力。Lambda表达式特别适合用于创建简单的匿名函数，而函数对象则更适合需要多次重用的情况。这些特性在现代C++编程中被广泛使用，特别是在与STL算法结合时。
