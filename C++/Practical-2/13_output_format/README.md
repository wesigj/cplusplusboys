# C++ Practical-2 day13 输出格式

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.输出格式

在 C++ 中，输出格式通常由 `iostream` 库中的流操作符（`<<`）控制。你可以使用这些操作符来格式化输出到标准输出（`std::cout`）或其他输出流。以下是一些常见的输出格式示例：

### 1.1.基础输出

```cpp
#include <iostream>

int main() {
    int num = 10;
    double pi = 3.14159;
    std::string str = "Hello, World!";

    std::cout << "Numbers: " << num << std::endl;
    std::cout << "Pi: " << pi << std::endl;
    std::cout << "String: " << str << std::endl;

    return 0;
}
```

### 1.2.宽度和精度

你可以设置流的宽度和精度来控制输出格式。

```cpp
#include <iostream>
#include <iomanip>

int main() {
    double price = 19.99;

    std::cout << "Default output: " << price << std::endl;
    std::cout << "Formatted output: " << std::fixed << std::setprecision(2) << price << std::endl;
    std::cout << "Right-justified: " << std::setw(10) << std::setfill('*') << "Right" << std::endl;

    return 0;
}
```

### 1.3.十六进制和科学计数法

```cpp
#include <iostream>
#include <iomanip>

int main() {
    int hexValue = 255;
    double scientificValue = 1234.56;

    std::cout << "Hexadecimal: " << std::hex << hexValue << std::endl;
    std::cout << "Scientific notation: " << std::scientific << scientificValue << std::endl;

    return 0;
}
```

### 1.4.布尔值

```cpp
#include <iostream>

int main() {
    bool isTrue = true;
    bool isFalse = false;

    std::cout << "Boolean true: " << isTrue << std::endl;   // 输出 1
    std::cout << "Boolean false: " << isFalse << std::endl; // 输出 0

    return 0;
}
```

### 1.5.宽字符和字符串

```cpp
#include <iostream>
#include <string>

int main() {
    wchar_t wideChar = L'A';
    std::wstring wstr = L"Wide String";

    std::wcout << "Wide character: " << wideChar << std::endl;
    std::wcout << "Wide string: " << wstr << std::endl;

    return 0;
}
```

### 1.6.格式化输出

```cpp
#include <iostream>
#include <iomanip>

int main() {
    int year = 2024;
    double temperature = 23.6;
    std::string location = "Shanghai";

    std::cout << "It is " << temperature << " degrees in " << location
              << " this year " << year << "." << std::endl;

    // 使用 setw 和 setfill 进行格式化
    std::cout << std::setw(5) << std::setfill('0') << year << std::endl;
    std::cout << std::fixed << std::setprecision(2) << temperature << std::endl;

    return 0;
}
```

### 1.6.错误处理

```cpp
#include <iostream>
#include <fstream>
#include <stdexcept>

int main() {
    std::ofstream outFile("example.txt");

    if (!outFile) {
        throw std::runtime_error("Unable to open file for writing.");
    }

    outFile << "Hello, File!" << std::endl;

    if (outFile.fail()) {
        throw std::runtime_error("Failed to write to file.");
    }

    outFile.close();

    return 0;
}
```

在这些示例中，我们使用了 `std::cout`、`std::wcout`、`std::fixed`、`std::setprecision`、`std::setw`、`std::setfill` 和 `std::hex` 等来控制输出格式。通过这些操作符和控制符，你可以创建清晰、一致的输出格式。

## 2.在输出中包含货币符号，比如美元符号，我应该如何设置 C++ 的输出格式？

在 C++ 中，如果你想在输出中包含货币符号，比如美元符号，你可以使用 `std::locale` 和 `std::cout` 的格式化功能。`std::locale` 允许你设置地区特定的格式化，包括货币符号。

以下是一个示例，展示了如何设置输出格式以包含美元符号：

```cpp
#include <iostream>
#include <locale>

int main() {
    // 设置地区为美国，这通常会使用美元符号
    std::locale::global(std::locale("en_US.UTF-8"));

    double amount = 1234.56;

    // 使用 std::cout 输出货币格式
    std::cout << std::showbase << "Amount: $" << amount << std::endl;

    // 如果你想要更精确地控制货币的显示格式，可以使用 std::moneypunct
    std::cout << "Amount with currency symbol: "
              << std::moneypunct<std::string::value_type,false>::char_type('¤') 
              << amount << std::endl;

    return 0;
}
```

