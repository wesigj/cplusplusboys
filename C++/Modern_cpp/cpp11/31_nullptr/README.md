# C++11 31-nullptr and nullptr_t

- [C++11 31-nullptr and nullptr\_t](#c11-31-nullptr-and-nullptr_t)
  - [Overview](#overview)
  - [1.nullptr and nullptr\_t](#1nullptr-and-nullptr_t)
    - [1.1.nullptr](#11nullptr)
    - [1.2.nullptr\_t](#12nullptr_t)
    - [1.3.示例](#13示例)
    - [1.4.注意事项](#14注意事项)
  - [2.在 C++11 标准中，nullptr 的值是什么，它与 nullptr\_t 有什么区别？](#2在-c11-标准中nullptr-的值是什么它与-nullptr_t-有什么区别)
    - [2.1.nullptr 的值](#21nullptr-的值)
    - [2.2.nullptr 与 nullptr\_t](#22nullptr-与-nullptr_t)
    - [2.3.区别](#23区别)
    - [2.4.示例](#24示例)
    - [2.5.总结](#25总结)
  - [3.在 C++ 中，除了 nullptr，还有哪些类型可以表示空指针？](#3在-c-中除了-nullptr还有哪些类型可以表示空指针)
    - [3.1.示例](#31示例)
  - [4.在 C++ 中，如何正确地使用 nullptr 来避免空指针解引用的问题？](#4在-c-中如何正确地使用-nullptr-来避免空指针解引用的问题)
  - [5.在C++11中，除了nullptr，还有哪些新的类型安全特性？](#5在c11中除了nullptr还有哪些新的类型安全特性)
  - [关于作者](#关于作者)

## Overview

---

## 1.nullptr and nullptr_t

在 C++11 之前，空指针通常用 `NULL` 或 `0` 来表示。C++11 引入了 `nullptr` 关键字，以提供类型安全的方式来表示空指针。`nullptr` 是一个真正意义上的空指针字面量，它比之前的表示方法更安全、更明确。

### 1.1.nullptr

- **类型安全**：`nullptr` 是一个类型安全的空指针字面量，它与任何指针类型兼容，但不是与整数类型兼容，这避免了 `NULL` 或 `0` 可能引起的类型转换问题。
- **值**：`nullptr` 的值是空指针，意味着它是一个不指向任何对象的指针。
- **表达式类型**：`nullptr` 在表达式中的类型是 `std::nullptr_t`。

### 1.2.nullptr_t

- **类型**：`std::nullptr_t` 是 `nullptr` 的类型，定义在头文件 `<cstddef>` 中。
- **用途**：`std::nullptr_t` 类型旨在作为指针类型，但它不指向任何对象。它是一个空的指针类型，可以转换为任何对象指针类型或成员指针类型。

### 1.3.示例

```cpp
#include <iostream>

void func(int* ptr) {
    std::cout << "int* version" << std::endl;
}

void func(double* ptr) {
    std::cout << "double* version" << std::endl;
}

int main() {
    int* ptr1 = nullptr;
    double* ptr2 = nullptr;

    func(ptr1);  // 调用 int* version
    func(ptr2);  // 调用 double* version

    nullptr_t n = nullptr; // 显式使用 nullptr_t

    return 0;
}
```

在这个示例中，`nullptr` 被用来定义两种不同类型的指针，分别是 `int*` 和 `double*`。此外，还展示了如何显式使用 `nullptr_t` 类型。

### 1.4.注意事项

- **与 `NULL` 和 `0` 的区别**：尽管 `nullptr` 与 `NULL` 或 `0` 在很多情况下可以互换使用，但 `nullptr` 更为类型安全，它不会隐式转换为非指针类型。
- **布尔上下文中**：当 `nullptr` 被用在布尔上下文中时，它的值是 `false`。
- **转换**：`nullptr` 可以转换为任何指针类型，也可以转换为 `bool` 类型，但不能转换为整数类型。

通过使用 `nullptr` 和 `std::nullptr_t`，C++11 提供了一种更安全和表达性更强的方式来处理空指针。

## 2.在 C++11 标准中，nullptr 的值是什么，它与 nullptr_t 有什么区别？

在 C++11 标准中，`nullptr` 是一个空指针字面量，用于表示一个不指向任何对象的指针值。`nullptr` 的设计目的是为了提供比传统的空指针表示方法 (`NULL` 或 `0`) 更好的类型安全性。

### 2.1.nullptr 的值

`nullptr` 的值是这样一个指针值：它不指向任何对象，且不在同一时间指向多个对象。在实现上，它通常表示为一个空指针，但这是由实现定义的，标准只保证它不会指向任何有效的对象。

### 2.2.nullptr 与 nullptr_t

- **nullptr**：`nullptr` 是一个字面量，用于表示空指针。它是 `std::nullptr_t` 类型的实例。
- **nullptr_t**：`std::nullptr_t` 是一个在 `<cstddef>` 头文件中定义的类型，专门用来表示 `nullptr` 的类型。

### 2.3.区别

因为 `nullptr` 本身就是一个值，不是类型。但 `nullptr` 的类型是 `std::nullptr_t`。这两者之间的关系是：

- **值**：`nullptr` 是值。
- **类型**：`std::nullptr_t` 是 `nullptr` 值的类型。

### 2.4.示例

```cpp
#include <iostream>

int main() {
    void* p = nullptr; // `nullptr` 被转换为 `void*`
    std::nullptr_t n = nullptr; // 显式使用 `std::nullptr_t` 类型
    bool b = nullptr; // `nullptr` 在布尔上下文中为 `false`

    std::cout << "p: " << p << std::endl;
    std::cout << "n: " << static_cast<void*>(n) << std::endl;
    std::cout << "b: " << b << std::endl;

    return 0;
}
```

在这个示例中，`nullptr` 被用来初始化三种不同类型的指针：

1. **`void* p = nullptr;`**：`nullptr` 被转换为 `void*` 类型。
2. **`std::nullptr_t n = nullptr;`**：显式使用 `std::nullptr_t` 类型。
3. **`bool b = nullptr;`**：`nullptr` 在布尔上下文中为 `false`。

### 2.5.总结

- `nullptr` 是一个空指针字面量，表示一个不指向任何对象的指针值。
- `std::nullptr_t` 是 `nullptr` 的类型。
- `nullptr` 可以被转换为任何指针类型，也可以转换为布尔类型（在布尔上下文中为 `false`），但不能转换为整数类型。

通过使用 `nullptr` 和 `std::nullptr_t`，C++11 提供了一种更安全和表达性更强的方式来处理空指针。

## 3.在 C++ 中，除了 nullptr，还有哪些类型可以表示空指针？

在 C++ 中，除了 `nullptr`，还有其他一些方法和类型可以用来表示空指针：

1. **`NULL`**：
   宏定义，通常被定义为 `0` 或者 `(void*)0`，用来表示空指针。它的类型不是 `nullptr_t`，而是 `int` 或者 `void*`。

2. **`0` 或 `0L`**：
   字面量 `0` 可以被隐式转换为 `NULL`，因此也可以用来表示空指针。使用 `0L`（长整型字面量）可以避免在某些情况下与 `NULL` 的 `int` 类型冲突。

3. **`NULLPTR`**：
   在 C++11 之前，`NULLPTR` 是 Boost 库中 `nullptr` 的前身，它是一个宏定义，等同于 `nullptr`。

4. **`std::numeric_limits<int>::max()` 或 `std::numeric_limits<unsigned long long>::max()`**：
   理论上，任何足够大的值，大到它不可能是一个有效的地址，都可以视为空指针。不过，这种做法不常见，且容易出错。

5. **空指针优化（Null Pointer Optimization）**：
   对于某些特定类型，如 `std::shared_ptr` 和 `std::unique_ptr`，可以通过将它们初始化为 `nullptr` 来表示空指针。这些智能指针类型有自己内部的空指针表示。

6. **指针常量**：
   定义一个指针常量并初始化为 `NULL` 或 `0`，例如：

   ```cpp
   const int* ptr = 0;
   ```

7. **`boost::detail::empty_function`**：
   在 Boost 库中，对于函数指针，`boost::detail::empty_function` 可以用来表示一个空函数指针。

8. **`std::function`**：
   对于可调用对象的包装器，`std::function` 类型可以被默认构造为一个空的可调用对象。

9. **`std::optional`**：
   在 C++17 中引入，可以被用来包装一个可能不存在的值，`std::optional<T>` 默认构造后表示一个“空”的状态。

10. **`std::monostate`**：
    在 C++17 中引入，作为 `std::variant` 的空状态，可以表示一个空的变体。

### 3.1.示例

以下是一些表示空指针的方法：

```cpp
int* ptr1 = nullptr; // C++11 之后的推荐方式
int* ptr2 = NULL;    // 传统宏定义方式
int* ptr3 = 0;       // 整数字面量
const int* ptr4 = 0; // 指针常量

std::shared_ptr<int> smartPtr1 = nullptr; // 对于智能指针
std::function<void()> func = nullptr;     // 对于可调用对象包装器

std::optional<int> opt; // 对于 std::optional
std::variant<int, std::monostate> var; // 对于 std::variant，monostate 表示空状态
```

在现代 C++ 编程中，推荐使用 `nullptr` 来表示空指针，因为它提供了类型安全性和清晰性。其他方法可能在旧代码或者特定的上下文中使用。

## 4.在 C++ 中，如何正确地使用 nullptr 来避免空指针解引用的问题？

在 C++ 中，使用 `nullptr` 代替 `NULL` 或 `0` 来表示空指针是避免空指针解引用问题的一种类型安全的方法。以下是一些正确使用 `nullptr` 的最佳实践：

1. **总是使用 `nullptr`**：
   对于所有的指针类型，始终使用 `nullptr` 来赋值和比较，而不是 `NULL` 或 `0`。

   ```cpp
   int* ptr = nullptr;
   if (ptr != nullptr) {
       // Do something with ptr
   }
   ```

2. **初始化指针**：
   在定义指针时立即初始化为 `nullptr`，避免未初始化的指针使用。

   ```cpp
   int* ptr = nullptr;
   ```

3. **使用智能指针**：
   尽可能使用智能指针（如 `std::unique_ptr` 或 `std::shared_ptr`）来自动管理内存和对象生命周期。

   ```cpp
   std::unique_ptr<int> uniquePtr = std::make_unique<int>(10);
   std::shared_ptr<int> sharedPtr = std::make_shared<int>(10);
   ```

4. **检查指针再解引用**：
   在解引用指针之前总是检查其是否为 `nullptr`。

   ```cpp
   if (ptr != nullptr) {
       *ptr = 10;
   }
   ```

5. **利用 `std::optional`**：
   在 C++17 及以上版本，可以使用 `std::optional` 来表示可能为空的值。

   ```cpp
   std::optional<int> maybeInt = std::make_optional(10);
   if (maybeInt) {
       // Safe to use *maybeInt or maybeInt.value()
   }
   ```

6. **利用布尔值检查**：
   由于 `nullptr` 在布尔上下文中等价于 `false`，可以利用这一特性进行检查。

   ```cpp
   if (ptr) {
       // Safe to use ptr
   }
   ```

7. **避免裸指针**：
   尽量避免使用裸指针，特别是在资源管理、容器管理和复杂对象图的操作中。

8. **利用现代 C++ 特性**：
   使用现代 C++ 特性，如范围 `for` 循环、基于范围的 `std::for_each` 算法，它们可以避免直接操作指针。

9. **使用自定义删除标志**：
   对于不能删除的指针，可以定义一个自定义删除标志，如 `delete_ptr`。

   ```cpp
   void* delete_ptr = nullptr;
   ```

10. **检查动态分配的内存**：
    在使用 `new` 分配内存后，总是检查返回的指针是否为 `nullptr`。

    ```cpp
    int* ptr = new (std::nothrow) int;
    if (ptr == nullptr) {
        // Handle allocation failure
    }
    ```

11. **确保空指针安全的操作和函数**：
    编写任何可能操作指针的函数时，确保它们能够安全地处理空指针。

12. **使用断言**：
    在开发阶段，使用断言来确保指针的有效性。

    ```cpp
    assert(ptr != nullptr);
    ```

通过遵循这些最佳实践，你可以减少因空指针解引用而导致的程序崩溃和不稳定的风险。

## 5.在C++11中，除了nullptr，还有哪些新的类型安全特性？

在 C++11 中，除了 `nullptr`，还有许多新特性增强了类型安全性，包括：

1. **类型别名（Type Aliases）**：
   使用 `using` 声明可以创建类型别名，这有助于简化复杂的类型名称，提高代码的可读性。

2. **强类型枚举（Strongly Typed Enums）**：
   `enum class` 引入了强类型枚举，避免了隐式转换到整数类型，提高了枚举类型的安全性。

3. **类型萃取（Type Traits）**：
   C++11 扩展了类型萃取功能，允许开发者在编译时获取和操作类型的信息。

4. **自动类型推导（Auto Keyword）**：
   `auto` 关键字允许编译器自动推导变量的类型，这有助于简化代码，尤其是在模板编程中。

5. **范围基于的 for 循环（Range-based for Loops）**：
   这种循环形式可以减少迭代器使用错误，提高代码的安全性。

6. **Lambda 表达式**：
   Lambda 表达式提供了一种方便的方式来创建匿名函数，并且可以捕获周围作用域的变量，减少了错误的变量引用。

7. **Smart Pointers（智能指针）**：
   `std::unique_ptr`, `std::shared_ptr`, 和 `std::weak_ptr` 提供了自动的内存管理，减少了内存泄漏的风险。

8. **noexcept 说明符**：
   `noexcept` 可以用来声明一个函数不会抛出异常，增加了函数行为的可预测性。

9. **静态断言（Static Assert）**：
   `static_assert` 关键字可以在编译时进行条件检查，提供了一种编译时的断言机制。

10. **右值引用（Rvalue References）**：
    右值引用和移动语义减少了不必要的对象复制，提高了资源使用的效率。

11. **类型安全的数值转换（Type-Safe Numeric Conversions）**：
    通过 `std::stoi`, `std::stol`, `std::stoul` 等函数进行字符串到整数的转换，提供了类型安全的转换机制。

12. **显式转换运算符（Explicit Conversion Operators）**：
    通过将转换运算符声明为 `explicit`，防止了隐式类型转换，增加了类型安全性。

13. **继承构造函数（Inherited Constructors）**：
    允许派生类继承基类的构造函数，简化了构造函数的编写，减少了错误。

14. **删除函数（Deleted Functions）**：
    使用 `= delete` 可以防止编译器生成默认的特殊成员函数，增加了对类行为的控制。

15. **表达式 SFINAE（Substitution Failure Is Not An Error）**：
    SFINAE 允许在模板编程中进行条件编译，增加了模板的灵活性。

16. **constexpr**：
    `constexpr` 关键字允许定义编译时常量，提高了性能和确定性。

17. **类型安全的联合（Type-Safe Unions）**：
    虽然 C++11 没有直接提供类型安全的联合，但是后续的 C++17 引入了 `std::variant` 来替代传统的 `union`。

这些特性一起为 C++11 提供了更强的类型安全性，减少了类型错误和相关的安全问题。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
