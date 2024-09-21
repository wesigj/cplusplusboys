# C++面试基础系列-C++虚函数virtual

[TOC]

## Overview

## 1.virtual

在 C++ 中，`virtual` 关键字用于实现多态性，它允许你定义虚函数。虚函数是一种成员函数，它可以在派生类中被重写（override），并且调用哪个函数版本是由对象的实际类型决定的，而不是由指针或引用的静态类型决定的。

以下是 `virtual` 关键字的一些关键点和示例：

### 1.1.虚函数

- 使用 `virtual` 关键字定义的函数可以在派生类中被重写。
- 调用虚函数时，将根据对象的实际类型调用相应的函数实现。

```cpp
class Base {
public:
    virtual void show() {
        std::cout << "Base show" << std::endl;
    }
    virtual ~Base() {} // 虚析构函数确保派生类的析构函数被调用
};

class Derived : public Base {
public:
    void show() override { // 使用 override 关键字明确重写意图
        std::cout << "Derived show" << std::endl;
    }
};
```

### 1.2.抽象类

- 如果类包含至少一个纯虚函数，它就成为了一个抽象类（abstract class），不能被实例化。

```cpp
class AbstractBase {
public:
    virtual void pureVirtualFunction() = 0; // 纯虚函数
    // 其他成员函数...
};
```

### 1.3.虚析构函数

- 定义虚析构函数以确保在删除通过基类指针删除派生类对象时，正确的析构函数被调用。

### 1.4.虚继承

- 使用 `virtual` 关键字进行虚继承可以解决菱形继承问题，避免重复继承同一基类。

```cpp
class Base1 {};
class Base2 {};
class Derived : virtual public Base1, virtual public Base2 {};
```

### 1.5.多态的使用

- 通过基类指针或引用调用虚函数，可以实现多态行为。

```cpp
Base* basePtr = new Derived();
basePtr->show(); // 调用 Derived 类的 show 函数
delete basePtr;
```

### 1.6.`final` 关键字

- 使用 `final` 关键字可以阻止进一步的重写。

```cpp
class FinalClass : public Base {
public:
    void show() final {
        std::cout << "FinalClass show" << std::endl;
    }
};
```

在这个例子中，`FinalClass` 中的 `show` 函数不能在任何派生类中被重写。

### 1.7.注意事项

- 虚函数提供了运行时多态性，这是 C++ 的核心特性之一。
- 虚函数通常用于接口类或基类，以提供可扩展的行为。
- 确保正确使用虚析构函数，以避免资源泄漏。
- 虚函数和纯虚函数是实现多态和抽象类的基础。

`virtual` 关键字是 C++ 实现面向对象编程的重要工具，它允许更灵活和动态的代码设计。

## 2.如何使用 C++ 的虚函数实现多态性？

在 C++ 中，多态性是指允许不同类的对象对同一消息做出响应的能力，但响应的方式取决于发送消息的对象的实际类型。多态性主要通过虚函数实现。以下是使用虚函数实现多态性的步骤和示例：

### 2.1. 定义基类和虚函数

首先，你需要定义一个基类，并在其中声明至少一个虚函数。虚函数使用 `virtual` 关键字声明。

```cpp
class Shape {
public:
    virtual void draw() const = 0; // 纯虚函数，强制实现多态性
    virtual ~Shape() {} // 虚析构函数，确保派生类的析构函数被调用
};
```

### 2.2. 在派生类中重写虚函数

然后，在每个派生类中重写基类的虚函数。这允许每个类以自己的方式响应函数调用。

```cpp
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a circle." << std::endl;
    }
};

class Square : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a square." << std::endl;
    }
};
```

### 2.3. 使用基类指针或引用

创建派生类对象的基类指针或引用，通过这些指针或引用调用虚函数。

```cpp
Shape* shapes[] = {new Circle(), new Square()};
```

### 2.4. 调用虚函数

通过基类指针或引用调用虚函数，实际调用的是对象实际类型的函数实现。

```cpp
for (const Shape* shape : shapes) {
    shape->draw(); // 根据对象的实际类型调用相应的 draw 函数
}
```