在这个示例中，我们首先使用 `std::locale::global` 设置了程序的全局区域设置为美国（`en_US.UTF-8`），这通常会使用美元符号。然后，我们使用 `std::showbase` 来指示输出货币符号。

注意，`std::moneypunct` 是一个facet，它定义了货币的格式化方式。在这个例子中，我们直接使用了美元符号，但你可以通过 `std::moneypunct` 来获取当前区域设置的货币符号。

请确保你的系统支持 `en_US.UTF-8` 区域设置，否则你可能需要调整为适合你系统的区域设置。

如果你想要更精细的控制，你可以进一步探索 `std::moneypunct` 和 `std::numpunct` 来自定义数字和货币的格式化。

此外，如果你的系统支持 C++20 或更高版本，你可以使用 `std::format` 来更灵活地格式化输出：

```cpp
#include <iostream>
#include <format>
#include <locale>

int main() {
    std::locale::global(std::locale("en_US.UTF-8"));

    double amount = 1234.56;

    // 使用 std::format 输出货币格式
    // 头文件添加 #include <format>
    // 编译选项添加：-std=C++20
    std::cout << std::format("{:$L}", amount) << std::endl;

    return 0;
}
```

在这个示例中，`{:$L}` 是一个格式说明符，`$` 表示货币符号，`L` 表示当前区域设置的货币单位。

请记住，区域设置的支持取决于你的平台和编译器，你可能需要在你的系统上进行适当的配置才能使用这些功能。

## 3.在 C++ 中，除了使用 `std::locale` 和 `std::cout`，还有其他方法可以设置货币符号吗？

在 C++ 中，除了使用 `std::locale` 和 `std::cout` 来设置货币符号，还有其他一些方法可以在输出中包含货币符号：

1. **字符串拼接**：
   直接将货币符号作为字符串拼接到数字前。

   ```cpp
   #include <iostream>
   #include <string>

   int main() {
       double amount = 1234.56;
       std::string currencySymbol = "$";
       std::cout << currencySymbol << amount << std::endl;
       return 0;
   }
   ```

2. **使用 `std::format`（C++20）**：
   如果你使用的是支持 C++20 的编译器，`std::format` 提供了一种灵活的方式来格式化字符串。

   ```cpp
   #include <iostream>
   #include <format>

   int main() {
       double amount = 1234.56;
       std::cout << std::format("${:.2f}", amount) << std::endl;
       return 0;
   }
   ```

3. **使用 `iomanip` 库**：
   `iomanip` 库提供了一些操作符，如 `setprecision` 和 `fixed`，来控制浮点数的输出格式，但不直接支持货币符号。你可以结合字符串拼接使用。

   ```cpp
   #include <iostream>
   #include <iomanip>

   int main() {
       double amount = 1234.56;
       std::cout << "$" << std::fixed << std::setprecision(2) << amount << std::endl;
       return 0;
   }
   ```

4. **使用 `sprintf` 或 `snprintf`（C 风格的函数）**：
   这些函数允许你在 C++ 程序中使用 C 语言风格的格式化。

   ```cpp
   #include <iostream>
   #include <cstdio>

   int main() {
       double amount = 1234.56;
       char buffer[50];
       sprintf(buffer, "$%.2f", amount);
       std::cout << buffer << std::endl;
       return 0;
   }
   ```

5. **使用 `std::ostringstream`**：
   `std::ostringstream` 是一个字符串流，可以用来构建复杂的字符串。

   ```cpp
   #include <iostream>
   #include <sstream>
   #include <iomanip>

   int main() {
       double amount = 1234.56;
       std::ostringstream ss;
       ss << "$" << std::fixed << std::setprecision(2) << amount;
       std::cout << ss.str() << std::endl;
       return 0;
   }
   ```

6. **使用第三方库**：
   一些第三方库，如 Boost.Format，提供了更多的格式化选项。

   ```cpp
   #include <iostream>
   #include <boost/format.hpp>

   int main() {
       double amount = 1234.56;
       std::cout << (boost::format("$%.2f") % amount).str() << std::endl;
       return 0;
   }
   ```

