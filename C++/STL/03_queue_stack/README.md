# C++ STL源码剖析 3-std::queue std::stack

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.std::queue std::stack

在C++标准模板库（STL）中，`std::queue`和`std::stack`是两种容器适配器，它们提供了对队列和栈这两种数据结构的支持。这些适配器并不直接存储数据，而是使用其他容器（如`std::deque`或`std::list`）来存储数据，并提供相应的数据结构操作。

### 1.1.`std::queue`

`std::queue`是一个先进先出（FIFO）的数据结构。它的头部是最早插入的元素，尾部是最后插入的元素。

**常用操作**：

- `push()`：在队列尾部插入一个元素。
- `pop()`：移除队列头部的元素。
- `front()`：访问队列头部的元素。
- `back()`：访问队列尾部的元素。
- `empty()`：检查队列是否为空。
- `size()`：返回队列中元素的数量。

**默认底层容器**：`std::deque`，但你也可以使用`std::list`来作为底层容器，这通常用于优化空间使用，因为`std::list`在尾部插入和删除的效率更高。

### 1.2.`std::stack`

`std::stack`是一个后进先出（LIFO）的数据结构。最新添加的元素可以通过`top()`访问，并通过`pop()`移除。

**常用操作**：

- `push()`：在栈顶添加一个元素。
- `pop()`：移除栈顶的元素。
- `top()`：访问栈顶的元素。
- `empty()`：检查栈是否为空。
- `size()`：返回栈中元素的数量。

**默认底层容器**：`std::deque`，但同样可以使用`std::list`或`std::vector`作为底层容器。使用`std::vector`作为底层容器时，`push()`和`pop()`操作可能会较慢，因为它们可能涉及到大量的元素移动。

### 1.3.示例代码

以下是使用`std::queue`和`std::stack`的简单示例：

```cpp
#include <iostream>
#include <queue>
#include <stack>

int main() {
    // 使用 std::queue
    std::queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    std::cout << "Queue: ";
    while (!q.empty()) {
        std::cout << q.front() << " ";  // 1 2 3
        q.pop();
    }
    std::cout << std::endl;

    // 使用 std::stack
    std::stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    std::cout << "Stack: ";
    while (!s.empty()) {
        std::cout << s.top() << " ";  // 3 2 1
        s.pop();
    }
    std::cout << std::endl;

    return 0;
}
```

### 1.4.输出结果

```shell
Queue: 1 2 3 
Stack: 3 2 1 
```

### 1.5.注意事项

- `std::queue`和`std::stack`只提供有限的接口，这意味着它们不支持迭代器、不能随机访问元素等。
- 在使用这些适配器时，应考虑底层容器的选择对性能的影响。
- 这些适配器是异常安全的，但使用它们时仍需注意异常安全编程实践。

通过使用`std::queue`和`std::stack`，你可以方便地实现队列和栈这两种基本数据结构，而无需手动管理底层数据存储。

## 2.std:stack在多线程环境下的安全性如何，有没有可能发生栈溢出？

`std::stack` 是 C++ 标准模板库中的一个容器适配器，它提供了后进先出（LIFO）的数据结构功能。然而，`std::stack` 本身并不是线程安全的。在多线程环境中，如果没有适当的同步机制，多个线程同时对同一个 `std::stack` 实例进行操作可能会导致数据竞争和不一致的状态。

### 2.1.线程安全

为了在多线程环境中安全地使用 `std::stack`，你需要添加额外的同步机制，例如互斥锁（`std::mutex`）和条件变量（`std::condition_variable`）。每次访问堆栈时，都需要锁定互斥体，以确保一次只有一个线程可以修改堆栈。

### 2.2.栈溢出

栈溢出通常发生在程序的递归调用过深或分配了过大的局部变量时，导致栈空间耗尽。在 `std::stack` 的情况下，栈溢出可能发生在以下情况：

1. **递归调用**：如果 `std::stack` 被用作递归算法的一部分，而递归深度过大，可能会导致栈溢出。
2. **大量局部变量**：如果在 `std::stack` 相关的函数中分配了大量的局部变量，可能会占用过多栈空间。