### 2.5. 释放资源

如果使用动态分配（`new`），不要忘记释放内存。如果基类有一个虚析构函数，那么通过基类指针删除派生类对象时，将正确地调用派生类的析构函数。

```cpp
for (auto* shape : shapes) {
    delete shape;
}
```

### 2.6. 示例代码

```cpp
#include <iostream>
#include <vector>

// 基类
class Shape {
public:
    virtual void draw() const = 0; // 纯虚函数
    virtual ~Shape() {} // 虚析构函数
};

// 派生类
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a circle." << std::endl;
    }
};

class Square : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a square." << std::endl;
    }
};

int main() {
    std::vector<Shape*> shapes;
    shapes.push_back(new Circle());
    shapes.push_back(new Square());

    for (Shape* shape : shapes) {
        shape->draw(); // 多态性：调用对象实际类型的 draw 函数
    }

    // 清理资源
    for (Shape* shape : shapes) {
        delete shape;
    }

    return 0;
}
```

在这个示例中，`Shape` 类是一个抽象基类，它声明了一个纯虚函数 `draw`。`Circle` 和 `Square` 类是 `Shape` 的具体实现，它们重写了 `draw` 函数。通过基类指针数组 `shapes` 存储派生类对象的指针，然后在循环中调用 `draw` 函数，展示了多态性的行为。每个对象调用其实际类型的 `draw` 函数，而不是指针静态类型的函数。

## 3.在C++中，虚函数和纯虚函数有什么区别？

在 C++ 中，虚函数和纯虚函数都是用来实现多态性的，但它们之间存在一些关键区别：

1. **定义方式**：
   - 虚函数：使用 `virtual` 关键字声明，可以有实现，也可以没有（即只有声明）。
   - 纯虚函数：使用 `virtual` 关键字声明，并在函数声明末尾加上 `= 0`，必须没有实现。

2. **实现**：
   - 虚函数：可以在基类中提供默认实现，派生类可以选择重写它。
   - 纯虚函数：没有实现，派生类必须提供实现，否则派生类也会变成抽象类。

3. **抽象类**：
   - 虚函数：基类中可以包含虚函数，但即使包含虚函数的类也不一定是抽象类。
   - 纯虚函数：如果一个类包含至少一个纯虚函数，这个类就是抽象类，不能被实例化。

4. **多态性**：
   - 虚函数：允许在派生类中重写基类的行为，实现多态性。
   - 纯虚函数：强制派生类提供具体实现，以确保每个派生类都有其特定的行为。

5. **使用目的**：
   - 虚函数：用于定义接口，同时提供默认行为，允许派生类根据需要重写。
   - 纯虚函数：用于定义接口规范，确保派生类遵循接口，强制实现特定的行为。

6. **析构函数**：
   - 虚函数：虚析构函数用于确保通过基类指针删除派生类对象时，调用正确的析构函数。
   - 纯虚函数：通常不用于析构函数，但技术上可以声明析构函数为纯虚函数（不推荐）。

### 示例

```cpp
class Base {
public:
    virtual void doSomething() {
        std::cout << "Base implementation" << std::endl;
    }
    virtual ~Base() {} // 虚析构函数
};

class Derived : public Base {
public:
    void doSomething() override {
        std::cout << "Derived implementation" << std::endl;
    }
};

class AbstractBase {
public:
    virtual void pureVirtualFunction() = 0; // 纯虚函数
};

// AbstractBase obj; // 错误：不能实例化抽象类
```

在这个示例中，`Base` 类中的 `doSomething` 是一个虚函数，可以在 `Derived` 类中被重写。`Base` 类的析构函数是一个虚析构函数。`AbstractBase` 类包含一个纯虚函数 `pureVirtualFunction`，使其成为一个抽象类，不能被直接实例化。

理解虚函数和纯虚函数的区别对于设计灵活且可扩展的 C++ 程序非常重要。

## 4.能否给我一个使用虚继承解决菱形继承问题的C++代码示例？

