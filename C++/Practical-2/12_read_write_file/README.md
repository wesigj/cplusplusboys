# C++ Practical-2 day12 读写文件综合题

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.读写文件综合题

在 C++ 中，读写文件是一个常见的任务。我们可以使用标准的文件流（`std::ifstream` 用于读取，`std::ofstream` 用于写入）来处理文件操作。以下是一个综合示例，展示了如何在 C++ 中创建一个文件，写入一些内容，然后读取并显示这些内容。

### 1.1.写入文件

首先，我们将创建一个函数来写入文件：

```cpp
#include <fstream>
#include <string>

void writeToFile(const std::string& filename, const std::string& content) {
    std::ofstream outFile(filename); // 创建一个 ofstream 对象并打开文件
    if (!outFile) {
        std::cerr << "Unable to create file " << filename << std::endl;
        return;
    }

    outFile << content; // 写入内容到文件
    outFile.close(); // 关闭文件
}
```

### 1.2.读取文件

接下来，我们将创建一个函数来读取文件：

```cpp
void readFromFile(const std::string& filename) {
    std::ifstream inFile(filename); // 创建一个 ifstream 对象并打开文件
    if (!inFile) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) { // 逐行读取文件内容
        std::cout << line << std::endl;
    }

    inFile.close(); // 关闭文件
}
```

### 1.3.主函数

最后，我们在 `main` 函数中使用这些函数：

```cpp
int main() {
    std::string filename = "example.txt";
    std::string content = "Hello, World!\nThis is a test file.\n";

    // 写入文件
    writeToFile(filename, content);

    // 读取文件
    readFromFile(filename);

    return 0;
}
```

### 1.4.完整代码

将以上代码片段组合在一起，我们得到一个完整的程序：

```cpp
#include <fstream>
#include <string>
#include <iostream>

void writeToFile(const std::string& filename, const std::string& content) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Unable to create file " << filename << std::endl;
        return;
    }

    outFile << content;
    outFile.close();
}

void readFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::cout << line << std::endl;
    }

    inFile.close();
}

int main() {
    std::string filename = "example.txt";
    std::string content = "Hello, World!\nThis is a test file.\n";

    writeToFile(filename, content);
    readFromFile(filename);

    return 0;
}
```

这个程序首先创建一个名为 `example.txt` 的文件，并向其中写入一些文本内容。然后，程序读取该文件的内容，并将其输出到控制台。这是一个简单的文件读写示例，展示了 C++ 中基本的文件操作。

## 2.如何使用 C++ 进行更复杂的文件读写，比如追加内容或者以二进制模式读写？

在 C++ 中，进行更复杂的文件读写操作可以通过指定文件打开模式来实现。以下是一些常见的文件操作模式：

### 2.1.追加模式

在追加模式下打开文件，所有写入操作都会从文件末尾开始追加内容。在 `std::ofstream` 中，可以使用 `std::ios::app` 模式来追加内容。

```cpp
#include <iostream>
#include <fstream>
#include <string>

void appendToFile(const std::string &filename, const std::string &content) {
    std::ofstream outFile(filename, std::ios::app); // 以追加模式打开文件
    if (!outFile) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }

    outFile << content; // 追加内容到文件
    outFile.close();    // 关闭文件
}
```

### 2.2.二进制读写模式

在二进制模式下读写文件，可以使用 `std::ios::binary` 模式。这在处理非文本文件（如图片、音频、视频等）时非常有用。

