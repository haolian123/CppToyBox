# 容器输出工具

## 简介

___

​	这是一个用于方便地在 C++ 中打印各种容器的工具。通过重载 `operator<<` 实现对 `std::ostream` 的支持，从而可以直接使用 `std::cout` 或其他输出流来打印标准容器，如 `std::vector`、`std::map` 等。

## 特性

___

- 支持多种容器类型，包括 `std::vector`、`std::map`、`std::list`、`std::set` 等。
- 支持容器的嵌套打印。
- 支持基本数据类型（如 int、float、char）及字符串的打印。
- 支持对 `bool` 类型的特殊处理，将其打印为 `true` 或 `false`。

## 使用

___

### 引入头文件

在项目中包含 `container_output.h`：

```cpp
#include "container_output.h"
```

### 打印容器

使用 `operator<<` 打印容器：

```cpp
std::vector<int> vec = {1, 2, 3, 4};
std::cout << "打印 vector<int>: " << vec << std::endl;

std::map<int, std::string> map = {{1, "one"}, {2, "two"}};
std::cout << "打印 map<int, string>: " << map << std::endl;
```

嵌套容器：

```cpp
std::vector<std::vector<int>> nestedVec = {{1, 2}, {3, 4}, {5, 6}};
std::cout << "打印 vector<vector<int>>: " << nestedVec << std::endl;
```

### 注意事项

- 确保编译器支持 C++17 标准，因为本工具使用了 C++17 中的一些特性。
- 如果容器包含自定义类型，请确保这些类型重载了 `operator<<`，以便工具可以正确打印。

## 测试

终端输入

```shell
make
./test
```

