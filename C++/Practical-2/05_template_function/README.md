# C++ Practical-2 day5 模板之函数模板

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.模板之函数模板

函数模板是C++中一种支持泛型编程的工具，它允许你编写与数据类型无关的函数。通过使用模板，你可以创建一个函数，它可以在编译时自动适应任何给定的数据类型。

### 1.1.基本语法

```cpp
template <typename T>
function declaration;
```

- `template` 是声明模板的关键字。
- `<typename T>` 是一个参数列表，其中 `T` 是一个占位符，表示任何类型。
- `function declaration` 是函数的声明和定义。

### 1.2.示例

下面是一个简单的函数模板，它交换两个变量的值：

```cpp
#include <iostream>

// 函数模板声明
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 10;
    int y = 20;
    std::cout << "Before swap: x = " << x << ", y = " << y << std::endl;
    swap(x, y);
    std::cout << "After swap: x = " << x << ", y = " << y << std::endl;

    double a = 5.5;
    double b = 10.5;
    std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
    swap(a, b);
    std::cout << "After swap: a = " << a << ", b = " << b << std::endl;

    return 0;
}
```

### 1.3.模板参数

- `typename`：用于模板参数的类型。在C++11之前，也可以使用 `class` 关键字。
- `T`：一个占位符，表示任何类型。

### 1.4.模板特化

模板特化是为特定类型提供特定实现的方法。这在你需要为某些特定类型提供优化或特殊行为时非常有用。

#### 1.4.1.完全特化

```cpp
// 普通模板
template <typename T>
void print(T value) {
    std::cout << value << std::endl;
}

// 特化模板
template <>
void print<int>(int value) {
    std::cout << "Integer: " << value << std::endl;
}

int main() {
    print(10);    // 调用特化版本
    print(5.5);   // 调用普通模板
    return 0;
}
```

#### 1.4.2.偏特化 template partial specialization

偏特化通常用于类模板，但也可以通过模板重载实现函数的偏特化。

```cpp
// 普通模板
template <typename T1, typename T2>
void print(T1 value1, T2 value2) {
    std::cout << value1 << " and " << value2 << std::endl;
}

// 偏特化
template <typename T>
void print(int value1, T value2) {
    std::cout << "Integer and other type: " << value1 << ", " << value2 << std::endl;
}

int main() {
    print(10, 5.5);   // 调用偏特化
    print(5.5, 10);   // 调用普通模板
    return 0;
}
```

### 1.5.模板的注意事项

1. **编译时多态**：模板在编译时进行类型检查和代码生成，这称为编译时多态。
2. **类型推导**：编译器可以根据函数调用的参数类型自动推导出模板参数。
3. **代码膨胀**：每个模板实例都会生成独立的代码，这可能导致二进制文件变大。
4. **模板元编程**：模板不仅可以用于泛型编程，还可以用于模板元编程，这是一种在编译时执行计算的技术。

通过使用函数模板，你可以编写更加通用和灵活的代码。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
