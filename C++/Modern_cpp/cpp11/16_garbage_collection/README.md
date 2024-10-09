# C++11 16-垃圾收集 Garbage Collection

- [C++11 16-垃圾收集 Garbage Collection](#c11-16-垃圾收集-garbage-collection)
  - [Overview](#overview)
  - [1.垃圾收集 Garbage Collection](#1垃圾收集-garbage-collection)
  - [2.C++11中智能指针的工作原理是什么？](#2c11中智能指针的工作原理是什么)
  - [3.如何使用C++11的特性来避免内存泄漏？](#3如何使用c11的特性来避免内存泄漏)
  - [关于作者](#关于作者)

## Overview

---

## 1.垃圾收集 Garbage Collection

C++11标准本身并没有引入垃圾收集机制。C++是一种静态类型、编译时语言，它依赖于显式的资源管理和内存管理。程序员需要手动管理对象的生命周期，包括分配和释放内存。

然而，C++11引入了许多特性，可以帮助开发者管理内存和资源，减少内存泄漏和其他资源管理错误的可能性。以下是一些C++11中有助于内存管理的特性：

1. **智能指针**：
   - `std::unique_ptr`：独占所有权的智能指针，确保动态分配的对象在不再使用时自动释放。
   - `std::shared_ptr`：共享所有权的智能指针，使用引用计数机制管理对象的生命周期。
   - `std::weak_ptr`：一种不控制对象生命周期的智能指针，用于解决`std::shared_ptr`可能导致的循环引用问题。

2. **RAII（Resource Acquisition Is Initialization）**：
   - 一种编程习惯，通过将资源的生命周期绑定到对象的生命周期，确保在对象销毁时自动释放资源。

3. **`std::make_shared`和`std::make_unique`**：
   - 函数模板，用于创建`std::shared_ptr`和`std::unique_ptr`，以更安全和高效的方式管理动态分配的内存。

4. **基于区间的for循环**：
   - 提供了一种更安全和方便的方式来遍历容器，减少了索引错误和越界访问的可能性。

5. **`noexcept`说明符**：
   - 用于指示函数不会抛出异常，有助于异常安全的资源管理。

6. **Lambda表达式**：
   - 允许在需要时捕获和使用外部变量，有助于编写更简洁和安全的代码。

7. **原子操作**：
   - 通过`std::atomic`类型，提供了一种机制来安全地在多线程环境中操作数据。

尽管C++11没有内置垃圾收集器，但通过使用智能指针和RAII模式，可以大大减少手动内存管理的复杂性和风险。如果需要垃圾收集功能，你可能需要考虑其他语言，如Java或C#，或者探索第三方库，如Boehm垃圾收集器，它可以与C++代码一起使用。

在C++中，通常的做法是使用智能指针来自动管理内存，以及使用RAII来管理其他资源，从而避免手动调用`new`和`delete`。这些方法提供了一种高效且相对安全的方式来处理资源和内存管理。

## 2.C++11中智能指针的工作原理是什么？

C++11引入了三种智能指针，它们都是定义在`std`命名空间下的模板类，用于自动管理动态分配（使用`new`分配）的内存，以防止内存泄漏和其他资源管理错误。这些智能指针的工作原理如下：

1. **`std::unique_ptr`**：
   - `std::unique_ptr`代表对动态分配对象的独占所有权模型。它不允许复制（Copy Constructor和Copy Assignment Operator是删除的），但可以移动（Move Constructor和Move Assignment Operator是合法的），这意味着可以传递`std::unique_ptr`实例，但不可以共享它。
   - 当`std::unique_ptr`被销毁时（例如离开其作用域），它会自动删除其所拥有的对象。

   ```cpp
   std::unique_ptr<int> ptr(new int(10)); // 分配一个int对象
   // 当ptr超出作用域时，int对象会被自动删除
   ```

2. **`std::shared_ptr`**：
   - `std::shared_ptr`通过引用计数机制管理对象的生命周期。每个`std::shared_ptr`实例都保存着一个指向共享对象的指针和一个指向引用计数的指针。
   - 当有`std::shared_ptr`被销毁时，引用计数会减少。只有当最后一个拥有该对象的`std::shared_ptr`被销毁时，对象才会被删除。

   ```cpp
   std::shared_ptr<int> ptr1(new int(10));
   std::shared_ptr<int> ptr2 = ptr1; // 共享同一个对象
   // 当ptr1和ptr2都超出作用域时，对象会被删除
   ```

3. **`std::weak_ptr`**：
   - `std::weak_ptr`是一种不控制对象生命周期的智能指针，它用来解决`std::shared_ptr`可能导致的循环引用问题。
   - `std::weak_ptr`持有一个对`std::shared_ptr`所管理对象的弱引用，不增加引用计数。它可以用来观察对象，但不可以独自拥有对象。

   ```cpp
   std::shared_ptr<int> sp(new int(10));
   std::weak_ptr<int> wp = sp;
   if (!wp.expired()) { // 检查是否有关联的shared_ptr实例
       std::shared_ptr<int> sp2 = wp.lock(); // 获取一个shared_ptr实例
   }
   ```

智能指针的实现通常涉及以下关键技术：

- **自定义删除器**：智能指针可以与自定义删除器一起使用，允许为资源清理提供特定的逻辑。

- **异常安全**：智能指针保证在构造、赋值和析构过程中，即使发生异常，也不会引起内存泄漏。

- **线程安全**：`std::shared_ptr`的复制和析构操作是原子的，可以在多线程环境中安全使用。

- **辅助类**：如`std::enable_shared_from_this`允许`std::shared_ptr`从成员函数安全地复制`this`指针。

智能指针是C++11中非常重要的特性之一，它们提供了一种更安全和方便的方式来管理资源，尤其是在复杂和并发的程序中。

## 3.如何使用C++11的特性来避免内存泄漏？

使用C++11的特性来避免内存泄漏，可以遵循以下最佳实践：

1. **使用智能指针**：
   - 使用`std::unique_ptr`来管理单个对象，确保对象在不再需要时自动释放。
   - 使用`std::shared_ptr`来管理共享对象，确保对象在其最后一个引用被销毁时自动释放。
   - 使用`std::weak_ptr`来避免`std::shared_ptr`导致的循环引用问题。

2. **RAII（Resource Acquisition Is Initialization）**：
   - 封装资源（如动态内存、文件句柄、网络连接等）在对象中，并确保资源在对象生命周期结束时自动释放。

3. **利用构造函数和析构函数**：
   - 在构造函数中分配资源，在析构函数中释放资源，确保即使在异常发生时也能释放资源。

4. **使用`noexcept`**：
   - 将析构函数声明为`noexcept`，确保在析构函数中不会抛出异常，从而避免析构过程中的异常导致资源未被释放。

5. **避免裸指针**：
   - 尽量避免使用裸指针管理动态分配的内存，如果必须使用，确保使用智能指针来接管资源管理。

6. **使用`std::make_unique`和`std::make_shared`**：
   - 使用这些函数模板创建智能指针，它们提供了一种更安全和高效的方式来管理动态分配的内存。

7. **使用`std::array`或`std::vector`**：
   - 代替裸指针数组，这些容器会自动管理内存，并在超出作用域时自动释放。

8. **利用`std::unique_lock`或`std::lock_guard`**：
   - 在多线程环境中，使用这些RAII风格的锁管理工具来避免死锁和未解锁的情况。

9. **使用`std::unordered_map`或`std::map`**：
   - 代替指针数组或散列表，这些容器会自动管理内存，并在超出作用域时自动释放。

10. **使用`std::shared_ptr`的自定义删除器**：
    - 为特定的资源管理需求提供自定义删除器。

11. **内存泄漏检测工具**：
    - 使用如 Valgrind、AddressSanitizer 等工具定期检测内存泄漏。

12. **避免在循环中使用动态分配**：
    - 在循环中使用`new`可能会导致内存泄漏，因为如果循环被异常中断，分配的内存可能不会被释放。

13. **谨慎使用`delete`**：
    - 确保每次`delete`操作都有一个对应的`new`操作，避免重复删除和野指针。

14. **使用Lambda表达式和`std::function`**：
    - 捕获外部变量时要小心，避免捕获指向动态分配内存的指针。

通过遵循这些实践，你可以有效地利用C++11的特性来避免内存泄漏，提高程序的稳定性和可靠性。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
