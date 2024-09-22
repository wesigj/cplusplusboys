# C++ Practical-1 day4

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.exception 异常处理

在C++中，异常处理是一种错误处理机制，它允许程序在遇到无法正常处理的情况时，将控制权转移给异常处理器。C++使用`try`、`catch`、`throw`和`finally`（在C++11中用`RAII`风格替代）关键字来实现异常处理。

### 1.1.异常处理的关键字

1. **`try`**：用于指定一个代码块，在该代码块中可能会抛出异常。
2. **`catch`**：用于捕获并处理特定类型的异常。
3. **`throw`**：用于抛出一个异常。
4. **`finally`**：在C++11之前，没有`finally`关键字，但可以使用`try`块后的代码来执行清理操作。C++11引入了`std::exception_ptr`和`std::rethrow_exception`来处理异常传播。

### 1.2.示例：基本的异常处理

```cpp
#include <iostream>
#include <stdexcept>

// 函数声明
void mightGoWrong() {
    throw std::runtime_error("Something went wrong!");
}

int main() {
    try {
        mightGoWrong();
    } catch (const std::runtime_error& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}
```

在这个例子中，`mightGoWrong`函数抛出了一个`std::runtime_error`异常。在`main`函数中，我们使用`try`块来调用这个函数，并使用`catch`块来捕获和处理异常。

### 1.3.示例：多个`catch`块

```cpp
#include <iostream>
#include <stdexcept>

void mightGoWrong(int i) {
    if (i == 0)
        throw std::runtime_error("Argument is zero");
    else if (i < 0)
        throw std::invalid_argument("Argument is negative");
    else
        throw std::logic_error("Argument is too large");
}

int main() {
    try {
        mightGoWrong(-1);
    } catch (const std::runtime_error& e) {
        std::cout << "Runtime error: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::logic_error& e) {
        std::cout << "Logic error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Unknown exception: " << e.what() << std::endl;
    }
    return 0;
}
```

在这个例子中，`mightGoWrong`函数根据参数的不同抛出不同类型的异常。`main`函数中的`try`块调用这个函数，并有多个`catch`块来捕获不同类型的异常。

### 1.4.注意事项

1. **异常应该是异常类的实例**：通常，异常应该是`std::exception`类或其派生类的实例。

2. **异常不应该被忽略**：如果一个`try`块中的异常没有被捕获，程序将终止。

3. **异常的类型**：可以抛出任何类型的异常，但通常是抛出标准异常类型或自定义的异常类型。

4. **异常的堆栈跟踪**：在抛出异常时，程序会记录异常的堆栈跟踪信息，这对于调试非常有用。

5. **资源管理**：在抛出异常之前，确保释放所有分配的资源，或者使用RAII机制来自动管理资源。

6. **异常传播**：在函数中捕获异常并重新抛出，可以使用`std::rethrow_exception`来保持原始的异常堆栈信息。

7. **异常对象的复制**：异常对象在抛出时会被复制，因此应该提供拷贝构造函数。

通过使用异常处理，你可以编写更健壮、更易于维护的代码，并且可以更好地处理程序运行中可能出现的错误情况。

## 2.C++中有哪些自定义异常类，它们通常用于什么场景?

在C++中，自定义异常类通常是通过继承自`std::exception`类来实现的。自定义异常允许你为特定错误情况提供更多的上下文信息。以下是创建和使用自定义异常类的一些常见步骤：

1. **继承`std::exception`**：创建一个新类，继承自`std::exception`，并重写`what()`方法，该方法返回一个描述异常的字符串。

2. **提供构造函数**：为你的异常类提供构造函数，允许设置错误消息和其他相关信息。

3. **抛出异常**：在代码中使用`throw`关键字抛出你的自定义异常对象。

4. **捕获异常**：使用`try-catch`块捕获并处理异常。

### 2.1.示例：自定义异常类