为了防止栈溢出，可以采取以下措施：

1. **限制递归深度**：确保递归有明确的退出条件，并且深度不会过大。
2. **使用堆代替栈**：对于大的数据结构，使用动态内存分配（如 `new` 和 `delete`）在堆上分配，而不是在栈上。
3. **增加栈空间**：在某些情况下，可以通过增加程序的栈大小来避免栈溢出，但这通常不是最佳解决方案。

### 2.3.示例代码

下面是一个简单的线程安全 `std::stack` 的实现示例：

```cpp
#include <stack>
#include <mutex>
#include <condition_variable>

template<typename T>
class ThreadSafeStack {
private:
    std::stack<T> stack;
    mutable std::mutex mutex;
    std::condition_variable cond_var;

public:
    void push(const T& value) {
        std::lock_guard<std::mutex> lock(mutex);
        stack.push(value);
    }

    void pop() {
        std::lock_guard<std::mutex> lock(mutex);
        if (!stack.empty()) {
            stack.pop();
        }
    }

    T top() {
        std::lock_guard<std::mutex> lock(mutex);
        if (!stack.empty()) {
            return stack.top();
        }
        throw std::runtime_error("Stack is empty");
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mutex);
        return stack.empty();
    }
};
```

在这个示例中，我们使用 `std::mutex` 来保护 `std::stack` 的操作，确保每次只有一个线程可以修改堆栈。这样可以避免在多线程环境中发生数据竞争。

总的来说，`std::stack` 是一个有用的数据结构，但在多线程环境中使用时需要额外的同步机制来保证线程安全，并需要注意栈溢出的问题。

## 3.如何使用 std::queue 来实现一个生产者-消费者问题？

生产者-消费者问题是多线程编程中的经典问题，涉及到多个线程（生产者线程和消费者线程）对共享资源的访问。生产者负责生成数据放入共享缓冲区，而消费者则从共享缓冲区取出数据进行处理。为了避免竞态条件和数据不一致的问题，通常需要使用互斥锁（mutex）和条件变量（condition variable）来同步线程。

在C++中，可以使用`std::queue`作为共享缓冲区，结合`std::mutex`和`std::condition_variable`来实现生产者-消费者问题。以下是一个简单的示例：

```cpp
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

std::queue<int> q;         // 共享队列
std::mutex mtx;            // 互斥锁
std::condition_variable cv; // 条件变量

// 生产者函数
void producer(int id) {
    for (int i = 0; i < 5; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        std::cout << "Producer " << id << " produced " << i << std::endl;
        q.push(i);
        lock.unlock();
        cv.notify_one(); // 通知一个等待的消费者
    }
}

// 消费者函数
void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !q.empty(); }); // 等待直到队列非空
        int val = q.front();
        q.pop();
        std::cout << "Consumer " << id << " consumed " << val << std::endl;
        lock.unlock();
        // 如果消费了某个值后结束（例如-1），则退出循环
        if (val == -1) break;
    }
}

int main() {
    std::thread producers[2];
    std::thread consumers[2];

    // 创建生产者线程
    for (int i = 0; i < 2; ++i) {
        producers[i] = std::thread(producer, i);
    }

    // 创建消费者线程
    for (int i = 0; i < 2; ++i) {
        consumers[i] = std::thread(consumer, i);
    }

    // 等待生产者线程结束
    for (int i = 0; i < 2; ++i) {
        producers[i].join();
    }

    // 添加结束信号
    // 生产者线程结束后，向队列添加特殊值通知消费者线程结束
    {
        std::lock_guard<std::mutex> lock(mtx);
        q.push(-1);
        cv.notify_all();
    }

    // 等待消费者线程结束
    for (int i = 0; i < 2; ++i) {
        consumers[i].join();
    }

    return 0;
}
```

在这个示例中，我们创建了两个生产者线程和两个消费者线程。生产者线程生成数据放入共享队列，而消费者线程从共享队列中取出数据进行处理。使用`std::mutex`来保护共享资源（即`std::queue`），使用`std::condition_variable`来同步生产者和消费者线程。

