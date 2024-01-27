## 参考

___

[CMake 保姆级教程 | 爱编程的大丙 (subingwen.cn)](https://subingwen.cn/cmake/CMake-primer/)

## CMake概述

___

- CMake是一个跨平台的项目构建工具。它不仅能够生成Makefile，还能自动根据不同的编译平台生成相应的工程文件，简化了传统Makefile的复杂性和依赖问题。
- 与传统的Makefile相比，CMake的优势在于：
  - **跨平台性**：适用于多种操作系统和编译环境。
  - **管理大型项目**：更适合大型复杂项目的构建管理。
  - **简化构建过程**：自动化处理依赖关系和构建流程，降低了手动编写Makefile的难度。
  - **可扩展性**：允许开发者编写模块扩充CMake的功能。

## CMake使用

___

CMake 支持大写、小写、混合大小写的命令。如果在编写 CMakeLists.txt 文件时使用的工具有对应的命令提示，那么大小写随缘即可，不要太过在意。

### 2.1 注释

#### 2.1.1 注释行

CMake 使用 `#` 进行行注释，可以放在任何位置。

```cmake
# 这是一个 CMakeLists.txt 文件
cmake_minimum_required(VERSION 3.0.0)
```

#### 2.1.2 注释块

CMake 使用 `#[[ ]]` 形式进行块注释。

```cmake
# [[ 这是一个 CMakeLists.txt 文件。
这是一个 CMakeLists.txt 文件
这是一个 CMakeLists.txt 文件 ]]
cmake_minimum_required(VERSION 3.0.0)
```

## 编译多个文件的示例

___

以下是一个基本的 CMake 项目结构，用于编译多个源文件。

### 项目结构

假设您有以下项目结构：

```
project/
│   CMakeLists.txt
│
└───src/
    │   main.cpp
    │   hello.cpp
    │   hello.h
```

### CMakeLists.txt 文件

```cmake
cmake_minimum_required(VERSION 3.0.0)
project(MyProject VERSION 1.0.0)

# 添加 src 目录下的所有源文件到变量 SOURCES
aux_source_directory(src SOURCES)

# 指定生成目标
add_executable(MyProject ${SOURCES})
```

### 源文件

- `main.cpp`：程序的入口点。
- `hello.cpp` 和 `hello.h`：一个简单的模块，用于展示如何组织多个文件。

hello.h ：

```cpp
#ifndef HELLO_H
#define HELLO_H

void say_hello();

#endif
```

hello.cpp ：

```cpp
#include "hello.h"
#include <iostream>

void say_hello() {
    std::cout << "Hello, World!" << std::endl;
}
```

main.cpp：

```cpp
#include "hello.h"

int main() {
    say_hello();
    return 0;
}
```

#### 编译项目

1. 在项目根目录（与 `CMakeLists.txt` 文件相同的目录）打开终端。
2. 运行以下命令来生成构建系统：

   ```bash
   cmake -S . -B build
   ```

3. 编译项目：

   ```bash
   cmake --build build
   ```

## 高级项目组织策略

___

在探讨 CMake 的高级项目组织策略时，关键在于理解如何有效管理由 CMake 生成的文件，以保持项目目录的整洁和易于维护。

### 创建隔离的构建目录

创建一个专用的构建目录（如 `build`）可以有效地将编译过程中生成的文件与源代码分离。

### 步骤 1: 创建和进入 Build 目录

首先，创建并切换到名为 `build` 的目录：

```shell
$ mkdir build
$ cd build
```

### 步骤 2: 执行 CMake 配置

在 `build` 目录中执行 `cmake` 命令，并将上一级目录（包含 `CMakeLists.txt`）作为参数：

```shell
$ cmake ..
```

这一步骤会初始化项目构建环境，检测系统的编译器等配置。

### 步骤 3: 生成 Makefile 和其他文件

完成配置后，`build` 目录中将生成 `Makefile` 及其他辅助文件：

```shell
$ tree build -L 1
build
├── CMakeCache.txt
├── CMakeFiles
├── cmake_install.cmake
└── Makefile

1 directory, 3 files
```

### 项目的编译与管理

在此结构中，所有由 CMake 和 Make 生成的文件都位于 `build` 目录，实现了与源代码的有效隔离。这种方法不仅保持了源代码目录的清洁，而且便于项目的后续管理和维护。

## 变量定义、C++标准指定和输出路径设置

___

CMake 提供了多种方法来自定义和优化构建过程。以下是几个关键的自定义选项，包括变量定义、指定 C++ 标准和设置输出路径。

### 定义变量

在处理多个源文件时，重复书写每个文件名是不便的。为解决这个问题，CMake 允许通过 `set` 指令定义变量来存储这些文件名。

### 使用 SET 指令

语法示例：

```cmake
# SET 指令的基本语法
SET(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])

# 定义变量，存储源文件名
# 方式1: 使用空格间隔各个文件
set(SRC_LIST add.c  div.c  main.c  mult.c  sub.c)

# 方式2: 使用分号间隔各个文件
set(SRC_LIST add.c;div.c;main.c;mult.c;sub.c)

# 使用定义的变量来指定编译的源文件
add_executable(app ${SRC_LIST})
```

### 指定使用的 C++ 标准

为了使用 C++ 的高级特性，如 C++11、C++14 等，需要在编译时指定使用的 C++ 标准。

#### 在 CMakeLists.txt 中指定 C++ 标准

```cmake
# 在 CMakeLists.txt 中通过 set 命令指定 C++ 标准
set(CMAKE_CXX_STANDARD 11) # C++11
set(CMAKE_CXX_STANDARD 14) # C++14
set(CMAKE_CXX_STANDARD 17) # C++17
```

#### 在执行 cmake 命令时指定 C++ 标准

```shell
# 通过命令行指定 C++ 标准
cmake -DCMAKE_CXX_STANDARD=11 <CMakeLists.txt路径> # C++11
cmake -DCMAKE_CXX_STANDARD=14 <CMakeLists.txt路径> # C++14
cmake -DCMAKE_CXX_STANDARD=17 <CMakeLists.txt路径> # C++17
```

### 指定输出的路径

在 CMake 中，可以指定可执行文件的输出路径，以便管理生成的二进制文件。

#### 设置 EXECUTABLE_OUTPUT_PATH

```cmake
# 设置可执行文件的输出路径
set(HOME /home/robin/Linux/Sort)
set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin)

# 注意：如果输出路径的子目录不存在，CMake 将自动创建
```

在上述配置中，`EXECUTABLE_OUTPUT_PATH` 宏用于定义可执行文件的最终输出路径。若使用相对路径（如 `./bin`），路径将相对于包含 `Makefile` 的目录。

### 示例

假设项目结构如下：

```
my_project/
│   CMakeLists.txt
│
└───src/
    │   main.cpp
    │   add.cpp
    │   add.h
    │   sub.cpp
    │   sub.h
```

#### CMakeLists.txt 文件

在 `my_project` 目录中的 `CMakeLists.txt` 文件如下：

```cmake
cmake_minimum_required(VERSION 3.0.0)
project(MyProject VERSION 1.0.0)

# 定义变量来存储源文件
set(SRC_LIST src/main.cpp src/add.cpp src/sub.cpp)

# 指定使用 C++11 标准
set(CMAKE_CXX_STANDARD 11)

# 设置可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 添加可执行文件
add_executable(MyApp ${SRC_LIST})
```

#### 文件说明

1. **变量定义** (`set(SRC_LIST ...)`)：定义了一个变量 `SRC_LIST`，它包含了所有源文件的路径。这使得在 `add_executable` 命令中引用这些文件变得更加方便。

2. **指定 C++ 标准** (`set(CMAKE_CXX_STANDARD 11)`)：这里指定了项目应该使用 C++11 标准进行编译。这允许在源代码中使用 C++11 的特性。

3. **设置输出路径** (`set(EXECUTABLE_OUTPUT_PATH ...)`)：这行指定了可执行文件的输出路径。在这个例子中，所有的可执行文件将被放置在项目根目录下的 `bin` 文件夹中。

#### main.cpp

```cpp
#include <iostream>
#include "add.h"
#include "sub.h"

int main() {
    std::cout << "Addition of 5 and 3 is " << add(5, 3) << std::endl;
    std::cout << "Subtraction of 5 from 8 is " << sub(8, 5) << std::endl;
    return 0;
}
```

#### add.cpp

```cpp
#include "add.h"

int add(int a, int b) {
    return a + b;
}
```

#### add.h

```cpp
#ifndef ADD_H
#define ADD_H

int add(int a, int b);

#endif
```

#### sub.cpp

```cpp
#include "sub.h"

int sub(int a, int b) {
    return a - b;
}
```

#### sub.h

```cpp
#ifndef SUB_H
#define SUB_H

int sub(int a, int b);

#endif
```

#### 构建过程

1. 在 `my_project` 目录中创建一个名为 `build` 的目录。
2. 在终端中切换到 `build` 目录。
3. 运行 `cmake ..` 来配置项目并生成 Makefile。
4. 运行 `make` 来编译项目。编译后的可执行文件将位于 `my_project/bin`。

## 含头文件的方法

___

### 示例项目结构

假设项目的目录结构如下：

```
project_root/
├── build/
├── CMakeLists.txt
├── include/
│   └── head.h
└── src/
    ├── add.cpp
    ├── div.cpp
    ├── main.cpp
    ├── mult.cpp
    └── sub.cpp
```

### CMakeLists.txt 文件内容

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
set(CMAKE_CXX_STANDARD 11)
set(HOME /home/robin/Linux/calc)
set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin/)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(app  ${SRC_LIST})
```

### 关键点解释

1. **include_directories**
   - `include_directories(${PROJECT_SOURCE_DIR}/include)` 这行命令是关键。它告诉 CMake 在编译时包含 `include` 目录。这样编译器就能找到所有在源文件中引用的头文件。
   - `${PROJECT_SOURCE_DIR}` 是一个 CMake 变量，指向使用 `cmake` 命令时指定的目录（通常是项目的根目录）。

2. **file(GLOB SRC_LIST ...)**
   - 这行命令使用通配符自动查找所有的 `.cpp` 文件，并将它们的路径赋值给 `SRC_LIST` 变量。

3. **add_executable**
   - `add_executable(app  ${SRC_LIST})` 这行创建了一个名为 `app` 的可执行文件，它包含 `SRC_LIST` 变量中指定的所有源文件。

### 作用

这个 `CMakeLists.txt` 文件配置了一个名为 `CALC` 的项目，它会编译 `src` 目录下的所有 `.cpp` 文件，并将头文件目录 `include` 包含到项目中。通过这种方式，可以确保项目能够正确地找到并包含所有必要的头文件，从而顺利编译。

## 动态库或静态库

___

###  制作静态库

**CMakeLists.txt 示例**

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(calc STATIC ${SRC_LIST})
```