```cpp
#include <iostream>
#include <exception>
#include <string>

// 自定义异常类
class MyException : public std::exception {
private:
    std::string message;
public:
    MyException(const std::string& msg) : message(msg) {}

    // 重写 what() 方法
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// 一个可能抛出异常的函数
void mightGoWrong(int value) {
    if (value < 0) {
        throw MyException("Negative value is not allowed");
    }
}

int main() {
    try {
        mightGoWrong(-1);
    } catch (const MyException& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught standard exception: " << e.what() << std::endl;
    }
    return 0;
}
```

在这个示例中，`MyException`类继承自`std::exception`，并重写了`what()`方法来返回错误消息。`mightGoWrong`函数在接收到负值时抛出`MyException`。`main`函数中的`try-catch`块捕获并处理了这个异常。

### 2.2.使用场景

- **文件处理**：当文件无法打开或读取时，可以抛出一个包含错误信息的自定义异常。
- **网络通信**：在网络请求失败时，可以抛出一个包含错误代码和消息的异常。
- **数据验证**：如果输入数据不符合预期，可以抛出一个异常来指示具体的错误。
- **业务逻辑**：在业务规则被违反时，可以使用自定义异常来通知调用者。

自定义异常类使得错误处理更加灵活和表达性更强，有助于调试和维护大型应用程序。

## 3.在C++中，除了自定义异常类，还有哪些错误处理机制？

在C++中，除了使用自定义异常类进行错误处理，还有以下几种常见的错误处理机制：

1. **错误码**：
   - 许多函数通过返回特定的错误码来指示操作是否成功，例如`errno`全局变量常用于指示上一次系统调用的错误。

2. **断言（Assert）**：
   - `assert`宏用于在调试期间检查程序状态，如果条件为假，则终止程序执行并输出错误信息。它通常用于检查程序的前提条件。

3. **返回值**：
   - 函数可以通过返回值来指示操作是否成功，例如返回布尔值或自定义的枚举类型。

4. **输出参数**：
   - 函数可以将错误信息或状态代码通过输出参数传递给调用者。

5. **异常抛出（Throw）**：
   - 除了自定义异常类，也可以抛出基本数据类型或其他类型的异常对象。

6. **错误处理库**：
   - 使用如Boost.Error或Poco库等第三方库提供的错误处理功能。

7. **标准库异常**：
   - 使用C++标准库提供的异常类，如`std::runtime_error`、`std::logic_error`等。

8. **资源获取即初始化（RAII）**：
   - 使用RAII机制管理资源，确保在发生异常时资源能够被正确释放。

9. **错误恢复**：
   - 在某些情况下，程序可以通过执行某些恢复操作来从错误状态中恢复。

10. **日志记录**：
    - 在检测到错误时记录详细的错误信息，以便于后续分析。

11. **条件编译**：
    - 使用预处理器指令（如`#ifdef`、`#ifndef`）来处理不同平台或配置下的错误处理。

12. **静态分析工具**：
    - 使用静态分析工具（如Clang Static Analyzer、Cppcheck）来检测潜在的错误。

13. **单元测试**：
    - 通过编写和运行单元测试来确保代码的正确性。

14. **代码审查**：
    - 通过代码审查来发现和修复潜在的错误。

15. **用户界面反馈**：
    - 在图形用户界面（GUI）程序中，通过用户界面提供错误信息。

16. **操作系统错误报告**：
    - 在Windows上使用`GetLastError`和`FormatMessage`等函数获取系统错误信息。

17. **信号处理**：
    - 使用信号处理机制（如`signal`和`sigaction`）来处理程序运行时的异常情况。

每种错误处理机制都有其适用的场景，选择合适的机制取决于具体的应用需求、性能考虑和编程风格。在实际开发中，通常会结合使用多种错误处理机制来提高程序的健壮性和可维护性。

## 4.在C++中实现一个多线程程序，异常处理应该如何设计以避免线程安全问题？

