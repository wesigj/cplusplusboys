# C++面试基础系列-polymorphic

[TOC]

## Overview

- C++ 支持面向对象编程，包括类（Class）和对象（Object）、继承（Inheritance）、封装（Encapsulation）和多态（Polymorphism）。
- C 语言不支持面向对象编程。

## 1.polymorphic多态性

在C++中，多态性（Polymorphism）是一个核心概念，它允许我们通过基类的接口来使用派生类的对象。多态性使得代码更加灵活和可扩展，主要有以下几种形式：

1. **编译时多态（静态绑定）**：通过函数重载和运算符重载实现，它们在编译时就已经确定。

2. **运行时多态（动态绑定）**：通过虚函数实现，调用哪个函数的实现是在运行时根据对象的实际类型来确定的。

## 2.编译时多态的实现

编译时多态，也称为静态多态或早绑定（Early Binding），是在编译期间确定函数调用的机制。在C++中，编译时多态主要通过以下几种方式实现：

1. **函数重载（Function Overloading）**：
   - 允许在同一个作用域内定义多个同名函数，只要它们的参数列表不同（参数类型、数量或顺序不同）。

2. **运算符重载（Operator Overloading）**：
   - 允许为自定义类型定义或修改已有运算符的行为。

3. **模板（Templates）**：
   - 允许创建泛型类和函数，它们可以在编译时根据模板参数实例化出不同类型的具体实现。

### 示例代码

#### 函数重载示例

```cpp
#include <iostream>

// 函数重载示例
void print(int num) {
    std::cout << "Integer: " << num << std::endl;
}

void print(double num) {
    std::cout << "Double: " << num << std::endl;
}

int main() {
    print(10);    // 调用第一个print函数
    print(3.14);  // 调用第二个print函数
    return 0;
}
```

在这个例子中，`print` 函数被重载了两次，一次接受 `int` 类型的参数，另一次接受 `double` 类型的参数。编译器根据传递给 `print` 函数的参数类型来决定调用哪个函数。

#### 运算符重载示例：

```cpp
#include <iostream>

class Point {
public:
    int x, y;

    Point(int x, int y) : x(x), y(y) {}

    // 运算符重载，实现点的加法
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
};

int main() {
    Point p1(1, 2);
    Point p2(3, 4);
    Point p3 = p1 + p2; // 使用重载的 + 运算符
    std::cout << "p3: (" << p3.x << ", " << p3.y << ")" << std::endl;
    return 0;
}
```

在这个例子中，我们为 `Point` 类重载了 `+` 运算符，使其能够实现两个点的加法。编译器在编译时根据操作数的类型确定使用哪个 `+` 运算符。

#### 模板示例：

```cpp
#include <iostream>

// 模板类示例
template <typename T>
class Container {
private:
    T value;

public:
    Container(T val) : value(val) {}

    T getValue() const {
        return value;
    }
};

int main() {
    Container<int> intContainer(10);
    Container<double> doubleContainer(3.14);

    std::cout << "intContainer value: " << intContainer.getValue() << std::endl;
    std::cout << "doubleContainer value: " << doubleContainer.getValue() << std::endl;
    return 0;
}
```

在这个例子中，我们定义了一个模板类 `Container`，它可以存储任何类型的值。编译器在编译时根据模板参数的类型来实例化 `Container` 类的不同版本。

编译时多态的优点是调用效率高，因为它在编译期间就已经确定了调用的具体函数或方法。然而，它的局限性在于只能在编译时知道所有可能的调用类型。

## 3.运行时多态的实现

- **虚函数（Virtual Functions）**：在基类中使用 `virtual` 关键字声明的函数，可以被子类重写（Override）。
- **虚析构函数（Virtual Destructor）**：确保通过基类指针删除派生类对象时，能够调用到正确的析构函数。
- **动态类型识别（Dynamic Cast）**：在运行时检查对象的类型，并在需要时将基类指针转换为派生类指针。

### 示例代码

