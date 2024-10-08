# C++11 30-可变参数模板 Variadic Templates

- [C++11 30-可变参数模板 Variadic Templates](#c11-30-可变参数模板-variadic-templates)
  - [Overview](#overview)
  - [1.可变参数模板 Variadic Templates](#1可变参数模板-variadic-templates)
    - [1.1.基本语法](#11基本语法)
    - [1.2.参数包展开](#12参数包展开)
    - [1.3.示例](#13示例)
    - [1.4.常用技术](#14常用技术)
  - [2.C++11 中的可变参数模板和旧版本的模板有什么区别？](#2c11-中的可变参数模板和旧版本的模板有什么区别)
    - [2.1.C++11 之前的模板](#21c11-之前的模板)
    - [2.2.C++11 的可变参数模板](#22c11-的可变参数模板)
    - [2.3.示例对比](#23示例对比)
  - [3.C++11 中的可变参数模板在实际项目中有哪些应用场景？](#3c11-中的可变参数模板在实际项目中有哪些应用场景)
  - [4.如何使用可变参数模板实现一个函数，它可以处理任意数量的参数？](#4如何使用可变参数模板实现一个函数它可以处理任意数量的参数)
    - [4.1. 基础案例](#41-基础案例)
    - [4.2. 递归展开](#42-递归展开)
    - [4.3. 使用折叠表达式](#43-使用折叠表达式)
    - [4.4.示例实现](#44示例实现)
    - [4.5.注意事项](#45注意事项)
  - [5.在C++11中，除了可变参数模板，还有哪些其他类型的模板值得学习？](#5在c11中除了可变参数模板还有哪些其他类型的模板值得学习)
  - [关于作者](#关于作者)

## Overview

---

## 1.可变参数模板 Variadic Templates

C++11 引入了可变参数模板（Variadic Templates），它允许开发者编写可以接受任意数量模板参数的模板。这项特性极大地增强了模板的表达能力和灵活性，使得编写泛型代码更加强大和通用。

### 1.1.基本语法

可变参数模板的基本语法如下：

```cpp
template <typename... Ts>  // 'Ts' 是一个模板参数包（Template Parameter Pack）
class MyClass {
    // ...
};
```

这里，`typename...` 表示参数包，可以有零个或多个类型参数。

### 1.2.参数包展开

可以使用递归模板特化来展开参数包：

```cpp
template<typename T>
void print(T t) {
    std::cout << t << std::endl;
}

template<typename T, typename... Rest>
void print(T t, Rest... rest) {
    std::cout << t << ", ";
    print(rest...);  // 递归展开参数包
}
```

### 1.3.示例

以下是一个使用可变参数模板的示例，它定义了一个计算任意数量参数之和的模板函数：

```cpp
#include <iostream>

template <typename... Ts>
int sum(Ts... args) {
    return (args + ... + 0);  // 使用折叠表达式计算总和
}

int main() {
    std::cout << "Sum: " << sum(1, 2, 3, 4) << std::endl;  // 10
    std::cout << "Sum: " << sum(1.5, 2.5, 3.5) << std::endl;  // 7.5
    return 0;
}
```

在这个例子中，使用了折叠表达式（Fold Expression）来计算参数的总和。

### 1.4.常用技术

1. **参数包转发**：
   在模板中，可以将参数包转发给其他函数：

   ```cpp
   template <typename... Ts>
   void wrapper(Ts... args) {
       someFunction(std::forward<Ts>(args)...);  // 使用 std::forward 完美转发参数
   }
   ```

2. **参数包构建其他模板**：
   可以将参数包作为构建其他模板的一部分：

   ```cpp
   template <typename... Ts>
   struct Wrapper {
       using Type = std::tuple<Ts...>;  // 构建一个类型元组
   };
   ```

3. **参数包与静态数组**：
   可以将参数包与静态数组结合使用：

   ```cpp
   template <typename... Ts>
   void printValues(const Ts&... args) {
       constexpr int values[sizeof...(Ts)] = {args...};
       // ...
   }
   ```

可变参数模板是 C++11 中最强大和最灵活的特性之一，它使得模板元编程更加强大，也为标准库中的许多新功能提供了基础，如 `std::tuple`、`std::variant` 和 `std::any`。

## 2.C++11 中的可变参数模板和旧版本的模板有什么区别？

C++11 之前的模板系统与 C++11 引入的可变参数模板（Variadic Templates）相比，有以下主要区别：

### 2.1.C++11 之前的模板

1. **固定参数数量**：
   旧版本的模板需要预先指定一个固定数量的模板参数。例如，如果你想要定义一个模板类或函数，你需要明确指出它接受一个参数、两个参数还是更多。

   ```cpp
   template <typename T>
   class MyClass;

   template <typename T1, typename T2>
   class MyPair;
   ```

2. **不支持参数包**：
   无法定义接受任意数量参数的模板。每个模板必须明确知道它将要处理的参数数量。

3. **模板特化**：
   需要为每种特定情况手动编写模板特化版本，这在处理多种类型时可能导致代码冗余。

### 2.2.C++11 的可变参数模板

1. **不定数量的参数**：
   可变参数模板允许模板类或函数接受任意数量的模板参数。

   ```cpp
   template <typename... Ts>
   class MyClass;
   ```

2. **参数包**：
   引入了参数包（Parameter Pack）的概念，可以对模板参数进行递归展开和处理。

3. **递归模板特化**：
   可以使用递归模板特化来处理参数包，从而编写出可以接受任意数量参数的模板。

4. **完美转发**：
   可变参数模板与 `std::forward` 一起使用，可以实现参数的完美转发，保留参数的lvalue/rvalue特性。

5. **折叠表达式**：
   引入了折叠表达式（Fold Expressions），允许对参数包进行初始化、累加等操作。

6. **更简洁的语法**：
   可变参数模板的语法比旧版本模板更加简洁，可以更直观地表达意图。

### 2.3.示例对比

**C++11 之前的模板**：

```cpp
template <typename T1, typename T2, typename T3>
void process(T1& a, T2& b, T3& c) {
    // ...
}
```

**C++11 的可变参数模板**：

```cpp
template <typename... Ts>
void process(Ts&... args) {
    // 使用参数包 args
}
```

在 C++11 之前的版本中，如果需要处理不同数量的参数，你需要为每种情况编写不同的模板。而在 C++11 中，你可以使用单个可变参数模板来处理所有这些情况。

总的来说，C++11 的可变参数模板提供了更强大的表达能力，允许开发者编写出更通用、更灵活的代码。

## 3.C++11 中的可变参数模板在实际项目中有哪些应用场景？

C++11 中的可变参数模板在实际项目中的应用场景非常广泛，它们提供了极大的灵活性和通用性。以下是一些典型的应用场景：

1. **通用数据结构**：
   可变参数模板可以用于实现如 `std::tuple` 这样的通用数据结构，它可以存储不同类型和数量的数据项。这种数据结构在需要将多个数据项组合成一个单一对象时非常有用。

2. **泛型编程**：
   在泛型编程中，可变参数模板允许开发者编写可以接受任意数量参数的函数或类模板。例如，可以实现一个函数，它可以接受任意数量的参数并将它们相加。

3. **类型安全的函数封装**：
   可变参数模板可以用于创建类型安全的函数封装器，这些封装器可以接受任意数量和类型的参数，并将其转发给另一个函数。这在实现中间件、日志记录机制或任何需要动态参数处理的层时非常有用。

4. **初始化列表和参数转发**：
   可变参数模板可以与初始化列表和参数转发结合使用，以实现如 `std::make_tuple` 这样的函数，它们可以根据输入参数构造元组。

5. **递归模板特化**：
   通过递归模板特化，可变参数模板可以用于处理参数包的展开，这在需要对参数进行逐个处理时非常有用。

6. **模板元编程**：
   可变参数模板可以与其他编译时编程技术结合使用，如模板特化、SFINAE（Substitution Failure Is Not An Error）等，以实现编译时的复杂计算和类型检查。

7. **通用迭代器**：
   可变参数模板可以用于创建可以迭代不同类型对象的通用迭代器，这在处理异构数据集合时非常有用。

8. **类型萃取和类型安全的函数**：
   可变参数模板可以用于实现类型安全的函数，这些函数在处理多种参数类型时可以确保类型正确。

9. **函数包装和高阶函数**：
   可变参数模板可以用于创建函数包装器，这些包装器可以接受任意数量的参数，并将它们转发给另一个函数，这在实现高阶函数时非常有用。

10. **实现 `emplace_back` 类似的功能**：
    可变参数模板可以用于实现类似于 `emplace_back` 的功能，直接在容器中构造对象，避免额外的拷贝或移动操作。

这些应用场景展示了可变参数模板在现代 C++ 编程中的多样性和实用性。通过使用这些特性，开发者可以编写出更加通用、灵活和高效的代码。

## 4.如何使用可变参数模板实现一个函数，它可以处理任意数量的参数？

使用可变参数模板实现一个函数，使其能够处理任意数量和类型的参数，可以通过递归模板展开和折叠表达式来完成。以下是实现这样一个函数的步骤：

### 4.1. 基础案例

首先，定义一个基础案例，处理当参数包为空时的情况：

```cpp
template<typename... Ts>
void process(Ts... /*args*/) {
    // 基础案例：当没有参数时，什么也不做
}
```

注意：由于基础案例不处理任何参数，参数可以用 `/*args*/` 来忽略。

### 4.2. 递归展开

然后，定义一个带有至少一个参数的模板重载，它将处理一个参数，并递归调用自身来处理剩余的参数：

```cpp
template<typename T, typename... Rest>
void process(T first, Rest... rest) {
    handle(first); // 处理第一个参数
    process(rest...); // 递归调用以处理剩余参数
}

template<typename T>
void process(T first) {
    handle(first); // 处理第一个参数，没有更多的参数
}
```

这里，`handle` 是一个假定的函数，用于处理单个参数。

### 4.3. 使用折叠表达式

使用 C++17 的折叠表达式（如果你使用的是 C++11 或 C++14，需要使用不同的递归展开方法）：

```cpp
template<typename... Ts>
void process(Ts... args) {
    (std::cout << ... << args) << '\n';
}
```

这个例子使用了左折叠表达式（left fold）来展开参数包 `args` 并将它们发送到标准输出。

### 4.4.示例实现

以下是一个更完整的示例，它展示了如何使用可变参数模板来实现一个函数，该函数将计算任意数量整数参数的总和：

```cpp
#include <iostream>

// 基础案例
template<typename... Ts>
int sum(Ts... /*args*/) {
    return 0;
}

// 递归展开
template<typename T, typename... Rest>
int sum(T first, Rest... rest) {
    return first + sum(rest...);
}

int main() {
    std::cout << "Sum: " << sum(1, 2, 3, 4, 5) << std::endl; // 输出 15
    return 0;
}
```

在这个示例中，`sum` 函数通过递归调用自身来处理参数包，直到参数包为空，触发基础案例。

### 4.5.注意事项

- 可变参数模板在使用时需要谨慎，以避免无限递归。
- 在 C++11 和 C++14 中，通常需要使用递归模板展开来处理参数包。
- C++17 引入的折叠表达式为处理参数包提供了更简洁的方式。

通过这种方式，你可以实现一个函数，它可以接受任意数量和类型的参数，并执行相应的操作。

## 5.在C++11中，除了可变参数模板，还有哪些其他类型的模板值得学习？

在 C++11 中，除了可变参数模板，还有许多其他重要的模板特性和相关概念值得学习和掌握：

1. **类型萃取（Type Traits）**：
   类型萃取是模板元编程的基础，它使用模板特化来在编译时提取或计算类型信息。例如，`std::is_same`, `std::add_const`, `std::remove_reference` 等。

2. **模板特化（Template Specialization）**：
   特化允许为特定类型或类型组合定制模板的实现。这可以用于优化通用模板类或函数对特定类型的行为。

3. **SFINAE（Substitution Failure Is Not An Error）**：
   SFINAE 是一种模板元编程技巧，允许在重载决策中使模板替换失败成为一个可接受的结果，而不是一个错误。

4. **完美转发（Perfect Forwarding）**：
   完美转发涉及到使用模板和 `std::forward` 来保留参数值类别（lvalue/rvalue）的转发技术。

5. **尾置返回类型（Trailing Return Type）**：
   尾置返回类型语法为模板函数提供了更清晰和优雅的返回类型定义方式。

6. **继承构造函数（Inherited Constructors）**：
   允许派生类继承基类的构造函数，简化模板类的构造函数定义。

7. **静态_assert**：
   `static_assert` 是一个编译时断言，它使用类型萃取来在编译时检查条件。

8. **decltype**：
   `decltype` 关键字用于推导表达式的类型，常用于模板元编程。

9. **constexpr**：
   `constexpr` 用于定义在编译时可以计算的常量表达式，它与模板一起使用可以生成编译时的常量。

10. **模板别名（Template Aliases）**：
    使用 `using` 关键字可以创建模板别名，它提供了一种简洁的方式来表示复杂的模板类型。

11. **嵌套模板（Nested Templates）**：
    如 `std::vector<T>::iterator`，它允许在类模板内部定义另一个模板。

12. **递归模板**：
    递归模板是递归函数的一种模板形式，它们可以用于实现复杂的编译时计算。

13. **模板元编程（Template Metaprogramming）**：
    使用模板进行编译时计算和代码生成，这在标准库中广泛使用，如 `std::tuple`。

14. **auto 关键字**：
    `auto` 关键字可以用于类型推断，它与模板结合使用可以简化代码。

15. **Lambda 表达式与模板**：
    Lambda 表达式经常与模板一起使用，尤其是在算法实现中。

16. **std::enable_if**：
    这是一个条件编译时的 if，它使用模板特化来启用或禁用某些函数重载。

这些特性和概念是现代 C++ 模板编程的基础，掌握它们可以提高编写高效、灵活和可重用代码的能力。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
