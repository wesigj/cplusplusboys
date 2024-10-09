# C++11 23-头文件中的 inline 变量 Inline variable in header file

- [C++11 23-头文件中的 inline 变量 Inline variable in header file](#c11-23-头文件中的-inline-变量-inline-variable-in-header-file)
  - [Overview](#overview)
  - [1.头文件中的 inline 变量 Inline variable in header file](#1头文件中的-inline-变量-inline-variable-in-header-file)
    - [1.1.为什么使用`inline`变量](#11为什么使用inline变量)
    - [1.2.如何定义`inline`变量](#12如何定义inline变量)
    - [1.3.注意事项](#13注意事项)
    - [1.4.示例](#14示例)
  - [2.在C++11中，除了使用inline关键字，还有哪些方法可以避免重复定义错误？](#2在c11中除了使用inline关键字还有哪些方法可以避免重复定义错误)
  - [3.如果我想在头文件中定义一个非const的inline变量，应该如何操作？](#3如果我想在头文件中定义一个非const的inline变量应该如何操作)
    - [3.1.注意事项](#31注意事项)
  - [4.使用inline变量时，有哪些常见的陷阱或者注意事项需要避免？](#4使用inline变量时有哪些常见的陷阱或者注意事项需要避免)
  - [5.inline 变量和全局变量区别](#5inline-变量和全局变量区别)
  - [6.C++11标准中对inline变量有哪些新的规定？](#6c11标准中对inline变量有哪些新的规定)
  - [关于作者](#关于作者)

## Overview

---

## 1.头文件中的 inline 变量 Inline variable in header file

在C++11中，可以在头文件中定义`inline`变量。这种变量通常用于实现跨多个编译单元的常量值共享。当你在头文件中定义一个`inline`变量时，它告诉编译器这个变量的定义是与链接相关的，并且可以在多个编译单元中包含这个头文件。

### 1.1.为什么使用`inline`变量

使用`inline`变量的主要原因是允许头文件中的常量在包含它的每个编译单元中具有唯一的定义。这避免了链接时的重复定义错误。在C++11之前，常量定义在头文件中会导致每个源文件都有自己的定义，这在链接时会引起问题。

### 1.2.如何定义`inline`变量

在头文件中定义`inline`变量的语法如下：

```cpp
// constants.h
#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int myConstant = 42;

inline const int anotherConstant = 100;

#endif // CONSTANTS_H
```

在这个例子中，`myConstant`是一个`constexpr`变量，它用于编译时计算的常量表达式。`anotherConstant`是一个`inline`变量，它在每个包含此头文件的编译单元中都有一个定义。

### 1.3.注意事项

1. **头文件保护**：确保使用宏定义来保护头文件，避免头文件被多次包含。

2. **链接时的单一定义**：`inline`变量确保每个编译单元都有一个定义，但链接器会看到多个相同的定义。链接器需要能够识别这些定义实际上是相同的，因此它们必须是字面值常量。

3. **使用`const`还是`constexpr`**：对于`inline`变量，通常使用`const`，因为`constexpr`变量必须在编译时是已知的，而`inline`变量可以在运行时初始化。

4. **避免非字面值类型**：`inline`变量应该是字面值类型，如整数、枚举等。对于非字面值类型（如`std::string`），使用`inline`变量可能会导致问题。

5. **使用`extern`**：对于非字面值类型的全局变量，可以使用`extern`关键字在头文件中声明变量，并在源文件中定义它。

### 1.4.示例

```cpp
// constants.h
#ifndef CONSTANTS_H
#define CONSTANTS_H

inline const int maxUsers = 100;

#endif // CONSTANTS_H

// main.cpp
#include "constants.h"
#include <iostream>

int main() {
    std::cout << "Max Users: " << maxUsers << std::endl;
    return 0;
}
```

在这个例子中，`maxUsers`在每个包含`constants.h`的编译单元中都有一个定义，链接器会处理这些定义，确保只有一个实例被使用。

使用`inline`变量是一种有效的方法来在多个编译单元中共享常量值，同时避免链接时的重复定义问题。

## 2.在C++11中，除了使用inline关键字，还有哪些方法可以避免重复定义错误？

在C++中，为了避免重复定义错误，通常使用以下几种方法：

1. **头文件保护（Include Guards）**：
   - 通过宏定义来确保头文件只被包含一次，防止重复定义。

   ```cpp
   // example.h
   #ifndef EXAMPLE_H
   #define EXAMPLE_H

   // 头文件内容

   #endif // EXAMPLE_H
   ```

2. **`#pragma once`**：
   - 这是非标准的预处理指令，但被大多数编译器支持，用于防止头文件被重复包含。

   ```cpp
   // example.h
   #pragma once

   // 头文件内容
   ```

3. **`constexpr`变量**：
   - 用于定义编译时常量，可以在多个编译单元中使用而不会重复定义。

   ```cpp
   // constants.h
   #ifndef CONSTANTS_H
   #define CONSTANTS_H

   constexpr int myConstant = 42;

   #endif // CONSTANTS_H
   ```

4. **外部链接（`extern`）**：
   - 使用`extern`关键字声明全局变量，然后在一个源文件中定义变量。

   ```cpp
   // global.h
   #ifndef GLOBAL_H
   #define GLOBAL_H

   extern int globalVar;

   #endif // GLOBAL_H

   // global.cpp
   #include "global.h"

   int globalVar = 42;
   ```

5. **匿名命名空间**：
   - 在头文件中使用匿名命名空间，每个编译单元都会创建一个唯一的命名空间。

   ```cpp
   // example.h
   #ifndef EXAMPLE_H
   #define EXAMPLE_H

   namespace {
       int uniqueValue = 42;
   }

   #endif // EXAMPLE_H
   ```

6. **类型嵌套**：
   - 将静态成员定义在类内部，这样每个编译单元都有自己的定义。

   ```cpp
   // example.h
   #ifndef EXAMPLE_H
   #define EXAMPLE_H

   class Example {
   public:
       static int value;
   };

   int Example::value = 42;

   #endif // EXAMPLE_H
   ```

7. **模板类/函数**：
   - 模板定义通常包含在头文件中，并且可以被多个源文件包含而不会重复定义。

   ```cpp
   // example.h
   #ifndef EXAMPLE_H
   #define EXAMPLE_H

   template <typename T>
   class Container {
       T data;
   };

   #endif // EXAMPLE_H
   ```

8. **类静态成员变量**：
   - 类静态成员变量在类外定义，每个编译单元有自己的定义。

   ```cpp
   // example.h
   #ifndef EXAMPLE_H
   #define EXAMPLE_H

   class Example {
   public:
       static int staticVar;
   };

   #endif // EXAMPLE_H

   // example.cpp
   #include "example.h"

   int Example::staticVar = 42;
   ```

9. **`inline`函数**：
   - `inline`函数可以定义在头文件中，并且可以在多个编译单元中包含而不会重复定义。

   ```cpp
   // example.h
   #ifndef EXAMPLE_H
   #define EXAMPLE_H

   inline int add(int a, int b) {
       return a + b;
   }

   #endif // EXAMPLE_H
   ```

使用这些方法可以有效地避免在多个编译单元中包含同一个头文件时出现的重复定义错误。每种方法适用于不同的场景，可以根据具体需求选择使用。

## 3.如果我想在头文件中定义一个非const的inline变量，应该如何操作？

在C++中，如果你想在头文件中定义一个非`const`的`inline`变量，你需要使用`inline`关键字和`static`关键字。`static`关键字确保了变量在全局命名空间中只被定义一次，而`inline`关键字使得变量可以在多个编译单元中包含而不会违反“一次定义规则”（One Definition Rule，ODR）。

以下是如何在头文件中定义一个非`const`的`inline`变量的示例：

```cpp
// example.h
#ifndef EXAMPLE_H
#define EXAMPLE_H

inline static int nonConstInlineVar = 42;

#endif // EXAMPLE_H
```

在这个例子中，`nonConstInlineVar`是一个非`const`的`inline`变量，它被初始化为`42`。由于它被声明为`inline`和`static`，它在每个包含此头文件的编译单元中都有一个定义，但是链接器会看到它们是相同的定义。

### 3.1.注意事项

1. **头文件保护**：确保使用宏定义来保护头文件，避免头文件被多次包含。

2. **非`const`变量**：由于`inline`变量通常用于常量，如果你需要一个非`const`变量，确保你了解为什么需要它，并确保使用方式是安全的。

3. **线程安全**：非`const`的`inline`变量在多线程环境中可能会遇到线程安全问题。如果你的程序是多线程的，并且这个变量会被多个线程访问，你需要确保适当的同步。

4. **初始化**：非`const`的`inline`变量可以在声明时初始化，但它们不能在类定义中初始化，因为类定义中的静态成员需要在类外进行初始化。

5. **使用场景**：通常，非`const`的全局变量应该避免使用，因为它们可能导致代码难以理解和维护。如果你需要一个全局变量，考虑使用单例模式或者依赖注入来管理状态。

6. **链接器**：虽然`inline`变量可以避免ODR违规，但链接器需要能够识别这些定义实际上是相同的。这意味着它们必须具有相同的类型和相同的初始化器。

通过这种方式，你可以在头文件中定义一个非`const`的`inline`变量，并且在多个编译单元中使用它。

## 4.使用inline变量时，有哪些常见的陷阱或者注意事项需要避免？

使用`inline`变量时，确实存在一些常见的陷阱和注意事项。了解这些可以帮助你避免潜在的问题：

1. **理解`inline`变量的行为**：
   - `inline`变量（在C++17之前称为`static`变量）在每个包含它的编译单元中都有一个单独的定义，链接器必须能够识别出这些定义实际上是同一个全局变量。

2. **链接器的视角**：
   - 链接器需要能够将每个编译单元中的`inline`变量视作同一个全局变量。如果变量的类型或初始值在不同的编译单元中不一致，链接器可能会报错。

3. **避免非字面值常量**：
   - `inline`变量通常是字面值类型（如整数、枚举）。如果使用非字面值类型（如`std::string`），则可能导致链接错误。

4. **头文件保护**：
   - 确保使用宏定义（include guards）来防止头文件被多次包含，这可以避免重复定义错误。

5. **不要在类定义中使用`inline`变量**：
   - 在类定义中使用`inline`变量是非法的，因为类定义中的静态成员需要在类外进行定义。

6. **不要在`inline`变量中使用非常量表达式**：
   - `inline`变量必须是常量表达式，因为它们需要在编译时初始化。

7. **不要依赖`inline`变量的顺序**：
   - `inline`变量的初始化顺序是未定义的，因此不要依赖于它们之间的初始化顺序。

8. **避免在`inline`变量中使用动态初始化**：
   - 避免在`inline`变量的初始化中使用动态表达式，如函数调用或运行时计算的值。

9. **不要在`inline`变量中使用复杂的逻辑**：
   - 尽量保持`inline`变量的初始化简单，避免复杂的逻辑。

10. **避免在`inline`变量中使用全局静态对象**：
    - 如果`inline`变量依赖于全局静态对象，那么它的初始化可能会受到静态初始化顺序问题的影响。

11. **考虑线程安全**：
    - 如果`inline`变量在多线程环境中使用，确保适当的同步机制，以避免竞态条件。

12. **避免在模板中使用`inline`变量**：
    - 在模板中使用`inline`变量可能会导致意外的行为，因为模板实例化可能会在编译单元之间产生复杂的依赖关系。

13. **避免在匿名命名空间中使用`inline`变量**：
    - 在匿名命名空间中使用`inline`变量可能会导致链接错误，因为匿名命名空间中的对象应该是内部链接，而`inline`变量需要外部链接。

通过了解和遵循这些注意事项，你可以更安全地使用`inline`变量，避免常见的陷阱。

## 5.inline 变量和全局变量区别

`inline`变量和全局变量在C++中有不同的用途和行为。以下是它们之间的主要区别：

1. **定义位置**：
   - **全局变量**：定义在函数之外，可以是文件作用域的变量，也可以是命名空间作用域的变量。
   - **`inline`变量**：通常定义在头文件中，可以在多个编译单元中包含而不会违反“一次定义规则”（ODR）。

2. **链接视角**：
   - **全局变量**：具有外部链接（除非是`static`全局变量），在程序中全局可见。
   - **`inline`变量**：具有内部链接，每个包含定义的编译单元都有自己的定义，链接器需要将这些定义视为同一个全局变量。

3. **初始化**：
   - **全局变量**：可以在定义时初始化，也可以在定义后初始化。
   - **`inline`变量**：必须是字面值常量表达式，必须在定义时初始化。

4. **作用域**：
   - **全局变量**：在定义它的文件或命名空间内可见。
   - **`inline`变量**：在包含头文件的每个编译单元内可见。

5. **头文件包含**：
   - **全局变量**：通常不在头文件中定义，以避免在多个编译单元中重复定义。
   - **`inline`变量**：定义在头文件中，允许在多个编译单元中包含。

6. **类型**：
   - **全局变量**：可以是任何类型。
   - **`inline`变量**：在C++17之前，通常是`const`或`constexpr`类型。从C++17开始，可以使用`inline`变量定义非`const`变量。

7. **存储期**：
   - **全局变量**：具有静态存储期，直到程序结束时才销毁。
   - **`inline`变量**：也具有静态存储期，但它们的存储期可能在不同的编译单元中是独立的。

8. **线程安全**：
   - **全局变量**：如果被多个线程访问，需要外部同步机制。
   - **`inline`变量**：与全局变量相同，需要外部同步机制。

9. **模板实例化**：
   - **全局变量**：可以在模板中定义。
   - **`inline`变量**：在模板中定义时需要特别注意，以避免链接错误。

10. **匿名命名空间**：
    - **全局变量**：可以在匿名命名空间中定义，具有文件内部链接。
    - **`inline`变量**：通常不在匿名命名空间中定义。

11. **生命周期**：
    - **全局变量**：在整个程序的生命周期内有效。
    - **`inline`变量**：在包含头文件的每个编译单元中都有自己的生命周期。

12. **初始化顺序**：
    - **全局变量**：在main函数执行前初始化，初始化顺序可能依赖于它们的定义顺序。
    - **`inline`变量**：初始化顺序未定义，可能在首次访问时初始化。

使用`inline`变量时，通常是为了避免在多个编译单元中包含同一个头文件时出现的重复定义错误。而全局变量则用于在程序的不同部分之间共享数据。

## 6.C++11标准中对inline变量有哪些新的规定？

在C++11标准中，并没有引入名为“inline变量”的新概念，但是对`inline`关键字的使用进行了扩展。在C++17标准中，对`inline`变量进行了进一步的明确和规定。

在C++11中，`inline`关键字主要用于指示编译器对函数进行内联展开，以优化性能。而在C++17中，`inline`关键字被扩展用于变量声明，允许在头文件中定义变量，而不会在每个包含该头文件的编译单元中产生多个定义，从而避免了“一次定义规则”（One Definition Rule，ODR）的违规。

以下是C++17中对`inline`变量的一些新规定：

1. **内联静态成员变量**：可以在类定义中直接初始化静态成员变量，而不需要在源文件中单独定义。

2. **外部链接**：内联变量默认具有外部链接，这意味着它们可以在不同的编译单元中共享。

3. **多个定义**：允许在不同的编译单元中定义相同的内联变量，链接器会确保它们是同一个实体。

4. **类型一致性**：在不同的编译单元中，内联变量的类型必须完全一致。

5. **初始化**：内联变量必须在声明时初始化，且初始化表达式必须是一个常量表达式。

6. **存储期**：内联变量具有静态存储期，这意味着它们的生命周期从定义时开始，直到程序结束。

7. **地址一致性**：内联变量在每个翻译单元中具有相同的地址。

8. **模板实例化**：内联变量可以用于模板中，确保模板实例化时变量的定义是一致的。

9. **特征测试宏**：C++17中定义了`__cpp_inline_variables`特征测试宏，用于检测编译器是否支持内联变量。

这些规定使得在头文件中定义全局变量变得更加安全和方便，尤其是在创建跨多个编译单元的库时。通过使用`inline`关键字，可以确保变量在程序中只有一个定义，避免了链接时的错误。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
