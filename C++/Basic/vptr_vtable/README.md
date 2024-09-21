# C++面试基础系列-C++虚函数vptr_vtable

[TOC]

## Overview

## 1.简单介绍

在 C++ 中，虚函数的实现细节涉及到虚表指针（`vptr`）和虚表（`vtable`）。这些是编译器用来实现运行时多态性的机制。以下是关于 `vptr` 和 `vtable` 的一些关键点：

### 1.1.vptr（虚表指针）

- `vptr` 是一个指针，存储在对象的内存布局中，指向该对象的虚表。
- 每个包含虚函数的类都有自己的虚表。
- `vptr` 的位置和大小可能因编译器而异，但通常位于对象的内存布局的开始处。
- `vptr` 的存在是透明的，程序员不需要（也不应该）直接操作它。

### 1.2.vtable（虚表）

- `vtable` 是一个表格，包含了类中所有虚函数的地址。
- 每个类都有自己的 `vtable`，它包含了该类所有虚函数的指针。
- 当你调用一个虚函数时，程序会查找对象的 `vptr` 指向的 `vtable`，然后在表中查找正确的函数地址来执行。

### 1.3.工作原理

1. **构造对象**：当创建一个对象时，编译器会在对象的内存中安排 `vptr` 和类的成员变量。
2. **调用虚函数**：当通过对象调用虚函数时，程序会先访问对象的 `vptr`，然后查找 `vtable` 中对应的函数地址。
3. **多态性**：如果对象是派生类实例，但通过基类指针或引用调用，`vtable` 会确保调用正确的函数实现，即使基类指针或引用的静态类型不知道实际对象的动态类型。

### 1.4.示例

```cpp
class Base {
public:
    virtual void func() { std::cout << "Base::func" << std::endl; }
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void func() override { std::cout << "Derived::func" << std::endl; }
};

int main() {
    Base* basePtr = new Derived();
    basePtr->func(); // 调用 Derived::func，展示了多态性

    delete basePtr;
    return 0;
}
```

在这个示例中，`Base` 类和 `Derived` 类都有自己的 `vtable`。`Derived` 类的 `vtable` 覆盖了 `Base` 类的 `vtable` 中的 `func` 条目。当通过 `Base` 类型的指针调用 `func` 时，实际调用的是 `Derived` 类的 `func` 函数。

### 1.5.注意事项

- 不要直接操作 `vptr` 或 `vtable`，它们是编译器实现细节。
- 虚函数的使用可能会影响程序的性能，因为它们引入了间接调用。
- 当类中有虚函数时，复制或移动操作可能需要特别处理，以确保 `vptr` 正确设置。

`vptr` 和 `vtable` 是 C++ 实现多态性的核心机制，它们使得程序能够在运行时确定调用哪个函数实现。

在 C++ 中，`vptr`（虚表指针）和 `vtable`（虚表）是实现多态性机制的底层技术。下面将更详细地介绍它们的工作原理和相关概念：

## 2.强化认识

### 2.1.vtable（虚表）

1. **结构**：`vtable` 是一个或多个函数指针的数组。每个包含虚函数的类都有自己的 `vtable`。

2. **布局**：`vtable` 通常按照类中虚函数的声明顺序排列，每个条目对应一个虚函数的地址。

3. **继承**：当一个类继承自另一个类时，它的 `vtable` 会包含基类 `vtable` 的引用以及它自己新增的虚函数的地址。

4. **动态绑定**：`vtable` 用于在运行时确定应该调用哪个函数。当调用一个虚函数时，程序会查找对象的 `vptr` 指向的 `vtable`，然后根据虚函数的声明顺序找到对应的函数地址。

5. **例子**：

   ```cpp
   class Base {
   public:
       virtual void func1() { std::cout << "Base func1" << std::endl; }
       virtual void func2() { std::cout << "Base func2" << std::endl; }
   };
   ```

   在这个例子中，`Base` 类的 `vtable` 可能包含两个条目，每个条目指向 `func1` 和 `func2` 的实现。

### 2.2.vptr（虚表指针）

1. **存储**：`vptr` 是一个指针，通常存储在对象的内存布局的最前面。

2. **作用**：`vptr` 指向对象的 `vtable`，它用于访问类的虚函数。

3. **隐藏性**：`vptr` 对程序员是透明的，由编译器自动管理。

4. **继承**：在多重继承情况下，对象可能包含多个 `vptr`，每个 `vptr` 对应一个基类的 `vtable`。

5. **例子**：

   ```cpp
   Base obj;
   ```

   在这个例子中，`obj` 的内存布局中会包含一个指向 `Base` 类 `vtable` 的 `vptr`。

### 2.3.多态性实现

1. **基类指针**：当使用基类指针指向派生类对象时，通过基类指针调用虚函数，实际调用的是派生类版本的函数。

2. **构造和析构**：在构造派生类对象时，会先构造基类部分，设置 `vptr` 指向正确的 `vtable`，然后再构造派生类新增的部分。在析构时，顺序相反。

3. **例子**：

   ```cpp
   Base* basePtr = new Derived();
   basePtr->func1(); // 调用 Derived::func1
   delete basePtr;
   ```

   在这个例子中，通过 `Base` 类型的指针 `basePtr` 调用 `func1`，实际执行的是 `Derived` 类重写的 `func1` 函数。

### 2.4.性能考虑

1. **间接调用**：由于虚函数的调用需要通过 `vptr` 和 `vtable`，可能会引入一些性能开销。

2. **优化**：现代编译器和优化器会使用诸如内联函数、虚函数表优化等技术来减少这些开销。

### 2.5.内存布局

1. **对象内存**：对象的内存布局首先包含 `vptr`，然后是类的成员变量。

2. **多重继承**：在多重继承情况下，对象的内存布局可能包含多个 `vptr`，每个对应一个基类的 `vtable`。

### 2.6.注意事项

- 虚函数不能是静态的（`static`）或常量（`const`）成员函数。
- 虚函数的声明必须使用 `virtual` 关键字，而重写虚函数时可以使用 `override` 关键字来提高代码可读性。
- 理解 `vptr` 和 `vtable` 有助于深入学习 C++ 的内存管理和多态性机制。

通过深入理解 `vptr` 和 `vtable`，你可以更好地掌握 C++ 的多态性机制，编写出更高效、更安全的面向对象代码。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
