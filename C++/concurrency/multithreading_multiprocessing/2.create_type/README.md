# C++ 创建线程的五种类型

- [C++ 创建线程的五种类型](#c-创建线程的五种类型)
  - [Overview](#overview)
  - [1.创建线程的五种类型](#1创建线程的五种类型)
    - [1.1. 使用 `std::thread`](#11-使用-stdthread)
    - [1.2. 使用 `std::async`](#12-使用-stdasync)
    - [1.3. 使用 POSIX 线程（`pthread`）](#13-使用-posix-线程pthread)
    - [1.4. 使用 Windows 线程（`CreateThread`）](#14-使用-windows-线程createthread)
    - [1.5. 使用线程池](#15-使用线程池)
  - [2.在 C++ 中，如何使用 `std::thread` 来管理线程的生命周期？](#2在-c-中如何使用-stdthread-来管理线程的生命周期)
    - [2.1.创建线程](#21创建线程)
    - [2.2.等待线程完成](#22等待线程完成)
    - [2.3.检查线程状态](#23检查线程状态)
    - [2.4.线程分离](#24线程分离)
    - [2.5.传递参数给线程](#25传递参数给线程)
    - [2.6.异常处理](#26异常处理)
    - [2.7.线程生命周期管理](#27线程生命周期管理)
    - [2.8.使用 `std::thread` 的注意事项](#28使用-stdthread-的注意事项)
  - [3. `std:async` 和 `~std:thread` 在性能上有什么差异？](#3-stdasync-和-stdthread-在性能上有什么差异)
    - [3.1.`std::async` 的特点](#31stdasync-的特点)
    - [3.2.`std::thread` 的特点](#32stdthread-的特点)
    - [3.3.性能差异](#33性能差异)
    - [3.4.使用场景](#34使用场景)
  - [4.使用POSIX线程（pthread）和Windows线程（CreateThread"）在跨平台开发中有哪些考虑因素?](#4使用posix线程pthread和windows线程createthread在跨平台开发中有哪些考虑因素)
  - [关于作者](#关于作者)

## Overview

---

## 1.创建线程的五种类型

在 C++ 中，创建线程可以通过多种方式实现，每种方式有其特定的用途和特点。以下是五种常见的创建线程的方法：

### 1.1. 使用 `std::thread`

这是 C++11 引入的最直观的线程创建方式，允许你直接在 C++ 代码中创建和管理线程。

**示例代码**：

```cpp
#include <iostream>
#include <thread>

void hello() {
    std::cout << "Hello from thread" << std::endl;
}

int main() {
    std::thread t(hello);
    t.join();
    return 0;
}
```

### 1.2. 使用 `std::async`

`std::async` 是基于 `std::thread` 的一个封装，它不仅创建了一个线程，还返回一个 `std::future` 对象，可以用来获取异步操作的结果。

**示例代码**：

```cpp
#include <iostream>
#include <future>

int compute() {
    return 42;
}

int main() {
    std::future<int> result = std::async(std::launch::async, compute);
    std::cout << "Result: " << result.get() << std::endl;
    return 0;
}
```

### 1.3. 使用 POSIX 线程（`pthread`）

这是在 UNIX-like 系统中使用的标准线程库。虽然 C++11 提供了 `std::thread`，但在某些情况下，你可能仍然需要使用 POSIX 线程，尤其是在需要更底层控制时。

**示例代码**：

```cpp
#include <iostream>
#include <pthread.h>

void* hello(void*) {
    std::cout << "Hello from pthread" << std::endl;
    return nullptr;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, nullptr, hello, nullptr);
    pthread_join(tid, nullptr);
    return 0;
}
```

### 1.4. 使用 Windows 线程（`CreateThread`）

这是 Windows 操作系统提供的线程创建API。与 POSIX 线程类似，这是操作系统级别的线程创建方法。

**示例代码**：

```cpp
#include <windows.h>
#include <iostream>

DWORD WINAPI ThreadFunc(LPVOID lpParam) {
    std::cout << "Hello from Windows thread" << std::endl;
    return 0;
}

int main() {
    HANDLE hThread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    return 0;
}
```

### 1.5. 使用线程池

线程池可以管理一组工作线程，允许你提交任务给线程池处理，而不是每次都创建和销毁线程。这可以减少资源消耗和提高效率。

**示例代码**：

```cpp
#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

class ThreadPool {
public:
    ThreadPool(size_t threads) {
        for(size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this] {
                while(true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock, [this]{ return this->stop || !this->tasks.empty(); });
                        if(this->stop && this->tasks.empty())
                            return;
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) 
        -> std::future<typename std::result_of<F(Args...)>::type> {
        using return_type = typename std::result_of<F(Args...)>::type;
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if(stop)
                throw std::runtime_error("enqueue on stopped ThreadPool");
            tasks.emplace([task](){ (*task)(); });
        }
        condition.notify_one();
        return res;
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for(std::thread &worker: workers)
            worker.join();
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop = false;
};

int main() {
    ThreadPool pool(4);
    auto result = pool.enqueue([](int answer) { return answer; }, 42);
    std::cout << "Result: " << result.get() << std::endl;
    return 0;
}
```

这些方法各有优缺点，选择哪一种取决于你的具体需求，例如平台兼容性、性能要求、代码的可维护性等。

## 2.在 C++ 中，如何使用 `std::thread` 来管理线程的生命周期？

在 C++ 中，`std::thread` 类是用来创建和管理线程的。以下是如何使用 `std::thread` 来管理线程生命周期的一些关键步骤：

### 2.1.创建线程

使用 `std::thread` 类创建线程时，你需要提供一个函数或函数对象以及该函数的参数。

```cpp
#include <thread>

void threadFunction() {
    // 线程要执行的代码
}

int main() {
    // 创建线程
    std::thread myThread(threadFunction);
    // ...
    return 0;
}
```

### 2.2.等待线程完成

使用 `join` 方法等待线程完成其执行。这将阻塞主线程直到 `myThread` 执行结束。

```cpp
myThread.join();
```

### 2.3.检查线程状态

使用 `joinable` 方法检查线程是否可以被 `join`。

```cpp
if (myThread.joinable()) {
    myThread.join();
}
```

### 2.4.线程分离

使用 `detach` 方法可以让线程在后台运行，而不会阻塞主线程。

```cpp
myThread.detach();
```

分离线程后，主线程可以继续执行，而不需要等待分离的线程完成。但是，分离的线程必须在主线程结束之前完成执行，否则程序可能会在尝试退出时崩溃。

### 2.5.传递参数给线程

可以通过构造函数向线程传递参数。

```cpp
void threadFunctionWithArgs(int x, double y) {
    // 使用参数 x 和 y
}

int main() {
    int myInt = 5;
    double myDouble = 3.14;
    std::thread myThread(threadFunctionWithArgs, myInt, myDouble);
    myThread.join();
    return 0;
}
```

### 2.6.异常处理

线程执行的函数可能会抛出异常，应该在适当的位置处理这些异常。

```cpp
void threadFunction() {
    throw std::runtime_error("Error in thread");
}

int main() {
    try {
        std::thread myThread(threadFunction);
        myThread.join();
    } catch (const std::exception& e) {
        std::cerr << "Exception in thread: " << e.what() << std::endl;
    }
    return 0;
}
```

### 2.7.线程生命周期管理

确保在线程生命周期结束前调用 `join` 或 `detach`，以避免资源泄露。

```cpp
int main() {
    std::thread myThread;
    
    // 线程开始执行
    myThread = std::thread(threadFunction);
    
    // 线程结束前调用 join 或 detach
    if (myThread.joinable()) {
        myThread.join();
    }
    
    return 0;
}
```

### 2.8.使用 `std::thread` 的注意事项

- 不要对同一个线程调用 `join` 或 `detach` 多次。
- 确保在线程结束前不要释放或修改传递给线程的参数。
- 避免在线程中使用非线程安全的全局变量。

正确管理线程的生命周期对于编写稳定、高效的多线程程序至关重要。

## 3. `std:async` 和 `~std:thread` 在性能上有什么差异？

在 C++ 中，`std::async` 和 `std::thread` 都是用于创建并行任务的工具，但它们在性能和使用场景上有一些差异。

### 3.1.`std::async` 的特点

- `std::async` 创建的是一个异步任务，它可能会在线程池中的一个线程上执行，也可能在调用 `get()` 或 `wait()` 时才执行，这取决于启动策略。
- 返回一个 `std::future` 对象，可以用来获取异步任务的结果。
- 可以指定执行策略，例如 `std::launch::async` 强制创建新线程，`std::launch::deferred` 则延迟执行直到调用 `get()`。

### 3.2.`std::thread` 的特点

- `std::thread` 总是创建一个新的线程。
- 不返回执行结果，需要通过其他方式获取，比如共享变量。
- 提供了更多的控制，包括直接的线程句柄。

### 3.3.性能差异

- **资源管理**：`std::async` 可能使用线程池，这有助于减少线程创建和销毁的开销，但也可能因为线程池的负载均衡而引入额外的延迟。
- **创建开销**：`std::thread` 创建线程的开销可能比 `std::async` 大，因为 `std::async` 可能复用现有线程。
- **执行策略**：使用 `std::launch::deferred` 时，`std::async` 可能不会立即执行任务，这在某些情况下可以减少不必要的线程创建，从而提高性能。
- **异常处理**：`std::async` 会捕获异步任务中的异常并存储在 `std::future` 中，这可能会影响性能，尤其是在异常频繁抛出的情况下。

### 3.4.使用场景

- **使用 `std::async`**：当你需要异步执行一个任务并且可能想要获取其结果时。它适合于 I/O 密集型或者可以明显分离开的计算任务。
- **使用 `std::thread`**：当你需要更细粒度的控制线程，或者需要确保任务在单独的线程上执行时。它适合于需要直接与线程交互的场景。

总的来说，选择 `std::async` 还是 `std::thread` 取决于你的具体需求，包括是否需要返回值、是否关心线程的生命周期管理、以及对性能的特定要求。

## 4.使用POSIX线程（pthread）和Windows线程（CreateThread"）在跨平台开发中有哪些考虑因素?

在跨平台开发中，选择使用 POSIX 线程（pthread）和 Windows 线程（CreateThread）时，有几个重要的考虑因素：

1. **兼容性**：
   - POSIX 线程（pthread）是基于 POSIX 标准实现的，它在类 Unix 系统（如 Linux 和 macOS）中是原生支持的。但在 Windows 中，需要使用 pthread 的 Windows 兼容版本，例如 pthreads-win32 库。
   - Windows 线程（CreateThread）是 Windows API 的一部分，专为 Windows 设计。在非 Windows 平台，需要使用特定的兼容层或模拟器，例如 Cygwin 或 MinGW。

2. **性能**：
   - 在 Windows 上，CreateThread 可能提供更好的性能，因为它是直接针对 Windows 内核优化的。
   - POSIX 线程可能在非 Windows 平台上有更好的性能，因为它们是这些系统的原生线程实现。

3. **可移植性**：
   - 使用 pthread 可以提高代码的可移植性，因为它们在多个 Unix-like 系统上都有支持。
   - 如果你的应用程序主要面向 Windows，使用 CreateThread 可能更合适，因为它简化了 Windows 特定的功能和优化。

4. **线程管理**：
   - pthread 提供了丰富的线程管理功能，如线程创建、同步、取消等。
   - CreateThread 提供了 Windows 平台特有的线程管理功能，包括线程优先级和亲和力设置。

5. **异常处理**：
   - 在 C++ 中，pthread 允许你在线程函数中使用 try/catch 块来处理异常。
   - Windows 线程可能需要额外的工作来处理异常。

6. **资源管理**：
   - pthread 通常需要手动管理线程资源，如显式地 join 或 detach 线程。
   - CreateThread 在 Windows 上创建的线程可能更容易管理，因为 Windows 提供了丰富的线程控制机制。

7. **第三方库**：
   - 对于跨平台开发，可以考虑使用第三方库，如 Boost.Thread，它提供了一个跨平台的线程管理接口。

8. **开发环境**：
   - 如果你的开发环境主要在 Windows 上，可能会更倾向于使用 CreateThread。
   - 如果你的开发环境需要在多个平台上工作，pthread 可能是更好的选择。

9. **社区和支持**：
   - pthread 有一个广泛的社区和大量的文档，特别是在开源社区中。
   - Windows 线程有 Microsoft 的官方文档和支持。

在决定使用哪种线程模型时，需要考虑你的应用程序的具体需求、目标平台、开发资源和长期维护计划。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