```cpp
#include <fstream>
#include <vector>

void writeBinaryFile(const std::string& filename, const std::vector<char>& data) {
    std::ofstream outFile(filename, std::ios::binary); // 以二进制模式打开文件
    if (!outFile) {
        std::cerr << "Unable to create binary file " << filename << std::endl;
        return;
    }

    outFile.write(data.data(), data.size()); // 写入二进制数据
    outFile.close(); // 关闭文件
}

void readBinaryFile(const std::string& filename, std::vector<char>& buffer) {
    std::ifstream inFile(filename, std::ios::binary); // 以二进制模式打开文件
    if (!inFile) {
        std::cerr << "Unable to open binary file " << filename << std::endl;
        return;
    }

    inFile.seekg(0, std::ios::end); // 移动到文件末尾
    size_t fileSize = inFile.tellg(); // 获取文件大小
    inFile.seekg(0, std::ios::beg); // 回到文件开头

    buffer.resize(fileSize); // 调整缓冲区大小
    inFile.read(buffer.data(), fileSize); // 读取文件内容到缓冲区
    inFile.close(); // 关闭文件
}
```

### 2.3.主函数

在 `main` 函数中，我们可以调用这些函数来执行追加和二进制读写操作。

```cpp
int main() {
    std::string filename = "example.txt";
    std::string textContent = "This is additional text.\n";

    // 追加文本内容
    appendToFile(filename, textContent);

    // 二进制写入
    std::vector<char> binaryData = { 0x00, 0x01, 0x02, 0x03, 0x04 };
    writeBinaryFile("binaryData.bin", binaryData);

    // 二进制读取
    std::vector<char> readData;
    readBinaryFile("binaryData.bin", readData);

    // 显示读取的二进制数据
    for (char c : readData) {
        std::cout << std::hex << (int)c << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 2.4.注意事项

- 在写入二进制文件时，确保数据是正确的二进制格式。
- 在读取二进制文件时，确保缓冲区足够大，以存储整个文件的内容。
- 使用二进制模式时，文件的读写不会受到换行符的影响，这与文本模式不同。

这些示例展示了如何在 C++ 中执行更复杂的文件操作，包括追加内容和以二进制模式读写文件。

## 3.在C++中，除了使用文件流，还有哪些方法可以进行文件操作？

在 C++ 中，除了使用文件流（如 `std::ifstream` 和 `std::ofstream`），还有一些其他方法可以进行文件操作：

1. **C 风格的文件操作**：
   使用 C 语言的文件操作函数，如 `fopen`, `fclose`, `fread`, `fwrite`, `fprintf`, `fscanf` 等。

   ```cpp
   FILE* file = fopen("example.txt", "w"); // 打开文件用于写操作
   if (file != nullptr) {
       fprintf(file, "Hello, World!\n");
       fclose(file); // 关闭文件
   }
   ```

2. **C++17 文件系统库 (std::filesystem)**：
   C++17 引入了 `std::filesystem` 库，提供了更现代的文件系统操作接口。

   ```cpp
   #include <filesystem>
   namespace fs = std::filesystem;

   fs::path filePath = "example.txt";
   fs::create_directory("example_dir"); // 创建目录
   fs::copy("source.txt", "destination.txt"); // 复制文件
   fs::remove("example.txt"); // 删除文件
   ```

3. **C++标准库中的其他流**：
   使用 `std::stringstream` 或 `std::istringstream` 和 `std::ostringstream` 进行字符串和文件内容之间的转换。

   ```cpp
   std::stringstream ss;
   ss << "Hello, World!" << std::endl;
   std::string fileContent = ss.str(); // 将流内容转换为字符串
   ```

4. **低级文件 I/O 操作**：
   使用操作系统提供的系统调用来直接操作文件，如 UNIX/Linux 系统中的 `open`, `read`, `write`, `close` 等系统调用。

   ```cpp
   #include <unistd.h>
   #include <fcntl.h>

   int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
   if (fd != -1) {
       const char* text = "Hello, World!";
       write(fd, text, strlen(text));
       close(fd);
   }
   ```

5. **内存映射文件**：
   使用操作系统提供的内存映射文件功能，如 Windows 的 `CreateFileMapping` 和 `MapViewOfFile`，或 UNIX/Linux 的 `mmap` 系统调用。

   ```cpp
   #include <sys/mman.h>
   #include <fcntl.h>
   #include <unistd.h>

   int fd = open("example.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
   write(fd, "Hello, World!", 13);
   ftruncate(fd, 13); // 调整文件大小

   // 映射文件到内存
   void* addr = mmap(nullptr, 13, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
   if (addr != MAP_FAILED) {
       // 使用映射的内存
       munmap(addr, 13); // 解除映射
   }
   close(fd);
   ```

6. **第三方库**：
   使用第三方库，如 Boost.Filesystem，提供了跨平台的文件系统操作功能。

   ```cpp
   #include <boost/filesystem.hpp>
   boost::filesystem::path filePath = "example.txt";
   boost::filesystem::create_directory("example_dir");
   boost::filesystem::copy_file("source.txt", "destination.txt");
   boost::filesystem::remove("example.txt");
   ```

7. **标准库中的其他工具**：
   使用 `std::tmpfile` 创建临时文件，这些文件在程序结束时自动删除。

   ```cpp
   FILE* tempFile = std::tmpfile();
   if (tempFile != nullptr) {
       fprintf(tempFile, "Temporary data");
       rewind(tempFile); // 回到文件开头
       // 读取或处理文件...
       fclose(tempFile); // 关闭文件，文件内容会被删除
   }
   ```

这些方法提供了不同级别的文件操作控制，从底层系统调用到高级抽象，可以根据具体需求和平台特性选择合适的方法。

## 4.在C++中，如何检查文件读写操作是否成功，以及在失败时如何处理错误？

在 C++ 中，检查文件读写操作是否成功通常涉及到检查文件流的状态。`std::fstream`、`std::ifstream` 和 `std::ofstream` 都提供了成员函数 `fail()` 和 `bad()` 来检查流的状态。

### 4.1.检查文件操作是否成功

1. **使用 `fail()` 函数**：
   `fail()` 函数在流遇到任何形式的输入/输出失败时返回 `true`。

   ```cpp
   std::ofstream outFile("example.txt");
   if (outFile.fail()) {
       std::cerr << "Failed to open file for writing." << std::endl;
   } else {
       outFile << "Hello, World!" << std::endl;
       if (outFile.fail()) {
           std::cerr << "Failed to write to file." << std::endl;
       }
   }
   outFile.close();
   ```

2. **使用 `bad()` 函数**：
   `bad()` 函数在流遇到不可恢复的错误时返回 `true`，如读写错误。

   ```cpp
   std::ifstream inFile("example.txt");
   if (inFile.bad()) {
       std::cerr << "Failed to open file for reading." << std::endl;
   } else {
       std::string line;
       while (std::getline(inFile, line)) {
           if (inFile.bad()) {
               std::cerr << "Failed to read from file." << std::endl;
               break;
           }
           std::cout << line << std::endl;
       }
   }
   inFile.close();
   ```

3. **检查特定操作的状态**：
   每次读写操作后，可以立即检查操作是否成功。

   ```cpp
   std::ofstream outFile("example.txt", std::ios::app);
   outFile << "Appending text." << std::endl;
   if (!outFile) { // 等同于检查 fail() 或 bad()
       std::cerr << "Write operation failed." << std::endl;
   }
   outFile.close();
   ```

### 4.2.错误处理

1. **关闭文件**：
   如果检测到错误，应该关闭文件以释放资源。

   ```cpp
   if (outFile.fail()) {
       outFile.close();
       // 进一步的错误处理...
   }
   ```

2. **抛出异常**：
   可以在检测到错误时抛出异常，让上层代码处理。

   ```cpp
   if (outFile.fail()) {
       throw std::runtime_error("Failed to write to file.");
   }
   ```

3. **返回错误代码**：
   在函数中返回错误代码，让调用者根据错误代码进行处理。

   ```cpp
   bool writeFile(const std::string& filename, const std::string& content) {
       std::ofstream outFile(filename);
       if (outFile.fail()) {
           return false;
       }
       outFile << content;
       if (outFile.fail()) {
           outFile.close();
           return false;
       }
       outFile.close();
       return true;
   }
   ```

4. **使用错误码**：
   定义错误码枚举或类，用于表示不同的错误情况。

   ```cpp
   enum class FileError {
       None,
       OpenFailed,
       WriteFailed,
       CloseFailed
   };

   FileError writeFile(const std::string& filename, const std::string& content) {
       std::ofstream outFile(filename);
       if (outFile.fail()) {
           return FileError::OpenFailed;
       }
       outFile << content;
       if (outFile.fail()) {
           outFile.close();
           return FileError::WriteFailed;
       }
       if (!outFile.close()) {
           return FileError::CloseFailed;
       }
       return FileError::None;
   }
   ```

5. **记录错误信息**：
   使用日志记录错误信息，便于调试和跟踪问题。

   ```cpp
   if (outFile.fail()) {
       logError("File writing failed.");
       // 进一步的错误处理...
   }
   ```

6. **资源泄漏处理**：
   确保在发生错误时释放已分配的资源，避免资源泄漏。

7. **用户提示**：
   在 GUI 应用程序或需要用户交互的场景中，向用户显示错误信息。

8. **重试机制**：
   在某些情况下，如果操作失败，可以实施重试机制。

通过这些方法，你可以在 C++ 中有效地检查文件操作是否成功，并在失败时进行适当的错误处理。

## 5.如果文件读写操作失败，我应该如何优雅地处理异常，而不是直接崩溃程序？

在 C++ 中，优雅地处理文件读写操作失败的异常，而不是让程序直接崩溃，通常涉及到以下几个步骤：

### 5.1. 检查流状态

在进行文件操作之前和之后，检查文件流的状态。这可以通过检查流对象的 `fail()`、`bad()` 或 `eof()` 成员函数来实现。

### 5.2. 使用异常处理

使用 `try` 和 `catch` 块来捕获和处理可能抛出的异常。

### 5.3. 提供错误反馈

向用户提供清晰的错误信息，而不是让程序默默失败。

### 5.4. 资源清理

确保在发生异常时释放所有已分配的资源。

### 5.5. 记录日志

记录错误日志，以便于后续分析和调试。

### 5.6.示例代码

以下是一个示例，展示了如何在文件操作中使用异常处理：

```cpp
#include <fstream>
#include <iostream>
#include <string>

void writeToFile(const std::string& filename, const std::string& content) {
    std::ofstream outFile(filename);
    if (!outFile) {
        throw std::runtime_error("Unable to open file for writing: " + filename);
    }

    outFile << content;
    if (outFile.fail()) {
        outFile.close();
        throw std::runtime_error("Failed to write to file: " + filename);
    }

    outFile.close();
}

void readFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Unable to open file for reading: " + filename);
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (inFile.fail()) {
            inFile.close();
            throw std::runtime_error("Failed to read from file: " + filename);
        }
        std::cout << line << std::endl;
    }

    inFile.close();
}

int main() {
    std::string filename = "example.txt";
    std::string content = "Hello, World!\n";

    try {
        writeToFile(filename, content);
        readFromFile(filename);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        // 这里可以进行额外的错误处理，如用户提示、日志记录等
    }

    return 0;
}
```

### 5.7.注意事项

1. **不要吞没异常**：不要捕获异常而不处理，至少提供错误反馈或记录日志。
2. **资源管理**：使用 RAII（资源获取即初始化）原则管理资源，确保资源在异常发生时也能被正确释放。
3. **用户友好**：提供用户友好的错误信息，避免显示复杂的技术细节。
4. **日志记录**：记录详细的错误日志，以便于问题追踪和调试。
5. **异常安全**：确保程序在抛出和捕获异常时不会泄露资源或留下不可用的状态。

通过这些方法，你可以确保文件读写操作失败时，程序能够优雅地处理异常，而不是直接崩溃。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
