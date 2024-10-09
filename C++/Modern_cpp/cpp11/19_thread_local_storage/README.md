# C++11 19-线程局部存储 Thread Local Storage

- [C++11 19-线程局部存储 Thread Local Storage](#c11-19-线程局部存储-thread-local-storage)
  - [Overview](#overview)
  - [1.线程局部存储 Thread Local Storage](#1线程局部存储-thread-local-storage)
  - [2.如何使用 C++11 的 thread\_local 关键字来实现线程安全的单例模式？](#2如何使用-c11-的-thread_local-关键字来实现线程安全的单例模式)
    - [2.1. 定义单例类](#21-定义单例类)
    - [2.2. 使用单例](#22-使用单例)
    - [2.3.注意事项](#23注意事项)
  - [3.在多线程环境中，如何保证单例模式的线程安全性？](#3在多线程环境中如何保证单例模式的线程安全性)
    - [3.1. 懒汉式（Lazy Initialization）与锁](#31-懒汉式lazy-initialization与锁)
    - [3.2. 饿汉式（Eager Initialization）](#32-饿汉式eager-initialization)
    - [3.3. 局部静态变量](#33-局部静态变量)
    - [3.4. 双检锁（Double-Checked Locking）](#34-双检锁double-checked-locking)
    - [3.5. 使用`std::call_once`](#35-使用stdcall_once)
    - [3.6. 禁用复制和赋值](#36-禁用复制和赋值)
    - [3.7.注意事项](#37注意事项)
  - [4.如何确保线程结束时单例实例被正确销毁以避免内存泄漏？](#4如何确保线程结束时单例实例被正确销毁以避免内存泄漏)
  - [5.thread\_local变量的生命周期是如何管理的，如果线程提前结束，它的生命周期会怎样？](#5thread_local变量的生命周期是如何管理的如果线程提前结束它的生命周期会怎样)
  - [关于作者](#关于作者)

## Overview

---

## 1.线程局部存储 Thread Local Storage

在 C++11 中，线程局部存储（Thread Local Storage，TLS）是一种允许每个线程拥有自己的变量实例的机制。这种变量在线程开始时分配，在线程结束时回收。`thread_local` 是 C++11 引入的关键字，用于声明线程局部存储的变量。

使用 `thread_local` 关键字声明的变量，每个线程都会有自己的独立副本，互不影响。这在多线程编程中非常有用，因为它可以避免数据竞争和同步问题。例如，可以为每个线程存储特定的数据，如线程ID、状态或其他上下文信息。

以下是一些关于 `thread_local` 的使用要点：

1. **声明线程局部变量**：

   ```cpp
   thread_local int threadLocalVar = 0;
   ```

2. **与 `static` 或 `extern` 结合**：
   `thread_local` 可以与 `static` 或 `extern` 结合使用，以分别指定内部或外部链接。

   ```cpp
   thread_local static int staticThreadLocalVar = 0;
   extern thread_local int externThreadLocalVar;
   ```

3. **线程局部变量的生命周期**：
   线程局部变量的生命周期从线程创建时开始，到线程结束时结束。

4. **线程局部变量的初始化**：
   线程局部变量可以初始化，但必须是常量表达式。

5. **使用场景**：
   - 线程特定数据：为每个线程存储特定的数据。
   - 避免全局变量：使用 `thread_local` 代替全局变量，以避免数据竞争和同步问题。
   - 性能优化：在某些情况下，使用 `thread_local` 可以提高性能，例如，为每个线程分配一个缓冲区，避免频繁分配和释放内存。

6. **注意**：
   - 系统的线程局部存储区域的内存空间并不大，因此不建议存储大的数据块。
   - 如果需要存储大的数据块，可以将数据存储在堆内存中，然后将指针存储在线程局部存储区域。

在实际应用中，`thread_local` 可以用于实现线程安全的单例模式、线程局部缓存等。使用 `thread_local` 时，需要注意不要在块作用域中声明线程局部变量，也不能用于非常量表达式的初始化。

参考：

- C++11 中的 Thread Local Storage (TLS)
- C++11 线程局部存储

## 2.如何使用 C++11 的 thread_local 关键字来实现线程安全的单例模式？

使用 `thread_local` 关键字实现线程安全的单例模式意味着每个线程都会有它自己的单例实例，而不是在所有线程间共享同一个实例。这种方式适用于那些在多线程环境中需要隔离数据的场景。

以下是使用 `thread_local` 实现线程安全单例模式的步骤：

### 2.1. 定义单例类

首先，定义一个单例类，并在类内使用 `thread_local` 存储实例指针。

```cpp
class ThreadLocalSingleton {
private:
    ThreadLocalSingleton() = default;
    ~ThreadLocalSingleton() = default;

    // 确保不会复制和移动
    ThreadLocalSingleton(const ThreadLocalSingleton&) = delete;
    ThreadLocalSingleton& operator=(const ThreadLocalSingleton&) = delete;

public:
    static thread_local ThreadLocalSingleton* instance;

    // 获取当前线程的单例实例
    static ThreadLocalSingleton* getInstance() {
        if (instance == nullptr) {
            instance = new ThreadLocalSingleton();
        }
        return instance;
    }
};

// 初始化静态成员变量
thread_local ThreadLocalSingleton* ThreadLocalSingleton::instance = nullptr;
```

### 2.2. 使用单例

每个线程调用 `getInstance` 方法时，都会得到它自己的单例实例。

```cpp
void threadFunction() {
    ThreadLocalSingleton* singleton = ThreadLocalSingleton::getInstance();
    // 使用 singleton 进行操作
}
```

### 2.3.注意事项

1. **内存管理**：每个线程创建了自己的单例实例，因此必须确保在线程结束时释放内存。这通常需要在线程结束时手动删除实例。

2. **销毁时机**：需要考虑合适的时机来销毁单例实例，以避免内存泄漏。一种方法是在线程结束时，使用线程特定的清理机制（如 `pthread` 的 `pthread_key_create` 和 `pthread_key_delete`）来删除单例实例。

3. **销毁方法**：可以定义一个销毁方法，在适当的时机（如线程结束时）调用。

```cpp
class ThreadLocalSingleton {
private:
    ThreadLocalSingleton() = default;
    ~ThreadLocalSingleton() = default;

public:
    static thread_local ThreadLocalSingleton* instance;

    static ThreadLocalSingleton* getInstance() {
        if (instance == nullptr) {
            instance = new ThreadLocalSingleton();
        }
        return instance;
    }

    static void destroyInstance() {
        delete instance;
        instance = nullptr;
    }
};

thread_local ThreadLocalSingleton* ThreadLocalSingleton::instance = nullptr;
```

4. **线程结束时清理**：在线程结束时（例如，在线程的析构函数中），调用 `destroyInstance` 方法来清理单例实例。

```cpp
class Thread {
public:
    Thread() {
        // ...
    }
    ~Thread() {
        ThreadLocalSingleton::destroyInstance();
        // ...
    }
    void start() {
        // ...
    }
};

// 在线程结束时，Thread 类的析构函数会被调用，从而清理单例实例
```

使用 `thread_local` 实现线程安全的单例模式可以确保每个线程都有自己独立的单例实例，这对于隔离线程间的数据非常有用。然而，这也意味着需要额外关注内存管理和销毁时机，以避免内存泄漏。

## 3.在多线程环境中，如何保证单例模式的线程安全性？

在多线程环境中，确保单例模式的线程安全性是一个常见的挑战。以下是一些常用的方法：

### 3.1. 懒汉式（Lazy Initialization）与锁

懒汉式单例在第一次被引用时初始化。为了保证线程安全，通常需要使用互斥锁（`mutex`）来同步访问：

```cpp
class Singleton {
private:
    static Singleton* instance;
    static std::mutex mutex;
    Singleton() = default;

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* getInstance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
};

Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex;
```

### 3.2. 饿汉式（Eager Initialization）

饿汉式单例在程序启动时初始化。这种方式天然线程安全，因为实例在程序启动时就已创建好：

```cpp
class Singleton {
private:
    Singleton() = default;
    static Singleton instance;

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton& getInstance() {
        return instance;
    }
};

Singleton Singleton::instance;
```

### 3.3. 局部静态变量

C++11 保证了局部静态变量的线程安全初始化。因此，这种方法是线程安全的：

```cpp
class Singleton {
private:
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }
};
```

### 3.4. 双检锁（Double-Checked Locking）

双检锁模式在某些情况下可以减少锁的开销，但它实现复杂且容易出错：

```cpp
class Singleton {
private:
    static Singleton* instance;
    static std::mutex mutex;
    Singleton() = default;

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* getInstance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mutex);
            if (instance == nullptr) {
                instance = new Singleton();
            }
        }
        return instance;
    }
};

Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex;
```

### 3.5. 使用`std::call_once`

`std::call_once` 保证某个函数只被调用一次，即使多个线程同时请求执行它：

```cpp
class Singleton {
private:
    Singleton() = default;
    static Singleton* instance;
    static std::once_flag onceFlag;

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* getInstance() {
        std::call_once(onceFlag, []() {
            instance = new Singleton();
        });
        return instance;
    }
};

Singleton* Singleton::instance = nullptr;
std::once_flag Singleton::onceFlag;
```

### 3.6. 禁用复制和赋值

确保单例类不能被复制和赋值，这可以防止意外创建多个实例。

### 3.7.注意事项

- 在多线程环境中，确保单例的线程安全至关重要。
- 选择正确的单例实现方式取决于具体需求和上下文。
- 局部静态变量和 `std::call_once` 是实现线程安全单例的最简单和推荐的方式。

通过上述方法，你可以确保在多线程环境中单例模式的线程安全性。

## 4.如何确保线程结束时单例实例被正确销毁以避免内存泄漏？

要确保线程结束时单例实例被正确销毁以避免内存泄漏，可以采取以下措施：

1. **使用`thread_local`存储单例实例**：这样每个线程都会有自己的单例实例，并且在线程结束时自动销毁。但需要手动管理实例的生命周期，确保在线程结束前释放资源。

2. **在线程结束时清理**：如果使用`thread_local`，可以在线程结束前或者在特定的清理阶段调用销毁函数来释放单例实例。

3. **使用智能指针管理资源**：使用`std::shared_ptr`或`std::unique_ptr`来管理单例实例，确保资源在不再需要时自动释放。

4. **使用`std::call_once`和`std::once_flag`**：确保初始化代码只执行一次，并且在适当的时候释放资源。

5. **注册线程清理函数**：在线程开始时注册一个清理函数，当线程结束时自动调用该函数来销毁单例实例。

6. **使用线程池时特别注意**：线程池中的线程可能会被复用，因此需要确保在任务执行完毕后及时清理单例实例。

7. **使用`std::thread`的`join`方法**：确保在主线程结束之前，所有子线程都已完成执行并进行了适当的清理。

8. **内存泄漏检测工具**：定期使用内存泄漏检测工具，如 Valgrind、AddressSanitizer 等，来检测潜在的内存泄漏问题。

9. **编写单元测试**：编写测试用例来模拟多线程环境下的单例使用，确保在各种情况下都能正确销毁单例实例。

通过上述措施，可以有效地管理线程局部存储中的单例实例，避免内存泄漏。

## 5.thread_local变量的生命周期是如何管理的，如果线程提前结束，它的生命周期会怎样？

`thread_local` 关键字在 C++11 中用于定义线程局部存储，这意味着每个线程都会有一个该变量的独立副本。这些变量的生命周期通常与线程的生命周期相同：在线程开始时创建，在线程结束时销毁。

如果线程提前结束，`thread_local` 变量的生命周期也会随之结束。在线程结束时，其 `thread_local` 变量的销毁过程会遵循以下步骤：

1. 如果 `thread_local` 变量是一个对象，那么它的析构函数会被调用，这允许进行任何必要的清理工作。
2. 变量占用的内存会被释放，因为它不再被任何线程引用。

然而，如果线程意外结束（例如，由于异常或外部干预），`thread_local` 变量可能不会经历正常的析构过程，这可能导致资源泄漏。为了避免这种情况，可以采取以下措施：

1. **确保异常安全**：在 `thread_local` 对象的析构函数中，确保所有资源都被适当释放，即使在异常发生时也是如此。
2. **使用智能指针**：对于动态分配的资源，使用智能指针（如 `std::unique_ptr` 或 `std::shared_ptr`）可以确保资源在对象销毁时自动释放。
3. **手动管理资源**：在线程结束之前，显式地清理和释放 `thread_local` 变量持有的资源。

在多线程程序中，正确管理 `thread_local` 变量的生命周期对于避免内存泄漏和其他资源管理问题至关重要。如果线程池中的线程可能会被重用，需要特别注意在任务执行完毕后清理 `thread_local` 变量，以确保无用的对象能够及时释放。

此外，使用 `thread_local` 变量时，应避免在长时间运行的线程中使用它们，因为这些线程可能不会及时结束，从而导致 `thread_local` 变量长时间占用内存。在这些情况下，可以考虑使用其他同步机制或数据结构来存储线程间共享的数据。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