**解释**
- `add_library(calc STATIC ${SRC_LIST})`：这行命令指示 CMake 制作一个名为 `calc` 的静态库，包含 `SRC_LIST` 中指定的源文件。
- 静态库的文件名将自动格式化为 `libcalc.a`（在 Linux 系统中）。

###  制作动态库

**CMakeLists.txt 示例**

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(calc SHARED ${SRC_LIST})
```

**解释**
- `add_library(calc SHARED ${SRC_LIST})`：这行命令用于创建一个名为 `calc` 的动态库，同样包含 `SRC_LIST` 中的源文件。
- 动态库的文件名将自动格式化为 `libcalc.so`（在 Linux 系统中）。

### 指定输出的路径

**方式1：适用于动态库**

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
add_library(calc SHARED ${SRC_LIST})
```

- 这里，`EXECUTABLE_OUTPUT_PATH` 设置了动态库的输出路径。

**方式2：适用于静态库和动态库**

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
add_library(calc STATIC ${SRC_LIST})
# 或者制作动态库
# add_library(calc SHARED ${SRC_LIST})
```

- `LIBRARY_OUTPUT_PATH` 用于设置静态库或动态库的输出路径。

### 示例

假设项目结构如下：

```
math_library/
├── CMakeLists.txt
├── include/
│   ├── add.h
│   └── sub.h
└── src/
    ├── add.cpp
    └── sub.cpp
