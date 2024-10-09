# C++11 33-move aware class

- [C++11 33-move aware class](#c11-33-move-aware-class)
  - [Overview](#overview)
  - [1.move aware class](#1move-aware-class)
  - [2.如何在我的类中实现移动构造函数和移动赋值运算符？](#2如何在我的类中实现移动构造函数和移动赋值运算符)
    - [2.1. 定义移动构造函数](#21-定义移动构造函数)
    - [2.2. 定义移动赋值运算符](#22-定义移动赋值运算符)
    - [2.3. 禁用拷贝语义](#23-禁用拷贝语义)
    - [2.4. 考虑异常安全性](#24-考虑异常安全性)
    - [2.5. 测试你的类](#25-测试你的类)
  - [3.移动语义在多线程编程中有什么作用，我应该如何使用它？](#3移动语义在多线程编程中有什么作用我应该如何使用它)
    - [3.1.移动语义在多线程编程中的作用](#31移动语义在多线程编程中的作用)
    - [3.2.如何使用移动语义](#32如何使用移动语义)
  - [4.除了移动构造函数和移动赋值运算符，C++11还提供了哪些与移动语义相关的功能？](#4除了移动构造函数和移动赋值运算符c11还提供了哪些与移动语义相关的功能)
    - [4.1.移动语义的作用](#41移动语义的作用)
    - [4.2.如何使用移动语义](#42如何使用移动语义)
    - [4.3.示例](#43示例)
    - [4.4.注意事项](#44注意事项)
  - [5.C++11 移动语义在实际项目中如何应用以提高性能？](#5c11-移动语义在实际项目中如何应用以提高性能)
  - [关于作者](#关于作者)

## Overview

---

## 1.move aware class

在 C++11 中，移动语义（Move Semantics）是一种重要的特性，它允许资源（如动态分配的内存）在对象之间“移动”，而不是进行复制。这可以减少不必要的资源复制，提高程序的效率。一个“移动感知”的类（Move-aware class）会特别实现移动构造函数和移动赋值运算符，以便在适当的时候使用移动语义。

以下是一个简单的示例，展示了如何创建一个移动感知的类：

```cpp
#include <iostream>
#include <vector>

class MoveAwareClass {
public:
    // 默认构造函数
    MoveAwareClass() : data_(new int[10]) {
        std::cout << "Default constructor called" << std::endl;
    }

    // 拷贝构造函数
    MoveAwareClass(const MoveAwareClass& other) : data_(new int[10]) {
        std::copy(other.data_, other.data_ + 10, data_);
        std::cout << "Copy constructor called" << std::endl;
    }

    // 移动构造函数
    MoveAwareClass(MoveAwareClass&& other) noexcept : data_(other.data_) {
        other.data_ = nullptr;
        std::cout << "Move constructor called" << std::endl;
    }

    // 拷贝赋值运算符
    MoveAwareClass& operator=(const MoveAwareClass& other) {
        if (this != &other) {
            delete[] data_;
            data_ = new int[10];
            std::copy(other.data_, other.data_ + 10, data_);
        }
        std::cout << "Copy assignment called" << std::endl;
        return *this;
    }

    // 移动赋值运算符
    MoveAwareClass& operator=(MoveAwareClass&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            other.data_ = nullptr;
        }
        std::cout << "Move assignment called" << std::endl;
        return *this;
    }

    // 析构函数
    ~MoveAwareClass() {
        delete[] data_;
        std::cout << "Destructor called" << std::endl;
    }

private:
    int* data_;
};

int main() {
    MoveAwareClass obj1; // 调用默认构造函数
    MoveAwareClass obj2 = obj1; // 调用拷贝构造函数
    MoveAwareClass obj3(std::move(obj1)); // 调用移动构造函数
    obj2 = std::move(obj3); // 调用移动赋值运算符
    return 0;
}
```

在这个例子中，`MoveAwareClass` 定义了默认构造函数、拷贝构造函数、移动构造函数、拷贝赋值运算符和移动赋值运算符。移动构造函数和移动赋值运算符通过窃取（stealing）资源（这里是动态分配的数组）的所有权来避免不必要的复制，从而提高效率。

当使用 `std::move` 将一个对象转换为右值时，可以触发移动构造函数或移动赋值运算符的调用。这在处理临时对象或不再需要的对象时非常有用，因为它可以减少资源复制的开销。

移动语义是现代 C++ 编程的一个重要组成部分，它与智能指针（如 `std::unique_ptr` 和 `std::shared_ptr`）一起使用时尤其强大，因为这些智能指针类型是不可复制的，但可以移动。通过实现移动语义，可以确保这些资源管理类在现代 C++ 应用程序中的高效使用。

## 2.如何在我的类中实现移动构造函数和移动赋值运算符？

在 C++11 中实现移动构造函数和移动赋值运算符，可以让你的类更有效地处理资源所有权的转移，减少不必要的复制操作，从而提高性能。以下是如何在自定义类中实现这些移动特性的步骤：

### 2.1. 定义移动构造函数

移动构造函数接受一个右值引用作为参数，用于从另一个同类型对象中“窃取”资源。

```cpp
class MyClass {
public:
    // 构造函数
    MyClass(int* data) : data_(data) {}

    // 移动构造函数
    MyClass(MyClass&& other) noexcept : data_(other.data_) {
        other.data_ = nullptr; // 将源对象的资源指针置空，避免双重释放
    }

    // 析构函数
    ~MyClass() {
        delete[] data_;
    }

private:
    int* data_;
};
```

### 2.2. 定义移动赋值运算符

移动赋值运算符同样接受一个右值引用参数，并需要处理自赋值的情况。

```cpp
// 移动赋值运算符
MyClass& operator=(MyClass&& other) noexcept {
    if (this != &other) { // 检查自赋值
        delete[] data_;   // 释放现有资源
        data_ = other.data_; // 窃取资源
        other.data_ = nullptr; // 将源对象的资源指针置空
    }
    return *this;
}
```

### 2.3. 禁用拷贝语义

为了确保对象不会被复制，可以显式地删除拷贝构造函数和拷贝赋值运算符。

```cpp
class MyClass {
public:
    // 构造函数
    MyClass(int* data) : data_(data) {}

    // 移动构造函数
    MyClass(MyClass&& other) noexcept : data_(other.data_) {
        other.data_ = nullptr;
    }

    // 移动赋值运算符
    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            other.data_ = nullptr;
        }
        return *this;
    }

    // 禁用拷贝构造函数
    MyClass(const MyClass&) = delete;

    // 禁用拷贝赋值运算符
    MyClass& operator=(const MyClass&) = delete;

    // 析构函数
    ~MyClass() {
        delete[] data_;
    }

private:
    int* data_;
};
```

### 2.4. 考虑异常安全性

确保你的移动操作不会抛出异常。如果移动操作可能抛出异常，你需要确保程序的健壮性。

### 2.5. 测试你的类

确保你的移动操作按预期工作，包括移动后原对象的状态和资源的正确转移。

```cpp
int main() {
    int initialData[5] = {1, 2, 3, 4, 5};
    MyClass obj1(initialData);

    MyClass obj2(std::move(obj1)); // 测试移动构造函数
    for (int i = 0; i < 5; ++i) {
        std::cout << obj2.data_[i] << " ";
    }
    std::cout << std::endl;

    MyClass obj3(new int[5]{6, 7, 8, 9, 10});
    obj3 = std::move(obj2); // 测试移动赋值运算符
    for (int i = 0; i < 5; ++i) {
        std::cout << obj3.data_[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

通过实现移动构造函数和移动赋值运算符，你的类可以更有效地处理资源，避免不必要的复制，从而提高性能。

## 3.移动语义在多线程编程中有什么作用，我应该如何使用它？

移动语义（Move Semantics）在 C++11 中引入，主要是为了提高性能，特别是在对象的复制和赋值操作中。在多线程编程中，移动语义同样可以发挥作用，尤其是在涉及到临时对象的传递和资源所有权转移时。

### 3.1.移动语义在多线程编程中的作用

1. **性能提升**：
   在多线程环境中，线程之间经常需要传递数据。使用移动语义可以避免不必要的复制，从而减少线程同步的性能开销。例如，当一个线程需要将数据传递给另一个线程时，可以使用移动构造函数或移动赋值运算符，直接将资源（如动态分配的内存）转移给目标对象，而不是复制一份。

2. **资源管理**：
   移动语义可以用来管理线程特定的资源，如线程局部存储（Thread-Local Storage, TLS）或者线程池中的工作项。通过移动语义，可以将资源的所有权从一个线程转移到另一个线程，而不需要复制资源，这样可以减少资源的创建和销毁次数，提高资源利用率。

3. **异常安全**：
   在多线程环境中，异常处理尤为重要。移动操作通常不会抛出异常，这使得它们在多线程编程中更加安全。当一个线程在执行任务时发生异常，使用移动语义可以确保资源被正确释放，避免内存泄漏。

### 3.2.如何使用移动语义

1. **实现移动构造函数和移动赋值运算符**：
   在你的类中实现移动构造函数和移动赋值运算符。移动构造函数接受一个右值引用参数，并从该参数中“窃取”资源。移动赋值运算符则需要额外处理自赋值的情况。

   ```cpp
   class MyClass {
   public:
       // 移动构造函数
       MyClass(MyClass&& other) noexcept
           : data_(other.data_) {
           other.data_ = nullptr;
       }

       // 移动赋值运算符
       MyClass& operator=(MyClass&& other) noexcept {
           if (this != &other) {
               delete[] data_;
               data_ = other.data_;
               other.data_ = nullptr;
           }
           return *this;
       }

   private:
       int* data_;
   };
   ```

2. **使用 `std::move()`**：
   当你知道一个对象将要离开当前作用域，并且不再需要它时，可以使用 `std::move()` 将其转换为右值，从而触发移动构造函数或移动赋值运算符。

   ```cpp
   MyClass obj1;
   MyClass obj2 = std::move(obj1);
   ```

3. **线程安全**：
   确保你的移动操作是线程安全的。如果多个线程可能会同时访问和修改同一个对象，你需要使用互斥锁（mutexes）或其他同步机制来保护这些操作。

4. **测试和验证**：
   在多线程环境中，确保你的移动操作按预期工作，并且不会引起数据竞争或其他并发问题。

通过合理使用移动语义，你可以提高多线程程序的性能和资源管理效率。

## 4.除了移动构造函数和移动赋值运算符，C++11还提供了哪些与移动语义相关的功能？

移动语义是 C++11 引入的一项重要特性，它允许资源（如动态分配的内存）在对象之间转移，而不是复制。这在多线程编程中尤其有用，因为它可以提高线程间数据传递的效率。

### 4.1.移动语义的作用

1. **性能提升**：在多线程环境中，线程间传递数据时使用移动语义可以避免不必要的复制操作，从而减少线程同步的性能开销。

2. **资源管理**：移动语义可以用来管理线程特定的资源，如线程局部存储（Thread-Local Storage, TLS）或者线程池中的工作项。

3. **异常安全**：移动操作通常不会抛出异常，这使得它们在多线程编程中更加安全。

### 4.2.如何使用移动语义

1. **实现移动构造函数和移动赋值运算符**：在你的类中实现移动构造函数和移动赋值运算符，以便在对象间转移资源。

2. **使用 `std::move()`**：当你知道一个对象将要离开当前作用域，并且不再需要它时，可以使用 `std::move()` 将其转换为右值，从而触发移动构造函数或移动赋值运算符。

3. **线程安全**：确保你的移动操作是线程安全的。如果多个线程可能会同时访问和修改同一个对象，你需要使用互斥锁（mutexes）或其他同步机制来保护这些操作。

4. **测试和验证**：在多线程环境中，确保你的移动操作按预期工作，并且不会引起数据竞争或其他并发问题。

### 4.3.示例

```cpp
class MyClass {
public:
    int* data_;
    MyClass(int size) { data_ = new int[size]; }
    ~MyClass() { delete[] data_; }

    // 移动构造函数
    MyClass(MyClass&& other) noexcept : data_(other.data_) {
        other.data_ = nullptr;
    }

    // 移动赋值运算符
    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            other.data_ = nullptr;
        }
        return *this;
    }

    // 禁用拷贝构造函数和拷贝赋值运算符
    MyClass(const MyClass&) = delete;
    MyClass& operator=(const MyClass&) = delete;
};

// 在多线程环境中使用
std::thread t([]() {
    MyClass obj(10);
    // Do some work...
    // 将对象传递给另一个线程
    std::cout << "Object data: " << obj.data_ << std::endl;
});
t.join();
```

在这个例子中，`MyClass` 定义了移动构造函数和移动赋值运算符，使得在多线程环境中可以高效地传递对象。

### 4.4.注意事项

- 移动操作应该避免抛出异常，以确保线程安全的资源管理。
- 在实现移动操作时，确保源对象在移动后处于有效但不确定的状态，以防止悬挂指针或重复释放资源。

通过合理使用移动语义，你可以提高多线程程序的性能和资源管理效率。

## 5.C++11 移动语义在实际项目中如何应用以提高性能？

在实际项目中，C++11 的移动语义可以通过以下几种方式来提高性能：

1. **优化临时对象的处理**：
   在函数调用中，经常会产生临时对象，如在容器操作或函数返回时。使用移动语义可以避免这些临时对象的复制，直接将资源转移给目标对象。例如，在处理 `std::vector` 或 `std::string` 等资源密集型对象时，移动语义可以显著减少内存分配和数据复制的开销。

2. **提高资源管理效率**：
   对于动态分配内存或其他资源的对象，移动语义允许资源所有权的转移，而不是资源的复制。这减少了资源管理的复杂性和成本，尤其是在对象生命周期结束时。

3. **优化容器操作**：
   在 STL 容器（如 `std::vector`、`std::deque`）中，移动语义用于优化元素的插入和删除操作。容器可以移动元素而不是复制它们，从而提高性能。

4. **减少异常处理开销**：
   移动操作通常不会抛出异常，这使得在异常处理中使用移动语义可以避免不必要的复制，同时保持代码的异常安全。

5. **使用 `std::move()`**：
   当对象不再需要时，可以使用 `std::move()` 将其转换为右值，从而触发移动构造函数或移动赋值运算符，而不是默认的拷贝构造函数或赋值运算符。

6. **避免数据竞争**：
   在多线程环境中，移动语义可以确保资源在不同线程之间进行正确的所有权转移，避免了资源竞争和数据竞争的问题。

7. **与智能指针结合使用**：
   移动语义与智能指针（如 `std::unique_ptr`）结合使用，可以实现高效、安全的资源管理。例如，当函数返回一个资源时，可以使用 `std::unique_ptr` 和 `std::move()` 来避免资源的复制。

8. **优化函数返回值**：
   在函数返回局部对象时，使用移动语义可以避免创建临时对象，减少不必要的复制。编译器通常会优化返回局部对象的操作，但如果需要，可以使用 `std::move()` 来明确表示使用移动语义。

通过在项目中合理应用移动语义，可以显著提高程序的性能，尤其是在处理大型数据结构或频繁进行对象传递的场景中。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
