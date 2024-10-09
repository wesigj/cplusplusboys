# C++11 25-默认函数删除 =default =delete

- [C++11 25-默认函数删除 =default =delete](#c11-25-默认函数删除-default-delete)
  - [Overview](#overview)
  - [1.默认函数删除 =default =delete](#1默认函数删除-default-delete)
    - [1.1.`= default`](#11-default)
    - [1.2.`= delete`](#12-delete)
    - [1.3.组合使用 `= default` 和 `= delete`](#13组合使用--default-和--delete)
  - [2.在 C++ 中，除了 =default 和 =delete，还有哪些方式可以控制成员函数的默认实现？](#2在-c-中除了-default-和-delete还有哪些方式可以控制成员函数的默认实现)
  - [3.如果我想为类的成员函数提供默认实现，但是又想禁止某些成员函数的默认实现，应该如何操作？](#3如果我想为类的成员函数提供默认实现但是又想禁止某些成员函数的默认实现应该如何操作)
  - [4.在C++中，如何通过=default和=delete来优化类的内存管理？](#4在c中如何通过default和delete来优化类的内存管理)
  - [关于作者](#关于作者)

## Overview

---

## 1.默认函数删除 =default =delete

在 C++ 中，`= delete` 和 `= default` 是两个不同的概念，它们都与类的成员函数的显式定义有关。

### 1.1.`= default`

`= default` 用于显式地告诉编译器为成员函数生成默认实现。这通常用于那些编译器默认不会自动生成的成员函数，比如自定义类型的拷贝构造函数和拷贝赋值运算符。

```cpp
class MyClass {
public:
    MyClass() = default; // 使用编译器生成的默认构造函数
    MyClass(const MyClass&) = default; // 使用编译器生成的拷贝构造函数
    MyClass& operator=(const MyClass&) = default; // 使用编译器生成的拷贝赋值运算符
    // ...
};
```

在 C++11 之前，如果一个类没有显式定义拷贝构造函数和拷贝赋值运算符，编译器会默认生成它们。但是，如果你定义了析构函数或其他特殊成员函数，编译器就不会再自动生成这些函数。在 C++11 及以后的版本中，你可以使用 `= default` 来显式地要求编译器生成默认实现。

### 1.2.`= delete`

`= delete` 用于显式地禁止编译器生成某个特定的成员函数。这通常用于防止调用某些不应该被使用的函数，比如自定义类型的拷贝构造函数和拷贝赋值运算符。

```cpp
class MyClass {
public:
    MyClass() = default;
    MyClass(const MyClass&) = delete; // 禁止拷贝构造
    MyClass& operator=(const MyClass&) = delete; // 禁止拷贝赋值
    // ...
};
```

使用 `= delete` 可以防止编译器生成默认的成员函数实现，并且如果代码中尝试调用这些被删除的函数，编译器会报错。

### 1.3.组合使用 `= default` 和 `= delete`

有时，你可能需要为某些特定的成员函数提供默认实现，同时禁止其他成员函数。你可以在同一个类中组合使用 `= default` 和 `= delete`：

```cpp
class MyClass {
public:
    MyClass() = default;
    MyClass(const MyClass&) = default; // 允许拷贝构造
    MyClass& operator=(const MyClass&) = delete; // 禁止拷贝赋值
    // ...
};
```

在这个例子中，`MyClass` 允许拷贝构造，但禁止拷贝赋值。

这两种特性在现代 C++ 中非常有用，它们提供了对类成员函数更细粒度的控制。

## 2.在 C++ 中，除了 =default 和 =delete，还有哪些方式可以控制成员函数的默认实现？

在 C++ 中，除了使用 `= default` 和 `= delete` 来控制成员函数的默认实现之外，还有其他几种方式可以影响或控制成员函数的行为：

1. **显式定义成员函数**：
   最直接的方式是显式地定义成员函数。这会完全替代编译器提供的默认实现。

   ```cpp
   class MyClass {
   public:
       MyClass() {
           // 自定义构造函数
       }
       ~MyClass() {
           // 自定义析构函数
       }
       MyClass(const MyClass& other) {
           // 自定义拷贝构造函数
       }
       MyClass& operator=(const MyClass& other) {
           // 自定义拷贝赋值运算符
           return *this;
       }
   };
   ```

2. **继承**：
   如果一个类继承自另一个类，并且没有重新定义某个成员函数，那么它将继承基类中的实现。

   ```cpp
   class Base {
   public:
       virtual void func() const {
           // 基类的实现
       }
   };

   class Derived : public Base {
   public:
       // 继承了 Base 类的 func 成员函数
   };
   ```

3. **使用模板**：
   通过模板编程，可以在编译时根据模板参数生成成员函数的实现。

   ```cpp
   template <typename T>
   class MyClass {
   public:
       void func() {
           // T 类型的成员函数实现
       }
   };
   ```

4. **友元函数**：
   你可以定义一个非成员函数作为类的友元函数，这样它可以访问类的私有或受保护的成员。

   ```cpp
   class MyClass {
   friend void friendFunction(MyClass& obj);
   // ...
   };

   void friendFunction(MyClass& obj) {
       // 可以访问 MyClass 的私有成员
   }
   ```

5. **重写虚函数**：
   如果你的类继承自一个具有虚函数的基类，你可以重写这些虚函数来改变它们的行为。

   ```cpp
   class Base {
   public:
       virtual void func() const {
           // 基类的实现
       }
   };

   class Derived : public Base {
   public:
       void func() const override {
           // 重写基类的虚函数
       }
   };
   ```

6. **使用默认参数**：
   你可以在成员函数声明中提供默认参数，这会影响函数调用时的行为。

   ```cpp
   class MyClass {
   public:
       void func(int x = 10) const {
           // 使用默认参数的成员函数
       }
   };
   ```

7. **使用 constexpr**：
   使用 `constexpr` 可以定义在编译时计算的成员函数。

   ```cpp
   class MyClass {
   public:
       constexpr int getValue() const {
           return 42;
       }
   };
   ```

8. **使用静态成员函数**：
   静态成员函数不依赖于类实例，可以在没有类实例的情况下调用。

   ```cpp
   class MyClass {
   public:
       static int staticFunc() {
           return 42;
       }
   };
   ```

9. **使用 inline 函数**：
   使用 `inline` 关键字可以建议编译器在编译时将函数内联展开。

   ```cpp
   class MyClass {
   public:
       inline void inlineFunc() const {
           // 可能会被内联展开的成员函数
       }
   };
   ```

这些是控制成员函数默认实现的一些常见方法。每种方法都有其适用的场景和限制，选择合适的方法可以提高代码的灵活性和效率。

## 3.如果我想为类的成员函数提供默认实现，但是又想禁止某些成员函数的默认实现，应该如何操作？

如果你想要为类的成员函数提供默认实现，同时又想禁止某些成员函数的默认实现，你可以结合使用 `= default` 和 `= delete` 关键字。以下是如何操作的示例：

1. **为成员函数提供默认实现**：
   使用 `= default` 关键字来显式地要求编译器生成默认的构造函数、拷贝赋值运算符、移动构造函数、移动赋值运算符或析构函数。

   ```cpp
   class MyClass {
   public:
       // 默认构造函数
       MyClass() = default;
       // 默认拷贝构造函数
       MyClass(const MyClass&) = default;
       // 默认拷贝赋值运算符
       MyClass& operator=(const MyClass&) = default;
       // 默认移动构造函数
       MyClass(MyClass&&) = default;
       // 默认移动赋值运算符
       MyClass& operator=(MyClass&&) = default;
       // 默认析构函数
       ~MyClass() = default;
   };
   ```

2. **禁止某些成员函数的默认实现**：
   使用 `= delete` 关键字来显式地禁止编译器生成默认的构造函数、拷贝赋值运算符、移动构造函数、移动赋值运算符或析构函数。

   ```cpp
   class MyClass {
   public:
       // 默认构造函数
       MyClass() = default;
       // 禁止拷贝构造函数
       MyClass(const MyClass&) = delete;
       // 默认拷贝赋值运算符
       MyClass& operator=(const MyClass&) = default;
       // 禁止移动构造函数
       MyClass(MyClass&&) = delete;
       // 禁止移动赋值运算符
       MyClass& operator=(MyClass&&) = delete;
       // 默认析构函数
       ~MyClass() = default;
   };
   ```

3. **组合使用**：
   你可以在同一个类中组合使用 `= default` 和 `= delete` 来为某些成员函数提供默认实现，同时禁止其他成员函数的默认实现。

   ```cpp
   class MyClass {
   public:
       // 默认构造函数
       MyClass() = default;
       // 禁止拷贝构造函数
       MyClass(const MyClass&) = delete;
       // 禁止拷贝赋值运算符
       MyClass& operator=(const MyClass&) = delete;
       // 默认移动构造函数
       MyClass(MyClass&&) = default;
       // 默认移动赋值运算符
       MyClass& operator=(MyClass&&) = default;
       // 默认析构函数
       ~MyClass() = default;
   };
   ```

在这个例子中，`MyClass` 允许默认的构造、移动构造和移动赋值操作，但禁止了拷贝构造和拷贝赋值操作。

通过这种方式，你可以精确地控制类的成员函数的行为，确保类的行为符合你的设计意图。

## 4.在C++中，如何通过=default和=delete来优化类的内存管理？

在 C++ 中，`=default` 和 `=delete` 是两种用来控制成员函数默认实现的关键字。

1. **使用 `=default`**:
   - `=default` 关键字用于显式地要求编译器生成默认的特殊成员函数（如默认构造函数、拷贝构造函数、移动构造函数、拷贝赋值运算符、移动赋值运算符和析构函数）。这在类中显式定义了其他特殊成员函数时特别有用，因为它可以确保编译器提供默认行为。
   - 例如，如果你定义了一个自定义的析构函数，编译器不会再自动生成默认构造函数和拷贝赋值运算符，除非你显式地使用 `=default` 来要求它们。

2. **使用 `=delete`**:
   - `=delete` 关键字用于显式地禁止编译器生成默认的特殊成员函数。这通常用于那些不应该被复制或赋值的类，比如包含动态分配内存或其他资源的类。
   - 例如，如果你有一个管理资源的类，你可能不希望这个类的对象被复制，因为这会导致多重释放资源的问题。在这种情况下，你可以将拷贝构造函数和拷贝赋值运算符删除：`MyClass(const MyClass&) = delete;` `MyClass& operator=(const MyClass&) = delete;`

**优化内存管理**:

- **避免不必要的拷贝**：通过删除不需要的拷贝构造函数和拷贝赋值运算符，可以避免不必要的对象拷贝，从而节省内存和提高效率。
- **利用移动语义**：C++11 引入了移动语义，允许资源从即将销毁的对象转移到新对象，而不是进行拷贝。这可以通过定义移动构造函数和移动赋值运算符来实现，或者让编译器生成它们（如果你没有定义拷贝构造函数和拷贝赋值运算符）。
- **使用智能指针**：使用 `std::unique_ptr` 和 `std::shared_ptr` 等智能指针可以自动管理内存，避免内存泄漏，并提供更细粒度的控制。

**示例**:

```cpp
class ResourceManagingClass {
public:
    ResourceManagingClass() = default;
    ResourceManagingClass(const ResourceManagingClass&) = delete; // 禁止拷贝
    ResourceManagingClass& operator=(const ResourceManagingClass&) = delete; // 禁止拷贝赋值
    ResourceManagingClass(ResourceManagingClass&&) = default; // 移动构造函数
    ResourceManagingClass& operator=(ResourceManagingClass&&) = default; // 移动赋值运算符
    ~ResourceManagingClass() = default; // 默认析构函数
};
```

在这个例子中，`ResourceManagingClass` 类禁止了拷贝操作，同时保留了移动操作，这样可以在对象不再需要时将其资源转移给其他对象，而不是进行耗时的拷贝操作。

通过这种方式，你可以精确地控制类的内存管理行为，确保资源的有效利用和对象生命周期的正确管理。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