```

#### 文件内容

1. **add.h**

   ```cpp
   #ifndef ADD_H
   #define ADD_H

   int add(int a, int b);

   #endif
   ```

2. **add.cpp**

   ```cpp
   #include "add.h"

   int add(int a, int b) {
       return a + b;
   }
   ```

3. **sub.h**

   ```cpp
   #ifndef SUB_H
   #define SUB_H

   int sub(int a, int b);

   #endif
   ```

4. **sub.cpp**

   ```cpp
   #include "sub.h"

   int sub(int a, int b) {
       return a - b;
   }
   ```

#### CMakeLists.txt 文件

```cmake
cmake_minimum_required(VERSION 3.0)
project(MathLibrary)
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# 制作静态库
add_library(mathlib_static STATIC ${SRC_LIST})
set_target_properties(mathlib_static PROPERTIES OUTPUT_NAME "mathlib")

# 制作动态库
add_library(mathlib_shared SHARED ${SRC_LIST})
set_target_properties(mathlib_shared PROPERTIES OUTPUT_NAME "mathlib")

# 可选：指定库文件输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
```

#### 构建过程

1. 在 `math_library` 目录中创建一个名为 `build` 的目录。
2. 在终端中切换到 `build` 目录。
3. 运行 `cmake ..` 来配置项目并生成 Makefile。
4. 运行 `make` 来编译项目。

#### 结果

- 这个过程将在 `math_library/lib` 目录中生成两个库文件：`libmathlib.a`（静态库）和 `libmathlib.so`（动态库）。
- 这些库文件可以被其他项目链接和使用，提供加法和减法功能。

## 包含库文件的方法与实践

___

### 链接静态库

假设您已经有了一些源文件，并将其中一些编译成了静态库文件 `libcalc.a`。

**测试目录结构**

```
project/
├── build
├── CMakeLists.txt
├── include
│   └── head.h
├── lib
│   └── libcalc.a
└── src
    └── main.cpp
