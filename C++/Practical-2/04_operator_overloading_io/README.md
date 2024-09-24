# C++ Practical-2 运算符重载之输入输出运算符重载

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.运算符重载之输入输出运算符重载

在C++中，重载输入输出运算符（`operator<<` 和 `operator>>`）可以让你自定义类的对象与标准输入输出流（如 `std::cout` 和 `std::cin`）之间的交互方式。这使得你的类的对象可以像内置类型一样直接与输入输出流进行交互。

### 1.1.重载输出运算符 `<<`

#### 1.1.1.语法

```cpp
friend std::ostream& operator<<(std::ostream& os, const 类名& obj);
```

#### 1.1.2.示例

假设你有一个 `Point` 类，你想通过 `std::cout` 打印它的坐标。

```cpp
#include <iostream>

class Point {
private:
    int x, y;

public:
    Point(int x, int y) : x(x), y(y) {}

    // 重载输出运算符
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

int main() {
    Point p(10, 20);
    std::cout << p << std::endl;
    return 0;
}
```

### 1.2.重载输入运算符 `>>`

#### 1.2.1.语法

```cpp
friend std::istream& operator>>(std::istream& is, 类名& obj);
```

#### 1.2.2.示例

继续使用 `Point` 类，你可以定义一个输入运算符，允许从 `std::cin` 读取坐标。

```cpp
#include <iostream>

class Point {
private:
    int x, y;

public:
    Point() : x(0), y(0) {}

    // 重载输入运算符
    friend std::istream& operator>>(std::istream& is, Point& p) {
        is >> p.x >> p.y;
        return is;
    }

    // 重载输出运算符
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

int main() {
    Point p;
    std::cout << "Enter coordinates of the point (x y): ";
    std::cin >> p;
    std::cout << "You entered: " << p << std::endl;
    return 0;
}
```

### 1.3.注意事项

1. **友元函数**：输入输出运算符通常定义为类的友元函数，这样它们就可以访问类的私有成员。
2. **返回类型**：输入输出运算符应该返回对流的引用，以便可以链式调用。
3. **异常处理**：在处理输入输出时，应该考虑异常处理，例如输入不合法的情况。
4. **效率**：直接操作流可以提高效率，因为避免了额外的字符串转换。

通过重载输入输出运算符，你的类将更加易于使用，代码可读性也会提高。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
