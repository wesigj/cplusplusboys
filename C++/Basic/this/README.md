# C++面试基础系列-this指针

[TOC]

## Overview

## 1.this指针

在 C++ 中，`this` 指针是一个特殊的指针，它在每个非静态成员函数中自动可用。`this` 指向调用成员函数的当前对象实例。以下是 `this` 指针的一些关键特性和用法：

### 1.1.特性

1. **隐式存在**：在成员函数中，`this` 指针隐式地可用，不需要定义或声明。

2. **指向当前对象**：`this` 指针指向调用成员函数的对象。

3. **类型为当前类的指针**：`this` 的类型是成员函数所在类的指针类型。

4. **在静态成员函数中不可用**：由于静态成员不属于任何对象实例，因此在静态成员函数中 `this` 指针不可用。

5. **用于区分成员变量和局部变量**：当局部变量名与成员变量名相同时，`this` 可以用来区分它们。

### 1.2.用法

1. **访问成员变量**

   ```cpp
   class MyClass {
       int value;
   public:
       void setValue(int v) {
           this->value = v; // 使用 this 指针访问成员变量
       }
   };
   ```

2. **调用其他成员函数**：

   ```cpp
   class MyClass {
       void doSomething() {
           // ...
       }
   public:
       void execute() {
           this->doSomething(); // 使用 this 指针调用另一个成员函数
       }
   };
   ```

3. **在构造函数中使用**：

   ```cpp
   class MyClass {
   public:
       MyClass(int v) {
           this->setValue(v); // 在构造函数中使用 this 指针调用成员函数
       }
       void setValue(int v) {
           // ...
       }
   };
   ```

4. **实现赋值运算符**：

   ```cpp
   class MyClass {
       int value;
   public:
       MyClass& operator=(const MyClass& other) {
           if (this != &other) { // 检查自赋值
               this->value = other.value;
           }
           return *this; // 返回当前对象的引用
       }
   };
   ```

5. **用于多态**：
   当涉及到多态时，`this` 指针可以被转换为派生类的指针：

   ```cpp
   class Base {
   public:
       virtual ~Base() {}
   };
   
   class Derived : public Base {
       int extraValue;
   public:
       void process() {
           // 安全地将 this 转换为 Derived 类型的指针
           Derived* d = dynamic_cast<Derived*>(this);
           // 使用 d 指针
       }
   };
   ```

6. **在 lambda 表达式中使用**：
   在成员函数中定义的 lambda 可以捕获 `this` 指针：

   ```cpp
   class MyClass {
   public:
       void execute() {
           int value = 10;
           [=](){ // 通过值捕获 this 指针
               doSomething();
           }();
       }
       void doSomething() {
           // ...
       }
   };
   ```

7. **避免对象复制**：
   使用 `this` 指针实现深拷贝或浅拷贝逻辑。

### 1.3.注意事项

- 应谨慎使用 `this` 指针，避免不必要的使用，因为它可能会使代码的意图不够明确。
- 在多态情况下，使用 `dynamic_cast` 转换 `this` 指针时，只有在含有虚函数的类中才有效。
- 在构造函数和析构函数中也可以使用 `this` 指针，但要确保使用方式是安全的，因为这些特殊时期对象可能未完全构造或正在被销毁。

`this` 指针是 C++ 中一个强大的特性，正确使用它可以提高代码的灵活性和表达能力。

当然可以。在 C++ 中，多态性通常通过虚函数实现，而 `this` 指针在多态类中可以用来调用成员函数或访问成员变量，尤其是在需要明确对象类型时。以下是一个使用 `this` 指针的多态类的示例：

## 2.使用 'this' 指针的多态类的示例

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// 基类
class Animal {
public:
    virtual ~Animal() {}

    // 虚函数，用于多态
    virtual void speak() const {
        std::cout << "Some generic animal sound" << std::endl;
    }

    // 使用 this 指针调用其他成员函数
    void performAction() {
        std::cout << "The animal is performing an action." << std::endl;
        this->speak(); // 调用虚函数
    }
};

// 派生类
class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "Woof! Woof!" << std::endl;
    }
};

