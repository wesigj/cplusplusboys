# C++11 28-纯虚函数的默认实现 The default implementation of pure virtual functions

- [C++11 28-纯虚函数的默认实现 The default implementation of pure virtual functions](#c11-28-纯虚函数的默认实现-the-default-implementation-of-pure-virtual-functions)
  - [Overview](#overview)
  - [1.纯虚函数的默认实现 The default implementation of pure virtual functions](#1纯虚函数的默认实现-the-default-implementation-of-pure-virtual-functions)
    - [1.1.语法](#11语法)
    - [1.2.使用 `default` 关键字](#12使用-default-关键字)
    - [1.3.示例](#13示例)
    - [1.4.注意事项](#14注意事项)
  - [2.在 C++11 中，除了纯虚函数，还有哪些其他的特性可以提高代码的可扩展性？](#2在-c11-中除了纯虚函数还有哪些其他的特性可以提高代码的可扩展性)
  - [3.如何使用C++11的特性来避免多重继承带来的复杂性？](#3如何使用c11的特性来避免多重继承带来的复杂性)
  - [4.C++11中的默认函数重载是如何工作的，它与默认的纯虚函数有什么不同？](#4c11中的默认函数重载是如何工作的它与默认的纯虚函数有什么不同)
  - [5.能否举例说明如何使用Mixin设计模式来解决多重继承问题？](#5能否举例说明如何使用mixin设计模式来解决多重继承问题)
    - [5.1.Mixin 示例](#51mixin-示例)
    - [5.2.使用示例](#52使用示例)
    - [5.3.注意事项](#53注意事项)
  - [关于作者](#关于作者)

## Overview

---

## 1.纯虚函数的默认实现 The default implementation of pure virtual functions

在 C++11 之前，纯虚函数（也称为抽象函数）是不能有实现的，因为它们的定义是为了创建一个接口，让派生类必须提供自己的实现。然而，C++11 引入了一个特性，允许纯虚函数有默认实现。这为在基类中提供可重写的默认行为提供了便利。

### 1.1.语法

在 C++11 中，你可以使用 `= 0` 来将一个虚函数声明为纯虚函数，并且可以提供默认实现：

```cpp
class Base {
public:
    virtual void func() = 0;
};

class Derived : public Base {
public:
    void func() override {
        std::cout << "Derived's func" << std::endl;
    }
};
```

在这个例子中，`Base` 类的 `func()` 是一个纯虚函数，没有提供默认实现。然而，C++11 允许你这样写：

```cpp
class Base {
public:
    virtual void func() = 0 {
        std::cout << "Default implementation of func" << std::endl;
    }
};
```

这里，`func()` 函数被声明为纯虚函数，并且有一个默认实现。派生类可以提供自己的实现，或者继续使用这个默认实现。

### 1.2.使用 `default` 关键字

另一种方式是使用 `default` 关键字来为纯虚函数提供一个默认实现：

```cpp
class Base {
public:
    virtual void func() = default;
};
```

在这个例子中，`func()` 函数有一个默认实现，任何从 `Base` 派生的类都将继承这个默认实现。如果派生类没有重写 `func()`，它将使用这个默认实现。

### 1.3.示例

```cpp
#include <iostream>

class Base {
public:
    virtual void func() = 0 {
        std::cout << "Default implementation of func" << std::endl;
    }
};

class Derived : public Base {
public:
    void func() override {}
};

int main() {
    Derived d;
    d.func(); // 将调用 Derived 的 func()，即使它是空的
    return 0;
}
```

在这个示例中，`Base` 类的 `func()` 函数有一个默认实现，而 `Derived` 类重写了 `func()` 函数，提供了一个空实现。

### 1.4.注意事项

- 即使纯虚函数有默认实现，包含纯虚函数的类也仍然是抽象类，不能实例化。
- 派生类可以不提供纯虚函数的实现，而是继续使用默认实现。
- 使用默认实现的纯虚函数可以作为一种文档方式，说明派生类应该实现这个函数。

这个特性在设计接口时非常有用，因为它允许你在基类中提供一个默认行为，同时仍然强制派生类根据需要提供自己的实现。

## 2.在 C++11 中，除了纯虚函数，还有哪些其他的特性可以提高代码的可扩展性？

在 C++11 中，除了纯虚函数，还有许多其他特性可以提高代码的可扩展性：

1. **自动类型推断 (`auto` 关键字)**：可以减少手动指定类型的需要，特别是在处理复杂的模板或容器类型时。

2. **基于范围的 for 循环**：提供了一种更简洁和直观的方式来遍历容器或数组。

3. **Lambda 表达式**：允许在需要的地方定义匿名函数，这在与标准库算法一起使用时特别有用。

4. **智能指针 (`std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`)**：提供了自动的内存管理，减少了内存泄漏的风险。

5. **并发编程支持**：包括 `std::thread`, `std::async` 等，使得编写多线程代码更加容易。

6. **正则表达式支持 (`std::regex`)**：提供了一种方便的方式来处理字符串匹配和操作。

7. **原子操作和线程局部存储**：通过 `std::atomic` 和 `thread_local` 关键字，提供了基本的同步操作。

8. **可调用对象的包装器 (`std::function`)**：可以存储、复制和调用任何可调用对象，包括函数指针、函数对象和 lambda 表达式。

9. **类型安全的枚举 (`enum class`)**：提高了枚举类型的安全性和清晰度。

10. **委托构造函数**：允许一个构造函数调用另一个构造函数，减少了代码重复。

11. **`final` 关键字**：用于防止进一步继承类或重写虚函数。

12. **`override` 关键字**：确保派生类正确地重写了基类的虚函数。

13. **变长模板**：允许创建接受任意数量模板参数的模板。

14. **`static_assert`**：提供了一种在编译时进行断言的方式。

15. **`decltype`**：用于推导表达式的类型，常用于模板元编程。

16. **`noexcept`**：用于指定函数不会抛出异常，有助于异常安全的编程。

17. **`nullptr`**：提供了一个更好的空指针常量。

这些特性一起为 C++ 程序员提供了更多的工具来编写可扩展、可维护和现代化的代码。

## 3.如何使用C++11的特性来避免多重继承带来的复杂性？

## 4.C++11中的默认函数重载是如何工作的，它与默认的纯虚函数有什么不同？

在 C++11 中，避免多重继承带来的复杂性可以通过以下几种方式实现：

1. **使用虚继承（Virtual Inheritance）**：虚继承用于解决多重继承中的菱形继承问题，即当多个基类共享同一个基类时，通过虚继承可以确保派生类中只有一份基类拷贝，避免数据冗余和二义性问题。

2. **使用接口继承**：通过定义接口（抽象类），可以让派生类只继承接口而不直接继承实现，这样可以减少直接的实现依赖，降低类之间的耦合度。

3. **使用组合（Composition）**：组合是一种设计原则，通过将一个类的对象作为另一个类的成员，而不是通过继承来复用代码。这样可以更灵活地组合不同的功能，同时避免了多重继承的复杂性。

4. **利用Mixin设计模式**：Mixin 是一种允许多重继承的语言特性，它通过模板参数化的方式，使得可以在编译时动态地组合多个基类的功能。

5. **使用委托构造函数**：C++11 允许一个构造函数调用另一个构造函数，这有助于减少多重继承时构造函数的重复代码。

6. **使用继承构造函数**：C++11 允许派生类继承基类的构造函数，这样可以减少派生类中构造函数的编写工作，同时保持了基类的构造逻辑。

7. **利用`final`关键字**：通过将基类标记为`final`，可以防止进一步的继承，这样可以控制类的继承层次，避免不必要的复杂性。

8. **利用`override`关键字**：在派生类中重写虚函数时使用`override`关键字，可以确保函数正确地重写了基类中的虚函数，提高代码的安全性和可维护性。

通过这些方法，可以有效地减少多重继承带来的复杂性，提高代码的可扩展性和可维护性。

## 5.能否举例说明如何使用Mixin设计模式来解决多重继承问题？

Mixin 设计模式在 C++ 中通常用来向一个类添加多个来源的行为。Mixin 允许多重继承的优雅替代，通过模板和特化来组合多个类的行为。

### 5.1.Mixin 示例

假设我们有两个通用的功能类 `Able` 和 `Baker`，我们想将这两个功能都添加到类 `Charlie` 中。

```cpp
// 功能类 A
class Able {
public:
    void showA() {
        std::cout << "Able functionality." << std::endl;
    }
};

// 功能类 B
class Baker {
public:
    void showB() {
        std::cout << "Baker functionality." << std::endl;
    }
};

// 基类
class Base {};

// Mixin 类模板
template<typename T, typename... Rest>
class Mixin : public T, public Mixin<Rest...> {
public:
    using T::showA;
    using Mixin<Rest...>::showB;
};

// 空特化，结束递归
template<typename T>
class Mixin<T> : public T {
public:
    using T::showA;
};

// 使用 Mixin 组合 Able 和 Baker 功能
class Charlie : public Mixin<Able, Baker, Base> {
public:
    void introduce() {
        showA();
        showB();
    }
};
```

在这个例子中，`Mixin` 类模板是一个递归模板，它将参数列表中的所有类型作为基类。它使用 `using` 声明来引入所有基类的同名成员函数。递归在只有一个模板参数时结束，这是通过空特化实现的。

`Charlie` 类继承自 `Mixin<Able, Baker, Base>`，它组合了 `Able` 和 `Baker` 的行为，同时也可以继承自其他任何基类（在这个例子中是 `Base`）。

### 5.2.使用示例

```cpp
int main() {
    Charlie charlie;
    charlie.introduce(); // 输出 Able 和 Baker 的功能
    return 0;
}
```

### 5.3.注意事项

- Mixin 模式允许你动态地组合类的行为，而不需要直接使用多重继承。
- Mixin 类通常只提供一种或几种功能，并设计为可以轻松组合到其他类中。
- 你应该避免在 Mixin 类中添加状态（成员变量），因为每个 Mixin 都应该是轻量级的，主要用于提供行为。
- 使用 Mixin 时，需要注意成员函数名字的冲突和作用域的问题。

Mixin 设计模式是处理多重行为组合的一种非常有用的工具，它提供了一种避免多重继承带来的复杂性和潜在问题的方法。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