7. **自定义函数**：
   你可以编写自己的函数来格式化货币字符串。

   ```cpp
   #include <iostream>
   #include <string>

   std::string formatCurrency(double amount) {
       return std::to_string(amount) + "$";
   }

   int main() {
       double amount = 1234.56;
       std::cout << formatCurrency(amount) << std::endl;
       return 0;
   }
   ```

这些方法提供了不同的方式来在 C++ 中设置货币符号。你可以选择最适合你需求的方法。

## 4.C++ 中的 `std::format` 是如何工作的，它有哪些优势？

在 C++20 中，`std::format` 是一种新的字符串格式化功能，它提供了一种类型安全且易于阅读的方式来格式化字符串。它类似于 Python 中的 `str.format()` 方法，并且相比于传统的 `printf` 函数，`std::format` 在编译时就能检查格式字符串的正确性，从而提高了代码的安全性和可读性。

### 4.1.如何工作

`std::format` 通过一个格式化字符串和一个参数列表来工作。格式化字符串包含了用于替换的占位符，这些占位符被花括号 `{}` 包围。在花括号内部，你可以指定参数的索引（从 0 开始）以及格式规范，例如：

- `{}`：默认格式
- `{:.2f}`：浮点数，保留两位小数
- `{:#x}`：十六进制整数，包含 `0x` 前缀
- `{:<10}`：左对齐，宽度为 10
- `{:>10}`：右对齐，宽度为 10
- `{:^10}`：居中对齐，宽度为 10

### 4.2.优势

1. **类型安全**：在编译时检查格式字符串和参数类型，减少运行时错误的风险。
2. **直观的语法**：格式化语法直观易懂，类似于字符串插值。
3. **灵活的格式化选项**：支持宽度、精度、填充字符、对齐方式等格式化选项。
4. **内置类型支持**：直接支持多种内置类型，无需手动指定格式说明符。
5. **可扩展性**：可以通过特化 `std::formatter` 来支持自定义类型的格式化。

### 4.3.示例

```cpp
#include <format>
#include <iostream>

int main() {
    int num = 42;
    double pi = 3.141592653589793;
    std::string str = "Hello, World!";
    
    // 使用 std::format 进行格式化
    std::string message = std::format("The number is {}, and pi is {:.2f}.", num, pi);
    std::cout << message << std::endl;

    // 动态生成格式字符串
    int width = 10;
    char fill = '*';
    std::string dynamic_format = std::format("{:>{}}", str, width, fill);
    std::cout << dynamic_format << std::endl;

    return 0;
}
```

在这个示例中，我们首先使用 `std::format` 来格式化一个包含整数和浮点数的字符串。然后，我们展示了如何动态生成格式字符串，包括指定宽度和填充字符。

`std::format` 是 C++20 引入的一项新特性，它提供了一种现代且强大的字符串格式化工具，可以简化代码并提高其可读性和安全性。

## 5.C++ 中的 `std::format` 与 Python 的 `str.format()` 方法在性能上有什么差异？

`std::format` 是 C++20 引入的一个新特性，它提供了一种类型安全且易于阅读的方式来格式化字符串。它与 Python 的 `str.format()` 方法相似，但有一些关键的差异。

### 5.1.性能差异

在性能方面，`std::format` 通常比 Python 的 `str.format()` 更快，因为它是在 C++20 标准中设计时就考虑了性能的。`std::format` 利用了 C++ 的类型系统和编译时特性，可以生成高效的代码。相比之下，Python 的 `str.format()` 方法在运行时解析和处理格式字符串，这可能会引入一些额外的性能开销。

### 5.2.优势

`std::format` 的一些主要优势包括：

1. **类型安全**：在编译时检查格式字符串和参数类型，减少运行时错误的风险。
2. **直观的语法**：格式化语法直观易懂，类似于字符串插值。
3. **灵活的格式化选项**：支持宽度、精度、填充字符、对齐方式等格式化选项。
4. **内置类型支持**：直接支持多种内置类型，无需手动指定格式说明符。
5. **可扩展性**：可以通过特化 `std::formatter` 来支持自定义类型的格式化。

### 5.3.示例

以下是使用 `std::format` 的一个简单示例：