```cpp
#include <iostream>

// 基类
class Animal {
public:
    // 虚函数，用于模拟动物的声音
    virtual void speak() const {
        std::cout << "Some animal sound" << std::endl;
    }

    // 虚析构函数
    virtual ~Animal() {}
};

// 派生类 Dog
class Dog : public Animal {
public:
    // 重写基类的虚函数
    void speak() const override {
        std::cout << "Woof! Woof!" << std::endl;
    }
};

// 派生类 Cat
class Cat : public Animal {
public:
    // 重写基类的虚函数
    void speak() const override {
        std::cout << "Meow! Meow!" << std::endl;
    }
};

int main() {
    // 创建对象
    Animal* animal1 = new Dog();
    Animal* animal2 = new Cat();

    // 多态性：通过基类指针调用派生类的方法
    animal1->speak(); // 输出: Woof! Woof!
    animal2->speak(); // 输出: Meow! Meow!

    // 清理
    delete animal1;
    delete animal2;

    return 0;
}
```

在这个例子中，`Animal` 是一个基类，它有一个虚函数 `speak`。`Dog` 和 `Cat` 是 `Animal` 的派生类，它们重写了 `speak` 函数。在 `main` 函数中，我们创建了 `Dog` 和 `Cat` 的对象，并通过基类指针 `Animal*` 调用了 `speak` 函数。由于多态性，即使我们通过基类指针调用，实际执行的也是派生类中重写的 `speak` 函数。

这种通过基类接口来操作不同派生类对象的能力，就是多态性的体现。它使得我们可以编写更加通用的代码，而不必担心对象的具体类型。

## 4.编译时多态的优点

在实际开发中，选择使用编译时多态而不是运行时多态的原因通常包括以下几点：

1. **性能**：
   - 编译时多态（如函数重载和模板）通常比运行时多态（如虚函数）具有更高的性能。这是因为编译时多态在编译期间就已经确定了函数调用，没有运行时的类型检查和函数查找开销。

2. **类型安全**：
   - 编译时多态提供了更强的类型安全保证。编译器可以在编译期间检查类型错误和不一致性，从而避免了许多运行时错误。

3. **代码清晰和可维护性**：
   - 函数重载和模板可以提供更清晰的代码结构，使得代码更容易理解和维护。开发者可以直观地看到所有重载的函数或模板实例化，而不需要深入到类的继承层次中。

4. **避免虚函数的限制**：
   - 运行时多态依赖于虚函数，但虚函数有一些限制，例如不能是静态的，不能是构造函数，也不能是友元函数。在这些情况下，编译时多态是更合适的选择。

5. **避免虚函数表的开销**：
   - 运行时多态需要使用虚函数表（vtable）来实现，这会带来一定的内存和性能开销。对于小型对象或性能敏感的应用，这可能是不可接受的。

6. **静态链接**：
   - 编译时多态不依赖于运行时的动态链接，这使得程序的部署和链接更加简单和可靠。

7. **编译时决策**：
   - 在某些情况下，我们可能希望在编译时就做出某些决策，例如根据编译时常量来选择不同的实现。编译时多态允许我们根据模板参数或其他编译时已知信息来实现这一点。

8. **避免动态绑定的不确定性**：
   - 运行时多态的动态绑定可能会导致一些不确定性，例如当基类指针或引用指向的对象类型未知时。编译时多态可以消除这种不确定性，因为所有决策都是在编译时做出的。

9. **特定场景的需求**：
   - 在某些特定场景下，如元编程或编译时计算，编译时多态是实现这些需求的唯一或最佳方式。

10. **避免运行时错误**：
    - 运行时多态可能会因为类型不匹配或其他问题导致运行时错误。编译时多态可以在编译期间捕捉这些错误，从而提高程序的稳定性。

总之，编译时多态和运行时多态各有优势和适用场景。在实际开发中，开发者需要根据具体需求、性能要求、代码可维护性和其他因素来选择最合适的方法。在某些情况下，两者也可以结合使用，以实现最佳的编程效果。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