在C++中实现多线程程序时，异常处理需要特别小心，因为异常可能会跨越线程边界，这可能导致线程安全问题。以下是一些设计多线程程序异常处理时的准则：

1. **限制异常抛出的范围**：
   - 尽量在线程函数中避免抛出异常。如果必须抛出，确保它在同一个线程中被捕获和处理。

2. **使用异常捕获**：
   - 在每个线程的执行函数中使用`try-catch`块来捕获和处理异常。

3. **避免在析构函数中抛出异常**：
   - 析构函数中抛出异常是危险的，因为如果一个线程在执行析构函数时抛出异常，而这个异常没有被捕获，那么程序可能会直接退出。如果需要在析构函数中执行清理工作，考虑使用RAII（资源获取即初始化）技术。

4. **使用线程安全的异常处理机制**：
   - 如果需要在多个线程之间传递异常，可以使用线程安全的异常处理机制，如`std::current_exception`和`std::exception_ptr`。

5. **使用锁来保护共享资源**：
   - 在访问共享资源之前获取锁，并在可能抛出异常的操作之前释放锁，以避免死锁。

6. **小心使用动态内存分配**：
   - 在抛出异常之前，确保已经释放了所有动态分配的内存，或者使用智能指针来自动管理内存。

7. **使用线程局部存储**：
   - 使用`thread_local`关键字来定义线程局部存储，以避免在多个线程之间共享可能导致异常的对象。

8. **考虑异常传播**：
   - 如果你在一个线程中捕获了异常，并且需要将这个异常传递给其他线程，可以使用`std::exception_ptr`。

9. **使用日志记录异常信息**：
   - 在捕获异常时，使用日志记录异常信息，这样即使异常被处理，也可以在日志中追踪到异常发生的原因。

10. **测试多线程程序**：
    - 多线程程序的异常处理需要通过充分的测试来验证，确保在各种情况下都能正确处理异常。

11. **使用标准库中的线程工具**：
    - 使用C++11及更高版本中的标准库线程工具，如`std::thread`、`std::mutex`等，它们提供了一些线程安全的机制。

12. **避免使用不安全的函数**：
    - 避免在多线程环境中使用可能导致未定义行为的函数，如`longjmp`。

记住，多线程编程中的异常处理比单线程编程更加复杂，需要仔细设计以确保程序的稳定性和可靠性。

### 4.1.示例

当然，以下是一个简单的C++多线程程序示例，展示了如何在线程中处理异常：

```cpp
#include <iostream>
#include <thread>
#include <exception>
#include <string>

// 线程函数，可能会抛出异常
void threadFunction(int id) {
    try {
        // 模拟一些可能会抛出异常的操作
        if (id == 1) {
            throw std::runtime_error("Exception from thread with id 1");
        }
        std::cout << "Thread with id " << id << " is running..." << std::endl;
    } catch (const std::exception& e) {
        // 在线程内部捕获和处理异常
        std::cerr << "Exception caught in thread with id " << id << ": " << e.what() << std::endl;
    } catch (...) {
        // 捕获所有类型的异常
        std::cerr << "Unknown exception caught in thread with id " << id << std::endl;
    }
}

int main() {
    try {
        // 创建两个线程
        std::thread t1(threadFunction, 1);
        std::thread t2(threadFunction, 2);

        // 等待线程完成
        t1.join();
        t2.join();

    } catch (const std::exception& e) {
        // 主线程中捕获异常
        std::cerr << "Exception in main thread: " << e.what() << std::endl;
    } catch (...) {
        // 捕获所有类型的异常
        std::cerr << "Unknown exception in main thread" << std::endl;
    }

    return 0;
}
```

在这个示例中，`threadFunction` 是一个可能会抛出异常的线程函数。我们使用 `try-catch` 块来捕获和处理这些异常。如果线程函数抛出了异常，它会在该线程内部被捕获并处理，不会传播到主线程。

