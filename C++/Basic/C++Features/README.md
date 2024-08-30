# C++面试基础系列-C++Features

[TOC]

## Overview

## 1.C++Features

- C++与C的区别在于C++拥有更多的新特性
- "Explicit C++"（显式C++）通常指的是在C++编程中明确地、直接地使用C++的特性和语法，而不是隐式地或通过兼容C的方式。这通常意味着充分利用C++的面向对象编程（OOP）特性，例如
  - 类（classes）、
  - 对象（objects）、
  - 继承（inheritance）、
  - 多态（polymorphism）、
  - 抽象（abstraction）、
  - 封装（encapsulation）。
- 以下是一些显式C++编程的关键概念和实践：

1. **类和对象**：使用类来创建复杂的数据结构，这些结构可以包含数据成员和成员函数。

    ```cpp
    class MyClass {
    private:
        int privateData;
    public:
        MyClass() : privateData(0) {} // 构造函数
        void set(int value) { privateData = value; }
        int get() const { return privateData; }
    };
    ```

2. **构造函数和析构函数**：显式地定义构造函数来初始化对象，定义析构函数来执行清理工作。

    ```cpp
    MyClass::MyClass(int initialValue) : privateData(initialValue) {}
    ~MyClass() {
        // 清理工作
    }
    ```

3. **继承**：使用继承来创建基于现有类的新的类，实现代码复用。

    ```cpp
    class DerivedClass : public BaseClass {
        // 继承BaseClass的成员
    };
    ```

4. **多态**：通过虚函数实现多态性，允许通过基类指针或引用调用派生类的方法。

    ```cpp
    class Base {
    public:
        virtual void doSomething() { /* ... */ }
    };

    class Derived : public Base {
    public:
        void doSomething() override { /* ... */ }
    };
    ```

5. **抽象类**：使用纯虚函数创建抽象类，这些类不能被实例化，但可以作为其他类的接口。

    ```cpp
    class AbstractClass {
    public:
        virtual void pureVirtualFunc() = 0; // 纯虚函数
    };
    ```

6. **封装**：将数据和操作这些数据的函数封装在类中，隐藏实现细节。

    ```cpp
    class Encapsulation {
    private:
        int value;
    public:
        void setValue(int v) { value = v; }
        int getValue() const { return value; }
    };
    ```

7. **模板**：使用模板创建泛型类和函数，允许在编译时实例化多种类型的类和函数。

    ```cpp
    template <typename T>
    class TemplateClass {
        T data;
    public:
        void set(T d) { data = d; }
        T get() const { return data; }
    };
    ```

8. **异常处理**：使用try、catch和throw来处理程序中的异常情况。

    ```cpp
    try {
        // 可能抛出异常的代码
    } catch (const std::exception& e) {
        // 异常处理代码
    }
    ```

9. **智能指针**：使用智能指针（如`std::unique_ptr`和`std::shared_ptr`）来自动管理内存。

    ```cpp
    std::unique_ptr<MyClass> myPtr = std::make_unique<MyClass>(42);
    ```

10. **命名空间**：使用命名空间来组织代码，避免名称冲突。

    ```cpp
    namespace MyNamespace {
        class MyClass {
            // ...
        };
    }
    ```

11. **标准库**：充分利用C++标准库（STL），如容器、迭代器、算法等。

    ```cpp
    #include <vector>
    std::vector<int> myVector = {1, 2, 3};
    ```

显式C++编程鼓励使用C++特有的特性来提高代码的安全性、可读性和效率，而不是依赖C风格的做法。

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
