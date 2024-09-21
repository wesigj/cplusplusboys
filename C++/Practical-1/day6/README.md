# C++ Practical-1 day6

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.abstract_class 抽象类

在C++中，抽象类是一种不能被实例化的类，它通常作为基类使用，用于定义一个接口或规范，确保派生类遵循某些方法。抽象类通过包含至少一个纯虚函数（pure virtual function）来实现。

### 1.1.抽象类的特点

1. **纯虚函数**：抽象类至少包含一个纯虚函数。纯虚函数没有实现，使用`= 0`声明。

2. **不能被实例化**：由于抽象类不提供完整的实现，因此不能创建其实例。

3. **派生类必须覆盖所有纯虚函数**：派生类必须覆盖基类中的所有纯虚函数，除非派生类也是抽象类。

4. **虚析构函数**：通常在抽象类中定义虚析构函数，以确保删除派生类对象时正确调用派生类的析构函数。

### 1.2.示例：抽象类

```cpp
#include <iostream>
#include <memory>

// 抽象类
class Shape {
public:
    // 纯虚函数
    virtual void draw() const = 0;

    // 虚析构函数
    virtual ~Shape() {}
};

// 派生类
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a circle." << std::endl;
    }
};

// 另一个派生类
class Rectangle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a rectangle." << std::endl;
    }
};

int main() {
    // 使用基类指针指向派生类对象
    std::unique_ptr<Shape> shape1(new Circle());
    std::unique_ptr<Shape> shape2(new Rectangle());

    shape1->draw(); // 调用Circle的draw函数
    shape2->draw(); // 调用Rectangle的draw函数

    return 0;
}
```

在这个例子中，`Shape`是一个抽象类，它包含一个纯虚函数`draw`。`Circle`和`Rectangle`是派生自`Shape`的类，它们都覆盖了`draw`函数。在`main`函数中，我们使用`Shape`指针来指向`Circle`和`Rectangle`对象，并调用它们的`draw`函数。

### 1.3.注意事项

1. **接口定义**：抽象类通常用于定义接口，它规定了派生类必须实现的函数。

2. **多态**：抽象类通常与多态一起使用，允许通过基类指针或引用来调用派生类中覆盖的虚函数。

3. **抽象类和虚函数**：抽象类可以包含多个纯虚函数和普通虚函数。普通虚函数提供了默认实现，而纯虚函数没有。

4. **抽象类和继承**：派生类可以从多个抽象类继承，也可以是另一个抽象类的抽象类。

5. **抽象类的实现**：虽然抽象类不能被实例化，但它们可以包含成员函数的实现，这些实现可以被派生类继承。

6. **工厂模式**：抽象类经常与工厂模式结合使用，用于创建一系列相关对象。

抽象类是C++中实现面向对象设计原则的重要工具，它有助于定义清晰的接口和促进代码的模块化。

## 2.virtual_function 虚函数

在C++中，虚函数用于实现多态性，允许通过基类指针或引用调用派生类中覆盖的函数。以下是一个使用虚函数的编程实例：

### 2.1.示例：动物叫声的多态性

```cpp
#include <iostream>

// 基类
class Animal {
public:
    virtual void speak() const {
        std::cout << "The animal makes a sound." << std::endl;
    }

    virtual ~Animal() {} // 虚析构函数
};

// 派生类：狗
class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "The dog barks." << std::endl;
    }
};

// 派生类：猫
class Cat : public Animal {
public:
    void speak() const override {
        std::cout << "The cat meows." << std::endl;
    }
};

int main() {
    Animal* myAnimal = nullptr;

    Dog myDog;
    myAnimal = &myDog;
    myAnimal->speak(); // 输出: The dog barks.

    Cat myCat;
    myAnimal = &myCat;
    myAnimal->speak(); // 输出: The cat meows.

    return 0;
}
```

在这个例子中，`Animal`是一个基类，它有一个虚函数`speak`。`Dog`和`Cat`是派生自`Animal`的类，它们都覆盖了`speak`函数。在`main`函数中，我们使用`Animal`指针`myAnimal`来指向`Dog`和`Cat`对象，并调用它们的`speak`函数。

### 2.2.示例：计算图形的面积

```cpp
#include <iostream>

// 基类：形状
class Shape {
public:
    virtual double area() const = 0; // 纯虚函数
    virtual ~Shape() {} // 虚析构函数
};

// 派生类：圆形
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    double area() const override {
        return 3.14159 * radius * radius;
    }
};

// 派生类：矩形
class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double area() const override {
        return width * height;
    }
};

int main() {
    const double pi = 3.14159;
    Shape* shape;

    Circle circle(5); // 半径为5的圆
    shape = &circle;
    std::cout << "Circle area: " << shape->area() << std::endl; // 输出圆形的面积

    Rectangle rectangle(4, 6); // 宽4高6的矩形
    shape = &rectangle;
    std::cout << "Rectangle area: " << shape->area() << std::endl; // 输出矩形的面积

    return 0;
}
```

在这个例子中，`Shape`是一个抽象基类，它有一个纯虚函数`area`。`Circle`和`Rectangle`是派生自`Shape`的类，它们都覆盖了`area`函数。在`main`函数中，我们使用`Shape`指针`shape`来指向`Circle`和`Rectangle`对象，并调用它们的`area`函数。

### 2.3.注意事项

1. **多态性**：虚函数允许多态性，使得可以通过基类指针或引用来调用派生类中覆盖的函数。

2. **抽象基类**：包含纯虚函数的类是抽象基类，不能被实例化。

3. **派生类覆盖虚函数**：派生类可以使用`override`关键字来覆盖基类的虚函数。

4. **虚析构函数**：在基类中声明虚析构函数，以确保删除派生类对象时正确调用派生类的析构函数。

5. **动态类型识别**：可以使用`dynamic_cast`在运行时安全地将基类指针或引用转换为派生类指针或引用。

虚函数是C++中实现多态性的关键，使得代码更加灵活和可扩展。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/img/wechat.jpg width=60% />