当使用传统的多重继承时，可能会出现菱形继承问题，也称为钻石继承。在这种情况下，一个类（C）同时从两个类（A1 和 A2）继承，而这两个类又从同一个基类（B）继承。这会导致基类 B 的成员在类 C 中出现两次，从而产生歧义。

虚继承可以用来解决这个问题，它确保了基类 B 的成员在派生类 C 中只有一个副本。以下是使用虚继承解决菱形继承问题的 C++ 代码示例：

```cpp
#include <iostream>

// 基类 B
class B {
public:
    B() { std::cout << "B's constructor called." << std::endl; }
    virtual ~B() { std::cout << "B's destructor called." << std::endl; }
    void functionB() { std::cout << "Function in B" << std::endl; }
};

// 中间类 A1 和 A2，都虚继承自 B
class A1 : virtual public B {
public:
    A1() { std::cout << "A1's constructor called." << std::endl; }
    ~A1() { std::cout << "A1's destructor called." << std::endl; }
    void functionA1() { std::cout << "Function in A1" << std::endl; }
};

class A2 : virtual public B {
public:
    A2() { std::cout << "A2's constructor called." << std::endl; }
    ~A2() { std::cout << "A2's destructor called." << std::endl; }
    void functionA2() { std::cout << "Function in A2" << std::endl; }
};

// 派生类 C，继承自 A1 和 A2，它们都虚继承自 B
class C : public A1, public A2 {
public:
    C() { std::cout << "C's constructor called." << std::endl; }
    ~C() { std::cout << "C's destructor called." << std::endl; }
    void functionC() { std::cout << "Function in C" << std::endl; }
};

int main() {
    C c; // 创建 C 的对象，只会调用一次 B 的构造函数和析构函数

    c.functionB(); // 调用 B 中的函数
    c.functionA1(); // 调用 A1 中的函数
    c.functionA2(); // 调用 A2 中的函数;
    c.functionC(); // 调用 C 中的函数

    return 0;
}
```

在这个示例中：

- 类 `B` 是一个基类，包含一个成员函数 `functionB`。
- 类 `A1` 和 `A2` 都通过虚继承从 `B` 继承，这意味着 `B` 的成员在 `A1` 和 `A2` 中只会有一个副本。
- 类 `C` 同时继承自 `A1` 和 `A2`。由于 `A1` 和 `A2` 是通过虚继承从 `B` 继承的，`C` 中不会出现 `B` 的重复成员。
- 在 `main` 函数中，创建 `C` 的对象时，`B` 的构造函数和析构函数只会被调用一次，这展示了虚继承解决了菱形继承问题。

使用虚继承可以避免对象中出现基类成员的多个副本，是处理复杂多重继承关系的有效方法。

## 5.如果我想在派生类中调用基类的虚函数，但是不想让基类成为抽象类，我该怎么做？

如果你想在派生类中调用基类的虚函数，但又不想让基类成为抽象类，你可以简单地在基类中提供一个虚函数的定义，而不是声明它为纯虚函数。这样，基类就不是抽象类，可以被实例化，同时派生类也可以重写这个虚函数。

以下是如何做到这一点的示例：

```cpp
#include <iostream>

// 基类
class Base {
public:
    // 虚函数，不是纯虚函数
    virtual void display() {
        std::cout << "Display in Base" << std::endl;
    }
    
    virtual ~Base() {} // 提供虚析构函数
};

// 派生类
class Derived : public Base {
public:
    // 重写基类的虚函数
    void display() override {
        std::cout << "Display in Derived" << std::endl;
    }
};

int main() {
    Base* basePtr = new Derived(); // 基类指针指向派生类对象
    basePtr->display(); // 调用派生类的 display 函数，展示多态性

    // 在派生类中调用基类的虚函数
    Base& baseRef = *basePtr;
    baseRef.display(); // 调用基类的 display 函数

    delete basePtr;
    return 0;
}
```

在这个示例中：

