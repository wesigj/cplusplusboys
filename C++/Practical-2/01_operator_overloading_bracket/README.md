# C++ Practical-2 day1 重载函数调用运算符`()` 中括号

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.重载函数调用运算符`()` 中括号

在C++中，重载函数调用运算符`()`允许对象像函数一样被调用。这在设计模式中非常有用，特别是在实现工厂模式或者需要模拟函数指针时。

### 1.1.重载函数调用运算符的规则

1. **成员函数**：运算符`()`必须作为成员函数重载。
2. **无参数**：运算符`()`不接受任何参数。
3. **返回值**：必须指定返回类型，通常是类本身或者一个函数指针。

### 1.2.示例1：重载`()`运算符用于模拟函数指针

```cpp
#include <iostream>
#include <functional>

class FunctionWrapper {
public:
    // 存储一个可调用对象
    std::function<void()> func;

    // 构造函数
    FunctionWrapper(std::function<void()> f) : func(f) {}

    // 重载函数调用运算符
    void operator()() {
        func();
    }
};

int main() {
    // 创建一个lambda表达式
    auto lambda = []() { std::cout << "Hello, World!" << std::endl; };

    // 创建FunctionWrapper对象
    FunctionWrapper wrapper(lambda);

    // 使用重载的()运算符调用
    wrapper(); // 输出: Hello, World!

    return 0;
}
```

### 1.3.示例2：重载`()`运算符用于创建工厂对象

```cpp
#include <iostream>
#include <string>

class StringFactory {
public:
    // 重载函数调用运算符
    std::string operator()(const std::string& str) const {
        return str;
    }
};

int main() {
    StringFactory factory;

    std::string result = factory("Hello, Factory!");

    std::cout << result << std::endl; // 输出: Hello, Factory!

    return 0;
}
```

### 1.4.注意事项

1. **返回类型**：根据需要返回适当的类型，如果需要链式调用，则返回对象本身的引用。

2. **const成员函数**：如果重载的`()`运算符不应该修改对象的状态，应该将其声明为`const`。

3. **异常安全**：确保在调用过程中即使发生异常，对象也保持有效状态。

4. **资源管理**：如果运算符`()`涉及到资源管理，确保资源被正确分配和释放。

通过重载函数调用运算符`()`，可以使对象的使用更加灵活和表达式更加简洁。

## 2.重载函数调用运算符`()`

在C++中，重载函数调用运算符`()`允许一个对象像函数一样被调用。这通常用于创建类似于函数的对象，或者让对象能够执行某些操作。

以下是重载函数调用运算符的一般形式：

```cpp
class MyClass {
public:
    // 重载()运算符
    returnType operator()(arg1Type arg1, arg2Type arg2, ...) const {
        // 函数体
    }
};
```

这里的`MyClass`是一个类，`operator()`是成员函数，它重载了`()`运算符。`returnType`是函数调用的返回类型，`arg1Type`、`arg2Type`等是参数的类型。

### 2.1.示例

假设我们有一个类`Counter`，我们希望创建一个对象，该对象可以像函数一样被调用，并且每次调用都会增加计数器的值：

```cpp
#include <iostream>

class Counter {
private:
    int count;

public:
    // 构造函数
    Counter() : count(0) {}

    // 重载()运算符
    int operator()() {
        return ++count;
    }
};

int main() {
    Counter myCounter;
    std::cout << myCounter() << std::endl; // 输出 1
    std::cout << myCounter() << std::endl; // 输出 2
    std::cout << myCounter() << std::endl; // 输出 3
    return 0;
}
```

在这个例子中，每次调用`myCounter()`都会增加`count`的值，并返回新的值。

### 2.2.注意事项

1. **const修饰符**：如果你的重载的`()`运算符不会修改对象的状态，你应该在函数声明的末尾添加`const`关键字，以表明这个成员函数不会修改对象的任何成员变量。

2. **参数**：你可以为`()`运算符提供参数，就像普通函数一样。

3. **返回类型**：你需要指定函数调用的返回类型。

4. **成员函数**：`operator()`是一个成员函数，因此它可以直接访问对象的成员变量和成员函数。

通过重载函数调用运算符，你可以创建出非常灵活和强大的类，这些类的对象可以像函数一样被调用。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
