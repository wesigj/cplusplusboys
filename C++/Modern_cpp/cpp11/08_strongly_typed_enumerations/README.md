# C++11 08-强类型枚举 Strongly typed enumerations

- [C++11 08-强类型枚举 Strongly typed enumerations](#c11-08-强类型枚举-strongly-typed-enumerations)
  - [Overview](#overview)
  - [1.强类型枚举 Strongly typed enumerations](#1强类型枚举-strongly-typed-enumerations)
    - [1.1.定义强类型枚举](#11定义强类型枚举)
    - [1.2.类型安全性](#12类型安全性)
    - [1.3.比较运算符](#13比较运算符)
    - [1.4.底层类型](#14底层类型)
    - [1.5.与普通枚举的比较](#15与普通枚举的比较)
    - [1.6.总结](#16总结)
  - [2.C++11 中强类型枚举和普通枚举在实际编程中有哪些具体的区别？](#2c11-中强类型枚举和普通枚举在实际编程中有哪些具体的区别)
    - [2.1. 类型安全性](#21-类型安全性)
    - [2.2. 作用域](#22-作用域)
    - [2.3. 枚举类和枚举结构](#23-枚举类和枚举结构)
    - [2.4. 底层类型](#24-底层类型)
    - [2.5. 比较](#25-比较)
    - [2.6. 转换](#26-转换)
    - [2.7. 示例](#27-示例)
    - [2.8. 总结](#28-总结)
  - [3.如何使用强类型枚举来提高代码的可读性和可维护性？](#3如何使用强类型枚举来提高代码的可读性和可维护性)
    - [3.1. **清晰的类型定义**](#31-清晰的类型定义)
    - [3.2. **避免命名冲突**](#32-避免命名冲突)
    - [3.3. **类型安全**](#33-类型安全)
    - [3.4. **易于维护**](#34-易于维护)
    - [3.5. **使用自定义类型**](#35-使用自定义类型)
    - [3.6. **与流操作符配合使用**](#36-与流操作符配合使用)
    - [3.7. **转换为字符串**](#37-转换为字符串)
    - [3.8. **使用在 switch 语句中**](#38-使用在-switch-语句中)
  - [4.在C++11中，强类型枚举和普通枚举在内存布局上有什么不同？](#4在c11中强类型枚举和普通枚举在内存布局上有什么不同)
  - [5.如何使用C++11的强类型枚举来避免潜在的类型转换错误？](#5如何使用c11的强类型枚举来避免潜在的类型转换错误)
    - [5.1. 使用 `enum class` 或 `enum struct`](#51-使用-enum-class-或-enum-struct)
    - [5.2. 限定枚举值](#52-限定枚举值)
    - [5.3. 显式类型转换](#53-显式类型转换)
    - [5.4. 使用自定义类型](#54-使用自定义类型)
    - [5.5. 避免与整数的直接比较](#55-避免与整数的直接比较)
    - [5.6. 重载运算符](#56-重载运算符)
    - [5.7. 避免隐式转换](#57-避免隐式转换)
    - [5.8. 编译器警告](#58-编译器警告)
  - [关于作者](#关于作者)

## Overview

---

## 1.强类型枚举 Strongly typed enumerations

在 C++11 之前，枚举类型（enumerations）在 C++ 中是松散的类型，它们不会限制枚举值的类型，并且枚举值默认是 `int` 类型。这可能会导致枚举值与其他整型值之间的隐式转换，从而引发潜在的错误。

C++11 引入了“强类型枚举”（也称为“枚举类”或“enum 类”），它通过 `enum class”` 或 `enum struct` 关键字定义。强类型枚举提供了更好的类型安全性，枚举值不会隐式转换为整数，从而避免了上述问题。

### 1.1.定义强类型枚举

以下是如何定义强类型枚举的示例：

```cpp
#include <iostream>

// 使用 enum class 定义强类型枚举
enum class Color {
    RED,
    GREEN,
    BLUE
};

int main() {
    Color myColor = Color::RED;
    std::cout << "My favorite color is " << myColor << std::endl;
    return 0;
}
```

在这个例子中，`Color` 是一个强类型枚举，它的值不能隐式地转换为整数。

### 1.2.类型安全性

强类型枚举提供了更好的类型安全性。例如，你不能将 `Color` 枚举值直接赋给一个整数变量，这需要显式转换：

```cpp
int value = static_cast<int>(myColor); // 显式转换
```

### 1.3.比较运算符

强类型枚举的比较需要使用 `==` 或 `!=` 运算符，不能使用 `==` 比较枚举值和整数，也不能比较不同枚举类型的值。

### 1.4.底层类型

强类型枚举有一个底层类型，它默认为 `int`，但你可以指定其他整数类型：

```cpp
enum class Color : char {
    RED,   // 默认底层类型为 char
    GREEN, // 实际存储为 char 类型
    BLUE    // 实际存储为 char 类型
};
```

### 1.5.与普通枚举的比较

普通枚举（旧式枚举）的值可以隐式转换为整数，这可能会导致类型安全问题：

```cpp
enum Color {
    RED, GREEN, BLUE
};

int main() {
    Color myColor = RED;
    int num = myColor; // 隐式转换，可能导致问题
    return 0;
}
```

### 1.6.总结

C++11 引入的强类型枚举提供了更好的类型安全性，避免了枚举值与其他整数类型的隐式转换，使得代码更加可靠和易于维护。在新的 C++ 代码中，推荐使用强类型枚举来定义枚举类型。

## 2.C++11 中强类型枚举和普通枚举在实际编程中有哪些具体的区别？

在 C++11 中引入的强类型枚举（也称为枚举类或枚举结构）与 C++98 中的传统枚举（也称为枚举类型）相比，具有一些显著的区别。以下是它们在实际编程中的主要区别：

### 2.1. 类型安全性

- **强类型枚举**：提供了更好的类型安全性。强类型枚举的值不能隐式转换为整数，这意味着它们只能在相同枚举类型的上下文中使用，或者需要显式的类型转换。
- **普通枚举**：枚举值可以隐式转换为整数，这可能导致类型安全问题，因为你可以无意中将枚举值当作整数处理。

### 2.2. 作用域

- **强类型枚举**：枚举成员具有明确的作用域。你可以使用枚举类型名来限定成员，例如 `Color::RED`。
- **普通枚举**：枚举成员会被提升到包含枚举的同一作用域中，可能导致命名冲突。

### 2.3. 枚举类和枚举结构

- **强类型枚举**：可以使用 `enum class` 或 `enum struct` 定义。`enum class` 表示枚举类型是类类型，`enum struct` 表示枚举类型是结构体类型，但两者在 C++11 中行为相同。
- **普通枚举**：只能使用 `enum` 关键字定义。

### 2.4. 底层类型

- **强类型枚举**：默认底层类型是 `int`，但你可以显式指定其他整数类型，如 `enum class Color : char { RED, GREEN, BLUE };`。
- **普通枚举**：底层类型默认是 `int`，但也可以显式指定。

### 2.5. 比较

- **强类型枚举**：枚举值之间可以直接使用 `==` 和 `!=` 进行比较。
- **普通枚举**：枚举值可以与整数进行比较，但不同枚举类型的值之间不能直接比较。

### 2.6. 转换

- **强类型枚举**：需要显式转换为整数，例如使用 `static_cast<int>`。
- **普通枚举**：枚举值可以隐式转换为整数。

### 2.7. 示例

以下是强类型枚举和普通枚举的示例：

```cpp
#include <iostream>

// 普通枚举
enum OldStyle {
    OLD_ONE,
    OLD_TWO,
    OLD_THREE
};

// 强类型枚举
enum class NewStyle {
    ONE,
    TWO,
    THREE
};

int main() {
    // 普通枚举
    OldStyle os = OLD_ONE;
    int num = os; // 隐式转换
    std::cout << "Old style enum value: " << num << std::endl;

    // 强类型枚举
    NewStyle ns = NewStyle::TWO;
    int num2 = static_cast<int>(ns); // 显式转换
    std::cout << "New style enum value: " << num2 << std::endl;

    // 比较
    if (os == OLD_TWO) {
        std::cout << "Old style comparison" << std::endl;
    }

    if (ns == NewStyle::TWO) {
        std::cout << "New style comparison" << std::endl;
    }

    return 0;
}
```

### 2.8. 总结

强类型枚举提供了更好的类型安全性和作用域控制，使得枚举值的使用更加明确和安全。在现代 C++ 编程中，推荐使用强类型枚举来避免潜在的错误和提高代码的可维护性。

## 3.如何使用强类型枚举来提高代码的可读性和可维护性？

强类型枚举（也称为枚举类或枚举结构）在 C++11 及更高版本中提供了一种类型安全的方式来定义枚举，从而可以提高代码的可读性和可维护性。以下是一些使用强类型枚举来提升代码质量的方法：

### 3.1. **清晰的类型定义**

   使用强类型枚举可以清晰地定义枚举类型，使得枚举值的含义更加明确。

   ```cpp
   enum class Color {
       RED, GREEN, BLUE
   };

   Color myColor = Color::RED; // 明确表示这是一个颜色枚举
   ```

### 3.2. **避免命名冲突**

   强类型枚举的成员名称是限定在枚举类型内的，这避免了与其他枚举或全局变量的命名冲突。

   ```cpp
   enum class Status {
       SUCCESS, FAILURE
   };

   enum class Error {
       SUCCESS, FAILURE
   };

   // Status::SUCCESS 和 Error::SUCCESS 是不同的值
   ```

### 3.3. **类型安全**

   强类型枚举提供了更好的类型安全，因为它们的值不会隐式转换为整数。

   ```cpp
   void setColour(Color colour) {
       // ...
   }

   int main() {
       setColour(Color::RED); // 正确
       // setColour(1); // 错误：类型不匹配
   }
   ```

### 3.4. **易于维护**

   强类型枚举使得代码更加易于维护，因为你可以轻松地添加新的枚举值而不影响现有代码。

   ```cpp
   enum class Direction {
       NORTH, EAST, SOUTH, WEST
   };

   // 将来可以轻松添加 NORTHEAST, SOUTHWEST 等
   ```

### 3.5. **使用自定义类型**

   可以为强类型枚举指定一个底层类型，这有助于优化存储和性能。

   ```cpp
   enum class ErrorCode : uint8_t {
       NONE, TIMEOUT, OVERFLOW
   };
   ```

### 3.6. **与流操作符配合使用**

   可以为强类型枚举定义流操作符，以便于输出枚举值的字符串表示，从而提高调试的便利性。

   ```cpp
   std::ostream& operator<<(std::ostream& os, const Color& color) {
       switch (color) {
           case Color::RED:   os << "Red"; break;
           case Color::GREEN: os << "Green"; break;
           case Color::BLUE:  os << "Blue"; break;
           default:           os << "Unknown"; break;
       }
       return os;
   }
   ```

### 3.7. **转换为字符串**

   提供将枚举值转换为字符串的功能，这在用户界面显示或日志记录时非常有用。

   ```cpp
   std::string colorToString(Color color) {
       switch (color) {
           case Color::RED:   return "Red";
           case Color::GREEN: return "Green";
           case Color::BLUE:  return "Blue";
           default:          return "Unknown Color";
       }
   }
   ```

### 3.8. **使用在 switch 语句中**

   强类型枚举在 `switch` 语句中使用时更加清晰和安全。

   ```cpp
   void handleColor(Color color) {
       switch (color) {
           case Color::RED:   std::cout << "Red color"; break;
           case Color::GREEN: std::cout << "Green color"; break;
           case Color::BLUE:  std::cout << "Blue color"; break;
           default:           std::cout << "Invalid color";
       }
   }
   ```

通过这些方法，强类型枚举有助于编写更加清晰、安全和易于维护的代码。

## 4.在C++11中，强类型枚举和普通枚举在内存布局上有什么不同？

在 C++11 中，强类型枚举（也称为枚举类或枚举结构）与普通枚举（也称为非限定枚举）在内存布局上有以下几个主要区别：

1. **作用域**：
   - 强类型枚举具有限定的作用域，枚举成员必须通过枚举类型名来访问，例如 `Color::RED`，这有助于避免命名冲突。
   - 普通枚举是非限定的，枚举成员会提升到包含枚举的定义作用域中，可能导致命名冲突。

2. **类型安全**：
   - 强类型枚举提供了更好的类型安全，枚举成员不能隐式转换为整数，这有助于避免意外的类型转换错误。
   - 普通枚举的成员可以隐式转换为整数，这可能导致类型安全问题。

3. **底层类型**：
   - 强类型枚举允许开发者显式指定底层类型，例如 `enum class Color : uint8_t { RED, GREEN, BLUE };`，这有助于优化内存使用和性能。
   - 普通枚举的底层类型默认为 `int`，但也可以显式指定，不过不同编译器可能会有不同的默认底层类型。

4. **内存占用**：
   - 强类型枚举的内存占用取决于指定的底层类型和枚举成员的数量。
   - 普通枚举的内存占用同样取决于底层类型，但所有枚举成员共享相同的底层类型。

5. **枚举值的初始化**：
   - 在强类型枚举中，如果未显式初始化，成员的值默认从 `0` 开始依次递增。
   - 普通枚举也有类似的默认初始化规则。

6. **枚举的声明**：
   - 强类型枚举支持前置声明，例如 `enum class Color;`，这有助于分离枚举的定义和声明，减少编译依赖。
   - 普通枚举不支持前置声明。

7. **枚举的比较**：
   - 强类型枚举的值可以与其他枚举值或布尔值进行比较，但与整数类型的比较需要显式转换。
   - 普通枚举的值可以与整数类型进行隐式比较。

8. **枚举的字面量**：
   - 强类型枚举可以作为字面量使用，例如在模板元编程中。

总的来说，强类型枚举提供了更好的类型安全性和作用域控制，使得枚举值的使用更加明确和安全。在现代 C++ 编程中，推荐使用强类型枚举来定义枚举类型，以避免潜在的错误和提高代码的可维护性。

## 5.如何使用C++11的强类型枚举来避免潜在的类型转换错误？

在 C++11 之前，普通枚举（non-strongly typed enums）的成员可以隐式地转换为整数，这可能导致不安全的类型转换和潜在的错误。C++11 引入的强类型枚举（也称为枚举类或枚举结构）提供了更好的类型安全性，因为它们的值不会隐式转换为整数。以下是一些使用强类型枚举来避免潜在类型转换错误的策略：

### 5.1. 使用 `enum class` 或 `enum struct`

定义枚举时，使用 `enum class` 或 `enum struct` 而不是 `enum` 来创建强类型枚举。

```cpp
enum class Color {
    RED, GREEN, BLUE
};

// 强类型枚举
Color myColor = Color::RED;
```

### 5.2. 限定枚举值

在引用强类型枚举的成员时，使用枚举类型名作为限定符。

```cpp
Color myColor = Color::RED; // 正确
int number = myColor;      // 错误：类型不匹配
```

### 5.3. 显式类型转换

如果需要将强类型枚举的值转换为整数，使用显式类型转换。

```cpp
int number = static_cast<int>(myColor);
```

### 5.4. 使用自定义类型

为强类型枚举定义自定义类型，以便在需要时进行安全的类型转换。

```cpp
enum class Color {
    RED, GREEN, BLUE
};

Color toColor(int value) {
    switch (value) {
        case 0: return Color::RED;
        case 1: return Color::GREEN;
        case 2: return Color::BLUE;
        default: throw std::invalid_argument("Invalid color value");
    }
}
```

### 5.5. 避免与整数的直接比较

避免将强类型枚举的值直接与整数进行比较，而是使用枚举成员。

```cpp
if (myColor == Color::RED) {
    // Do something
}
```

### 5.6. 重载运算符

为强类型枚举重载输入/输出运算符，以便于调试和日志记录。

```cpp
std::ostream& operator<<(std::ostream& os, Color color) {
    switch (color) {
        case Color::RED:   os << "Red"; break;
        case Color::GREEN: os << "Green"; break;
        case Color::BLUE:  os << "Blue"; break;
        default: os << "Unknown";
    }
    return os;
}
```

### 5.7. 避免隐式转换

避免在函数参数和返回类型中使用强类型枚举，以防止隐式转换。

```cpp
void function(Color color); // 明确要求 Color 类型
```

### 5.8. 编译器警告

利用编译器的警告功能来检测潜在的类型转换错误。

通过这些方法，你可以利用 C++11 的强类型枚举来编写更安全、更可靠的代码，从而避免因类型转换错误导致的潜在问题。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
