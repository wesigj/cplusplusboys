# C++11 06-正则表达式 regular expression

- [C++11 06-正则表达式 regular expression](#c11-06-正则表达式-regular-expression)
  - [Overview](#overview)
  - [1.正则表达式 regular expression](#1正则表达式-regular-expression)
  - [2.在 C++11 中，如何使用正则表达式进行字符串的分割和提取？](#2在-c11-中如何使用正则表达式进行字符串的分割和提取)
    - [2.1. 包含必要的头文件](#21-包含必要的头文件)
    - [2.2. 使用 `std::regex` 进行分割](#22-使用-stdregex-进行分割)
      - [2.2.1.示例：分割字符串](#221示例分割字符串)
    - [2.3. 使用 `std::regex_search` 提取子串](#23-使用-stdregex_search-提取子串)
      - [2.3.1.示例：提取字符串](#231示例提取字符串)
    - [2.4. 使用命名捕获组](#24-使用命名捕获组)
      - [2.4.1.示例：使用命名捕获组](#241示例使用命名捕获组)
    - [2.5.注意事项](#25注意事项)
  - [3.在 C++ 中，如何使用正则表达式进行复杂的字符串匹配和替换？](#3在-c-中如何使用正则表达式进行复杂的字符串匹配和替换)
    - [3.1.字符串匹配](#31字符串匹配)
    - [3.2.字符串搜索](#32字符串搜索)
    - [3.3.字符串替换](#33字符串替换)
    - [3.4.使用正则表达式进行分割和提取](#34使用正则表达式进行分割和提取)
  - [4.C++11正则表达式中，如何使用命名捕获组来提取特定的匹配内容？](#4c11正则表达式中如何使用命名捕获组来提取特定的匹配内容)
    - [4.1. 定义命名捕获组](#41-定义命名捕获组)
    - [4.2. 示例代码](#42-示例代码)
    - [4.3. 详细步骤](#43-详细步骤)
    - [4.4. 替换操作中的命名捕获组](#44-替换操作中的命名捕获组)
  - [5.在使用正则表达式进行字符串分割时，如何避免常见的错误和陷阱？](#5在使用正则表达式进行字符串分割时如何避免常见的错误和陷阱)
    - [5.1.示例代码](#51示例代码)
  - [6.如何优化正则表达式以提高字符串分割的性能？](#6如何优化正则表达式以提高字符串分割的性能)
  - [7.在使用正则表达式时，有哪些常见的错误类型我应该避免？](#7在使用正则表达式时有哪些常见的错误类型我应该避免)
  - [关于作者](#关于作者)

## Overview

---

## 1.正则表达式 regular expression

在 C++11 中，正则表达式是通过 `<regex>` 头文件提供的，它支持 ECMAScript 语法作为默认的正则表达式语法。以下是一些基本的使用场景和示例：

1. **匹配整个字符串**：使用 `std::regex_match` 来检查整个字符串是否与正则表达式匹配。

   ```cpp
   std::string str = "Hello, world!";
   std::regex pattern("^[a-zA-Z ]+$");
   bool is_matched = std::regex_match(str, pattern);
   ```

2. **搜索字符串**：使用 `std::regex_search` 来查找字符串中是否包含与正则表达式匹配的子串。

   ```cpp
   std::string str = "Hello, world!";
   std::regex pattern("\\w+"); // 匹配一个或多个字母或数字
   std::smatch match;
   if (std::regex_search(str, match, pattern)) {
       // 找到了匹配项
   }
   ```

3. **替换字符串**：使用 `std::regex_replace` 来替换字符串中与正则表达式匹配的部分。

   ```cpp
   std::string str = "Hello, world!";
   std::regex pattern("world");
   std::string new_str = std::regex_replace(str, pattern, "there");
   ```

4. **使用迭代器遍历所有匹配项**：使用 `std::regex_iterator` 来遍历字符串中所有与正则表达式匹配的子串。

   ```cpp
   std::string str = "123 abc 456";
   std::regex pattern("\\d+"); // 匹配数字序列
   std::sregex_iterator it(str.begin(), str.end(), pattern);
   std::sregex_iterator end;
   for (; it != end; ++it) {
       std::smatch match = *it;
       std::cout << match.str() << std::endl;
   }
   ```

5. **使用命名捕获组**：可以在正则表达式中使用括号来创建捕获组，并在替换操作中引用它们。

   ```cpp
   std::string str = "John Smith";
   std::regex pattern("(\\w+) (\\w+)");
   std::string new_str = std::regex_replace(str, pattern, "$2, $1");
   ```

6. **使用正则表达式进行输入验证**：例如，验证电子邮件地址或电话号码。

   ```cpp
   std::string email = "user@example.com";
   std::regex email_pattern("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,6}$");
   bool is_valid_email = std::regex_match(email, email_pattern);
   ```

7. **使用正则表达式进行字符串分割**：使用 `std::regex_token_iterator` 来分割字符串。

   ```cpp
   std::string str = "apple,banana,cherry";
   std::regex pattern(",");
   std::sregex_token_iterator it(str.begin(), str.end(), pattern, -1);
   std::sregex_token_iterator end;
   for (; it != end; ++it) {
       std::cout << it->str() << std::endl;
   }
   ```

这些是 C++11 中正则表达式的一些基本应用。正则表达式是一个非常强大的工具，可以用来执行复杂的文本处理任务。

## 2.在 C++11 中，如何使用正则表达式进行字符串的分割和提取？

在 C++11 中，你可以使用 `<regex>` 库中的 `std::regex` 和 `std::sregex_token_iterator` 来分割字符串和提取子串。以下是如何进行字符串分割和提取的步骤和示例：

### 2.1. 包含必要的头文件

```cpp
#include <regex>
#include <string>
#include <iostream>
#include <vector>
```

### 2.2. 使用 `std::regex` 进行分割

你可以使用正则表达式来定义分割规则，然后使用 `std::regex_token_iterator` 来遍历匹配的子串。

#### 2.2.1.示例：分割字符串

```cpp
int main() {
    std::string str = "apple,banana,cherry";
    std::regex reg(",");  // 分隔符为逗号
    std::sregex_token_iterator it(str.begin(), str.end(), reg, -1);
    std::sregex_token_iterator end;

    std::vector<std::string> tokens;
    for (; it != end; ++it) {
        tokens.push_back(it->str());
    }

    for (const auto& token : tokens) {
        std::cout << token << std::endl;
    }

    return 0;
}
```

在这个例子中，我们使用逗号（`,`）作为分隔符来分割字符串，并将结果存储在 `std::vector<std::string>` 中。

### 2.3. 使用 `std::regex_search` 提取子串

如果你想根据正则表达式提取字符串中的特定部分，可以使用 `std::regex_search` 函数。

#### 2.3.1.示例：提取字符串

```cpp
int main() {
    std::string str = "John Doe <john.doe@example.com>";
    std::regex email_regex("(\\w+)\\s+<(.+?)>");
    std::smatch match;

    if (std::regex_search(str, match, email_regex)) {
        std::cout << "Name: " << match[1] << std::endl;
        std::cout << "Email: " << match[2] << std::endl;
    }

    return 0;
}
```

在这个例子中，我们使用正则表达式匹配名字和电子邮件地址，并从匹配结果中提取这两部分。

### 2.4. 使用命名捕获组

你可以在正则表达式中使用命名捕获组来更清晰地提取特定部分。

#### 2.4.1.示例：使用命名捕获组

```cpp
int main() {
    std::string str = "John Doe <john.doe@example.com>";
    std::regex email_regex("(?<name>\\w+)\\s+<(?<email>.+?)>");
    std::smatch match;

    if (std::regex_search(str, match, email_regex)) {
        std::cout << "Name: " << match["name"] << std::endl;
        std::cout << "Email: " << match["email"] << std::endl;
    }

    return 0;
}
```

在这个例子中，我们定义了两个命名捕获组 `name` 和 `email`，并使用它们来提取匹配的子串。

### 2.5.注意事项

1. **正则表达式性能**：复杂的正则表达式可能会影响性能，特别是在大型文本数据上。
2. **异常处理**：确保处理可能的正则表达式错误，例如使用 `std::regex_error`。
3. **迭代器失效**：在修改字符串时，确保迭代器仍然有效。

通过使用 C++11 的正则表达式库，你可以方便地进行字符串分割和提取操作，这为文本处理提供了强大的工具。

## 3.在 C++ 中，如何使用正则表达式进行复杂的字符串匹配和替换？

在 C++11 中，正则表达式库提供了强大的工具来执行复杂的字符串匹配和替换。以下是如何使用正则表达式进行这些操作的一些基本方法：

### 3.1.字符串匹配

使用 `std::regex_match` 可以检查整个字符串是否与正则表达式匹配。例如，如果你想检查一个字符串是否包含一个或多个数字，可以使用如下代码：

```cpp
#include <regex>
#include <string>

bool contains_digit(const std::string& str) {
    std::regex digit_regex(".*\\d+.*");
    return std::regex_match(str, digit_regex);
}
```

### 3.2.字符串搜索

使用 `std::regex_search` 可以在字符串中搜索与正则表达式匹配的子串。例如，如果你想找到字符串中的第一个数字序列，可以使用：

```cpp
#include <regex>
#include <string>

std::string find_first_digit(const std::string& str) {
    std::regex digit_regex("(\\d+)");
    std::smatch match;
    if (std::regex_search(str, match, digit_regex)) {
        return match.str(1); // 返回第一个捕获组的内容
    }
    return "";
}
```

### 3.3.字符串替换

使用 `std::regex_replace` 可以替换字符串中与正则表达式匹配的部分。例如，如果你想将字符串中的所有数字替换为星号（*），可以使用：

```cpp
#include <regex>
#include <string>

std::string replace_digits_with_stars(const std::string& str) {
    std::regex digit_regex("(\\d+)");
    return std::regex_replace(str, digit_regex, "*");
}
```

### 3.4.使用正则表达式进行分割和提取

如果你想使用正则表达式来分割字符串，可以使用 `std::regex_token_iterator`。例如，如果你想按照逗号分割字符串：

```cpp
#include <regex>
#include <string>
#include <vector>
#include <iostream>

std::vector<std::string> split_string(const std::string& str, char delimiter) {
    std::regex token_regex("([^,]+)");
    std::sregex_token_iterator it(str.begin(), str.end(), token_regex, -1);
    std::sregex_token_iterator reg_end;
    std::vector<std::string> tokens(std::distance(it, reg_end), "");

    for (; it != reg_end; ++it) {
        tokens.push_back(it->str());
    }

    return tokens;
}
```

这些是 C++11 中使用正则表达式进行字符串匹配和替换的基本方法。你可以根据自己的需求编写更复杂的正则表达式来执行更高级的文本处理任务。

## 4.C++11正则表达式中，如何使用命名捕获组来提取特定的匹配内容？

在 C++11 中，使用命名捕获组可以方便地从正则表达式中提取特定的匹配内容。命名捕获组允许你通过指定的名称来引用匹配的子组，这使得代码更加清晰和易于维护。

### 4.1. 定义命名捕获组

命名捕获组在正则表达式中通过 `?<name>` 语法定义。其中 `name` 是你为捕获组指定的名称。

### 4.2. 示例代码

以下是一个使用命名捕获组来提取特定匹配内容的示例：

```cpp
#include <iostream>
#include <regex>
#include <string>

int main() {
    std::string text = "John Smith: john.smith@example.com";
    std::regex email_regex("(?<name>[A-Za-z]+) (?<surname>[A-Za-z]+): (?<email>[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,6})");

    std::smatch match;
    if (std::regex_search(text, match, email_regex)) {
        std::cout << "Name: " << match["name"] << std::endl;
        std::cout << "Surname: " << match["surname"] << std::endl;
        std::cout << "Email: " << match["email"] << std::endl;
    }

    return 0;
}
```

### 4.3. 详细步骤

1. **包含必要的头文件**：

   ```cpp
   #include <regex>
   #include <string>
   #include <iostream>
   ```

2. **定义正则表达式**：
   使用命名捕获组语法 `?<name>` 来定义捕获组。

   ```cpp
   std::regex email_regex("(?<name>[A-Za-z]+) (?<surname>[A-Za-z]+): (?<email>[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,6})");
   ```

3. **搜索匹配项**：
   使用 `std::regex_search` 来在字符串中搜索匹配项。

   ```cpp
   std::smatch match;
   if (std::regex_search(text, match, email_regex)) {
       // 提取匹配的捕获组
   }
   ```

4. **提取命名捕获组**：
   使用命名捕获组的名称来提取匹配的子串。

   ```cpp
   std::cout << "Name: " << match["name"] << std::endl;
   std::cout << "Surname: " << match["surname"] << std::endl;
   std::cout << "Email: " << match["email"] << std::endl;
   ```

### 4.4. 替换操作中的命名捕获组

在替换操作中，也可以使用命名捕获组。例如，如果你想将名字和姓氏互换：

```cpp
#include <iostream>
#include <regex>
#include <string>

int main() {
    std::string text = "John Smith: john.smith@example.com";
    std::regex email_regex("(?<name>[A-Za-z]+) (?<surname>[A-Za-z]+): (?<email>[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,6})");

    std::string modified_text = std::regex_replace(text, email_regex, "$<surname> $<name>: $<email>");
    std::cout << modified_text << std::endl;

    return 0;
}
```

在这个例子中，`$<surname>`、`$<name>` 和 `$<email>` 分别表示命名捕获组的替换内容。

通过使用命名捕获组，你可以更方便地从正则表达式中提取特定的匹配内容，并使代码更加清晰和易于维护。

## 5.在使用正则表达式进行字符串分割时，如何避免常见的错误和陷阱？

在使用正则表达式进行字符串分割时，确实存在一些常见的错误和陷阱。以下是一些避免这些问题的建议：

1. **过度匹配**：
   - 确保你的正则表达式不会匹配比预期更多的内容。例如，使用 `\s+` 来分割字符串时，可能会过度匹配多个空格。
   - **解决方案**：使用非贪婪匹配，如 `(\s+)`。

2. **错误的分隔符**：
   - 确保选择正确的分隔符。错误的分隔符可能导致无法正确分割字符串。
   - **解决方案**：仔细选择和测试分隔符，确保它只匹配你想要分割的内容。

3. **包含分隔符**：
   - 在某些情况下，你可能不希望分隔符出现在结果数组中。
   - **解决方案**：使用 `std::regex_token_iterator` 并设置适当的子表达式索引。

4. **处理空字符串**：
   - 分割后可能会产生空字符串，特别是在分隔符连续出现的情况下。
   - **解决方案**：在处理结果时，检查空字符串并相应地处理。

5. **处理边缘情况**：
   - 确保处理字符串开头或结尾的分隔符。
   - **解决方案**：使用适当的正则表达式修饰符，如 `^` 和 `$`。

6. **性能问题**：
   - 复杂的正则表达式可能会导致性能问题，特别是在处理大量数据时。
   - **解决方案**：优化正则表达式，避免不必要的回溯和复杂的模式匹配。

7. **错误的迭代器使用**：
   - 在使用 `std::regex_token_iterator` 时，错误的迭代器使用可能导致漏掉匹配项或重复处理。
   - **解决方案**：确保正确使用迭代器，特别是在循环中。

8. **错误的捕获组**：
   - 如果使用捕获组，确保正确引用它们。
   - **解决方案**：使用 `std::smatch` 和相应的索引或命名捕获组来访问匹配项。

### 5.1.示例代码

以下是一个使用正则表达式分割字符串的示例，展示了如何避免一些常见的错误：

```cpp
#include <iostream>
#include <regex>
#include <vector>
#include <string>

int main() {
    std::string str = "apple,banana,,cherry";
    std::regex reg(",");
    std::sregex_token_iterator it(str.begin(), str.end(), reg, -1);
    std::sregex_token_iterator end;

    std::vector<std::string> tokens;
    for (; it != end; ++it) {
        std::string token = it->str();
        if (!token.empty()) {  // 忽略空字符串
            tokens.push_back(token);
        }
    }

    for (const auto& token : tokens) {
        std::cout << token << std::endl;
    }

    return 0;
}
```

在这个例子中，我们使用逗号（`,`）作为分隔符，并忽略空字符串。这样可以避免因连续分隔符导致的空字符串问题。

通过遵循这些建议，你可以避免在使用正则表达式进行字符串分割时的常见错误和陷阱。

## 6.如何优化正则表达式以提高字符串分割的性能？

要优化正则表达式以提高字符串分割的性能，可以考虑以下几个方面：

1. **避免使用复杂的正则表达式**：复杂的正则表达式可能会导致性能问题，尤其是在处理大规模文本数据时。简化正则表达式可以减少处理时间。

2. **使用非贪婪匹配**：在正则表达式中使用非贪婪量词（例如 `*?`、`+?`、`??`）来减少不必要的匹配，从而避免回溯问题。

3. **避免过多的分支选择**：分支选择（如 `(x|y|z)`）可能会导致正则表达式引擎尝试多个选项，增加了处理时间。如果可能，尝试合并分支或重新组织正则表达式。

4. **预编译正则表达式**：如果需要多次使用同一个正则表达式，预编译它以避免重复编译的开销。

5. **限制输入数据的大小**：在处理用户输入或大文件时，限制数据的大小可以减少匹配操作的负担。

6. **使用字符类和预定义字符集**：字符类（如 `[a-z]`）和预定义字符集（如 `\d`）通常比单独的字符更高效。

7. **避免不必要的捕获组**：不必要的捕获组会增加正则表达式的复杂度。如果不需要捕获组，可以使用非捕获组 `(?:...)`。

8. **使用适当的正则表达式引擎**：有些正则表达式引擎（如 RE2）在某些情况下可能比其他引擎（如 PCRE）更高效。

9. **避免使用过多的量词**：量词（如 `*`、`+`、`?`）可能会导致正则表达式引擎进行多次尝试，增加处理时间。

10. **测试和分析**：使用性能分析工具来测试正则表达式的性能，找出瓶颈并进行优化。

通过这些方法，可以提高正则表达式在字符串分割中的性能，减少处理时间并提高效率。

## 7.在使用正则表达式时，有哪些常见的错误类型我应该避免？

在使用正则表达式时，有一些常见的错误类型需要注意避免：

1. **过度匹配**：
   - 正则表达式可能会匹配比预期更多的内容。例如，使用 `.*` 可能会匹配整个字符串，包括换行符。

2. **错误的字符转义**：
   - 在正则表达式中，某些字符需要被转义（如 `.`、`*`、`?`、`(`、`)` 等）。如果忘记转义，可能会导致意外的结果。

3. **使用错误的量词**：
   - 错误地使用量词（如 `*`、`+`、`?`）可能导致匹配不符合预期。例如，`.*` 会匹配尽可能多的字符，而 `.+` 会匹配一个或多个字符。

4. **错误的字符类**：
   - 使用字符类时，可能会错误地包含或排除某些字符。例如，`[abc]` 只会匹配 `a`、`b` 或 `c`。

5. **锚点使用不当**：
   - 锚点（如 `^` 和 `$`）用于指定匹配的开始和结束位置。如果使用不当，可能会导致匹配结果不正确。

6. **分组和捕获组混淆**：
   - 捕获组（括号）和非捕获组（`(?:...)`）有不同的用途。如果混淆使用，可能会导致提取错误的匹配内容。

7. **贪婪量词与非贪婪量词混淆**：
   - 贪婪量词（如 `.*`）会尽可能多地匹配字符，而非贪婪量词（如 `.*?`）会尽可能少地匹配字符。混淆使用可能会导致性能问题或错误的匹配结果。

8. **复杂的嵌套和分支结构**：
   - 过于复杂的正则表达式可能会导致性能问题和难以理解的逻辑。

9. **忽略文化和区域设置**：
   - 在某些情况下，正则表达式可能需要考虑特定的文化和区域设置，如字符大小写和字符集。

10. **错误的括号匹配**：
    - 确保每个左括号 `(` 都有一个对应的右括号 `)`，反之亦然。

11. **使用正则表达式执行不可能的匹配**：
    - 某些模式可能在逻辑上不可能匹配任何内容，如 `a*b`（`a` 后面的 `b` 永远不会匹配）。

12. **在循环结构中不恰当地使用正则表达式**：
    - 在循环中使用正则表达式时，确保正确处理每次迭代的匹配结果。

13. **忽略正则表达式的性能影响**：
    - 复杂的正则表达式可能会对性能产生显著影响，特别是在处理大量数据时。

14. **错误的字符串边界处理**：
    - 使用 `\b` 来匹配单词边界，但有时候可能需要更精确地定义边界条件。

为了避免这些错误，建议编写正则表达式时进行充分的测试，并使用在线工具或IDE的正则表达式调试功能来检查和验证表达式的正确性。此外，保持正则表达式的简洁和易于理解也有助于减少错误。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
