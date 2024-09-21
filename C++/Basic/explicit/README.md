# C++面试基础系列-explicit

[TOC]

## Overview

## 1.explicit

在 C++ 中，"explicit" 关键字用于类构造函数，以防止隐式类型转换和复制初始化。使用 `explicit` 可以提高代码的安全性，因为它要求在转换类型时必须明确地进行。下面是一些关于 `explicit` 的使用场景和示例：

### 1.1.使用场景

1. **防止隐式转换**：当你希望类的构造函数只用于显示转换，而不是由编译器隐式执行时。
2. **避免歧义**：在多构造函数的情况下，`explicit` 可以避免编译器在选择调用哪个构造函数时产生歧义。

### 1.2.语法

```cpp
class MyClass {
public:
    explicit MyClass(Type param) {
        // 构造函数实现
    }
    // 其他成员和方法
};
```

### 1.3.示例

#### 1.3.1.防止隐式类型转换

```cpp
class NumericString {
public:
    explicit NumericString(const std::string& s) {
        // 初始化逻辑，可能包括检查字符串是否只包含数字
    }
};

int main() {
    NumericString ns("123"); // 正确，显示转换
    // NumericString ns2 = "123"; // 错误，因为构造函数是 explicit 的
    return 0;
}
```

#### 1.3.2.构造函数重载解析

如果有多个构造函数，`explicit` 可以帮助编译器确定应该调用哪个构造函数。

```cpp
class Date {
public:
    Date(int day, int month, int year) { /* ... */ } // 普通构造函数
    explicit Date(const std::string& dateString) { /* ... */ } // 显式构造函数
};

int main() {
    Date d1(1, 1, 2023); // 调用第一个构造函数
    Date d2("2023-01-01"); // 调用第二个构造函数，需要显示转换
    // Date d3 = "2023-01-01"; // 错误，因为第二个构造函数是 explicit 的
    return 0;
}
```

### 1.4.注意事项

- 默认情况下，所有构造函数都是隐式的。添加 `explicit` 关键字后，构造函数就不再参与隐式转换。
- `explicit` 只能用在单个参数的构造函数上。如果你需要调用一个多参数的构造函数，可以定义一个转换操作符或工厂函数。
- 在 C++11 及以后的版本中，列表初始化可以绕过 `explicit` 的限制，因此要谨慎使用。

通过使用 `explicit`，你可以在设计类时提供额外的安全性，防止错误的类型转换和潜在的 bug。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/img/wechat.jpg width=60% />