class Cat : public Animal {
public:
    void speak() const override {
        std::cout << "Meow! Meow!" << std::endl;
    }
};

// 使用多态和 this 指针
void makeAnimalsSpeak(const std::vector<std::shared_ptr<Animal>>& animals) {
    for (const auto& animal : animals) {
        // 通过 this 指针明确调用 speak 函数
        ((Animal*)this)->speak(); // 错误的使用示例，仅用于说明 this 的作用
        animal->speak(); // 正确的多态调用
    }
}

int main() {
    std::vector<std::shared_ptr<Animal>> animals;
    animals.push_back(std::make_shared<Dog>());
    animals.push_back(std::make_shared<Cat>());

    makeAnimalsSpeak(animals);

    return 0;
}
```

在这个示例中：

- `Animal` 是一个基类，有一个虚函数 `speak()` 和一个非虚函数 `performAction()`。`performAction()` 使用 `this` 指针调用 `speak()`，展示了如何在类内部使用 `this` 指针调用成员函数。
- `Dog` 和 `Cat` 是从 `Animal` 派生的子类，它们重写了 `speak()` 函数，提供了具体的实现。
- `makeAnimalsSpeak()` 函数接受一个 `Animal` 指针的 `std::vector`，并调用每个动物的 `speak()` 函数。这里展示了如何通过多态性使用 `this` 指针。注意，示例中的 `((Animal*)this)->speak();` 是错误的用法，仅用于说明 `this` 的作用。正确的用法是 `animal->speak();`，它利用了多态性调用正确的 `speak()` 版本。
- 在 `main()` 函数中，我们创建了一个 `Animal` 对象的向量，其中包括 `Dog` 和 `Cat` 的实例，并调用 `makeAnimalsSpeak()` 来演示多态性。

这个示例展示了如何在多态上下文中使用 `this` 指针，以及如何在派生类中重写虚函数来实现不同行为。

## 3.在C++中，指针和对象本身有什么区别？

在 C++ 中，指针和对象本身有几个关键的区别：

1. **存储内容**：
   - 对象：对象是实际的数据实体，它占用内存并包含数据和可能的行为（通过成员函数）。
   - 指针：指针是一个变量，它存储的是另一个对象的内存地址。

2. **内存占用**：
   - 对象：对象的大小通常比指针大，因为它包含了实际的数据。
   - 指针：指针的大小在 32 位系统上通常是 4 字节，在 64 位系统上是 8 字节，与它所指向的对象大小无关。

3. **访问数据**：
   - 对象：可以直接访问对象的成员变量和函数。
   - 指针：需要使用解引用操作符（*）来访问指针指向的对象的成员。

4. **生命周期**：
   - 对象：对象有自己的生命周期，它可能在栈上自动创建和销毁，或在堆上通过 `new` 和 `delete` 进行管理。
   - 指针：指针本身有自己的生命周期，但它指向的对象可能有不同的生命周期。

5. **别名**：
   - 对象：对象通常只有一个标识符。
   - 指针：可以通过多个指针引用同一个对象（别名），这可能导致复杂的内存管理问题。

6. **可变性**：
   - 对象：对象的地址在声明后通常不会改变（除非使用 `std::move`）。
   - 指针：指针的值（即它所指向的地址）可以在运行时改变。

7. **数组和指针**：
   - 对象：不能直接将对象视为数组来处理。
   - 指针：指针可以进行算术运算（如加法和减法），这使得指针可以像数组一样使用。

8. **传递性能**：
   - 对象：按值传递对象可能会涉及复制构造函数，这可能代价昂贵。
   - 指针：指针传递的是地址，通常是很小的数据量，开销较小。

9. **安全性**：
   - 对象：使用对象通常更安全，因为它们不允许悬空或未定义的状态。
   - 指针：指针需要小心管理，不当使用可能导致悬空指针、野指针或内存泄漏。

10. **语法**：
    - 对象：使用变量名直接访问。
    - 指针：需要通过 `->` 运算符来访问指针指向的对象的成员。

理解指针和对象之间的区别对于编写有效和安全的 C++ 程序至关重要。指针提供了强大的灵活性，但也需要更多的注意力来确保正确管理内存和对象的生命周期。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
