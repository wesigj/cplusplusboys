# C++ Join 与 Detachs

- [C++ Join 与 Detachs](#c-join-与-detachs)
  - [Overview](#overview)
  - [1.Join 与 Detachs](#1join-与-detachs)
    - [1.1.`std::thread::join`](#11stdthreadjoin)
    - [1.2.`std::thread::detach`](#12stdthreaddetach)
    - [1.3.选择 `join` 还是 `detach`](#13选择-join-还是-detach)
  - [2.在多线程编程中，除了 join 和 detach，还有哪些其他的方法可以管理线程？](#2在多线程编程中除了-join-和-detach还有哪些其他的方法可以管理线程)
  - [3.如何确保在多线程环境下，线程安全地访问共享资源？](#3如何确保在多线程环境下线程安全地访问共享资源)
    - [3.1. **互斥锁（Mutex）**](#31-互斥锁mutex)
    - [3.2. **读写锁（Shared-Time Mutexes）**](#32-读写锁shared-time-mutexes)
    - [3.3. **原子操作（Atomic Operations）**](#33-原子操作atomic-operations)
    - [3.4. **条件变量（Condition Variables）**](#34-条件变量condition-variables)
    - [3.5. **线程局部存储（Thread-Local Storage）**](#35-线程局部存储thread-local-storage)
    - [3.6. **信号量（Semaphores）**](#36-信号量semaphores)
    - [3.7. **使用线程安全的数据结构**](#37-使用线程安全的数据结构)
    - [3.8. **避免共享**](#38-避免共享)
    - [3.9. **锁分段（Lock Striping）**](#39-锁分段lock-striping)
    - [3.10. **使用高级抽象**](#310-使用高级抽象)
    - [3.11. **避免死锁**](#311-避免死锁)
    - [3.12.示例：使用互斥锁保护共享资源](#312示例使用互斥锁保护共享资源)
  - [4.在C++中，如果我想在线程中执行一个长时间运行的任务，但又不想阻塞主线程，我应该怎么做？](#4在c中如果我想在线程中执行一个长时间运行的任务但又不想阻塞主线程我应该怎么做)
    - [4.1. 使用 `std::thread` 并分离线程（Detaching）](#41-使用-stdthread-并分离线程detaching)
    - [4.2. 使用 `std::thread` 并加入线程（Joining）](#42-使用-stdthread-并加入线程joining)
    - [4.3. 使用 `std::async` 并获取结果（Future）](#43-使用-stdasync-并获取结果future)
    - [4.4. 使用线程池](#44-使用线程池)
    - [4.5. 使用异步 I/O](#45-使用异步-io)
    - [4.6. 使用协程（C++20）](#46-使用协程c20)
  - [5.在 C++ 中，如何确保线程安全地访问共享资源？](#5在-c-中如何确保线程安全地访问共享资源)
    - [5.1. **互斥锁（Mutex）**](#51-互斥锁mutex)
    - [5.2. **读写锁（Shared-Time Mutexes）**](#52-读写锁shared-time-mutexes)
    - [5.3. **原子操作（Atomic Operations）**](#53-原子操作atomic-operations)
    - [5.4. **条件变量（Condition Variables）**](#54-条件变量condition-variables)
    - [5.5. **线程局部存储（Thread-Local Storage）**](#55-线程局部存储thread-local-storage)
    - [5.6. **信号量（Semaphores）**](#56-信号量semaphores)
    - [5.7. **使用线程安全的数据结构**](#57-使用线程安全的数据结构)
    - [5.8. **避免共享**](#58-避免共享)
    - [5.9. **锁分段（Lock Striping）**](#59-锁分段lock-striping)
    - [5.10. **使用高级抽象**](#510-使用高级抽象)
    - [5.11. **避免死锁**](#511-避免死锁)
  - [6.如果我想在线程中执行多个长时间运行的任务，我应该如何选择线程的数量？](#6如果我想在线程中执行多个长时间运行的任务我应该如何选择线程的数量)
    - [6.1. **处理器核心数**](#61-处理器核心数)
    - [6.2. **I/O 密集型 vs 计算密集型**](#62-io-密集型-vs-计算密集型)
    - [6.3. **任务的特性**](#63-任务的特性)
    - [6.4. **资源限制**](#64-资源限制)
    - [6.5. **使用线程池**](#65-使用线程池)
    - [6.6. **性能测试**](#66-性能测试)
    - [6.7. **动态调整**](#67-动态调整)
    - [6.8.示例代码：使用线程池](#68示例代码使用线程池)
  - [关于作者](#关于作者)

## Overview

---

## 1.Join 与 Detachs

在 C++ 的多线程编程中，`join` 和 `detach` 是 `std::thread` 类的两个成员函数，它们用于管理线程的生命周期和执行方式。

### 1.1.`std::thread::join`

- **作用**：等待线程结束执行。
- **行为**：当一个线程对象被 `join` 时，主线程（通常是创建线程的那个线程）会等待该线程执行完成后才能继续执行。如果线程已经结束，`join` 调用将立即返回。
- **使用场景**：当你需要确保线程执行完成并且需要清理线程资源时使用。
- **注意事项**：
  - 一个线程只能被 `join` 一次。如果尝试多次 `join` 同一个线程，将会抛出一个 `std::system_error` 异常。
  - 如果在线程结束之前没有调用 `join`，程序将无法正常退出，因为 `std::thread` 的析构函数会抛出异常。

**示例代码**：

```cpp
#include <iostream>
#include <thread>

void exampleFunction() {
    std::cout << "Thread is running." << std::endl;
}

int main() {
    std::thread t(exampleFunction);
    t.join();  // 等待线程t执行完成
    std::cout << "Thread has finished." << std::endl;
    return 0;
}
```

### 1.2.`std::thread::detach`

- **作用**：让线程在后台独立运行。
- **行为**：当一个线程对象被 `detach` 后，该线程将独立于主线程运行，主线程不需要等待它结束就可以继续执行。如果主线程结束，`detach` 后的线程将继续执行直到完成。
- **使用场景**：当你不需要等待线程结束或者需要线程在后台长时间运行时使用。
- **注意事项**：
  - 一旦线程被 `detach`，就不能再对它进行 `join` 或 `detach` 操作。
  - 必须确保 `detach` 的线程在程序结束前完成执行，否则程序退出时可能会导致未定义行为。

**示例代码**：

```cpp
#include <iostream>
#include <thread>

void exampleFunction() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Thread is running." << std::endl;
}

int main() {
    std::thread t(exampleFunction);
    t.detach();  // 让线程t在后台执行
    std::cout << "Thread is detached and main thread continues." << std::endl;
    // 主线程不会等待detached线程结束
    return 0;
}
```

### 1.3.选择 `join` 还是 `detach`

- **使用 `join`**：
  - 当你需要确保线程完成其任务并且需要处理线程执行后的资源清理时。
  - 当线程执行的任务对程序的后续步骤至关重要时。

- **使用 `detach`**：
  - 当线程执行的任务是后台任务，不需要立即等待结果时。
  - 当线程执行的任务是长时间运行的任务，并且你不希望主线程被阻塞时。

在实际应用中，选择 `join` 或 `detach` 应根据具体需求和程序设计来决定。

## 2.在多线程编程中，除了 join 和 detach，还有哪些其他的方法可以管理线程？

在 C++ 的多线程编程中，除了 `join` 和 `detach` 方法外，还有一些其他方法和工具可以用于管理线程：

1. **条件变量（`std::condition_variable`）**：
   用于在特定条件下同步线程。线程可以在满足特定条件之前挂起，并在条件满足时被唤醒。

2. **互斥锁（`std::mutex`）**：
   用于保护共享数据，确保一次只有一个线程可以访问临界资源。

3. **原子操作（`std::atomic`）**：
   提供了一种无锁的线程安全编程方式，用于执行简单的线程安全操作。

4. **线程局部存储（`thread_local`）**：
   用于创建线程独有的数据，每个线程访问自己的数据副本。

5. **线程池（`std::thread` 池）**：
   管理一组工作线程，允许提交任务给线程池处理，而不是每次都创建和销毁线程。

6. **异步任务（`std::async`）**：
   创建一个异步任务，可能会在线程池中的一个线程上执行，也可能在调用 `get()` 或 `wait()` 时才执行。

7. **信号量（`std::counting_semaphore` / `std::binary_semaphore`）**：
   用于控制对共享资源的访问数量，C++20 引入。

8. **屏障（`std::barrier`）**：
   用于同步多个线程，直到它们都到达某个点，C++20 引入。

9. **锁守护者（`std::lock_guard` 和 `std::unique_lock`）**：
   用于管理互斥锁的自动获取和释放。

10. **线程标识（`std::this_thread::get_id`）**：
    用于获取当前线程的唯一标识符。

11. **线程取消（`std::thread::native_handle`）**：
    用于获取线程的原生句柄，可以用于平台特定的线程操作，包括线程取消。

12. **线程属性（`std::thread::attr`）**：
    用于设置线程的属性，如堆栈大小。

13. **线程安全的数据结构**：
    使用线程安全的数据结构，如 `std::shared_mutex`，可以简化同步逻辑。

14. **线程的创建和销毁**：
    通过管理线程的生命周期，确保线程在不再需要时被正确销毁。

15. **使用第三方库**：
    如 Boost.Thread 提供了跨平台的线程管理功能。

16. **同步数据流**：
    使用线程安全的队列和管道来同步线程间的数据流。

17. **事件监听**：
    使用事件监听机制来同步线程，类似于条件变量。

18. **协程**：
    使用协程来管理线程任务的执行流程，可以在不使用线程的情况下实现协作式多任务。

这些工具和方法可以单独使用，也可以组合使用，以满足不同的多线程编程需求。

## 3.如何确保在多线程环境下，线程安全地访问共享资源？

在多线程环境下，确保线程安全地访问共享资源是至关重要的。以下是一些常用的策略和技术：

### 3.1. **互斥锁（Mutex）**

互斥锁是确保同一时间只有一个线程可以访问共享资源的常用方法。

```cpp
#include <mutex>
#include <vector>

std::mutex mtx;
int shared_data = 0;

void increment() {
    std::lock_guard<std::mutex> lock(mtx);
    ++shared_data;
}
```

### 3.2. **读写锁（Shared-Time Mutexes）**

读写锁允许多个读线程同时访问共享资源，但写线程会独占访问。

```cpp
#include <shared_mutex>
#include <vector>

std::shared_mutex rw_mutex;
int shared_data = 0;

void read_data() {
    std::shared_lock<std::shared_mutex> lock(rw_mutex);
    // 读取 shared_data
}

void write_data(int data) {
    std::unique_lock<std::shared_mutex> lock(rw_mutex);
    shared_data = data;
}
```

### 3.3. **原子操作（Atomic Operations）**

原子类型提供了一种无锁的线程安全编程方式，适用于简单的数据操作。

```cpp
#include <atomic>
#include <thread>

std::atomic<int> shared_data(0);

void increment() {
    shared_data.fetch_add(1, std::memory_order_relaxed);
}
```

### 3.4. **条件变量（Condition Variables）**

条件变量用于线程间的同步，允许一个线程在特定条件成立之前挂起等待。

```cpp
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready; });
    // 访问共享资源
}

void setter() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_all();
}
```

### 3.5. **线程局部存储（Thread-Local Storage）**

线程局部存储确保每个线程有自己的数据副本，避免了共享资源的冲突。

```cpp
#include <vector>
#include <thread>

thread_local int thread_data = 0;

void worker() {
    thread_data = 42;  // 每个线程都有自己的 thread_data
}
```

### 3.6. **信号量（Semaphores）**

信号量用于控制对共享资源的访问数量。

```cpp
#include <semaphore>
#include <thread>

std::counting_semaphore<> sem(1);

void worker() {
    sem.acquire();
    // 访问共享资源
    sem.release();
}
```

### 3.7. **使用线程安全的数据结构**

使用标准库或第三方库提供的线程安全数据结构。

### 3.8. **避免共享**

尽可能设计无共享的并发策略，每个线程处理自己的数据，不共享数据。

### 3.9. **锁分段（Lock Striping）**

将数据分割成多个段，并为每段使用单独的锁，减少锁的竞争。

### 3.10. **使用高级抽象**

使用高级并发工具和库，如线程池、并发容器等。

### 3.11. **避免死锁**

使用锁顺序、超时、检测等策略避免死锁。

### 3.12.示例：使用互斥锁保护共享资源

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int shared_data = 0;

void increment(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        ++shared_data;
    }
}

int main() {
    std::thread t1(increment, 1000000);
    std::thread t2(increment, 1000000);
    t1.join();
    t2.join();
    std::cout << "Shared data: " << shared_data << std::endl;
    return 0;
}
```

通过这些方法，可以有效地确保在多线程环境下安全地访问共享资源。

## 4.在C++中，如果我想在线程中执行一个长时间运行的任务，但又不想阻塞主线程，我应该怎么做？

在 C++ 中，如果你希望执行一个长时间运行的任务而不阻塞主线程，你可以使用以下几种方法：

### 4.1. 使用 `std::thread` 并分离线程（Detaching）

```cpp
#include <thread>

void longRunningTask() {
    // 执行长时间运行的任务
}

int main() {
    std::thread t(longRunningTask);
    t.detach(); // 分离线程，让它在后台运行
    // 主线程可以继续执行其他任务
    // ...
    return 0;
}
```

### 4.2. 使用 `std::thread` 并加入线程（Joining）

```cpp
#include <thread>

void longRunningTask() {
    // 执行长时间运行的任务
}

int main() {
    std::thread t(longRunningTask);
    // 主线程执行其他任务，但可以在需要的时候等待长时间任务
    // ...
    t.join(); // 等待线程完成
    return 0;
}
```

### 4.3. 使用 `std::async` 并获取结果（Future）

```cpp
#include <future>
#include <iostream>

int longRunningTask() {
    // 执行长时间运行的任务
    return 42; // 假设返回值
}

int main() {
    std::future<int> result = std::async(std::launch::async, longRunningTask);
    // 主线程可以继续执行其他任务
    // ...
    int value = result.get(); // 获取结果，如果任务尚未完成则阻塞
    std::cout << "Task result: " << value << std::endl;
    return 0;
}
```

### 4.4. 使用线程池

```cpp
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

int longRunningTask() {
    // 执行长时间运行的任务
    return 42; // 假设返回值
}

int main() {
    ThreadPool pool(4);
    auto result = pool.enqueue(longRunningTask);
    // 主线程可以继续执行其他任务
    // ...
    int value = result.get(); // 获取结果，如果任务尚未完成则阻塞
    return 0;
}
```

### 4.5. 使用异步 I/O

对于涉及 I/O 的长时间任务，可以使用异步 I/O 库（如 Boost.Asio）来避免阻塞。

### 4.6. 使用协程（C++20）

C++20 引入了协程，它允许你以同步的方式编写异步代码。

```cpp
#include <coroutine>
#include <thread>

generator<int> LongRunningTask() {
    // 执行长时间运行的任务
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        yield i;
    }
}

int main() {
    for (auto value : LongRunningTask()) {
        std::cout << "Value: " << value << std::endl;
    }
    return 0;
}
```

选择哪种方法取决于你的具体需求，例如任务的性质、是否需要获取任务结果、是否需要在任务执行过程中与主线程交互等。

## 5.在 C++ 中，如何确保线程安全地访问共享资源？

在 C++ 中，确保线程安全地访问共享资源是多线程编程中的关键问题。以下是一些常用的方法和技术：

### 5.1. **互斥锁（Mutex）**

互斥锁是防止多个线程同时访问共享资源的最基本方式。

```cpp
#include <mutex>
#include <vector>

std::mutex mtx;
int shared_data = 0;

void increment() {
    std::lock_guard<std::mutex> lock(mtx);
    ++shared_data;
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

### 5.2. **读写锁（Shared-Time Mutexes）**

读写锁允许多个读线程同时访问共享资源，但写线程会独占访问。

```cpp
#include <shared_mutex>
#include <vector>

std::shared_mutex rw_mutex;
int shared_data = 0;

void read_data() {
    std::shared_lock<std::shared_mutex> lock(rw_mutex);
    // 读取 shared_data
}

void write_data(int data) {
    std::unique_lock<std::shared_mutex> lock(rw_mutex);
    shared_data = data;
}

int main() {
    std::thread t1(read_data);
    std::thread t2(write_data, 42);
    t1.join();
    t2.join();
    std::cout << "Shared data: " << shared_data << std::endl;
    return 0;
}
```

### 5.3. **原子操作（Atomic Operations）**

原子类型提供了一种无锁的线程安全编程方式，适用于简单的数据操作。

```cpp
#include <atomic>
#include <thread>

std::atomic<int> shared_data(0);

void increment() {
    shared_data.fetch_add(1, std::memory_order_relaxed);
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

### 5.4. **条件变量（Condition Variables）**

条件变量用于线程间的同步，允许一个线程在特定条件成立之前挂起等待。

```cpp
#include <mutex>
#include <condition_variable>
#include <vector>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready; });
    // 访问共享资源
}

void setter() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_all();
}

int main() {
    std::thread t1(setter);
    std::thread t2(worker);
    t1.join();
    t2.join();
    return 0;
}
```

### 5.5. **线程局部存储（Thread-Local Storage）**

线程局部存储确保每个线程有自己的数据副本，避免了共享资源的冲突。

```cpp
#include <vector>
#include <thread>

thread_local int thread_data = 0;

void worker() {
    thread_data = 42;  // 每个线程都有自己的 thread_data
}

int main() {
    std::thread t1(worker);
    std::thread t2(worker);
    t1.join();
    t2.join();
    std::cout << "Thread 1 data: " << thread_data << std::endl;
    return 0;
}
```

### 5.6. **信号量（Semaphores）**

信号量用于控制对共享资源的访问数量。

```cpp
#include <semaphore>
#include <thread>

std::counting_semaphore<> sem(1);

void worker() {
    sem.acquire();
    // 访问共享资源
    sem.release();
}

int main() {
    std::thread t1(worker);
    std::thread t2(worker);
    t1.join();
    t2.join();
    return 0;
}
```

### 5.7. **使用线程安全的数据结构**

使用标准库或第三方库提供的线程安全数据结构。

### 5.8. **避免共享**

尽可能设计无共享的并发策略，每个线程处理自己的数据，不共享数据。

### 5.9. **锁分段（Lock Striping）**

将数据分割成多个段，并为每段使用单独的锁，减少锁的竞争。

### 5.10. **使用高级抽象**

使用高级并发工具和库，如线程池、并发容器等。

### 5.11. **避免死锁**

使用锁顺序、超时、检测等策略避免死锁。

通过这些方法，可以有效地确保在多线程环境下安全地访问共享资源。

## 6.如果我想在线程中执行多个长时间运行的任务，我应该如何选择线程的数量？

在多线程编程中，选择线程的数量是一个重要的决策，它会影响程序的性能和资源利用率。以下是一些指导原则和方法来确定执行多个长时间运行任务的线程数量：

### 6.1. **处理器核心数**

首先，考虑你的处理器的核心数。这是一个起点，因为线程不能真正并行地超过可用的核心数。

- **核心数**：创建与处理器核心数相等的线程是一个起点。这样可以确保每个核心都保持忙碌，而不会有太多的上下文切换。
- **超线程**：如果处理器支持超线程（如 Intel 的 Hyper-Threading），可以考虑创建比物理核心数稍多的线程，但要注意不要过多。

### 6.2. **I/O 密集型 vs 计算密集型**

- **I/O 密集型任务**：如果任务涉及大量的 I/O 操作（如网络请求、磁盘读写），则可以创建比核心数更多的线程，因为线程可以在等待 I/O 完成时被阻塞，而其他线程可以继续执行。
- **计算密集型任务**：如果任务是计算密集型的，最好将线程数限制在核心数以内，以避免过多的上下文切换和缓存争用。

### 6.3. **任务的特性**

- **任务的依赖性**：如果任务之间有依赖关系，可能需要根据依赖关系来安排线程的数量和执行顺序。
- **任务的持续时间**：如果任务的持续时间非常不同，可能需要动态调整线程的数量或使用线程池来更有效地管理资源。

### 6.4. **资源限制**

- **内存限制**：每个线程都会占用一定的内存（堆栈空间）。如果创建了太多线程，可能会导致内存不足。
- **系统限制**：操作系统可能对可以创建的线程数量有限制。

### 6.5. **使用线程池**

使用线程池是管理多个长时间运行任务的一种有效方式。线程池可以：

- **限制最大线程数**：避免创建过多的线程。
- **重用线程**：任务完成后，线程可以被重新用于执行新的任务，而不是被销毁。

### 6.6. **性能测试**

- **基准测试**：在不同的线程数量下进行性能测试，找到最佳的线程数量。
- **监控资源使用**：监控 CPU 使用率、内存使用情况和其他资源，以确保系统稳定运行。

### 6.7. **动态调整**

- **根据负载调整**：根据系统的实时负载动态调整线程数量。
- **反馈机制**：实现反馈机制来调整线程数量，例如，如果发现线程大部分时间都在等待，可以减少线程数量。

### 6.8.示例代码：使用线程池

```cpp
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <iostream>

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

void longRunningTask(int id) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Task " << id << " finished." << std::endl;
}

int main() {
    ThreadPool pool(std::thread::hardware_concurrency());
    for(int i = 0; i < 10; ++i) {
        auto result = pool.enqueue(longRunningTask, i);
    }
    std::cout << "All tasks scheduled." << std::endl;
    return 0;
}
```

在这个示例中，线程池的大小设置为硬件并发数（核心数），这样可以有效地利用多核处理器的能力，同时避免过多的线程竞争。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