```cpp
#include <format>
#include <iostream>

int main() {
    int num = 42;
    double pi = 3.141592653589793;
    std::string str = "Hello, World!";
    
    // 使用 std::format 进行格式化
    std::string message = std::format("The number is {}, and pi is {:.2f}.", num, pi);
    std::cout << message << std::endl;

    // 动态生成格式字符串
    int width = 10;
    char fill = '*';
    std::string dynamic_format = std::format("{:>{}}\n", str, width, fill);
    std::cout << dynamic_format << std::endl;

    return 0;
}
```

在这个示例中，我们首先使用 `std::format` 来格式化一个包含整数和浮点数的字符串。然后，我们展示了如何动态生成格式字符串，包括指定宽度和填充字符。

### 5.4.性能注意事项

尽管 `std::format` 提供了现代的格式化功能，但在性能敏感的应用中，你可能需要考虑以下几点：

1. **避免频繁的格式化操作**：频繁创建和销毁格式化字符串可能会导致性能损失。
2. **使用预分配的内存**：对于频繁使用的字符串，预先分配足够的内存可以减少内存分配的开销。
3. **选择正确的格式化方法**：在某些情况下，使用 C 风格的 `printf` 可能更高效，尤其是在处理简单格式化时。

总的来说，`std::format` 是 C++20 中一个强大且灵活的字符串格式化工具，它在许多方面都优于传统的格式化方法。然而，在性能敏感的场景中，仍然需要仔细考虑格式化操作的影响。

## 6.C++ 中的 `std::format` 支持哪些类型的格式化选项？

在 C++20 中，`std::format` 支持多种类型的格式化选项，包括但不限于以下几种：

1. **整数**：
   - 十进制：`{:d}` 或 `{}`
   - 十六进制：`{:x}`（小写）或 `{:X}`（大写）
   - 八进制：`{:o}`
   - 二进制：`{:b}`
   - 带前缀的十六进制：`{:#x}` 或 `{:#X}`
   - 带前缀的八进制：`{:#o}`
   - 带前缀的二进制：`{:#b}`

2. **浮点数**：
   - 定点表示法：`{:f}`
   - 科学计数法：`{:e}`（小写）或 `{:E}`（大写）
   - 通用格式：`{:g}`（小写）或 `{:G}`（大写）
   - 百分比：`{:%}`

3. **字符串**：
   - 字符串：`{:s}`
   - 宽度和填充：`{:<10}`（左对齐），`{:>10}`（右对齐），`{:^10}`（居中对齐）
   - 填充字符：`{:*^10}`（使用 `*` 作为填充字符）

4. **字符**：
   - 字符：`{:c}`

5. **指针**：
   - 指针：`{:p}`（打印指针地址）

6. **布尔值**：
   - 布尔值：`{:b}`

7. **chrono 类型**：
   - 时间点和持续时间：`{:%Y-%m-%d %H:%M:%S}`（日期和时间）

8. **自定义类型**：
   - 通过特化 `std::formatter` 可以支持自定义类型的格式化。

### 6.1.格式化选项的组合

除了基本的类型格式化选项，`std::format` 还支持组合使用多种格式化选项，例如：

- **宽度**：`{:10}`（设置宽度为10）
- **精度**：`{:.2f}`（浮点数保留两位小数）
- **填充字符**：`{:_^10}`（使用 `_` 作为填充字符，居中对齐）
- **对齐**：
  - 左对齐：`{:<10}`
  - 右对齐：`{:>10}`
  - 居中对齐：`{:^10}`

### 6.2.示例

```cpp
#include <format>
#include <iostream>
#include <chrono>

int main() {
    int number = 42;
    double pi = 3.141592653589793;
    std::string text = "Hello, World!";
    bool flag = true;
    std::chrono::seconds duration(5);

    std::string formatted_text = std::format("{}, {:.2f}, {}, {:b}, {:p}, {:%S}", number, pi, text, flag, &number, duration);
    std::cout << formatted_text << std::endl;

    return 0;
}
```

在这个示例中，我们使用了不同类型的格式化选项来格式化整数、浮点数、字符串、布尔值、指针和 chrono 类型。

`std::format` 的灵活性和强大的格式化选项使其成为 C++20 中一个非常有用的工具。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