- `Base` 类包含一个虚函数 `display()`，它有一个具体的实现。这使得 `Base` 类可以被实例化，并且 `display()` 函数可以在对象上直接调用。
- `Derived` 类继承自 `Base` 并重写了 `display()` 函数，提供了自己的实现。
- 在 `main()` 函数中，我们创建了一个 `Derived` 类型的指针 `basePtr`，它指向 `Derived` 的实例，并通过基类指针调用 `display()` 函数来展示多态性。
- 然后，我们演示了如何在派生类的对象中通过基类引用调用基类的 `display()` 函数。

通过这种方式，你可以保留基类的对象实例化能力，同时在派生类中重写虚函数以展示不同的行为。如果派生类没有重写基类的虚函数，那么通过派生类对象调用该函数将执行基类中的版本。

## 6.常见面试问题

C++ 中的虚函数（`virtual`）是实现多态性的关键机制之一。虽然虚函数非常有用，但在使用过程中可能会遇到一些问题。以下是一些常见的问题以及它们的解决方案：

### 6.1. 忘记虚析构函数

**问题**：如果基类没有虚析构函数，通过基类指针删除派生类对象时，只调用派生类的析构函数，不会调用基类的析构函数，导致资源泄漏。
**解决方案**：在基类中声明一个虚析构函数。

```cpp
class Base {
public:
    virtual ~Base() {
        // 清理资源
    }
};
```

### 6.2. 覆盖虚函数但未使用 `override`

**问题**：在派生类中覆盖虚函数时，如果忘记了 `override` 关键字，而函数签名与基类中的不完全匹配，编译器可能不会报错，导致潜在的bug。
**解决方案**：使用 `override` 关键字明确你的目的。

```cpp
class Derived : public Base {
    void foo() override; // 如果签名不匹配，编译器会报错
};
```

### 6.3. 忘记虚函数的实现

**问题**：声明了虚函数但没有在基类或派生类中提供实现，导致链接错误。
**解决方案**：确保虚函数在基类或派生类中有定义。

```cpp
class Base {
public:
    virtual void bar();
};

void Base::bar() {
    // 实现
}
```

### 6.4. 非虚函数与虚函数的混淆

**问题**：在派生类中声明了一个与基类中虚函数同名但签名不同的函数，导致调用时出现混淆。
**解决方案**：确保派生类中的函数覆盖是有意为之，并且签名完全匹配。

```cpp
class Base {
public:
    virtual void baz(int x);
};

class Derived : public Base {
public:
    void baz(int x) override; // 正确覆盖
};
```

### 6.5. 私有虚函数

**问题**：在基类中将虚函数声明为私有，派生类无法访问或覆盖它。
**解决方案**：确保虚函数在基类中是公共（public）或受保护（protected）的。

```cpp
class Base {
public:
    virtual void foo(); // 公共访问权限
};
```

### 6.6. 多重继承中的虚函数冲突

**问题**：在多重继承中，两个基类有相同名称的虚函数，派生类需要明确覆盖哪个基类的函数。
**解决方案**：使用作用域运算符（`::`）来指定要覆盖的基类中的虚函数。

```cpp
class Base1 {
public:
    virtual void func();
};

class Base2 {
public:
    virtual void func();
};

class Derived : public Base1, public Base2 {
public:
    void Base1::func() override; // 覆盖 Base1 中的 func
    void Base2::func() override; // 覆盖 Base2 中的 func
};
```

### 6.7. 虚函数与模板

**问题**：在模板类中使用虚函数可能导致编译器错误或警告。
**解决方案**：确保模板类中的虚函数声明正确，并且在模板实例化时遵循虚函数的规则。

```cpp
template <typename T>
class TemplateBase {
public:
    virtual void templateFunc(T value) = 0; // 纯虚函数
};
```

### 6.8. 虚函数与友元

**问题**：虚函数不能声明为友元函数，因为它们需要通过虚表（vtable）进行调用，而友元函数不具备这种机制。
**解决方案**：避免将友元函数声明为虚函数。

理解并解决这些问题有助于你更有效地使用虚函数，并避免在 C++ 程序中引入难以发现的错误。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/img/wechat.jpg width=60% />