注意，我们在队列中使用了一个特殊值（-1）作为结束信号，当生产者线程结束后，向队列中添加这个值，并通知所有等待的消费者线程。消费者线程在消费到这个特殊值时退出循环。

这个示例展示了如何使用`std::queue`、`std::mutex`和`std::condition_variable`来实现生产者-消费者问题的基本框架。在实际应用中，可能需要根据具体需求进行调整和优化。

## 4.如何优化生产者-消费者问题中的同步机制以提高效率？

在多线程环境中优化生产者-消费者问题的同步机制以提高效率，可以考虑以下几个方面：

1. **使用适当的同步工具**：使用互斥锁（`std::mutex`）来保护共享资源，确保一次只有一个线程可以访问共享资源。同时，使用条件变量（`std::condition_variable`）来同步线程，当资源状态发生变化时（如缓冲区有空间或有新的数据可用），通知等待的线程。

2. **减少锁的争用**：尽量减少锁的争用时间，例如，可以在持有锁的代码块之外进行数据的加工和处理，只在实际需要修改共享资源时才持有锁。

3. **锁分离**：对于生产者和消费者操作，使用不同的锁，这样可以在某些情况下同时允许生产者和消费者操作，增加并行度。

4. **批量操作**：如果可能，实现批量生产和消费，这样可以减少线程同步的开销。

5. **使用无锁编程技术**：在某些情况下，可以考虑使用无锁编程技术，如原子操作（`std::atomic`），来避免锁的使用，提高性能。

6. **避免虚假唤醒**：在使用条件变量时，要注意虚假唤醒的问题，始终在循环中检查条件是否满足。

7. **合理设置线程数量**：根据系统资源和负载情况合理设置生产者和消费者线程的数量，避免过多的线程切换开销。

8. **使用读写锁**：如果读操作远多于写操作，可以考虑使用读写锁（`std::shared_mutex`），允许多个线程同时读取，但写操作会独占锁。

9. **资源池**：对于频繁创建和销毁的对象，可以使用资源池来管理，减少动态分配和释放资源的开销。

10. **监控和调优**：使用性能分析工具监控程序的运行，找出瓶颈并进行调优。

通过上述方法，可以有效地优化生产者-消费者问题的同步机制，提高程序的执行效率。

## 5.在多生产者-消费者场景下，如何扩展这个模型来处理更多的线程？

在多生产者-消费者场景下，要扩展模型以处理更多的线程，可以采取以下策略：

1. **使用线程池**：通过线程池来管理生产者和消费者线程，可以避免创建和销毁线程的开销，提高资源利用率。线程池中的线程可以循环使用，当任务到达时，线程池会分配空闲线程去执行任务，如果线程池满了，则任务会排队等待。

2. **优化锁策略**：减少锁的争用，例如使用读写锁（`std::shared_mutex`），允许多个读者同时访问，但写者会独占锁。这样可以在保证线程安全的同时，提高并发度。

3. **使用无锁编程技术**：在某些情况下，可以考虑使用无锁编程技术，如原子操作（`std::atomic`），来避免锁的使用，提高性能。

4. **条件变量**：使用条件变量（`std::condition_variable`）来同步线程，当缓冲区有空间或有新的数据可用时，通知等待的线程。

5. **批量操作**：如果可能，实现批量生产和消费，减少同步的频率，提高效率。

6. **监控和调优**：使用性能分析工具监控程序的运行，找出瓶颈并进行调优。

7. **合理的负载分配**：根据生产者和消费者的处理能力，合理分配负载，避免某一方成为性能瓶颈。

8. **避免虚假唤醒**：在使用条件变量时，要注意虚假唤醒的问题，始终在循环中检查条件是否满足。

9. **资源池**：对于频繁创建和销毁的对象，可以使用资源池来管理，减少动态分配和释放资源的开销。

通过上述方法，可以有效地扩展生产者-消费者模型，以适应多线程环境，提高程序的执行效率和资源利用率。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