主函数 `main` 中也使用了 `try-catch` 块来捕获可能从线程函数传播到主线程的异常，尽管在这个例子中我们没有让异常传播到主线程。

请注意，这个示例假设异常不会从线程传播到主线程。在实际应用中，如果需要将异常从线程传播到主线程，可以使用 `std::exception_ptr`。

这里是一个使用 `std::exception_ptr` 来传播异常的示例：

```cpp
#include <iostream>
#include <thread>
#include <exception>
#include <string>
#include <vector>

// 线程函数，可能会抛出异常
std::exception_ptr threadFunction(int id) {
    std::exception_ptr ptr = nullptr;
    try {
        // 模拟一些可能会抛出异常的操作
        if (id == 1) {
            throw std::runtime_error("Exception from thread with id 1");
        }
        std::cout << "Thread with id " << id << " is running..." << std::endl;
    } catch (...) {
        // 捕获所有异常并存储在exception_ptr中
        ptr = std::current_exception();
    }
    return ptr;
}

int main() {
    std::vector<std::thread> threads;
    std::vector<std::exception_ptr> exceptions;

    try {
        // 创建两个线程
        for (int i = 1; i <= 2; ++i) {
            threads.emplace_back(threadFunction, i);
            exceptions.push_back(threadFunction(i)); // 执行线程函数并存储异常
        }

        // 等待线程完成并重新抛出异常
        for (auto& t : threads) {
            t.join();
        }
        for (auto& e : exceptions) {
            if (e) {
                std::rethrow_exception(e);
            }
        }
    } catch (const std::exception& e) {
        // 主线程中捕获异常
        std::cerr << "Exception in main thread: " << e.what() << std::endl;
    } catch (...) {
        // 捕获所有类型的异常
        std::cerr << "Unknown exception in main thread" << std::endl;
    }

    return 0;
}
```

在这个示例中，`threadFunction` 返回一个 `std::exception_ptr`，它存储了线程中捕获的异常。在主线程中，我们等待所有线程完成，然后检查每个线程的 `std::exception_ptr`，如果有异常，就使用 `std::rethrow_exception` 重新抛出它。这样，异常就可以从线程传播到主线程了。

## 5.在C++中，如何使用RAII原则来管理资源？

RAII（Resource Acquisition Is Initialization）是C++中一种管理资源获取和释放的编程技术。RAII的核心思想是将资源的生命周期绑定到对象的生命周期。当对象创建时，它获取必要的资源，当对象销毁时，它释放这些资源。这通常通过构造函数来获取资源，通过析构函数来释放资源来实现。

### 5.1.RAII的基本原则

1. **资源获取**：在类的构造函数中分配或获取资源。
2. **资源释放**：在类的析构函数中释放资源。
3. **对象生命周期**：确保对象的生命周期与资源的生命周期一致。
4. **异常安全**：确保在构造过程中发生异常时，已经获取的资源能够被正确释放。

### 5.2.RAII的常见应用

1. **动态内存管理**：使用`new`和`delete`操作符。
2. **文件和网络资源**：使用文件句柄和网络连接。
3. **互斥锁**：使用互斥锁来保护临界区。

### 5.3.示例：使用RAII管理动态内存

```cpp
#include <iostream>

class AutoPtr {
private:
    int* ptr;

public:
    AutoPtr() : ptr(nullptr) {}
    explicit AutoPtr(int* p) : ptr(p) {}
    ~AutoPtr() {
        delete[] ptr;
    }

    // 禁止复制和赋值
    AutoPtr(const AutoPtr&) = delete;
    AutoPtr& operator=(const AutoPtr&) = delete;

    // 支持移动语义
    AutoPtr(AutoPtr&& other) : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    AutoPtr& operator=(AutoPtr&& other) {
        if (this != &other) {
            delete[] ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    int* get() const { return ptr; }
};

int main() {
    AutoPtr ap(new int[10]); // 分配数组
    // 不需要手动释放，析构函数会自动处理
    return 0;
}
```

