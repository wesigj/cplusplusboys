# C++面试基础系列-decltype

[TOC]

## Overview

- 在C++中，`decltype` 是一个类型推导关键字，它用于确定表达式的类型。`decltype` 可以在编译时确定一个变量或表达式的类型，而不需要显式地声明类型。这在模板编程和泛型编程中非常有用，尤其是在C++11及以后的版本中。
  
---

## 1.decltype关键点

以下是 `decltype` 的一些关键点：

1. **基本用法**：
   - `decltype` 的基本语法是 `decltype(表达式)`，它返回表达式的类型。

2. **引用修饰符**：
   - 如果表达式是一个左值，`decltype` 将返回带有引用修饰符的类型（例如 `int&`）。如果表达式是一个右值，返回的类型将不包含引用修饰符（例如 `int`）。

3. **数组和函数类型**：
   - `decltype` 不会从数组或函数类型中推导出 `pointer` 类型，而是保持原始类型（例如 `int[]` 或 `void()`）。

4. **结合 `auto` 关键字**：
   - `decltype` 经常与 `auto` 关键字结合使用，以实现类型推导。

5. **模板参数推导**：
   - 在模板参数推导中，`decltype` 可以用于推导出模板参数的类型。

6. **lambda 表达式**：
   - 对于 lambda 表达式，`decltype` 推导出的类型是 `std::function` 的实例类型。

### 示例代码

```cpp
#include <iostream>
#include <vector>
#include <functional>
#include <typeinfo> // 需要包含这个头文件来使用 typeid

void exampleFunction(int& i) {
    std::cout << "Type of i: " << typeid(i).name() << std::endl;
    // 注意：这里不需要使用 decltype，因为 i 已经是 int& 类型
}

int main() {
    int a = 10;
    double b = 3.14;

    std::cout << "Type of a: " << typeid(a).name() << std::endl;
    // decltype(a) 是不必要的，因为 a 已经是一个 int 类型的变量

    auto x = a; // 使用 auto 推导 x 的类型为 int
    std::cout << "Type of x: " << typeid(x).name() << std::endl;

    // 移除 exampleFunction 的调用，因为它没有返回值
    // auto y = exampleFunction(a); // 这行是错误的

    // 代码中 auto y = exampleFunction(a); 这一行存在问题，因为 exampleFunction 函数没有返回值，所以尝试将一个没有返回值的函数调用赋值给变量 y 是不正确的。auto 关键字在这里会推导出 void 类型，因为 exampleFunction 的返回类型是 void。

    // decltype 推导 lambda 表达式的类型
    auto lambda = [](int i) { return i * 2; };
    std::cout << "Type of lambda: " << typeid(lambda).name() << std::endl;

    return 0;
}
```

> 在这个示例中，`decltype` 用于推导不同表达式的类型。注意，`typeid` 用于输出类型信息，它需要包含 `<typeinfo>` 头文件。`decltype` 在这里用于推导变量 `a` 的类型，以及 `auto` 变量 `x` 的类型。对于 `exampleFunction` 函数，`decltype` 推导了函数参数 `i` 的类型。最后，对于 lambda 表达式，`decltype` 推导出了一个 `std::function` 类型。
> \
> 请注意，typeid(lambda).name() 可能不会返回一个有用的字符串，因为 lambda 表达式产生的函数对象类型通常不是多态类型，name() 方法对于非多态类型可能返回空指针。如果你想要打印 lambda 表达式的类型，你可能需要使用其他方法，例如直接使用 std::cout 来输出类型信息。

`decltype` 是C++11引入的一个非常有用的关键字，它简化了类型声明，并在模板编程中提供了极大的灵活性。

## 2.C++类型推导

C++ 类型推导是一个强大的特性，它允许编译器自动确定变量或表达式的类型，而不需要显式地声明类型。这在编写模板代码、使用泛型编程、以及简化代码时非常有用。以下是一些C++中类型推导的关键点和机制：

1. **自动类型推导（Auto）**：
   - 使用 `auto` 关键字可以让编译器根据初始化表达式推导出变量的类型。

2. **decltype**：
   - `decltype` 关键字用于推导出某个表达式的类型，但不会对表达式结果进行值的推导。

3. **模板参数推导**：
   - 当使用模板函数或模板类时，编译器可以推导出模板参数的类型。

4. **构造函数的类型推导**：
   - C++11 引入了构造函数的成员初始化列表，允许从构造函数参数推导出成员变量的类型。

5. **类型别名（Type Aliases）**：
   - 使用 `using` 或 `typedef` 声明类型别名，可以简化复杂类型名的书写。

6. **类型特征（Type Traits）**：
   - `<type_traits>` 头文件提供了一系列编译时检查和修改类型的工具。

7. **C++14 泛型 lambda 表达式**：
   - 在 C++14 中，lambda 表达式的捕获列表可以使用 `auto` 来自动推导捕获变量的类型。

8. **C++17 结构化绑定**：
   - 结构化绑定允许从元组、pair 或数组中提取多个值，并自动推导出这些值的类型。

9. **C++17 if 语句和 switch 语句中的初始化**：
   - 在 C++17 中，可以在 if 或 switch 语句中初始化变量，并自动推导其类型。

10. **C++20 概念（Concepts）**：
    - 概念允许定义类型必须满足的条件，这有助于在模板编程中进行更精确的类型推导。

11. **C++20 模块（Modules）**：
    - 模块可以帮助简化包含和类型声明，间接影响类型推导。

12. **C++20 `consteval` 关键字**：
    - 允许声明一个函数总是被编译器在编译时调用，有助于编译时的类型推导。

13. **C++20 `requires` 子句**：
    - 在模板定义中使用 `requires` 子句可以指定模板参数的类型约束和概念要求。

类型推导使得C++代码更加简洁和灵活，特别是在模板编程中。它减少了代码冗余，提高了代码的可读性和可维护性。然而，过度依赖类型推导有时也可能导致代码难以理解，因此在使用时需要权衡其利弊。

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
