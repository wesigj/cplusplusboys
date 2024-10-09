# C++11 18-用户定义的字面量 User defined literal values

- [C++11 18-用户定义的字面量 User defined literal values](#c11-18-用户定义的字面量-user-defined-literal-values)
  - [Overview](#overview)
  - [1.用户定义的字面量 User defined literal values](#1用户定义的字面量-user-defined-literal-values)
    - [1.1.基本语法](#11基本语法)
    - [1.2.示例](#12示例)
    - [1.3.使用场景](#13使用场景)
    - [1.4.注意事项](#14注意事项)
  - [2.C++11 中用户定义的字面量（UDLs）有哪些常见的使用场景？](#2c11-中用户定义的字面量udls有哪些常见的使用场景)
    - [2.1.示例代码](#21示例代码)
  - [3.如何为自定义的字面量编写一个安全且易于理解的解析函数？](#3如何为自定义的字面量编写一个安全且易于理解的解析函数)
    - [3.1.示例代码](#31示例代码)
  - [4.在C++中，除了用户定义的字面量，还有哪些方法可以增强语言的表达能力？](#4在c中除了用户定义的字面量还有哪些方法可以增强语言的表达能力)
  - [5.C++11中的UDLs如何与现有的类型系统兼容？](#5c11中的udls如何与现有的类型系统兼容)
  - [关于作者](#关于作者)

## Overview

---

## 1.用户定义的字面量 User defined literal values

C++11 引入了用户定义的字面量（User-Defined Literals, UDLs），这是一种允许开发者为字面量（如字符串、数字等）定义自定义的后缀，从而实现自定义操作的机制。UDLs 使得开发者能够扩展字面量的语义，提供更丰富的表达能力和灵活性。

### 1.1.基本语法

用户定义的字面量通过在字面量后面添加自定义的后缀来实现，格式如下：

```cpp
your_literal_operator your_literal;
```

其中 `your_literal_operator` 是你定义的操作符，`your_literal` 是普通的字面量。

### 1.2.示例

假设我们想为整数添加一个自定义的字面量，用于创建一个特定的数据类型 `Meter`，表示长度单位米：

```cpp
#include <iostream>
#include <string>

// 定义 Meter 类
class Meter {
public:
    double length;

    Meter(double len) : length(len) {}

    friend std::string operator"" _m(long double value);
};

// 定义用户自定义字面量 _m
std::string operator"" _m(long double value) {
    Meter instance(value);
    return std::to_string(instance.length) + " meters";
}

int main() {
    auto result = 100.0_m;
    std::cout << result << std::endl;  // 输出: 100 meters
    return 0;
}
```

### 1.3.使用场景

1. **单位转换**：如上例所示，可以为数字添加单位，例如长度、时间、货币等。

2. **配置和解析**：用于解析特定格式的字符串，例如配置文件中的值。

3. **字符串处理**：对字符串字面量进行快速处理，例如转换为大写、小写等。

4. **数学和物理计算**：为数字字面量添加自定义操作，例如向量计算、物理单位转换等。

5. **日志和调试**：生成带有额外信息的日志条目，例如时间戳、日志级别等。

### 1.4.注意事项

- 用户定义的字面量应该谨慎使用，因为它们可能会使代码的可读性降低，特别是对于不熟悉 UDLs 的开发者。
- 确保自定义操作符的实现尽可能简单和直观，避免复杂的逻辑。
- 在使用时，要注意 UDLs 可能会与现有的操作符重载冲突。

用户定义的字面量提供了一种强大的机制来扩展 C++ 的表达能力，但应该在不牺牲代码清晰度和可维护性的前提下使用。

## 2.C++11 中用户定义的字面量（UDLs）有哪些常见的使用场景？

C++11 中引入的用户定义字面量（User-Defined Literals，UDLs）为语言增加了极大的灵活性。UDLs 允许开发者为字面量定义自定义的后缀，从而实现特定的操作。以下是一些常见的使用场景：

1. **单位系统**：
   - 为数值字面量添加单位，如长度、重量、时间、货币等，以提高代码的可读性和减少单位错误。

   ```cpp
   double distance = 10.0_km; // 如果_km是为千米定义的UDL
   ```

2. **字符串处理**：
   - 对字符串字面量进行格式化或处理，如转换为大写、小写，或者添加前缀和后缀。

   ```cpp
   std::string upperCase = "example"_to_upper;
   ```

3. **日志记录**：
   - 在日志消息中添加时间戳、日志级别或其他元数据。

   ```cpp
   log("Error occurred"_log);
   ```

4. **配置文件解析**：
   - 解析带有特定格式的配置字符串，如从一个配置字面量中提取键值对。

   ```cpp
   auto config = "key=value"_cfg;
   ```

5. **数学和物理计算**：
   - 为科学计算定义自定义字面量，如向量、复数或物理常数。

   ```cpp
   auto force = 9.81_m_s2;
   ```

6. **颜色表示**：
   - 在图形和UI编程中，定义颜色的字面量表示。

   ```cpp
   auto color = "255,0,255"_rgb;
   ```

7. **数据格式化**：
   - 将数值格式化为特定的字符串表示，如固定精度、科学记数法等。

   ```cpp
   std::string formatted = 123.456_to_string;
   ```

8. **编码和加密**：
   - 对字面量进行编码或加密，如Base64编码、URL编码等。

   ```cpp
   std::string encoded = "data"_base64;
   ```

9. **网络地址**：
   - 解析和验证网络地址，如IP地址、端口号等。

   ```cpp
   int port = "8080"_port;
   ```

10. **自定义类型创建**：
    - 快速创建自定义类型的实例，如日期、时间等。

    ```cpp
    DateTime now = "2023-01-01"_date;
    ```

UDLs 提供了一种强大的工具来扩展语言的能力，但它们也可能导致代码的可读性降低，尤其是对于不熟悉特定 UDLs 的开发者。因此，在使用 UDLs 时，应该确保它们增加了代码的清晰度和表达力，而不是相反。

### 2.1.示例代码

以下是一个简单的 UDL 示例，用于定义一个带有单位的数值：

```cpp
#include <iostream>
#include <string>
#include <chrono>

// 定义一个简单的长度类
class Meter {
public:
    double length;
    Meter(double len) : length(len) {}
};

// 定义_km后缀，用于创建Meter实例
Meter operator"" _km(long double value) {
    return Meter(value);
}

// 定义_to_string后缀，用于将数字转换为字符串
std::string operator"" _to_string(const char* str, size_t len) {
    return std::string(str, len);
}

int main() {
    Meter distance = 100.0_km;
    std::cout << "Distance: " << distance.length << " km" << std::endl;

    std::string formatted = "123.456"_to_string;
    std::cout << "Formatted string: " << formatted << std::endl;

    return 0;
}
```

在这个示例中，我们定义了两个 UDLs：`_km` 用于创建 `Meter` 类型的实例，`_to_string` 用于将字符串字面量转换为 `std::string` 对象。

## 3.如何为自定义的字面量编写一个安全且易于理解的解析函数？

编写安全且易于理解的用户定义字面量（UDLs）解析函数时，需要考虑以下几个关键点：

1. **明确意图**：
   - 确定UDL的目的和它所期望的行为。文档化其用法和行为，以便其他开发者可以理解其意图。

2. **简洁明了**：
   - 保持UDL操作符的实现尽可能简洁。复杂的逻辑可能会使错误更难追踪，也难以理解。

3. **输入验证**：
   - 对输入进行验证，确保其符合预期的格式和类型。对于不合法的输入，应该抛出异常或返回错误。

4. **错误处理**：
   - 提供清晰的错误信息。当解析失败时，返回易于理解的错误提示。

5. **避免歧义**：
   - 避免创建可能引起混淆的UDLs，特别是那些与现有操作符或常见约定相冲突的。

6. **使用现有的类型和库**：
   - 尽可能利用标准库和第三方库中的功能，而不是重新实现相同的功能。

7. **考虑性能**：
   - 评估UDL的性能影响，特别是在性能敏感的应用中。

8. **使用合适的数据类型**：
   - 选择正确的数据类型来存储解析后的结果，以避免精度丢失或其他问题。

9. **避免全局污染**：
   - 避免滥用UDLs，以免造成命名空间污染。可以将UDLs定义在命名空间中。

10. **适当的访问级别**：
    - 根据UDL的用途，确定其是否应该是public、internal或是private。

11. **遵循一致的风格**：
    - 如果项目中使用了多个UDLs，确保它们的命名和实现风格一致。

12. **测试**：
    - 编写测试用例以验证UDLs的正确性，并确保它们在各种边缘情况下都能正常工作。

### 3.1.示例代码

以下是一个简单的UDL解析函数示例，它将一个数字字面量后缀为`_km`的字符串解析为一个包含公里单位的自定义类型：

```cpp
#include <iostream>
#include <stdexcept>
#include <string>

// 自定义类型，用于存储带单位的数值
struct Kilometer {
    double value;
};

// 声明解析函数
Kilometer operator"" _km(const char* str, size_t len);

// 实现解析函数
Kilometer operator"" _km(const char* str, size_t len) {
    try {
        // 将字面量转换为字符串，然后转换为double
        std::string num_str(str, len);
        double value = std::stod(num_str);
        return Kilometer{value};
    } catch (const std::invalid_argument& e) {
        // 输入字符串不是一个有效的数字
        throw std::runtime_error("Invalid argument: Unable to convert to number.");
    } catch (const std::out_of_range& e) {
        // 数值超出double的范围
        throw std::runtime_error("Out of range error: Number is too large or too small.");
    }
}

int main() {
    auto distance = 123.45_km;
    std::cout << "Distance in kilometers: " << distance.value << " km" << std::endl;
    return 0;
}
```

在这个示例中，我们定义了一个`Kilometer`结构体来存储数值和单位。UDL操作符`_km`负责将字面量字符串解析为`double`类型的数值，并返回一个`Kilometer`实例。如果解析失败，我们抛出一个异常来通知调用者。

通过遵循上述准则，你可以编写出安全且易于理解的用户定义字面量解析函数。

## 4.在C++中，除了用户定义的字面量，还有哪些方法可以增强语言的表达能力？

在C++中，除了用户定义的字面量（UDLs），还有多种方法可以增强语言的表达能力，提高代码的可读性和可维护性。以下是一些常用的方法：

1. **模板元编程**：
   - 使用模板进行编译时计算和决策，可以创建通用且高效的代码。

2. **运算符重载**：
   - 允许已定义的运算符对自定义类型进行操作，使得自定义类型的使用更加直观。

3. **模板特化**：
   - 允许为特定类型或模板参数提供特定的模板实现。

4. **类型萃取**：
   - 使用`decltype`、`typename`和`auto`关键字来简化类型表达式，并让类型依赖于表达式的结果。

5. **Lambda 表达式**：
   - 提供了一种方便的方式来创建匿名函数，简化了代码，尤其是在使用算法时。

6. **尾置返回类型**：
   - 使用尾置返回类型（`auto`关键字）来简化函数声明，尤其是当函数返回类型依赖于函数参数时。

7. **智能指针**：
   - `std::unique_ptr`、`std::shared_ptr`和`std::weak_ptr`等，提供了更安全和方便的资源管理方式。

8. **并发编程**：
   - 使用`std::thread`、`std::async`和原子操作等并发工具，简化多线程和并行编程。

9. **范围基于的for循环**：
   - 提供了一种更简洁和直观的方式来遍历容器和数组。

10. **变长模板**：
    - 允许模板函数或类接受任意数量的模板参数。

11. **SFINAE（Substitution Failure Is Not An Error）**：
    - 用于模板元编程中，实现条件编译和重载决议。

12. **异常处理**：
    - 使用`try`、`catch`、`throw`和`typeid`等关键字来处理程序中的错误。

13. **类型特征（Type Traits）**：
    - 用于在编译时进行类型检查和类型属性查询。

14. **constexpr和编译时执行**：
    - 允许在编译时执行函数和计算表达式，提高程序性能。

15. **属性（Attributes）**：
    - 如 `[[nodiscard]]`、`[[deprecated]]` 等，为函数、类或变量提供元数据。

16. **标准库容器和算法**：
    - 提供了一套丰富的容器（如`std::vector`、`std::map`）和算法（如`std::sort`、`std::transform`）来操作数据。

17. **正则表达式**：
    - 提供了一种方便的方式来处理字符串匹配和文本处理。

18. **模块化和命名空间**：
    - 使用命名空间来组织代码，避免命名冲突。

19. **C++20 新特性**：
    - 如概念（Concepts）、范围（Ranges）、协程（Coroutines）等，进一步增强了语言的表达能力。

通过合理使用这些特性，可以编写出更加强大、灵活和可维护的C++代码。

## 5.C++11中的UDLs如何与现有的类型系统兼容？

用户定义的字面量（UDLs）在 C++11 中被引入，为语言提供了一种扩展机制，允许开发者为字面量定义自定义的后缀，从而创建特定类型的字面量。UDLs 与现有类型系统的兼容性主要体现在以下几个方面：

1. **类型安全**：UDLs 允许开发者定义新的字面量类型，这些类型在使用时必须明确指定，这有助于保持类型安全。例如，定义一个表示米的类型，用户必须显式使用 `_km` 后缀来创建该类型的字面量 。

2. **与现有字面量区分**：UDLs 通过后缀与现有的字面量区分开来，避免了与现有字面量的冲突。例如，`123` 是一个整数字面量，而 `123_km` 则是一个带有自定义后缀的用户定义字面量。

3. **编译时解析**：UDLs 在编译时被解析，这意味着它们不会影响程序的运行时性能，同时编译器可以检查 UDLs 的使用是否正确。

4. **表达能力增强**：UDLs 可以增强语言的表达能力，使得代码更加直观和易于理解。例如，使用 `1000.0_m` 来表示距离，比单独的数字更直观地传达了数值的单位。

5. **标准库支持**：C++ 标准库也使用了 UDLs，如 `std::chrono` 中的时间字面量（例如 `10ms` 表示 10 毫秒），这为时间相关的操作提供了便利。

6. **错误处理**：UDLs 可以设计成在解析失败时抛出异常或返回错误，这有助于错误处理和调试。

7. **灵活性**：UDLs 提供了极大的灵活性，允许开发者根据需要定义几乎任何类型的字面量。

8. **避免全局命名冲突**：UDLs 通常定义在特定的命名空间中，这有助于避免全局命名冲突。

总的来说，UDLs 是一种强大的工具，可以在不破坏现有类型系统的前提下，为 C++ 语言提供扩展。开发者可以利用 UDLs 来创建更加清晰、直观和易于维护的代码。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