在这个例子中，`AutoPtr`类使用RAII模式管理一个整数数组的生命周期。当`AutoPtr`对象创建时，它分配内存；当对象销毁时，它释放内存。

### 5.4.示例：使用RAII管理文件资源

```cpp
#include <iostream>
#include <fstream>

class File {
private:
    std::fstream file;

public:
    File(const std::string& filename, std::ios_base::openmode mode) {
        file.open(filename, mode);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file");
        }
    }

    ~File() {
        if (file.is_open()) {
            file.close();
        }
    }

    // 禁止复制和赋值
    File(const File&) = delete;
    File& operator=(const File&) = delete;

    // 支持移动语义
    File(File&& other) : file(std::move(other.file)) {}
    File& operator=(File&& other) {
        file = std::move(other.file);
        return *this;
    }
};

int main() {
    try {
        File f("example.txt", std::ios::in);
        // 使用文件
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    // 文件在f的析构函数中自动关闭
    return 0;
}
```

在这个例子中，`File`类使用RAII模式管理文件资源。当`File`对象创建时，它打开文件；当对象销毁时，它关闭文件。

### 5.5.注意事项

1. **禁止复制**：通常，管理资源的对象应该禁止复制，以避免资源泄漏。
2. **支持移动语义**：支持移动构造函数和移动赋值运算符，以便在不同对象之间传递资源。
3. **异常安全**：确保在构造函数中获取资源时，如果发生异常，已经获取的资源能够被正确释放。
4. **资源泄露**：避免在析构函数中抛出异常，因为这可能导致资源泄露。

RAII是一种强大的资源管理技术，它可以简化代码，提高资源管理的安全性和可靠性。

## 6.在C++中，除了RAII，还有哪些资源管理技术？

在C++中，除了RAII（Resource Acquisition Is Initialization）原则，还有其他一些资源管理技术，这些技术有助于确保资源的正确管理和释放。以下是一些常见的资源管理技术：

1. **智能指针**：
   - `std::unique_ptr`：独占式拥有其所指向的对象，不允许复制，但可以移动。
   - `std::shared_ptr`：共享式拥有其所指向的对象，具有引用计数机制。
   - `std::weak_ptr`：用于解决`std::shared_ptr`可能导致的循环引用问题。

2. **函数对象**（Functors）：
   - 封装状态和行为的对象，可以像函数一样被调用。

3. **模板类**：
   - 通过模板编程，可以编写通用的资源管理代码，如`std::unique_ptr`。

4. **继承和多态**：
   - 通过继承和多态，可以在基类中定义资源管理的接口，由派生类实现具体的资源管理逻辑。

5. **异常处理**：
   - 使用`try`、`catch`和`throw`关键字来捕获和处理异常，确保在异常发生时资源能够被正确释放。

6. **条件编译**：
   - 使用宏定义和条件编译来管理不同平台或配置下的资源。

7. **手动管理**：
   - 直接使用`new`和`delete`，`malloc`和`free`来管理内存资源。

8. **垃圾回收**：
   - 虽然C++标准库中没有内置的垃圾回收机制，但可以使用第三方库或特定的内存管理策略来实现类似垃圾回收的功能。

9. **内存池**（Memory Pool）：
   - 预先分配一块大的内存区域，用于频繁地分配和释放固定大小的对象，以减少内存碎片和提高性能。

10. **对象池**（Object Pool）：
    - 预先创建一组对象，以便快速重用，避免频繁的构造和析构。

11. **线程局部存储**（Thread-Local Storage）：
    - 使用线程局部变量来存储每个线程独有的资源。

12. **原子操作**：
    - 使用`std::atomic`来管理对共享资源的并发访问。

13. **互斥锁**（Mutexes）：
    - 使用互斥锁来保护临界区，确保同一时间只有一个线程可以访问共享资源。