```

在 CMake 中，链接静态库的命令为：

```cmake
link_libraries(<static lib> [<static lib>...])
```

您可以指定静态库的完整名称，例如 `libxxx.a`，或者只指定库名 `xxx`（不包括 `lib` 前缀和 `.a` 后缀）。

如果静态库不是系统提供的，可能需要指定库文件的路径：

```cmake
link_directories(<lib path>)
```

修改后的 `CMakeLists.txt` 文件可能如下所示：

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)
link_libraries(calc)
add_executable(app ${SRC_LIST})
```

### 链接动态库

链接动态库与链接静态库类似，但有些差异。动态库的链接具有传递性，并且可以设定链接的动态库的访问权限（`PRIVATE`, `PUBLIC`, `INTERFACE`）。

**链接命令**

```cmake
target_link_libraries(
    <target> 
    <PRIVATE|PUBLIC|INTERFACE> <item>... 
    [<PRIVATE|PUBLIC|INTERFACE> <item>...]...)
```

**示例**：链接系统提供的动态库

```cmake
cmake_minimum_required(VERSION 3.0)
project(TEST)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(app ${SRC_LIST})
target_link_libraries(app pthread)
```

**示例**：链接第三方动态库

假设您制作了一个动态库 `libcalc.so`：

**目录结构**

```
project/
├── build
├── CMakeLists.txt
├── include
│   └── head.h
├── lib
│   └── libcalc.so
└── main.cpp
```

**CMakeLists.txt**

```cmake
cmake_minimum_required(VERSION 3.0)
project(TEST)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(app ${SRC_LIST})
target_link_libraries(app pthread calc)
```

**链接库路径**

如果动态库不在标准路径中，需要通过 `link_directories` 指定库的位置：

```cmake
link_directories(${PROJECT_SOURCE_DIR}/lib)
```

修改后的 `CMakeLists.txt` 文件如下：

```cmake
cmake_minimum_required(VERSION 3.0)
project(TEST)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)
add_executable(app ${SRC_LIST})
target_link_libraries(app pthread calc)
```



