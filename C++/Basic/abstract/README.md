# C++面试基础系列-abstract

[TOC]

## Overview

在C++中，`abstract`这个概念主要与抽象类`（Abstract Class）`相关。抽象类是一种不能被实例化的类，它通常包含至少一个纯虚函数`（Pure Virtual Function）`。抽象类用于定义接口或行为规范，可以被其他类继承并实现具体的功能。

## 1.abstract关键点

以下是一些关于C++中抽象类的关键点：

- 纯虚函数：
  - 纯虚函数是在基类中声明但没有实现的虚函数，其声明方式是在函数声明的末尾加上= 0。
  - 例如：`virtual void doSomething() = 0;`
- 抽象类的定义：
  - 包含至少一个纯虚函数的类就是抽象类。
  - 抽象类不能被直接实例化，但可以被用作其他类的基类。
- 继承抽象类：
  - 派生类必须实现基类中的所有纯虚函数，否则派生类也会是抽象类。
- 接口定义：
  - 抽象类通常用于定义接口，让不同的派生类实现相同的接口。
- 多态性：
  - 抽象类支持多态性，可以通过基类指针或引用调用派生类重写的虚函数。
示例：

```cpp
// 抽象类声明
class Shape {
public:
    virtual void draw() const = 0;  // 纯虚函数
    virtual ~Shape() {}  // 虚析构函数，确保派生类析构正确性
};

// 派生类实现抽象类
class Circle : public Shape {
public:
    void draw() const override {
        // 绘制圆形的代码
    }
};

// 使用抽象类
Shape* shape = new Circle();
shape->draw();
delete shape;
```

- 抽象类的作用：
  - 强制实现接口：确保所有派生类都实现了抽象类中定义的纯虚函数。
  - 代码复用：基类可以提供一些通用的实现，派生类可以重写或继承这些实现。
- 设计原则：
  - 遵循里氏替换原则（Liskov Substitution Principle），确保派生类可以替换其基类。
- 注意事项：
  - 抽象类通常包含虚析构函数，以确保派生类的析构函数被正确调用。
- C++11及以后版本：
  - C++11引入了final关键字，可以修饰类或成员函数，表示它们不能被进一步继承或重写。

抽象类是C++面向对象编程中的一个重要概念，它有助于实现代码的模块化和可扩展性。通过使用抽象类，开发者可以定义清晰的接口，并在不同的派生类中实现这些接口的具体行为。

## 2.C++ 抽象类和纯虚函数的例子

- 在这个例子中，Shape 是一个抽象类，它定义了一个纯虚函数 getArea。
  - Circle 和 Rectangle 是 Shape 的派生类，它们分别实现了 getArea 函数。
  - 由于 Shape 是抽象类，我们不能直接创建它的实例，但可以创建 Circle 和 Rectangle 的实例。

```cpp
#include <iostream>

// 抽象基类
class Shape {
public:
    // 纯虚函数，用于计算面积
    virtual double getArea() const = 0;

    // 虚析构函数
    virtual ~Shape() {}
};

// 派生类 Circle
class Circle : public Shape {
public:
    // 构造函数
    Circle(double radius) : radius(radius) {}

    // 实现基类的纯虚函数
    double getArea() const override {
        return 3.14159 * radius * radius;
    }

private:
    double radius;
};

// 派生类 Rectangle
class Rectangle : public Shape {
public:
    // 构造函数
    Rectangle(double width, double height) : width(width), height(height) {}

    // 实现基类的纯虚函数
    double getArea() const override {
        return width * height;
    }

private:
    double width, height;
};

int main() {
    // 由于 Shape 是抽象类，不能直接实例化
    // Shape shape; // 错误

    Circle circle(5.0);
    Rectangle rectangle(4.0, 6.0);

    std::cout << "Circle area: " << circle.getArea() << std::endl;
    std::cout << "Rectangle area: " << rectangle.getArea() << std::endl;

    return 0;
}
```

## 3.abstract重点

- 纯虚函数使一个类变成抽象类
- 抽象类类型的指针和引用
- 如果我们不在派生类中覆盖纯虚函数，那么派生类也会变成抽象类
- 抽象类可以有构造函数
- 构造函数不能是虚函数，而析构函数可以是虚析构函数

```cpp
// 抽象类
class Base  {
public:
    Base(){ cout << "Constructor: Base" << endl; }
    virtual ~Base(){ cout << "Destructor : Base" << endl; }
    
    virtual void func() = 0;
};

class Derived: public Base {
public:
    Derived(){ cout << "Constructor: Derived" << endl; }
    ~Derived(){ cout << "Destructor : Derived" << endl;}
    
    void func(){cout << "In Derived.func()." << endl;}
};
```

>当基类指针指向派生类对象并删除对象时，我们可能希望调用适当的析构函数。
> 如果析构函数不是虚拟的，则只能调用基类析构函数。

---

## 关于作者

- 本文作者:WeSiGJ
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 微信公众号:WeSiGJ

<html><body><img src="/./img/wechat.jpg" width="60%"></body></html>
