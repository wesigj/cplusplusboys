# C++11 04-并发编程 Concurrent programming

- [C++11 04-并发编程 Concurrent programming](#c11-04-并发编程-concurrent-programming)
  - [Overview](#overview)
  - [1.并发编程 Concurrent programming](#1并发编程-concurrent-programming)
    - [1.1. 线程库 (`<thread>`)](#11-线程库-thread)
    - [1.2. 互斥锁 (`<mutex>`)](#12-互斥锁-mutex)
    - [1.3. 条件变量 (`<condition_variable>`)](#13-条件变量-condition_variable)
    - [1.4. 原子操作 (`<atomic>`)](#14-原子操作-atomic)
    - [1.5. 线程安全的初始化和销毁](#15-线程安全的初始化和销毁)
    - [1.6. 避免死锁](#16-避免死锁)
    - [1.7. 资源管理](#17-资源管理)
  - [2.C++11 中的原子操作是如何保证线程安全和操作的原子性的？](#2c11-中的原子操作是如何保证线程安全和操作的原子性的)
    - [2.1.原子类型](#21原子类型)
    - [2.2.原子操作的保证](#22原子操作的保证)
    - [2.3.原子操作的例子](#23原子操作的例子)
    - [2.4.内存顺序选项](#24内存顺序选项)
  - [3.在C++11中，如何使用互斥锁来保护共享资源不被多个线程同时访问？](#3在c11中如何使用互斥锁来保护共享资源不被多个线程同时访问)
    - [3.1. 包含必要的头文件](#31-包含必要的头文件)
    - [3.2. 定义互斥锁](#32-定义互斥锁)
    - [3.3. 使用互斥锁保护共享资源](#33-使用互斥锁保护共享资源)
      - [3.3.1.使用 `std::lock_guard`](#331使用-stdlock_guard)
      - [3.3.2.直接使用 `lock()` 和 `unlock()`](#332直接使用-lock-和-unlock)
    - [3.4. 注意死锁](#34-注意死锁)
    - [3.5. 使用 `std::unique_lock` 进行更灵活的锁定](#35-使用-stdunique_lock-进行更灵活的锁定)
  - [4.C++11的条件变量和信号量有什么区别，它们在并发编程中通常如何使用？](#4c11的条件变量和信号量有什么区别它们在并发编程中通常如何使用)
    - [4.1.条件变量 (`std::condition_variable`)](#41条件变量-stdcondition_variable)
    - [4.2.信号量 (`std::counting_semaphore`)](#42信号量-stdcounting_semaphore)
    - [4.3.在并发编程中的使用](#43在并发编程中的使用)
    - [4.4.选择使用条件变量还是信号量](#44选择使用条件变量还是信号量)
    - [4.5.示例](#45示例)
  - [5.如何使用 C++11 的条件变量来解决生产者-消费者问题？](#5如何使用-c11-的条件变量来解决生产者-消费者问题)
    - [5.1. 包含必要的头文件](#51-包含必要的头文件)
    - [5.2. 定义共享资源和同步原语](#52-定义共享资源和同步原语)
    - [5.3. 定义生产者函数](#53-定义生产者函数)
    - [5.4. 定义消费者函数](#54-定义消费者函数)
    - [5.5. 在主函数中创建线程](#55-在主函数中创建线程)
    - [5.6.注意事项](#56注意事项)
  - [6.信号量在多线程环境下如何帮助避免竞态条件？](#6信号量在多线程环境下如何帮助避免竞态条件)
    - [6.1.如何使用信号量避免竞态条件？](#61如何使用信号量避免竞态条件)
    - [6.2.示例代码](#62示例代码)
  - [关于作者](#关于作者)

## Overview

---

## 1.并发编程 Concurrent programming

C++11 引入了对并发编程的原生支持，通过标准库中的线程库（`<thread>`）、互斥锁（`<mutex>`）、条件变量（`<condition_variable>`）和原子操作（`<atomic>`）等组件，使得编写多线程程序变得更加容易和安全。

以下是 C++11 并发编程的一些关键点：

### 1.1. 线程库 (`<thread>`)

C++11 提供了 `std::thread` 类来创建和管理线程。

```cpp
#include <iostream>
#include <thread>

void hello() {
    std::cout << "Hello from thread!" << std::endl;
}

int main() {
    std::thread t(hello);
    t.join(); // 等待线程 t 完成
    return 0;
}
```

你也可以将 Lambda 表达式作为线程的入口点：

```cpp
std::thread t([]() {
    std::cout << "Hello from thread!" << std::endl;
});
t.join();
```

### 1.2. 互斥锁 (`<mutex>`)

为了防止多个线程同时访问共享数据，造成数据竞争，C++11 提供了多种互斥锁：

- `std::mutex`：基本的互斥锁。
- `std::recursive_mutex`：允许一个线程多次锁定互斥锁。
- `std::timed_mutex`：可以在指定时间内尝试锁定互斥锁。
- `std::recursive_timed_mutex`：结合了递归和定时特性的互斥锁。

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int shared_data = 0;

void increment() {
    mtx.lock();
    ++shared_data;
    mtx.unlock();
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << "Shared data: " << shared_data << std::endl;
    return 0;
}
```

### 1.3. 条件变量 (`<condition_variable>`)

条件变量用于线程间的同步，可以让一个线程在特定条件下挂起，直到被另一个线程唤醒。

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{ return ready; });
    std::cout << "Thread " << id << std::endl;
}

int main() {
    std::thread threads[10];
    for (int i = 0; i < 10; ++i) {
        threads[i] = std::thread(print_id, i);
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_all();
    for (auto& th : threads) {
        th.join();
    }
    return 0;
}
```

### 1.4. 原子操作 (`<atomic>`)

原子操作提供了一种机制，使得对某些类型的操作是原子的，即不可分割的。

```cpp
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> count(0);

void increment() {
    count.fetch_add(1, std::memory_order_relaxed);
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << "Count: " << count << std::endl;
    return 0;
}
```

### 1.5. 线程安全的初始化和销毁

确保线程安全的初始化和销毁，特别是在创建和销毁线程时。

### 1.6. 避免死锁

避免死锁的常见方法包括锁定顺序、超时机制和使用`std::lock_guard`和`std::unique_lock`。

### 1.7. 资源管理

确保线程使用的资源在线程结束后能够正确释放，避免资源泄漏。

通过使用 C++11 提供的并发编程工具，你可以编写更安全、更高效的多线程程序。

## 2.C++11 中的原子操作是如何保证线程安全和操作的原子性的？

在 C++11 中，原子操作是通过 `<atomic>` 头文件提供的一系列原子类型和操作来保证线程安全和操作的原子性的。原子操作确保了在多线程环境中，即使多个线程同时访问同一个变量，每个操作也好像是在没有其他线程干扰的情况下完成的。

### 2.1.原子类型

C++11 标准库提供了多种原子类型，包括：

- `std::atomic`：用于内置的整数类型。
- `std::atomic<bool>`：用于布尔类型。
- `std::atomic<char>`：用于字符类型。
- `std::atomic<signed char>`、`std::atomic<unsigned char>`、`std::atomic<wchar_t>`、`std::atomic<char16_t>`、`std::atomic<char32_t>`：用于不同的字符和宽字符类型。
- `std::atomic<short>`、`std::atomic<unsigned short>`：用于短整型。
- `std::atomic<int>`、`std::atomic<unsigned int>`：用于整型。
- `std::atomic<long>`、`std::atomic<unsigned long>`：用于长整型。
- `std::atomic<long long>`、`std::atomic<unsigned long long>`：用于长长整型。
- `std::atomic<float>`、`std::atomic<double>`、`std::atomic<long double>`：用于浮点类型。
- `std::atomic<std::ptrdiff_t>`、`std::atomic<size_t>`：用于指针和大小计算。

### 2.2.原子操作的保证

原子操作保证了以下特性：

1. **原子性**：原子操作是不可中断的，要么完全执行，要么完全不执行，不会出现中间状态。

2. **内存顺序**：原子操作定义了内存的访问顺序，以避免编译器和处理器的乱序执行。

3. **线程安全**：原子操作在多线程环境中是安全的，不需要额外的同步机制。

### 2.3.原子操作的例子

以下是一些使用原子操作的例子：

```cpp
#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> count(0);

void increment() {
    count.fetch_add(1, std::memory_order_relaxed); // 原子地增加 count 的值
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    std::thread t3(increment);
    std::thread t4(increment);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << "Final count: " << count << std::endl; // 输出可能是 4
    return 0;
}
```

在这个例子中，`fetch_add` 是一个原子操作，它将 `count` 的当前值与 1 相加，并存储结果，所有这些都在单个原子操作中完成。

### 2.4.内存顺序选项

C++11 原子操作提供了不同的内存顺序选项，包括：

- `std::memory_order_relaxed`：不对执行顺序做任何保证。
- `std::memory_order_consume`：确保在当前原子操作之前的读取操作对在它之后的读取操作可见。
- `std::memory_order_acquire`：确保在当前原子操作之前的读取操作对在它之后的所有操作可见。
- `std::memory_order_release`：确保当前原子操作之后的读取操作对在它之前的写入操作可见。
- `std::memory_order_acq_rel`：结合了 `acquire` 和 `release` 的语义。
- `std::memory_order_seq_cst`：提供顺序一致的内存顺序。

通过这些特性，C++11 的原子操作为多线程程序提供了一种有效的方式来实现线程安全和操作的原子性。

## 3.在C++11中，如何使用互斥锁来保护共享资源不被多个线程同时访问？

在 C++11 中，使用互斥锁（mutex）来保护共享资源是多线程编程中确保线程安全的一种常见做法。互斥锁可以确保任何时候只有一个线程可以访问被保护的资源。C++11 提供了 `std::mutex` 来实现这样的锁机制。

以下是如何使用 `std::mutex` 来保护共享资源的步骤：

### 3.1. 包含必要的头文件

首先，需要包含 `<mutex>` 头文件。

```cpp
#include <mutex>
```

### 3.2. 定义互斥锁

在共享资源的同一作用域中定义一个 `std::mutex` 对象。

```cpp
std::mutex mtx;
```

### 3.3. 使用互斥锁保护共享资源

在访问共享资源之前锁定互斥锁，并在访问完成后释放锁。这可以通过 `std::lock_guard`（RAII方式）或直接调用 `lock()` 和 `unlock()` 方法来实现。

#### 3.3.1.使用 `std::lock_guard`

`std::lock_guard` 是一种自动管理互斥锁锁定和解锁的辅助类，它在构造时自动锁定互斥锁，并在析构时自动释放锁。

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int shared_data = 0;

void increment() {
    std::lock_guard<std::mutex> lock(mtx);
    ++shared_data; // 安全地修改共享资源
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    std::thread t3(increment);
    std::thread t4(increment);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << "Shared data: " << shared_data << std::endl; // 输出 4
    return 0;
}
```

#### 3.3.2.直接使用 `lock()` 和 `unlock()`

如果你需要更细粒度的锁控制，可以直接调用 `lock()` 和 `unlock()` 方法。

```cpp
void increment() {
    mtx.lock();
    ++shared_data;
    mtx.unlock();
}
```

### 3.4. 注意死锁

在使用互斥锁时，要注意避免死锁。确保在所有情况下都能释放锁，并且考虑使用 `std::lock_guard` 来自动管理锁的释放。

### 3.5. 使用 `std::unique_lock` 进行更灵活的锁定

`std::unique_lock<std::mutex>` 提供了比 `std::lock_guard` 更灵活的锁定机制，它允许延迟锁定和重复锁定。

```cpp
void increment() {
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
    // 可以选择在需要的时候调用 lock.lock()
    lock.lock();
    ++shared_data;
    lock.unlock();
}
```

通过使用 `std::mutex` 和相关的锁定机制，你可以有效地保护共享资源，防止多个线程同时访问，从而确保线程安全。

## 4.C++11的条件变量和信号量有什么区别，它们在并发编程中通常如何使用？

在 C++11 中，条件变量 (`std::condition_variable`) 和信号量 (`std::counting_semaphore`) 是两种不同的同步机制，它们在并发编程中有着不同的用途和特点。

### 4.1.条件变量 (`std::condition_variable`)

条件变量主要用于线程间的同步，它允许一个或多个线程等待某个条件成立。使用条件变量时，通常与互斥锁 (`std::mutex`) 结合使用。条件变量可以阻塞线程直到被另一个线程通知，并且条件成立。

- **用途**：用于线程间协调，等待特定条件发生。
- **工作方式**：与互斥锁结合使用，通过 `wait`、`wait_for` 或 `wait_until` 函数挂起线程，直到被通知。
- **特点**：必须与互斥锁一起使用，用于复杂的同步逻辑。

### 4.2.信号量 (`std::counting_semaphore`)

信号量是一种轻量级的同步原语，用于控制对共享资源的并发访问。与条件变量不同，信号量不依赖于互斥锁，它通过内部计数器来控制资源的访问。

- **用途**：用于控制资源的并发访问数量。
- **工作方式**：通过 `acquire` 和 `release` 函数来控制资源的访问，计数器递减表示资源被占用，递增表示资源被释放。
- **特点**：可以设置最大资源访问数量，适用于限制并发资源访问的场景。

### 4.3.在并发编程中的使用

1. **条件变量**：
   - 当需要等待某个条件成立时使用，如等待数据变得可用。
   - 通常用于生产者-消费者问题，其中一个线程生产数据，另一个线程消费数据。

2. **信号量**：
   - 当需要限制对共享资源的并发访问数量时使用，如限制同时访问某个资源的线程数量。
   - 适用于需要信号通知的场景，如线程池中的任务调度。

### 4.4.选择使用条件变量还是信号量

- 如果你需要等待一个条件成立，并且这个条件与互斥锁保护的共享数据有关，那么条件变量是更好的选择。
- 如果你需要控制对资源的并发访问数量，或者需要在没有互斥锁的情况下进行线程间的同步，那么信号量可能更适合。

### 4.5.示例

**条件变量**：

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker_thread() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{ return ready; });
    std::cout << "Thread is processing data\n";
}

int main() {
    std::thread worker(worker_thread);
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
        cv.notify_one();
    }
    worker.join();
    return 0;
}
```

**信号量**：

```cpp
#include <iostream>
#include <thread>
#include <semaphore>

std::counting_semaphore<1> sem(0);

void worker_thread() {
    sem.acquire();
    std::cout << "Thread is processing data\n";
    sem.release();
}

int main() {
    std::thread worker(worker_thread);
    sem.release();
    worker.join();
    return 0;
}
```

在实际应用中，选择哪种同步机制取决于具体的并发需求和场景。

## 5.如何使用 C++11 的条件变量来解决生产者-消费者问题？

在 C++11 中，条件变量 (`std::condition_variable`) 是解决生产者-消费者问题的理想工具，因为它允许线程在某些条件成立之前挂起等待，并在条件满足时被唤醒。生产者-消费者问题通常涉及到多个线程，其中一些线程负责生产数据，而另一些线程负责消费数据。

以下是使用条件变量解决生产者-消费者问题的步骤：

### 5.1. 包含必要的头文件

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
```

### 5.2. 定义共享资源和同步原语

定义一个互斥锁（`std::mutex`）和一个条件变量（`std::condition_variable`），以及一个用于存储数据的队列。

```cpp
std::mutex mtx;
std::condition_variable cv;
std::queue<int> data_queue;
```

### 5.3. 定义生产者函数

生产者函数将数据放入队列，并通知消费者数据已准备好。

```cpp
void producer(int id) {
    for (int i = 0; i < 5; ++i) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            data_queue.push(id * 10 + i);
            std::cout << "Produced " << id * 10 + i << std::endl;
        }
        cv.notify_one(); // 通知一个等待的消费者
    }
}
```

### 5.4. 定义消费者函数

消费者函数从队列中获取数据进行处理。

```cpp
void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{ return !data_queue.empty(); }); // 等待直到队列不为空
        int data = data_queue.front();
        data_queue.pop();
        lock.unlock();
        std::cout << "Consumed " << data << std::endl;
    }
}
```

### 5.5. 在主函数中创建线程

在主函数中创建生产者和消费者线程。

```cpp
int main() {
    std::thread t1(producer, 1);
    std::thread t2(consumer);

    t1.join();
    // 停止条件，这里简单地等待生产者完成
    cv.wait(std::unique_lock<std::mutex>(mtx, std::defer_lock), []{ return data_queue.empty(); });
    t2.detach(); // 消费者线程将继续运行，直到程序结束

    return 0;
}
```

### 5.6.注意事项

1. **死锁避免**：确保在调用 `wait` 之前已经获取了互斥锁。
2. **虚假唤醒**：使用 `std::condition_variable::wait` 的谓词来防止虚假唤醒。
3. **唤醒策略**：`notify_one` 唤醒一个等待线程，`notify_all` 唤醒所有等待线程。根据需要选择使用。
4. **资源清理**：确保在程序结束前正确地清理资源，如销毁线程。

通过这种方式，生产者线程可以安全地生成数据，而消费者线程可以安全地消费数据，而不会访问到正在被生产者修改的数据。条件变量确保了生产者和消费者之间的同步。

## 6.信号量在多线程环境下如何帮助避免竞态条件？

在多线程环境下，信号量（semaphore）是一种用于控制对共享资源的并发访问的同步机制。它通过一个计数器来限制对共享资源的访问数量，从而帮助避免竞态条件。

### 6.1.如何使用信号量避免竞态条件？

1. **互斥信号量（Mutex Semaphore）**：
   - 使用二元信号量（binary semaphore）可以实现互斥，确保一次只有一个线程可以访问临界资源。这类似于互斥锁（mutex），通常用于保护临界区。
   - 例如，如果多个线程需要访问一个共享变量，可以在访问前执行 `semaphore.wait()`，在访问后执行 `semaphore.signal()`。

2. **计数信号量（Counting Semaphore）**：
   - 计数信号量允许多个线程同时访问资源，只要不超过信号量的计数限制。
   - 例如，如果有多个生产者线程向一个固定大小的缓冲区添加数据，可以使用计数信号量来限制同时访问缓冲区的线程数量。

3. **信号量的初始化**：
   - 在 C++ 中，可以使用 `<semaphore>` 头文件中的 `std::counting_semaphore` 类来创建信号量。
   - 信号量应该在线程执行之前初始化，并且初始计数应该设置为允许同时访问资源的最大线程数。

4. **使用信号量进行同步**：
   - 使用 `semaphore.wait()`（或 `acquire()`）来请求资源，如果信号量的计数大于0，则减少计数并继续执行；如果为0，则线程阻塞，直到信号量的计数增加。
   - 使用 `semaphore.signal()`（或 `release()`）来释放资源，增加信号量的计数，并可能唤醒等待的线程。

5. **避免死锁**：
   - 确保每次 `wait()` 调用都有对应的 `signal()` 调用，以避免死锁。
   - 使用适当的错误处理和超时机制来处理信号量操作可能失败的情况。

### 6.2.示例代码

```cpp
#include <semaphore>
#include <thread>
#include <iostream>

std::counting_semaphore<3> sem(3); // 允许最多3个线程同时访问

void threadFunction() {
    sem.acquire(); // 请求资源
    // 执行临界区代码
    std::cout << "Thread " << std::this_thread::get_id() << " is running." << std::endl;
    sem.release(); // 释放资源
}

int main() {
    std::thread threads[5];
    for (int i = 0; i < 5; ++i) {
        threads[i] = std::thread(threadFunction);
    }
    for (auto& th : threads) {
        th.join();
    }
    return 0;
}
```

在这个例子中，我们创建了一个初始计数为3的信号量，允许最多3个线程同时执行临界区代码。每个线程在执行前会请求资源，执行完毕后释放资源。

通过使用信号量，你可以有效地控制对共享资源的并发访问，从而避免竞态条件。同时，合理的信号量设计还可以提高程序的并发性能。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
