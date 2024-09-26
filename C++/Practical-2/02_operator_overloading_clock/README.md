# C++ Practical-2 day2 运算符重载之时钟类++运算符

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃
- clock_overloading

---

## 1.时间类 重载后缀`++`运算符来递增时间

在C++中创建一个时钟类并重载函数调用运算符`()`，可以使得该类的实例可以像函数一样被调用，以执行特定的操作，比如获取当前时间、设置时间等。

下面是一个简单的示例，展示如何定义一个时钟类，该类重载了函数调用运算符来获取当前时间：

为了实现通过重载后缀`++`运算符来递增时间，我们需要在`Clock`类中添加一个特殊的成员函数。这个成员函数将实现后缀递增操作。

```cpp
#include <iostream>
#include <ctime>

class Clock {
private:
    time_t currentTime;

public:
    // 构造函数
    Clock() {
        currentTime = time(0); // 初始化为当前时间
    }

    // 重载()运算符，返回当前时间的字符串表示
    std::string operator()() const { // 保持const
        tm *ltm = localtime(&currentTime); // 转换为本地时间
        char buffer[80];
        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", ltm); // 格式化时间
        return std::string(buffer);
    }

    // 设置时间
    void setTime(time_t newTime) {
        currentTime = newTime;
    }

    // 获取时间
    time_t getTime() const {
        return currentTime;
    }

    // 计算两个时间点之间的差异（秒）
    double timeDifference(const Clock &other) const {
        return difftime(other.currentTime, currentTime);
    }

    // 时间递增
    void incrementTime(int seconds) {
        currentTime += seconds;
    }

    // 重载前置++运算符
    Clock& operator++() {
        incrementTime(1); // 递增1秒
        return *this;
    }

    // 重载后置++运算符
    Clock operator++(int) {
        Clock temp = *this; // 保存当前状态
        incrementTime(1);   // 递增1秒
        return temp;       // 返回递增前的状态
    }
};

int main() {
    Clock myClock;
    std::cout << "Current time: " << myClock() << std::endl;

    // 手动设置时间
    myClock.setTime(time(0)); // 重新设置为当前时间
    std::cout << "Current time after setting: " << myClock() << std::endl;

    // 创建另一个时钟实例
    Clock anotherClock;
    anotherClock.setTime(time(0) + 3600); // 设置为当前时间1小时后

    // 计算两个时间点之间的差异
    double diff = myClock.timeDifference(anotherClock);
    std::cout << "Time difference: " << diff << " seconds" << std::endl;

    // 使用后置++运算符递增时间
    myClock++;
    std::cout << "Current time after incrementing: " << myClock() << std::endl;

    return 0;
}
```

### 1.1.解释

1. **重载后缀`++`运算符**：
   - 功能：实现后缀递增操作，即每次调用`myClock++`时，`currentTime`递增1秒。
   - 返回值：返回`Clock`对象的引用，允许链式调用。

2. **main函数**：
   - 创建`Clock`类的实例`myClock`。
   - 使用重载的`()`运算符获取并打印当前时间。
   - 手动设置时间，并再次打印当前时间。
   - 计算两个时间点之间的差异，并打印结果。
   - 使用后缀`++`运算符递增时间，并打印递增后的时间。

3. **Clock类**：
   - **私有成员变量**：`currentTime`，用于存储时间。
   - **构造函数**：初始化`currentTime`为当前时间。
   - **重载的`()`运算符**：返回当前时间的字符串表示。它使用`time()`函数获取当前时间，然后使用`localtime()`将其转换为本地时间，最后使用`strftime()`格式化时间字符串。
   - **`setTime`成员函数**：允许设置时间。
   - **`getTime`成员函数**：返回当前时间。

通过这种方式，`Clock`类现在可以通过重载后缀`++`运算符来递增时间，使得代码更加简洁和直观。

### 1.2.注意事项

1. **const修饰符**：如果你的重载的`()`运算符不会修改对象的状态，你应该在函数声明的末尾添加`const`关键字，以表明这个成员函数不会修改对象的任何成员变量。

2. **参数**：你可以为`()`运算符提供参数，比如设置时间。

3. **返回类型**：你需要指定函数调用的返回类型。

通过这种方式，你可以创建一个非常灵活的时钟类，该类的对象可以像函数一样被调用，以执行特定的操作。

## 2.如何确保时间递增操作在多线程环境中是线程安全的？

为了确保时间递增操作在多线程环境中是线程安全的，我们需要确保当多个线程尝试同时修改时间时，这些修改不会相互干扰，导致数据不一致。这通常涉及到使用同步机制，如互斥锁（mutexes），来保护对共享资源的访问。

以下是一些确保线程安全的方法：

1. **使用互斥锁（Mutex）**：
   在C++中，可以使用`std::mutex`来确保只有一个线程可以同时修改时间。在递增时间的函数中，我们需要在修改时间之前获取锁，并在修改后释放锁。

   ```cpp
    #include <string>
    #include <mutex>
    #include <ctime>

    class Clock {
    private:
        time_t currentTime;
        mutable std::mutex mtx; // 使用mutable因为mtx在const成员函数中使用

    public:
        Clock() {
            currentTime = time(0);
        }

        // 重载()运算符
        std::string operator()() const {
            std::lock_guard<std::mutex> lock(mtx); // 使用lock_guard自动加锁和解锁
            tm  *ltm = localtime(&currentTime);
            char buffer[80];
            strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", ltm);
            return std::string(buffer);
        }

        // 线程安全的时间递增
        void incrementTime(int seconds) {
            std::lock_guard<std::mutex> lock(mtx);
            currentTime += seconds;
        }

        // 重载后缀++运算符
        Clock &operator++() {
            incrementTime(1);
            return *this;
        }
    };
   ```

2. **使用原子操作**：
   如果时间递增操作可以被设计为原子操作，那么可以使用`std::atomic`来确保操作的原子性。

   ```cpp
   #include <atomic>
   #include <ctime>

   class Clock {
   private:
       std::atomic<time_t> currentTime;

   public:
       Clock() {
           currentTime.store(time(0));
       }

       void incrementTime(int seconds) {
           currentTime.fetch_add(seconds, std::memory_order_relaxed);
       }

       Clock& operator++() {
           incrementTime(1);
           return *this;
       }
   };
   ```

3. **使用条件变量**：
   如果需要更复杂的线程间协调，可以使用`std::condition_variable`来等待和通知时间变化。

4. **避免共享**：
   如果可能，避免共享时间对象，每个线程可以使用本地时间副本，然后定期同步。

5. **使用线程安全的类**：
   使用标准库中已经保证线程安全的类，如`std::chrono`中的一些类。

确保线程安全通常需要仔细设计，并且在多线程程序中进行充分的测试，以确保没有死锁或竞态条件。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
