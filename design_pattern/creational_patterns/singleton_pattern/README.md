# 设计模式-单例模式

[TOC]

## Overview

单例模式是一种创建型设计模式， 让你能够保证一个类只有一个实例， 并提供一个访问该实例的全局节点。

---

**初次接触，直接说懒汉式和饿汉式，容易把人搞懵掉，先认识一下吧！**

## 1.单例模式中懒汉式和饿汉式区别

单例模式中的懒汉式和饿汉式是两种不同的实现策略，它们在实例化单例对象的时机和线程安全性方面有所不同。以下是懒汉式和饿汉式单例模式的主要区别：

### 1.1.懒汉式（Lazy Initialization）

1. **实例化时机**：懒汉式单例在第一次被使用时才会创建实例，即延迟初始化。
2. **线程安全性**：标准的懒汉式实现不是线程安全的。需要引入锁机制（如双重检查锁定）来保证线程安全。
3. **资源利用率**：由于延迟初始化，懒汉式可能在某些情况下减少资源占用，但这也取决于具体实现和使用场景。
4. **性能开销**：在多线程环境下，可能因为锁机制引入额外的性能开销。
5. **实现示例**：

   ```cpp
   class LazySingleton {
   private:
       static LazySingleton* instance;
       static std::mutex mutex;

       LazySingleton() {} // 私有构造函数

   public:
       static LazySingleton* getInstance() {
           if (instance == nullptr) {
               std::lock_guard<std::mutex> lock(mutex);
               if (instance == nullptr) {
                   instance = new LazySingleton();
               }
           }
           return instance;
       }
   };

   LazySingleton* LazySingleton::instance = nullptr;
   std::mutex LazySingleton::mutex;
   ```

### 1.2.饿汉式（Eager Initialization）

1. **实例化时机**：饿汉式单例在程序启动时就立即创建实例，即立即初始化。
2. **线程安全性**：饿汉式实现是线程安全的，因为它在程序启动时就完成了实例化，不存在多线程竞争的问题。
3. **资源利用率**：饿汉式可能会在程序启动时就占用资源，即使该单例实例尚未被使用。
4. **性能开销**：由于避免了锁机制，饿汉式在单例获取时通常具有较高的性能。
5. **实现示例**：

   ```cpp
   class EagerSingleton {
   private:
       static EagerSingleton instance; // 静态实例

       EagerSingleton() {} // 私有构造函数

   public:
       static EagerSingleton& getInstance() {
           return instance;
       }
   };

   EagerSingleton EagerSingleton::instance;
   ```

### 1.3.选择建议

- 如果单例对象的创建成本较高，且在程序早期不需要立即使用，懒汉式可能更合适，因为它可以延迟对象的创建。
- 如果需要确保线程安全，且对单例对象的创建时机没有特别要求，饿汉式是一个简单且有效的选择。
- 在多线程环境中，如果使用懒汉式，需要确保通过适当的同步机制（如双重检查锁定）来保证线程安全。

两种实现方式各有优缺点，应根据具体应用场景和需求来选择最合适的实现策略。

## 2.单例模式 Singleton 实现方式及详细介绍

在 C++中，单例模式是一种创建型设计模式，它确保一个类只有一个实例，并提供一个全局访问点来访问这个实例。以下是单例模式的实现方式及详细介绍：

### 2.1. 懒汉式（线程不安全）

懒汉式单例模式在第一次使用时才会创建实例。

```cpp
class Singleton {
private:
    static Singleton* instance;

    Singleton() {} // 私有构造函数

    // 禁用拷贝构造函数和赋值操作符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
    
    // 其他成员函数和数据成员
    void doSomething() {
        // ...
    }
};

// 初始化静态成员变量
Singleton* Singleton::instance = nullptr;
```

- 在上述代码中， getInstance 函数在第一次被调用时才会创建Singleton类的实例。如果该函数后续被再次调用，将直接返回已经创建的实例。

### 2.2. 懒汉式（线程安全）

- 懒汉式单例模式在多线程环境下可能会出现问题。如果多个线程同时进入getInstance函数并且instance为nullptr，那么可能会创建多个实例。
- 为了解决这个问题，可以使用互斥锁来确保在多线程环境下只有一个线程能够创建实例。例如：

```cpp
#include <mutex>

class Singleton {
private:
    static Singleton* instance;
    static std::mutex mutex;

    Singleton() {} // 私有构造函数

    // 禁用拷贝构造函数和赋值操作符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mutex);
            if (instance == nullptr) {
                instance = new Singleton();
            }
        }
        return instance;
    }
    
    // 其他成员函数和数据成员
    void doSomething() {
        // ...
    }
};

// 初始化静态成员变量
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex;
```

