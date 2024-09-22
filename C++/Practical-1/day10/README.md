# C++ Practical-1 day4

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.文件流`std::ifstream` `std::ofstream`

在C++中处理文件通常涉及到使用标准库中的文件流类，如`std::ifstream`（输入文件流）和`std::ofstream`（输出文件流）。以下是如何在C++中打开、读取、写入和关闭文件的示例：

```cpp
#include <iostream>
#include <fstream>
#include <string>

int main() {
    // 定义文件名
    const std::string filename = "example.txt";

    // 创建输出文件流对象，用于写入文件
    std::ofstream outFile(filename);

    // 检查文件是否成功打开
    if (!outFile.is_open()) {
        std::cerr << "Failed to open " << filename << " for writing." << std::endl;
        return 1;
    }

    // 写入内容到文件
    outFile << "Hello, World!\n";
    outFile << "This is a simple C++ file operation example.\n";

    // 关闭文件
    outFile.close();

    // 创建输入文件流对象，用于读取文件
    std::ifstream inFile(filename);

    // 检查文件是否成功打开
    if (!inFile.is_open()) {
        std::cerr << "Failed to open " << filename << " for reading." << std::endl;
        return 1;
    }

    // 读取文件内容
    std::string line;
    while (std::getline(inFile, line)) {
        std::cout << line << std::endl;
    }

    // 关闭文件
    inFile.close();

    return 0;
}
```

在这个示例中，我们首先创建了一个名为`example.txt`的文件，并使用`std::ofstream`向其中写入了一些文本。写入完成后，我们关闭了文件。然后，我们使用`std::ifstream`打开同一个文件，并读取其内容，将其打印到标准输出。

### 1.1.异常处理

在文件操作中，异常处理非常重要，因为文件可能因为各种原因（如权限问题、磁盘空间不足等）无法打开或写入。以下是如何在文件操作中添加异常处理的示例：

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <exception>

