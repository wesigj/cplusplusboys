# C++ Practical-2 day3 运算符重载之强制转换

- [C++ Practical-2 day3 运算符重载之强制转换](#c-practical-2-day3-运算符重载之强制转换)
  - [Overview](#overview)
  - [1.运算符重载之强制转换](#1运算符重载之强制转换)
    - [1.1.类型转换运算符](#11类型转换运算符)
      - [1.1.1.语法](#111语法)
      - [1.1.2.示例](#112示例)
    - [1.2.转换构造函数](#12转换构造函数)
      - [1.2.1.语法](#121语法)
      - [1.2.2.示例](#122示例)
    - [1.3.注意事项](#13注意事项)
  - [关于作者](#关于作者)

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.运算符重载之强制转换

在C++中，运算符重载允许你定义或修改大多数运算符的行为，以适应你自己的类。对于强制类型转换，C++提供了两种方式：类型转换运算符和转换构造函数。

### 1.1.类型转换运算符

类型转换运算符允许你定义一个运算符，使得你的类的对象可以自动转换为特定的类型。这通常是通过重载 `operator` 关键字实现的。

#### 1.1.1.语法

```cpp
operator TypeName() const {
    // 转换逻辑
}
```

#### 1.1.2.示例

假设你有一个类 `Distance`，你想让它可以自动转换为 `double` 类型，表示距离的数值。

```cpp
class Distance {
private:
    double meters;

public:
    Distance(double m) : meters(m) {}

    // 重载类型转换运算符为double
    operator double() const {
        return meters;
    }
};

int main() {
    Distance d(10.5);
    double length = d;  // 自动调用operator double()
    return 0;
}
```

### 1.2.转换构造函数

转换构造函数是一种特殊的构造函数，它允许对象在需要时自动转换为另一种类型。它通常用于类之间的隐式转换。

#### 1.2.1.语法

```cpp
class_name(Type type);
```

#### 1.2.2.示例

继续使用上面的 `Distance` 类，我们可以定义一个转换构造函数，允许从 `double` 类型隐式转换为 `Distance` 对象。

```cpp
class Distance {
private:
    double meters;

public:
    Distance(double m) : meters(m) {
    }

    // 方法一：转换构造函数
    // Distance(const double &m) : meters(m) {
    // }

    // 方法二：重载类型转换运算符为double
    operator double() const {
        return meters;
    }
    // 方法一，方法二会冲突，注释其中一个即可
};

int main() {
    Distance d(10.5);
    double   length = d;    // 自动调用operator double()
    Distance d2     = 20.0; // 自动调用转换构造函数
    return 0;
}
```

问题解释

当您尝试使用 Distance d2 = 20.0; 时，编译器发现两个构造函数都可以用来从 double 类型的参数构造 Distance 对象：

  1. Distance(double m)：直接接受 double 参数。
  2. Distance(const double &m)：接受 double 的引用。
由于这两个构造函数在功能上是相同的，编译器无法决定使用哪一个，因此报错。

解决方案

您应该只保留一个构造函数，通常，转换构造函数应该接受一个引用参数，以避免不必要的复制，但在这个特定情况下，由于您已经有了一个接受 double 参数的构造函数，转换构造函数是多余的。

### 1.3.注意事项

1. **隐式转换**：类型转换运算符默认是隐式的，这意味着它们可以在没有显式转换的情况下被调用。如果你不希望这样，可以在运算符前面加上 `explicit` 关键字，使其变为显式转换。
2. **使用场景**：类型转换运算符应该谨慎使用，因为它们可能会导致代码难以理解和维护。通常，只有当你的类确实需要与内置类型无缝交互时，才使用类型转换运算符。
3. **性能**：类型转换可能会影响性能，特别是在频繁调用的情况下。

通过这些方法，你可以为你的类定义合适的类型转换行为，使其更加灵活和强大。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