### 2.3. 饿汉式（线程安全）

饿汉式单例模式在程序启动时就创建实例。

```cpp
class Singleton {
private:
    static Singleton instance; // 静态实例

    Singleton() {} // 私有构造函数

    // 禁用拷贝构造函数和赋值操作符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton& getInstance() {
        return instance;
    }
    
    // 其他成员函数和数据成员
    void doSomething() {
        // ...
    }
};

// 实现静态成员变量
Singleton Singleton::instance;
```

### 2.4. C++11后 局部静态变量（线程安全）

- 实现原理
  - C++11 引入了线程安全的静态局部变量初始化特性。利用这个特性，可以在获取单例实例的方法中声明一个静态局部变量，该变量在第一次调用方法时被初始化，并且保证线程安全。
  - 利用局部静态变量的线程安全特性实现单例模式。

```cpp
class Singleton {
private:
    Singleton() {} // 私有构造函数

    // 禁用拷贝构造函数和赋值操作符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton& getInstance() {
        static Singleton instance; // 局部静态变量
        return instance;
    }
    
    // 其他成员函数和数据成员
    void doSomething() {
        // ...
    }
};
```

### 2.5. 注意事项

- 单例类的构造函数、拷贝构造函数和赋值操作符通常都是私有的，以防止创建多个实例。
- 需要确保单例的析构函数是公共的，以便能够销毁单例对象。
- 在多线程环境中，需要特别注意线程安全问题，可以选择使用锁或原子操作来保证线程安全。

单例模式在实际应用中非常广泛，比如配置管理器、数据库连接池管理器等场景。然而，过度使用单例可能导致代码难以测试和维护，因此应谨慎使用。

## 3.单例模式的应用场景

- 日志系统
  - 在一个应用程序中，通常只需要一个日志系统来记录各种信息。使用单例模式可以确保无论在程序的哪个部分调用日志系统，都只有一个实例在运行，避免了多个日志系统之间的冲突和资源浪费。
  - 例如，可以将日志系统实现为单例类，提供统一的接口来记录不同级别的日志信息。
- 数据库连接
  - 在访问数据库时，通常需要建立一个数据库连接。使用单例模式可以确保只有一个数据库连接实例存在，避免了重复建立连接的开销和资源浪费。
  - 例如，可以将数据库连接类实现为单例类，提供方法来执行数据库查询和更新操作。
- 配置管理
  - 应用程序的配置信息通常在整个程序中都需要访问。使用单例模式可以确保只有一个配置管理实例存在，方便在程序的任何地方获取和修改配置信息。
  - 例如，可以将配置管理类实现为单例类，提供方法来读取和修改配置文件中的参数。

总之，单例模式在 C++ 中是一种非常有用的设计模式，它可以确保一个类只有一个实例，并提供一个全局访问点来访问这个实例。在实际应用中，可以根据具体情况选择懒汉式或饿汉式单例模式，并注意线程安全和资源管理等问题。

## 4.单例模式在多线程环境下如何保证线程安全？

在多线程环境下保证单例模式的线程安全，可以采用以下几种方法：

### 4.1. 双重检查锁定（Double-Checked Locking, DCL）

双重检查锁定是一种常见的线程安全单例实现方式，它减少了锁的开销。

```cpp
#include <mutex>

class Singleton {
private:
    static Singleton* instance;
    static std::mutex mutex;

    Singleton() {} // 私有构造函数

    // 禁用拷贝构造函数和赋值操作符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mutex);
            if (instance == nullptr) { // 再次检查实例是否已被创建
                instance = new Singleton();
            }
        }
        return instance;
    }
};

// 初始化静态成员变量
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex;
```

### 4.2. 局部静态变量

利用局部静态变量的线程安全特性，编译器和其他运行时环境保证了局部静态变量的线程安全初始化。

```cpp
class Singleton {
private:
    Singleton() {} // 私有构造函数

    // 禁用拷贝构造函数和赋值操作符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton& getInstance() {
        static Singleton instance; // 局部静态变量
        return instance;
    }
};
```

### 4.3. 原子操作

使用原子操作来确保实例化过程的原子性，避免多线程同时创建实例。

```cpp
#include <atomic>
#include <mutex>

class Singleton {
private:
    static std::atomic<bool> initialized;
    static Singleton* instance;
    static std::mutex mutex;

    Singleton() {} // 私有构造函数

    // 禁用拷贝构造函数和赋值操作符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton* getInstance() {
        if (!initialized.load()) {
            std::lock_guard<std::mutex> lock(mutex);
            if (!initialized.load()) {
                instance = new Singleton();
                initialized.store(true);
            }
        }
        return instance;
    }
};

// 初始化静态成员变量
std::atomic<bool> Singleton::initialized(false);
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex;
```