int main() {
    try {
        const std::string filename = "example.txt";

        // 创建输出文件流对象，用于写入文件
        std::ofstream outFile(filename);

        if (!outFile.is_open()) {
            throw std::runtime_error("Failed to open " + filename + " for writing.");
        }

        outFile << "Hello, World!\n";
        outFile << "This is a simple C++ file operation example.\n";
        outFile.close();

        // 创建输入文件流对象，用于读取文件
        std::ifstream inFile(filename);

        if (!inFile.is_open()) {
            throw std::runtime_error("Failed to open " + filename + " for reading.");
        }

        std::string line;
        while (std::getline(inFile, line)) {
            std::cout << line << std::endl;
        }
        inFile.close();
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
```

在这个示例中，我们使用了`try-catch`块来捕获可能发生的异常。如果在打开文件或写入文件时发生异常，程序将捕获异常并打印错误信息。

### 1.2.注意事项

1. **确保关闭文件**：在文件操作完成后，确保调用`close()`方法关闭文件。
2. **异常处理**：使用`try-catch`块来处理可能的异常。
3. **检查文件是否成功打开**：在进行文件读写操作之前，检查文件流对象是否成功打开了文件。

这些基本的文件操作和异常处理技巧可以帮助你安全地在C++中处理文件。

## 2.文件流追加`std::ofstream` `std::ios::app`

在C++中，要进行文件的追加操作，你可以使用`std::ofstream`类的构造函数，并在其中指定打开文件的模式为追加模式。追加模式可以通过传递`std::ios::app`标志来设置。

以下是如何使用`std::ofstream`以追加模式打开文件并写入内容的示例：

```cpp
#include <iostream>
#include <fstream>
#include <string>

int main() {
    // 定义文件名
    const std::string filename = "example.txt";

    // 创建输出文件流对象，以追加模式打开文件
    std::ofstream outFile(filename, std::ios::app);

    // 检查文件是否成功打开
    if (!outFile.is_open()) {
        std::cerr << "Failed to open " << filename << " for appending." << std::endl;
        return 1;
    }

    // 写入内容到文件末尾
    outFile << "This line will be appended to the end of the file.\n";

    // 关闭文件
    outFile.close();

    return 0;
}
```

在这个示例中，我们创建了一个`std::ofstream`对象，并在构造函数中传递了`std::ios::app`标志，这告诉文件流以追加模式打开文件。如果文件已经存在，写入操作将从文件的末尾开始，而不是覆盖现有内容。如果文件不存在，它将被创建。

### 2.1.注意事项

1. **文件指针位置**：在追加模式下，文件指针初始位置在文件末尾，所以写入操作总是追加到文件的末尾。
2. **文件不存在时的行为**：如果指定的文件不存在，以追加模式打开文件流将会创建该文件。
3. **关闭文件**：虽然文件流的析构函数会在对象超出作用域时自动关闭文件，但显式调用`close()`方法是一个好习惯，尤其是在你还需要检查文件是否成功关闭的情况下。
4. **异常处理**：考虑在文件操作中添加异常处理，以处理可能发生的错误。

使用追加模式是处理日志文件或其他需要持续添加数据的场景的常用方法。

## 3.文件的特定位置插入内容，而不是追加

在C++中，如果你想在文件的特定位置插入内容，而不是追加到文件末尾，你需要执行以下步骤：

1. **读取文件内容**：首先，读取整个文件内容到内存中。
2. **修改内容**：在内存中修改内容，插入所需的文本。
3. **写入文件**：将修改后的内容写回文件，覆盖原始内容。

以下是一个示例，展示了如何在文件的特定位置插入内容：

```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

bool insertText(const std::string &filename, const std::string &insertText, int position) {
    std::ifstream inFile(filename, std::ios::in | std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open " << filename << " for reading." << std::endl;
        return false;
    }

    // 读取文件内容到字符串
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string fileContent = buffer.str();
    inFile.close();

    // 检查插入位置是否有效
    if (position < 0 || position > static_cast<int>(fileContent.size())) {
        std::cerr << "Invalid position for insertion." << std::endl;
        return false;
    }

    // 在特定位置插入文本
    std::string modifiedContent = fileContent.substr(0, position) + insertText + fileContent.substr(position);

    // 将修改后的内容写回文件
    std::ofstream outFile(filename, std::ios::out | std::ios::trunc | std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open " << filename << " for writing." << std::endl;
        return false;
    }
    outFile.write(modifiedContent.c_str(), modifiedContent.size());
    outFile.close();

    return true;
}

int main() {
    const std::string filename        = "example.txt";
    const std::string insertText_temp = "Inserted Text: ";
    int               position        = 10; // 插入位置

    if (insertText(filename, insertText_temp, position)) {
        std::cout << "Text inserted successfully." << std::endl;
    } else {
        std::cout << "Failed to insert text." << std::endl;
    }

    return 0;
}
```

在这个示例中，我们定义了一个`insertText`函数，它接受文件名、要插入的文本和插入位置作为参数。函数首先以读取模式打开文件，并读取文件内容到一个字符串中。然后，它检查插入位置是否有效，并在指定位置插入文本。最后，它以写入模式打开文件，并写入修改后的内容，覆盖原始文件。

### 3.1.注意事项

1. **文件大小**：如果文件非常大，将整个文件内容读入内存可能会导致内存不足的问题。
2. **二进制模式**：在处理非文本文件时，使用`std::ios::binary`标志以确保正确处理文件内容。
3. **错误处理**：确保在文件操作中添加异常处理和错误检查。
4. **性能**：对于大文件，这种操作可能会很慢，因为它需要读取和重写整个文件内容。

这种方法适用于需要在文件的特定位置插入内容的场景，但需要注意文件大小和内存使用。

## 4.文件中查找特定内容，有没有推荐的算法或工具？

在C++中，如果你想在文件中查找特定内容，有几种方法可以考虑：

1. **线性搜索**：这是最直接的方法，即从文件的开始逐字节或逐行读取，直到找到所需的内容。这种方法简单但效率不高，特别是对于大文件。

2. **使用标准库**：C++标准库提供了一些工具，如`std::string::find`，可以用来在字符串中搜索子串。如果你正在处理文本文件，你可以读取文件到一个字符串中，然后使用这种方法。

3. **使用文件流**：通过`std::ifstream`和`std::ofstream`类进行文件的读取和写入操作。你可以逐行读取文件内容，并使用`std::string::find`来查找特定的字符串。

4. **使用第三方库**：例如，使用Boost库中的算法，或者专门的文本搜索库，如`igotocode.com`上提到的文本搜索算法。

5. **分块查找**：如果文件非常大，可以考虑将文件分成多个块，并在每个块中进行搜索。这种方法可以减少内存消耗，并可能通过并行处理提高效率。

6. **二分查找**：如果你正在处理一个已排序的文件，可以使用二分查找算法来提高搜索效率。

7. **使用操作系统工具**：在某些情况下，使用操作系统提供的命令行工具（如Linux的`grep`）可能更简单、更快。

8. **使用专业软件**：对于非常大的文件，可能需要使用专业的文本搜索工具，如Everything、Listary或AnyTXT Searcher，这些工具能够建立文件内容的索引并快速搜索。

选择哪种方法取决于你的具体需求，包括文件大小、是否需要频繁搜索、是否可以接受外部依赖等。对于大多数简单用途，使用C++标准库中的文件流和字符串搜索功能可能就足够了。

## 5.使用文件流进行文件追加操作时，如何避免潜在的文件锁定问题？

在C++中，进行文件追加操作时，通常使用`std::ofstream`类的构造函数或`open`成员函数，并结合`ios::app`模式标志。这种方式下，所有写入操作都会自动定位到文件末尾，从而实现追加，而不会覆盖现有内容。

为了避免潜在的文件锁定问题，特别是在多线程或多进程环境中，可以采取以下措施：

1. **使用`ios::app`模式打开文件**：这确保了写入操作不会影响文件的其他部分。

   ```cpp
   std::ofstream outFile("filename.txt", std::ios::app);
   ```

2. **确保线程安全**：在多线程环境中，确保对文件的写入操作是线程安全的。如果多个线程需要写入同一个文件，可以使用互斥量（`std::mutex`）来同步访问。

   ```cpp
   std::mutex fileMutex;
   // 在写入之前锁定互斥量
   std::lock_guard<std::mutex> lock(fileMutex);
   outFile << "Some data" << std::endl;
   ```

3. **避免在持有锁时进行长时间操作**：如果你需要对文件执行复杂的写入操作，尽量避免在持有锁的状态下进行，这样可以减少锁的争用。

4. **使用文件锁**：在Unix/Linux系统上，可以使用`flock`或`fcntl`来实现文件锁，以防止多个进程同时写入同一个文件。这通常在涉及到多进程而非多线程时使用。

   ```cpp
   #include <fcntl.h>
   int fd = open("filename.txt", O_RDWR | O_CREAT, 0666);
   flock(fd, LOCK_EX); // 独占锁
   // 执行写入操作
   flock(fd, LOCK_UN); // 解锁
   close(fd);
   ```

5. **使用C++17文件系统库**：C++17引入了`std::filesystem`库，它提供了更高级的文件操作功能，包括文件锁等。

6. **考虑使用第三方库**：如果标准库提供的功能不足以满足需求，可以考虑使用第三方库，如Boost库中的文件锁机制。

7. **避免频繁的文件操作**：频繁地打开和关闭文件会增加锁的开销。如果可能，尝试批量处理文件写入操作。

8. **使用RAII机制管理资源**：确保文件在不再需要时能够被正确关闭。这可以通过对象的析构函数来自动完成。

通过上述措施，你可以有效地避免文件锁定问题，确保文件追加操作的安全性和效率。

## 6.函数get和getline读取数据

在C++中，`get`和`getline`是两个用于从输入流中读取数据的函数，它们通常与`istream`类的对象（如`cin`、`ifstream`）一起使用。这两个函数的主要区别在于它们处理空格和换行符的方式。

### 6.1.get()

`get()`函数用于从输入流中读取字符，直到遇到换行符或EOF（文件结束标志）。它会自动忽略前面的空白字符（包括空格、制表符和换行符），然后开始读取，直到遇到下一个换行符或EOF。`get()`函数可以用于读取单个字符或字符数组。

**读取单个字符：**

```cpp
int c;
cin.get(c);
```

**读取字符数组：**

```cpp
char buffer[100];
cin.get(buffer, 100);
// 或者
cin >> buffer;

```

注意：使用`>>`运算符和`get()`函数读取字符数组的效果是一样的。

### 6.2.getline()

`getline()`函数用于从输入流中读取一行数据，直到遇到换行符。它会将换行符也读取到字符串中，但通常在将字符串存储到`std::string`对象或字符数组时，换行符会被自动去除。`getline()`函数只能用于读取`std::string`对象或字符数组。

**读取到std::string对象：**

```cpp
std::string line;
getline(cin, line);
```

**读取到字符数组：**

```cpp
char buffer[100];
cin.getline(buffer, 100);

```

注意：`cin.getline()`是`istream`类的成员函数，它与全局函数`getline()`不同。`cin.getline()`不会自动去除换行符。

### 6.3.区别总结

- `get()`可以读取单个字符或字符数组，而`getline()`只能读取到`std::string`对象或字符数组。
- `get()`会忽略前面的空白字符，而`getline()`不会忽略任何字符，包括前面的空白字符。
- `getline()`会读取换行符之前的整行数据，而`get()`会读取到第一个换行符为止的数据。

### 6.4.示例

```cpp
#include <iostream>
#include <string>

int main() {
    std::string line;

    // 使用getline读取一行
    std::cout << "Enter a line: ";
    getline(std::cin, line);
    std::cout << "You entered: " << line << std::endl;

    // 使用get读取字符数组
    char buffer[100];
    std::cout << "Enter a word: ";
    std::cin.get(buffer, 100);
    std::cout << "You entered: " << buffer << std::endl;

    return 0;
}
```

在这个示例中，`getline()`用于读取用户输入的一整行数据，而`get()`用于读取用户输入的单个单词。注意，在调用`get()`之前，可能需要使用`cin.ignore()`来忽略前一个输入留在输入流中的换行符。

## 7.在C++中，除了get和getline，还有哪些其他方式可以读取用户输入？

在C++中，除了`get`和`getline`，还有多种其他方式可以读取用户输入。以下是一些常用的方法：

1. **使用`cin`和流提取运算符`>>`**：
   这是最常用的读取输入的方法，可以用于读取基本数据类型和自定义类型（只要它们重载了`>>`运算符）。

   ```cpp
   int num;
   std::cout << "Enter a number: ";
   std::cin >> num;
   ```

2. **使用`scanf`函数**：
   C语言中的`scanf`函数也可以用来在C++中读取输入。它提供了格式化的输入。

   ```cpp
   printf("Enter a number: ");
   scanf("%d", &num);
   ```

3. **使用`istream`类的成员函数`read`**：
   `read`函数用于读取指定数量的字符到字符数组中。

   ```cpp
   char buffer[100];
   std::cin.read(buffer, sizeof(buffer));
   ```

4. **使用`istream`类的成员函数`ignore`**：
   `ignore`函数用于忽略输入流中的指定数量的字符，或者直到遇到特定的分隔符。

   ```cpp
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   ```

5. **使用`istream`类的成员函数`get`**：
   `get`函数用于读取下一个字符（不读取换行符）。

   ```cpp
   char ch;
   std::cin.get(ch);
   ```

6. **使用`istream`类的成员函数`peek`**：
   `peek`函数用于查看下一个字符，但不从流中移除它。

   ```cpp
   int c = std::cin.peek();
   ```

7. **使用`istream`类的成员函数`unget`**：
   `unget`函数用于将一个字符放回输入流中（通常用于错误恢复）。

   ```cpp
   std::cin.unget();
   ```

8. **使用`std::string`类的成员函数`assign`**：
   可以从字符串流中读取一行或整个文件到`std::string`对象中。

   ```cpp
   std::string line;
   std::getline(std::cin, line);
   ```

9. **使用`std::stringstream`**：
   可以将输入读取到`std::stringstream`对象中，然后使用流提取运算符`>>`或`getline`读取到所需的变量中。

   ```cpp
   std::string input;
   std::cin >> input;
   std::stringstream ss(input);
   int num;
   ss >> num;
   ```

10. **使用`std::vector`和循环**：
    对于复杂的输入，如读取多个值，可以使用循环和`std::vector`。

    ```cpp
    std::vector<int> numbers;
    int num;
    while (std::cin >> num) {
        numbers.push_back(num);
    }
    ```

11. **使用`<conio.h>`库中的`getch`或`getche`**：
    在Windows系统中，可以使用`getch`或`getche`函数读取单个字符，而不需要按回车键。

    ```cpp
    #include <conio.h>
    char ch = _getch();
    ```

12. **使用`<iostream>`和`<sstream>`库**：
    可以将输入读取到`std::istringstream`对象中，然后从中提取数据。

    ```cpp
    std::string input;
    std::cin >> input;
    std::istringstream iss(input);
    int num;
    iss >> num;
    ```

这些方法可以根据不同的应用场景和需求选择使用。

## 8.std::cout

在C++中，`cout` 是标准库中的一个非常基本和常用的对象，它代表标准输出流。它通常用于将数据输出到控制台（屏幕）。`cout` 是 `std` 命名空间中的 `ostream` 类的一个实例，因此它支持插入运算符 (`<<`)，可以与各种数据类型一起使用来输出数据。

以下是一些使用 `cout` 输出数据的基本示例：

### 8.1.输出文本和变量

```cpp
#include <iostream>

int main() {
    int num = 10;
    double pi = 3.14159;
    std::cout << "Hello, World!\n";
    std::cout << "The value of num is: " << num << std::endl;
    std::cout << "The value of pi is: " << pi << std::endl;
    return 0;
}
```

### 8.2.输出不同的数据类型

```cpp
#include <iostream>

int main() {
    bool isTrue = true;
    char ch = 'A';
    int age = 30;
    double salary = 55000.50;

    std::cout << "Boolean: " << isTrue << std::endl;
    std::cout << "Character: " << ch << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Salary: " << salary << std::endl;
    return 0;
}
```

### 8.3.使用操纵符（Manipulators）

C++提供了一些操纵符来控制输出格式，例如 `std::setw` 设置字段宽度，`std::setprecision` 设置浮点数的精度等。

```cpp
#include <iostream>
#include <iomanip>

int main() {
    double pi = 3.14159;

    std::cout << "Default precision: " << pi << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Fixed precision: " << pi << std::endl;
    std::cout << std::setw(10) << "Width: " << std::left << "Left aligned." << std::endl;
    return 0;
}
```

### 8.4.输出字符串和字符

```cpp
#include <iostream>

int main() {
    std::string name = "John Doe";
    char ch = 'A';

    std::cout << "Name: " << name << std::endl;
    std::cout << "Character: " << ch << std::endl;
    return 0;
}
```

### 8.5.输出未定义流宽度的类型

对于像 `std::endl` 这样的流操纵符，或者像 `std::flush` 这样的函数，不需要指定变量，因为它们作用于流本身。

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl; // 输出并换行
    std::cout << "This message will not appear until we call flush." << std::flush; // 输出并刷新输出缓冲区
    return 0;
}
```

### 8.6.组合输出

可以将多个插入运算符组合起来，连续输出多个变量或文本。

```cpp
#include <iostream>

int main() {
    int a = 5;
    int b = 10;
    std::cout << "a + b = " << a + b << std::endl;
    return 0;
}
```

`cout` 是 C++ 中输出数据的默认和最方便的方式。它的行为可以通过各种流操纵符进行微调，以满足不同的输出需求。

## 9.std::cout format 格式化输出

在C++中，使用`cout`输出格式化文本通常涉及到以下几个方面：

1. **设置字段宽度**：使用`std::setw`来设置下一个输出项的宽度。

   ```cpp
   std::cout << std::setw(10) << "Value" << std::endl;
   ```

2. **设置精度**：使用`std::setprecision`来设置浮点数的输出精度。

   ```cpp
   std::cout << std::fixed << std::setprecision(2) << 3.14159 << std::endl;
   ```

3. **调整浮点数表示**：使用`std::fixed`或`std::scientific`来控制浮点数的输出格式。

   ```cpp
   std::cout << std::fixed << 3.14159 << std::endl; // 固定点表示
   std::cout << std::scientific << 3.14159 << std::endl; // 科学计数法表示
   ```

4. **设置对齐方式**：使用`std::left`或`std::right`来设置文本的对齐方式。

   ```cpp
   std::cout << std::setw(10) << std::left << "Left aligned" << std::endl;
   std::cout << std::setw(10) << std::right << "Right aligned" << std::endl;
   ```

5. **输出布尔值**：布尔值`true`和`false`通常被输出为`1`和`0`，但可以通过自定义流操纵符来改变这一行为。

6. **输出十六进制数**：使用`std::hexfloat`来输出浮点数的十六进制表示。

   ```cpp
   std::cout << std::hexfloat << 3.14159 << std::endl;
   ```

7. **填充字符**：使用`std::setfill`来设置用于填充额外空间的字符。

   ```cpp
   std::cout << std::setw(10) << std::setfill('*') << "Text" << std::endl;
   ```

8. **输出端的换行和空格**：使用`std::endl`来输出换行，使用`std::flush`来刷新输出缓冲区。

9. **宽字符和宽字符串**：使用`std::setw`和`std::setfill`的宽字符版本`std::setw(10, L'*')`来格式化宽字符。

下面是一个综合示例，展示了如何使用这些格式化技术：

```cpp
#include <iostream>
#include <iomanip>

int main() {
    double pi = 3.14159;
    std::string name = "Kimi";
    int number = 42;

    std::cout << "Formatted Output:\n";
    std::cout << std::setw(10) << std::setfill('*') << "Name: " << name << std::endl;
    std::cout << std::setw(10) << std::setfill('*') << "Num: " << number << std::endl;
    std::cout << std::setw(15) << std::setfill(' ') << std::left << "Pi value: " << pi << std::endl;
    std::cout << std::fixed << std::setprecision(3) << "Pi value (fixed): " << pi << std::endl;
    std::cout << std::scientific << "Pi value (scientific): " << pi << std::endl;
    std::cout << std::hexfloat << "Pi value (hex): " << pi << std::endl;

    return 0;
}
```

在这个示例中，我们设置了字段宽度、填充字符、对齐方式、浮点数精度和表示法。这些工具可以帮助你创建格式化的文本输出，以满足你的需求。

## 10.自定义格式化输出

在C++中，可以通过多种方式实现自定义的格式化输出。除了使用标准库中的流操纵符（如`std::setw`、`std::setprecision`、`std::fixed`、`std::scientific`等）之外，你还可以创建自定义的流操纵符或使用字符串流（`std::stringstream`）来进行更复杂的格式化。以下是一些方法：

### 10.1. 使用标准流操纵符

这是最简单和最直接的方法，如前所述，可以使用`std::setw`、`std::setprecision`等来控制输出格式。

### 10.2. 创建自定义流操纵符

你可以创建自己的流操纵符来实现特定的格式化需求。这通常涉及到重载`operator<<`。

```cpp
#include <iostream>

// 自定义流操纵符，用于输出带边框的值
struct bordered {
    const std::string value;

    bordered(const std::string &value) : value(value) {}

    friend std::ostream &operator<<(std::ostream &os, const bordered &obj) {
        os << "【" << obj.value << "】";
        return os;
    }
};

int main() {
    std::cout << bordered("Hello, World!") << std::endl; // 使用自定义流操纵符
    return 0;
}
```

### 10.3. 使用`std::stringstream`

`std::stringstream`提供了一种灵活的方式来构建和格式化复杂的字符串。

```cpp
#include <iostream>
#include <sstream>
#include <iomanip>

int main() {
    std::stringstream ss;
    int number = 42;
    double pi = 3.14159;

    ss << "Number: " << std::setw(10) << std::setfill('0') << number << std::endl;
    ss << "Pi: " << std::fixed << std::setprecision(2) << pi << std::endl;

    std::cout << ss.str() << std::endl;
    return 0;
}
```

### 10.4. 使用`std::format`（C++20）

从C++20开始，标准库中引入了`std::format`函数，它提供了一种类似于Python的字符串格式化方法。

```cpp
#include <iostream>
#include <format>

int main() {
    int number = 42;
    double pi = 3.14159;

    std::cout << std::format("Number: {:0>10}\n", number);
    std::cout << std::format("Pi: {:.2f}\n", pi);
    return 0;
}
```

### 10.5. 使用`iomanip`库中的其他函数

`<iomanip>`库中包含了许多用于格式化输出的函数。

```cpp
#include <iostream>
#include <iomanip>

int main() {
    int number = -42;
    std::cout << std::setw(10) << std::setfill('*') << std::showpos << number << std::endl;
    return 0;
}
```

### 10.6. 组合使用

你可以组合使用多种方法来实现复杂的格式化输出。

```cpp
#include <iostream>
#include <iomanip>
#include <sstream>

int main() {
    std::stringstream ss;
    int number = 42;
    double pi = 3.14159;

    ss << std::left << std::setw(20) << "Number: " << std::setw(10) << number << std::endl;
    ss << std::left << std::setw(20) << "Pi: " << std::fixed << std::setprecision(2) << pi << std::endl;

    std::cout << ss.str() << std::endl;
    return 0;
}
```

通过这些方法，你可以实现几乎任何你需要的自定义格式化输出。

## 11.自定义流操纵符来实现复杂的格式化输出

在C++中，自定义流操纵符可以通过重载插入运算符 (`operator<<`) 来实现。这允许你创建新的格式化输出操作，它们可以是模板，以支持不同类型的数据。以下是创建自定义流操纵符的步骤：

### 11.1. 定义一个辅助函数

这个函数将作为新的流操纵符，它接受一个输出流和一个要输出的值。

```cpp
#include <iostream>
#include <string>

// 自定义流操纵符，用于输出带边框的字符串
std::ostream& bordered(std::ostream& os, const std::string& str) {
    os << "[" << str << "]";
    return os;
}
```

### 11.2. 使用自定义流操纵符

在你的程序中，可以直接使用这个自定义流操纵符来格式化输出。

```cpp
int main() {
    std::string text = "Hello, World!";
    std::cout << bordered(text) << std::endl;
    return 0;
}
```

### 11.3. 创建更复杂的格式化

你可以创建更复杂的格式化操作，例如，同时设置宽度、填充字符和对齐方式。

```cpp
#include <iostream>
#include <iomanip>
#include <string>

// 自定义流操纵符，用于输出带边框并居中的字符串
std::ostream &bordered_and_centered(std::ostream &os, const std::string &str) {
    int length = str.length();
    int total_width = 20; // 定义总宽度，确保足够长
    int padding = (total_width - length) / 2;
    // 确保如果总宽度 - 长度是奇数，右侧的星号比左侧多一个
    int extra_padding = (total_width - length) % 2;
    std::string padding_str = std::string(padding, '*') + (extra_padding ? "*" : "");
    os << "[" << padding_str << str << padding_str << "]";
    return os;
}

int main() {
    std::string text = "C++";
    std::cout << bordered_and_centered(std::cout, text) << std::endl;
    return 0;
}
```

### 11.4. 使用模板创建通用操纵符

你可以创建模板函数来使操纵符对多种类型通用。

```cpp
#include <iostream>
#include <iomanip>

// 前向声明，以便在下面的 operator<< 中使用 Centered
template<typename T>
class Centered;

// 重载 operator<<
template<typename T>
std::ostream& operator<<(std::ostream& os, const Centered<T>& obj) {
    os << std::setw(20) << std::setfill('*') << std::internal << obj.value;
    return os;
}

// 自定义流操纵符模板，用于输出居中的值
template<typename T>
class Centered {
public:
    T value;

    Centered(const T& val) : value(val) {}
};

// 创建一个辅助函数来简化流操纵符的调用
template<typename T>
Centered<T> centered(const T& value) {
    return Centered<T>(value);
}

int main() {
    int number = 42;
    std::cout << centered(number) << std::endl;
    double pi = 3.14159;
    std::cout << centered(pi) << std::endl;
    return 0;
}
```

### 11.5. 结合标准库函数

你可以在自定义流操纵符中结合使用标准库的流操纵符。

```cpp
#include <iostream>
#include <iomanip>

// 自定义流操纵符结构，用于输出带边框并右对齐的浮点数
struct BorderedRightAligned {
    double value;

    BorderedRightAligned(double val) : value(val) {}
};

// 重载 operator<<
std::ostream &operator<<(std::ostream &os, const BorderedRightAligned &obj) {
    os << std::fixed << std::setprecision(2);
    os << "[" << std::right << std::setw(10) << obj.value << "]";
    return os;
}

// 创建一个辅助函数，用于创建 BorderedRightAligned 对象
inline BorderedRightAligned bordered_right_aligned(double value) {
    return BorderedRightAligned(value);
}

int main() {
    double pi = 3.14159;
    std::cout << bordered_right_aligned(pi) << std::endl; // 正确的调用
    return 0;
}
```

### 11.6. 处理复杂数据类型

如果你需要格式化复杂的自定义数据类型，可以在该类型的类内部或外部定义流操纵符。

```cpp
#include <iostream>
#include <iomanip>
#include <string>

class Point {
public:
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
};

// 为Point类定义流操纵符
std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << std::fixed << std::setprecision(2) << p.x << ", " << p.y << ")";
    return os;
}

int main() {
    Point p(3.14159, 2.71828);
    std::cout << "Point: " << p << std::endl;
    return 0;
}
```

通过这些方法，你可以创建几乎任何你需要的自定义格式化输出。自定义流操纵符提供了一种强大的方式来扩展C++的输出功能，使其能够适应复杂的格式化需求。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