14. **文件描述符封装**：
    - 封装文件描述符等操作系统资源，确保在对象销毁时关闭文件。

15. **事件驱动编程**：
    - 在事件循环中管理资源，确保资源在使用完成后能够被释放。

16. **依赖注入**：
    - 通过将资源作为参数传递给函数或对象，而不是在对象内部创建资源。

这些技术可以单独使用，也可以组合使用，以满足不同场景下的资源管理需求。正确选择和管理资源对于编写高效、可靠和可维护的C++程序至关重要。

## 7.在栈中使用异常处理

在C++中，使用栈（stack）时进行异常处理需要特别注意，因为异常可能会跨越多个栈帧，这可能会导致资源泄漏或其他问题。以下是一些在栈中使用异常处理时的准则：

1. **使用RAII（资源获取即初始化）**：
   - RAII是一种确保资源在对象生命周期内被正确管理的机制。当对象超出作用域时，其析构函数将自动被调用，从而释放资源。

2. **避免在析构函数中抛出异常**：
   - 如果一个对象的析构函数抛出异常，而这个异常没有被捕获，那么程序可能会直接退出。因此，应该在析构函数中避免抛出异常。

3. **使用智能指针管理动态内存**：
   - 使用`std::unique_ptr`或`std::shared_ptr`来自动管理动态分配的内存。

4. **使用`std::stack`的异常安全**：
   - `std::stack`是一个容器适配器，它提供了基本的异常安全保证。但是，如果你在`std::stack`中存储了自定义对象，并且这些对象的复制或移动操作可能会抛出异常，那么你需要确保这些操作是异常安全的。

5. **使用`try-catch`块**：
   - 在可能抛出异常的代码周围使用`try-catch`块来捕获和处理异常。

6. **使用`std::exception_ptr`**：
   - 如果你需要在多个线程之间传递异常，可以使用`std::exception_ptr`。

7. **使用`noexcept`**：
   - 在不会抛出异常的函数后面使用`noexcept`关键字，以告诉编译器这个函数不会抛出异常。

8. **使用`std::uncaught_exceptions`**：
   - `std::uncaught_exceptions`是C++17中引入的，它返回当前线程中未捕获的异常数量。这可以用来检测是否有异常正在传播。

下面是一个示例，展示了如何在栈中使用异常处理：

```cpp
#include <iostream>
#include <stack>
#include <memory>
#include <stdexcept>

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource released\n"; }
};

void safeFunction(std::stack<std::unique_ptr<Resource>>& s) {
    try {
        // 模拟可能会抛出异常的操作
        throw std::runtime_error("Exception in safeFunction");
    } catch (...) {
        // 捕获所有异常
        std::cerr << "Exception caught in safeFunction\n";
        // 确保栈中的资源被正确释放
        s = std::stack<std::unique_ptr<Resource>>(); // 清空栈
        throw; // 重新抛出异常
    }
}

int main() {
    std::stack<std::unique_ptr<Resource>> s;
    try {
        // 将资源推入栈中
        s.push(std::make_unique<Resource>());

        safeFunction(s);
    } catch (const std::exception& e) {
        // 主线程中捕获异常
        std::cerr << "Exception in main thread: " << e.what() << std::endl;
    } catch (...) {
        // 捕获所有类型的异常
        std::cerr << "Unknown exception in main thread" << std::endl;
    }

    // 栈中的资源将自动被释放
    return 0;
}
```

在这个示例中，我们使用`std::unique_ptr`来管理`Resource`对象的生命周期。当`Resource`对象超出作用域时，其析构函数将自动被调用，从而释放资源。在`safeFunction`中，我们捕获所有异常，并在捕获异常后清空栈，以确保栈中的资源被正确释放。然后，我们重新抛出异常，以便在主线程中进行处理。

请注意，这个示例假设异常不会从`safeFunction`传播到主线程。在实际应用中，如果需要将异常从`safeFunction`传播到主线程，可以使用`std::exception_ptr`。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
