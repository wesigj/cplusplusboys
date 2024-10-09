# C++11 17-文件系统库 File System Library

- [C++11 17-文件系统库 File System Library](#c11-17-文件系统库-file-system-library)
  - [Overview](#overview)
  - [1.文件系统库 File System Library](#1文件系统库-file-system-library)
  - [2.C++11 中的 std::filesystem 库有哪些常用的文件操作函数？](#2c11-中的-stdfilesystem-库有哪些常用的文件操作函数)
  - [3.Boost.Filesystem 和 std:filesystem 在功能上有哪些主要区别?](#3boostfilesystem-和-stdfilesystem-在功能上有哪些主要区别)
  - [4.在Windows平台上，除了使用WindowsAPls，还有哪些方法可以处理文件系统操作？](#4在windows平台上除了使用windowsapls还有哪些方法可以处理文件系统操作)
  - [5.std:filesystem在处理文件系统错误时有哪些异常类型？](#5stdfilesystem在处理文件系统错误时有哪些异常类型)
  - [6.如何使用std:filesystem进行文件的复制和移动操作？](#6如何使用stdfilesystem进行文件的复制和移动操作)
    - [6.1.包含必要的头文件](#61包含必要的头文件)
    - [6.2.复制文件](#62复制文件)
    - [6.3.移动文件](#63移动文件)
    - [6.4.示例：使用这些函数](#64示例使用这些函数)
    - [6.5.注意事项](#65注意事项)
  - [7.std:filesystem在跨平台的文件系统操作中有哪些限制或挑战？](#7stdfilesystem在跨平台的文件系统操作中有哪些限制或挑战)
  - [关于作者](#关于作者)

## Overview

---

## 1.文件系统库 File System Library

在C++11中，虽然没有直接集成文件系统库，但是可以通过一些方法来处理文件系统相关的操作。以下是一些可以使用的技术和库：

1. **Boost.Filesystem**：Boost库提供了一个广泛使用的文件系统库`boost.filesystem`，它在C++11之前就已经存在，并且是C++17标准文件系统库的基础。它提供了路径操作、文件创建、删除、移动、复制以及目录迭代等功能。

2. **GHC Filesystem**：这是一个实现了C++17 `std::filesystem`的库，并且支持C++11、C++14和C++17标准。它提供了与标准库`std::filesystem`相似的API，并且可以跨平台使用。

3. **POSIX APIs**：在Unix-like系统上，可以使用POSIX提供的文件系统操作API，例如`open`、`read`、`write`、`close`等函数。

4. **Windows APIs**：在Windows系统上，可以使用Windows提供的文件系统相关的API，例如`CreateFile`、`ReadFile`、`WriteFile`、`CloseHandle`等。

5. **使用C标准库**：可以使用C标准库中的文件操作函数，如`fopen`、`fread`、`fwrite`、`fclose`等。

6. **第三方库**：除了Boost之外，还有其他一些第三方库提供了文件系统操作的功能，例如ACL库。

7. **C++17 std::filesystem**：如果你的编译器支持C++17，那么可以直接使用标准库中的`std::filesystem`命名空间，它提供了一套完整的文件系统操作功能。

8. **使用C++17的第三方实现**：如果需要在C++11环境中使用`std::filesystem`，可以使用第三方实现，如`ghc::filesystem`，它提供了与C++17标准兼容的文件系统操作功能，并且支持C++11。

9. **使用C++11 TR2**：在C++11标准中，有一个技术报告2（TR2），其中包含了文件系统库的早期版本，可以在一些编译器中使用。

选择哪种方法取决于你的项目需求、目标平台以及编译器的支持情况。如果你需要一个跨平台的解决方案，那么Boost.Filesystem或GHC Filesystem可能是更好的选择。如果你的项目已经在使用Boost，那么使用Boost.Filesystem可能是最方便的。如果你的编译器支持C++17，那么直接使用`std::filesystem`将是最简单的。

## 2.C++11 中的 std::filesystem 库有哪些常用的文件操作函数？

实际上，`std::filesystem` 是 C++17 标准中引入的，而不是 C++11。在 C++17 中，`std::filesystem` 提供了一套全面的文件系统操作功能。以下是一些常用的文件操作函数：

1. **路径操作**：
   - `std::filesystem::path::string()`：获取路径的字符串表示。
   - `std::filesystem::path::u8string()`：获取路径的 UTF-8 字符串表示。
   - `std::filesystem::path::generic_string()`：获取路径的通用字符串表示。
   - `std::filesystem::path::filename()`：获取路径中的文件名部分。
   - `std::filesystem::path::parent_path()`：获取路径中的父目录部分。

2. **文件状态**：
   - `std::filesystem::exists()`：检查给定路径的文件或目录是否存在。
   - `std::filesystem::is_directory()`：检查给定路径是否为目录。
   - `std::filesystem::is_regular_file()`：检查给定路径是否为常规文件。
   - `std::filesystem::is_symlink()`：检查给定路径是否为符号链接。
   - `std::filesystem::file_size()`：获取文件的大小。

3. **文件内容**：
   - `std::filesystem::copy()`：复制文件或目录。
   - `std::filesystem::copy_file()`：复制文件，可以选择是否覆盖目标文件。

4. **文件创建和删除**：
   - `std::filesystem::create_directory()`：创建新目录。
   - `std::filesystem::create_directories()`：递归创建新目录。
   - `std::filesystem::remove()`：删除文件或目录。
   - `std::filesystem::remove_all()`：删除文件或目录及其所有内容。

5. **文件修改**：
   - `std::filesystem::rename()`：重命名文件或目录。
   - `std::filesystem::resize_file()`：更改文件大小。

6. **文件时间**：
   - `std::filesystem::last_write_time()`：获取或设置文件的最后写入时间。

7. **符号链接**：
   - `std::filesystem::create_symlink()`：创建符号链接。
   - `std::filesystem::read_symlink()`：读取符号链接指向的目标。

8. **当前工作目录**：
   - `std::filesystem::current_path()`：获取或设置当前工作目录。

9. **文件系统信息**：
   - `std::filesystem::space()`：获取文件系统的空间信息。

10. **文件系统遍历**：
    - `std::filesystem::directory_iterator`：遍历目录中的条目。

请注意，`std::filesystem`库在不同的标准库实现中可能存在一些差异，因此在使用时需要参考特定编译器的文档。此外，`std::filesystem`提供了异常处理机制，因此在处理文件系统操作时，建议使用异常处理来捕获可能发生的错误。

## 3.Boost.Filesystem 和 std:filesystem 在功能上有哪些主要区别?

Boost.Filesystem 和 std::filesystem 都是 C++ 中用于文件系统操作的库，但它们之间存在一些差异：

1. **库的来源**：
   - Boost.Filesystem 是 Boost 库的一部分，是一个广泛使用的文件系统库，它在 C++11 之前就已经存在。
   - std::filesystem 是 C++17 标准的一部分，是语言标准中的文件系统库。

2. **兼容性**：
   - Boost.Filesystem 需要用户手动包含头文件 `<boost/filesystem.hpp>` 并链接 Boost 库。
   - std::filesystem 只需要包含 `<filesystem>` 头文件，并且是标准库的一部分，不需要额外的链接。

3. **平台支持**：
   - Boost.Filesystem 支持多种平台，包括那些还没有完全支持 C++17 的平台。
   - std::filesystem 需要编译器支持 C++17 标准。

4. **功能差异**：
   - Boost.Filesystem 提供了一些额外的功能，如文件流操作，这些在 std::filesystem 中可能不直接提供。
   - std::filesystem 提供了一套与 Boost.Filesystem 类似的 API，但有一些细微的差别，例如路径处理和错误处理的方式。

5. **性能**：
   - 两者在性能上可能有所不同，这取决于具体的实现和平台。

6. **错误处理**：
   - Boost.Filesystem 使用 `boost::filesystem::filesystem_error` 异常来报告错误。
   - std::filesystem 使用 `std::filesystem::filesystem_error` 异常。

7. **使用习惯**：
   - 如果你已经在使用 Boost 库，那么使用 Boost.Filesystem 可能更自然。
   - 如果你希望使用标准库，并且你的编译器支持 C++17，那么使用 std::filesystem 可能更合适。

8. **移植性**：
   - Boost.Filesystem 通常被认为是更可移植的，因为它在很多旧的编译器和平台上都有良好的支持。
   - std::filesystem 的移植性取决于编译器对 C++17 的支持程度。

总的来说，如果你的项目已经在使用 Boost，并且不需要迁移到 C++17，那么继续使用 Boost.Filesystem 是合理的。如果你使用的是支持 C++17 的编译器，并且希望减少对外部库的依赖，那么迁移到 std::filesystem 是一个不错的选择。

## 4.在Windows平台上，除了使用WindowsAPls，还有哪些方法可以处理文件系统操作？

在Windows平台上，除了使用Windows API进行文件系统操作，还可以采用以下几种方法：

1. **命令行工具**：
   - 使用如`fsutil`这样的命令行工具来执行文件系统相关的操作，如磁盘管理、文件系统检查和修复等。

2. **第三方文件管理器**：
   - 使用第三方文件管理器，如XYplorer、Total Commander、FreeCommander等，这些工具提供了比Windows自带的资源管理器更多的功能和定制选项。

3. **脚本和批处理**：
   - 利用PowerShell、批处理脚本（.bat）或Python脚本来自动化文件系统任务。

4. **文件资源管理器替代品**：
   - 使用如Files UWP、Clover等资源管理器替代品，它们提供了标签页、多窗格等增强功能。

5. **Boost.Filesystem**：
   - 在C++中，可以使用Boost库中的Filesystem模块，它提供了跨平台的文件系统操作功能。

6. **第三方库**：
   - 使用第三方库，如Qt的文件系统模块，它提供了一套完整的文件系统操作API。

7. **使用第三方软件**：
   - 使用如赤友NTFS助手等软件，这些软件专为文件系统操作设计，提供了读写NTFS硬盘等功能。

8. **网络共享**：
   - 通过设置网络共享，不同操作系统的设备可以访问和交换文件，无需考虑文件系统的差异。

9. **共享文件系统**：
   - 使用如exFAT这样的文件系统，它同时在Windows和macOS上得到支持，适合作为交换数据的中间格式。

选择合适的方法取决于你的具体需求、技术栈以及对跨平台支持的要求。

## 5.std:filesystem在处理文件系统错误时有哪些异常类型？

在 C++17 中，`std::filesystem` 命名空间定义了几种异常类型，用于在文件系统操作中处理错误。这些异常类型都源自 `std::filesystem::filesystem_error`，它本身继承自 `std::system_error`，最终继承自 `std::exception`。

以下是 `std::filesystem` 中定义的一些异常类型：

1. **filesystem_error**：
   - 这是所有文件系统异常的基类。它包含一个字符串描述和错误代码，指示发生的具体错误。

2. **filesystems_not_supported**：
   - 这个异常表明尝试获取或设置不支持的文件系统属性。

3. **invalid_argument**：
   - 当提供给文件系统操作的参数无效时抛出，例如，传递给 `std::filesystem::create_directory` 的路径是空的。

4. **operation_not_permitted**：
   - 当尝试执行不被允许的操作时抛出，例如，没有足够的权限删除一个文件。

5. **not_found**：
   - 当尝试访问不存在的文件或目录时抛出。

6. **file_exists**：
   - 当尝试创建已存在的文件或目录时抛出。

7. **directory_not_empty**：
   - 当尝试删除一个非空目录时抛出。

8. **not_a_directory**：
   - 当尝试执行目录操作，但给定的路径不是目录时抛出。

9. **is_a_directory**：
   - 当尝试执行文件操作，但给定的路径是目录时抛出。

10. **invalid_file_permission**：
    - 当尝试设置无效的文件权限时抛出。

11. **no_space**：
    - 当磁盘空间不足，无法完成操作时抛出。

这些异常类型提供了足够的信息来诊断文件系统操作失败的原因。在实际使用中，你可以通过捕获这些异常来处理错误情况。

```cpp
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main() {
    try {
        fs::remove("nonexistent_file.txt");
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << '\n';
    }
    return 0;
}
```

请注意，为了确保代码的健壮性，你应该在可能抛出异常的文件系统操作周围使用 try-catch 块。

## 6.如何使用std:filesystem进行文件的复制和移动操作？

在 C++17 中，`std::filesystem` 提供了简单直接的方法来执行文件的复制和移动操作。以下是如何使用 `std::filesystem` 进行这些操作的示例：

### 6.1.包含必要的头文件

首先，确保包含 `<filesystem>` 头文件，并使用命名空间 `std::filesystem`。

```cpp
#include <filesystem>
namespace fs = std::filesystem;
```

### 6.2.复制文件

使用 `fs::copy_file` 函数复制文件。你可以指定源文件路径和目标文件路径。如果目标文件已存在，它将被覆盖（默认情况下）或者保持不变，这取决于你如何设置 `copy_options`。

```cpp
bool copy_file(const fs::path& source, const fs::path& destination) {
    try {
        fs::copy_file(source, destination);
        return true;  // 返回 true 表示复制成功
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error copying file: " << e.what() << '\n';
        return false; // 返回 false 表示复制失败
    }
}
```

### 6.3.移动文件

使用 `fs::rename` 函数移动文件。这个函数在不同平台上可能表现不同，但通常用于重命名和移动文件。

```cpp
bool move_file(const fs::path& source, const fs::path& destination) {
    try {
        fs::rename(source, destination);
        return true;  // 返回 true 表示移动成功
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error moving file: " << e.what() << '\n';
        return false; // 返回 false 表示移动失败
    }
}
```

### 6.4.示例：使用这些函数

```cpp
int main() {
    fs::path source_path = "path/to/source.txt";
    fs::path destination_path = "path/to/destination.txt";

    // 复制文件
    if (copy_file(source_path, destination_path)) {
        std::cout << "File copied successfully.\n";
    }

    // 移动文件
    if (move_file(source_path, destination_path)) {
        std::cout << "File moved successfully.\n";
    }

    return 0;
}
```

### 6.5.注意事项

1. **错误处理**：操作可能会因多种原因失败（如权限问题、路径不存在等），因此使用异常处理来捕获这些错误是一个好的实践。

2. **覆盖文件**：默认情况下，`fs::copy_file` 在目标文件已存在时会覆盖它。你可以通过传递 `fs::copy_options` 来改变这种行为。

3. **移动和重命名**：在某些情况下，`fs::rename` 可能仅用于重命名，而不支持跨文件系统移动文件。如果需要明确移动文件，考虑使用平台特定的 API 或检查文件系统类型。

4. **文件属性**：移动和复制操作可能不会保留所有文件属性（如权限位、时间戳等），这取决于操作系统和文件系统。

通过使用 `std::filesystem`，你可以以一种可移植的方式执行文件系统操作，而不必担心底层操作系统的差异。

## 7.std:filesystem在跨平台的文件系统操作中有哪些限制或挑战？

`std::filesystem` 是 C++17 标准中引入的，用于处理文件系统操作的库。它提供了跨平台的文件和目录操作功能，但确实存在一些限制和挑战：

1. **平台兼容性**：虽然 `std::filesystem` 旨在提供跨平台的文件系统操作，但不同操作系统的文件系统在实现细节上可能有所不同。例如，Windows 使用的路径分隔符与 POSIX 系统（如 Linux 和 macOS）不同，这可能会影响路径操作的结果。

2. **文件系统限制**：某些文件系统可能不支持 `std::filesystem` 的所有操作。例如，FAT 文件系统不支持符号链接，且硬链接的数量也有限制。

3. **异常处理**：`std::filesystem` 的许多操作可能会抛出异常，尤其是 `std::filesystem::filesystem_error`，这要求开发者在使用时进行适当的错误处理。

4. **性能考虑**：文件系统操作可能涉及大量的磁盘 I/O，这可能成为性能瓶颈。此外，某些操作（如遍历大型目录结构）可能会消耗大量资源。

5. **权限问题**：在某些系统上，文件系统操作可能受到权限限制，尤其是在 UNIX-like 系统中，这可能会影响文件的创建、删除和修改。

6. **编码问题**：在处理文件路径时，需要注意字符编码的问题。Windows 上通常使用 UTF-16，而 POSIX 系统使用 UTF-8。这可能会导致在不同平台上处理字符串时出现问题。

7. **库的可用性**：虽然 C++17 已经广泛支持，但某些编译器或平台可能还没有完全实现 `std::filesystem` 库。

8. **API 的使用**：`std::filesystem` 提供了许多功能，但正确使用这些 API 需要对库有深入的了解。例如，`copy` 和 `copy_file` 在默认情况下会覆盖现有文件，这可能不是总是期望的行为。

为了克服这些限制和挑战，开发者应该：

- 在不同平台上进行彻底的测试，确保文件系统操作按预期工作。
- 处理所有可能的异常，并为用户提供清晰的错误信息。
- 在性能关键的应用中，考虑文件系统操作的开销，并探索可能的优化。
- 了解目标平台的文件系统限制，并在代码中相应地处理。
- 使用适当的字符编码，并在必要时进行转换。
- 确保使用的编译器和标准库实现支持 C++17。
- 仔细阅读和理解 `std::filesystem` 的文档，以正确使用 API。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