### 4.4. 使用 `std::call_once` 和 `std::once_flag`

C++11 引入了 `std::call_once` 函数，它保证在多线程环境下对给定函数的首次调用是单线程执行的。

```cpp
#include <mutex>

class Singleton {
private:
    static std::mutex mutex;
    static std::once_flag onceFlag;
    static Singleton* instance;

    Singleton() {} // 私有构造函数

    // 禁用拷贝构造函数和赋值操作符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton* getInstance() {
        std::call_once(onceFlag, [](){
            instance = new Singleton();
        });
        return instance;
    }
};

// 初始化静态成员变量
std::mutex Singleton::mutex;
std::once_flag Singleton::onceFlag;
Singleton* Singleton::instance = nullptr;
```

### 4.5. 注意事项

- 双重检查锁定需要使用 `std::atomic` 或者合适的锁机制来避免多线程环境下的竞态条件。
- 局部静态变量的方法简单且线程安全，但可能在程序的生命周期内无法释放单例对象占用的资源。
- `std::call_once` 是C++11引入的，它提供了一种优雅的方式来保证线程安全的单例模式实现。

在设计单例模式时，需要根据实际的应用场景和需求来选择合适的线程安全实现方式。

## 5.除了懒汉式和饿汉式，还有哪些实现单例模式的方法？

除了懒汉式和饿汉式，C++中还有其他几种实现单例模式的方法，包括使用C++11标准引入的线程安全静态局部变量、基于函数的局部静态变量、以及使用智能指针。以下是这些方法的示例：

### 5.1. 线程安全静态局部变量（C++11）

C++11标准规定，静态局部变量在首次使用时会自动初始化，并且是线程安全的。

```cpp
class Singleton {
private:
    Singleton() {} // 私有构造函数

    // 禁用拷贝构造函数和赋值操作符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton& getInstance() {
        static Singleton instance; // 线程安全的静态局部变量
        return instance;
    }
    
    // 其他成员函数和数据成员
};
```

### 5.2. 基于函数的局部静态变量

在C++中，函数内部的静态变量在首次调用函数时初始化，并且具有线程安全的特性。

```cpp
class Singleton {
private:
    Singleton() {} // 私有构造函数

    // 禁用拷贝构造函数和赋值操作符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton& getInstance() {
        static Singleton& instance = createInstance();
        return instance;
    }

private:
    static Singleton& createInstance() {
        static Singleton instance;
        return instance;
    }
};

// 其他成员函数和数据成员
```

### 5.3. 使用 `std::call_once` 和 `std::once_flag`

C++11引入了`std::call_once`，它用于确保在多线程环境下对某个函数的调用是单次的。

```cpp
#include <mutex>

class Singleton {
private:
    static std::once_flag onceFlag;
    static Singleton* instance;

    Singleton() {} // 私有构造函数

    // 禁用拷贝构造函数和赋值操作符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton* getInstance() {
        std::call_once(onceFlag, [](){
            instance = new Singleton();
        });
        return instance;
    }
    
    // 确保析构函数是公共的，以便能够销毁单例对象
    ~Singleton() {}
};

// 初始化静态成员变量
std::once_flag Singleton::onceFlag;
Singleton* Singleton::instance = nullptr;
```

### 5.4. 使用智能指针

使用`std::shared_ptr`来管理单例实例，可以自动处理内存释放。

```cpp
#include <memory>

class Singleton {
private:
    static std::shared_ptr<Singleton> instance;

    Singleton() {} // 私有构造函数

    // 禁用拷贝构造函数和赋值操作符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static std::shared_ptr<Singleton> getInstance() {
        if (instance == nullptr) {
            instance.reset(new Singleton());
        }
        return instance;
    }
    
    // 其他成员函数和数据成员
};

// 初始化静态成员变量
std::shared_ptr<Singleton> Singleton::instance;
```

### 5.5. 注意事项

- 选择实现单例模式的方法时，需要考虑线程安全性、性能、资源管理等因素。
- 确保单例的析构函数是公共的，以便能够销毁单例对象。
- 智能指针方法虽然可以自动管理内存，但在某些情况下可能会引起循环引用或其他问题，需要谨慎使用。

这些方法各有优缺点，可以根据项目的具体需求和约束来选择最合适的实现方式。

---

## 关于作者

- 本文作者:WeSiGJ
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 微信公众号:WeSiGJ

<img src=/./img/wechat.jpg width=60% />
