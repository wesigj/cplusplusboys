# C++11 05-智能指针 Smart pointer

- [C++11 05-智能指针 Smart pointer](#c11-05-智能指针-smart-pointer)
  - [Overview](#overview)
  - [1.智能指针 Smart pointer](#1智能指针-smart-pointer)
    - [1.1. `std::unique_ptr`](#11-stdunique_ptr)
    - [1.2. `std::shared_ptr`](#12-stdshared_ptr)
    - [1.3. `std::weak_ptr`](#13-stdweak_ptr)
    - [1.4. 注意事项](#14-注意事项)
  - [2.C++11 中的智能指针在多线程环境中如何安全使用？](#2c11-中的智能指针在多线程环境中如何安全使用)
  - [3.如何使用智能指针来管理动态分配的数组？](#3如何使用智能指针来管理动态分配的数组)
    - [3.1.使用 `std::unique_ptr` 管理动态数组](#31使用-stdunique_ptr-管理动态数组)
    - [3.2.使用 `std::shared_ptr` 管理动态数组](#32使用-stdshared_ptr-管理动态数组)
    - [3.3.注意事项](#33注意事项)
  - [4.如何使用智能指针来管理动态分配的字符串数组？](#4如何使用智能指针来管理动态分配的字符串数组)
  - [5.在多线程环境下，智能指针有哪些常见的使用场景和注意事项？](#5在多线程环境下智能指针有哪些常见的使用场景和注意事项)
    - [5.1.使用 `std::shared_ptr`](#51使用-stdshared_ptr)
    - [5.2.使用 `std::unique_ptr`](#52使用-stdunique_ptr)
    - [5.3.注意事项](#53注意事项)
  - [6.使用智能指针管理动态数组时，如果我想在数组中添加元素，智能指针会自动管理内存分配吗？](#6使用智能指针管理动态数组时如果我想在数组中添加元素智能指针会自动管理内存分配吗)
    - [6.1. 手动重新分配内存](#61-手动重新分配内存)
    - [6.2. 使用标准库容器](#62-使用标准库容器)
    - [注意事项](#注意事项)
  - [7.如果我想在智能指针管理的动态数组中删除元素，应该如何操作？](#7如果我想在智能指针管理的动态数组中删除元素应该如何操作)
    - [7.1.使用 `std::unique_ptr` 动态数组删除元素](#71使用-stdunique_ptr-动态数组删除元素)
    - [7.2.使用 `std::shared_ptr` 动态数组删除元素](#72使用-stdshared_ptr-动态数组删除元素)
    - [7.3.使用标准库容器](#73使用标准库容器)
    - [7.4.注意事项](#74注意事项)
  - [关于作者](#关于作者)

## Overview

---

## 1.智能指针 Smart pointer

C++11 引入了几种智能指针，以自动管理动态分配的内存，从而防止内存泄漏和其他与动态内存分配相关的问题。以下是 C++11 中三种主要的智能指针：

### 1.1. `std::unique_ptr`

`std::unique_ptr` 表示对一个对象的独占所有权。一个 `std::unique_ptr` 不能被复制，只能被移动，这确保了其唯一性。当 `std::unique_ptr` 被销毁时，它所拥有的对象也会被自动删除。

**使用场景**：

- 适用于拥有唯一所有权的情况。
- 不需要共享指针。

**示例**：

```cpp
#include <memory>
#include <iostream>

void function() {
    std::unique_ptr<int> ptr(new int(10));
    std::cout << *ptr << std::endl;
    // ptr不能被复制，只能被移动
    // std::unique_ptr<int> anotherPtr = *ptr; // 错误
}

int main() {
    function();
    return 0;
}
```

### 1.2. `std::shared_ptr`

`std::shared_ptr` 表示对一个对象的共享所有权。它使用引用计数机制来管理对象的生命周期。当最后一个 `std::shared_ptr` 被销毁时，对象会被自动删除。

**使用场景**：

- 适用于共享对象所有权的情况。
- 需要在多个指针之间共享对象。

**示例**：

```cpp
#include <memory>
#include <iostream>

void function() {
    std::shared_ptr<int> ptr1(new int(10));
    {
        std::shared_ptr<int> ptr2 = ptr1;
        std::cout << *ptr1 << std::endl; // 输出 10
        std::cout << *ptr2 << std::endl; // 输出 10
    }
    // ptr2 离开作用域，但对象不会被删除，因为 ptr1 仍然持有引用
}

int main() {
    function();
    return 0;
}
```

### 1.3. `std::weak_ptr`

`std::weak_ptr` 是对 `std::shared_ptr` 的一种非拥有（弱）引用。它不增加引用计数，并且可以用来解决强引用循环的问题。

**使用场景**：

- 用于解决 `std::shared_ptr` 可能导致的循环引用问题。

**示例**：

```cpp
#include <memory>
#include <iostream>

void function() {
    std::shared_ptr<int> ptr1(new int(10));
    std::weak_ptr<int> weakPtr = ptr1;

    if (!weakPtr.expired()) {
        std::shared_ptr<int> ptr2 = weakPtr.lock();
        std::cout << *ptr2 << std::endl; // 输出 10
    }
}

int main() {
    function();
    return 0;
}
```

### 1.4. 注意事项

- 智能指针不应该被用来管理由栈或静态分配的对象。
- 避免在智能指针和原始指针之间进行转换。
- 确保不要同时使用智能指针和原始指针来管理同一个对象，这可能导致内存泄漏或双重删除。
- 智能指针也有开销，如内存占用和引用计数的维护，因此不应该过度使用。

智能指针在现代 C++ 编程中非常重要，它们提供了一种安全的方式来管理动态内存，有助于减少内存泄漏和其他资源管理错误。

## 2.C++11 中的智能指针在多线程环境中如何安全使用？

在多线程环境中，智能指针的使用需要特别注意，因为它们管理的对象生命周期可能会跨越多个线程的执行。以下是一些关于如何在多线程环境中安全使用 C++11 智能指针的指南：

1. **std::shared_ptr**：
   - `std::shared_ptr` 使用引用计数来管理对象的生命周期。在多线程环境中，`std::shared_ptr` 的复制和销毁是线程安全的，因为引用计数的增加和减少是原子操作 。
   - 但是，如果多个线程需要同时写入同一个 `std::shared_ptr` 指向的对象，那么必须使用互斥锁来同步这些线程，以避免数据竞争 。

2. **std::unique_ptr**：
   - `std::unique_ptr` 不能被复制，只能被移动，这意味着它的所有权可以在线程之间转移，但不会有两个 `std::unique_ptr` 同时拥有同一个对象。
   - 在多线程环境中，如果你需要在线程间传递 `std::unique_ptr`，可以使用 `std::move` 来转移所有权 。

3. **std::weak_ptr**：
   - `std::weak_ptr` 是对 `std::shared_ptr` 的一种非拥有（弱）引用，它不增加引用计数。在多线程环境中，它可以安全地用于观察 `std::shared_ptr` 而不会延长对象的生命周期。

4. **使用锁**：
   - 当智能指针与互斥锁（如 `std::mutex`）结合使用时，可以保护共享资源不被多个线程同时访问 。

5. **避免循环引用**：
   - 在多线程环境中，要特别注意避免 `std::shared_ptr` 导致的循环引用问题，因为这可能导致内存泄漏。

6. **线程局部存储**：
   - 如果每个线程都需要有自己的独立对象副本，可以使用 `thread_local` 关键字声明线程局部存储的智能指针 。

7. **资源管理**：
   - 在多线程环境中，智能指针应该用来管理线程间共享的资源，如动态分配的内存、文件句柄、网络连接等。

8. **异常安全**：
   - 在多线程环境中，智能指针的异常安全尤为重要。确保在抛出异常时，智能指针能够正确释放资源。

9. **避免条件竞争**：
   - 当使用条件变量（如 `std::condition_variable`）与智能指针结合时，确保在条件变量等待期间，智能指针仍然有效。

通过以上措施，可以确保在多线程环境中智能指针的安全使用，从而避免资源泄漏、数据竞争和其他并发问题。

## 3.如何使用智能指针来管理动态分配的数组？

在 C++ 中，管理动态分配的数组需要特别小心，因为数组的内存分配和释放需要使用 `new[]` 和 `delete[]`。标准智能指针如 `std::unique_ptr` 和 `std::shared_ptr` 默认不支持数组的删除操作。因此，C++11 引入了针对数组的特化版本，允许智能指针安全地管理动态数组。

### 3.1.使用 `std::unique_ptr` 管理动态数组

`std::unique_ptr` 对于数组提供了一个特化版本，允许你使用 `std::unique_ptr` 来管理动态数组。这是首选的方式，因为它提供了独占所有权，意味着在同一时间只能有一个智能指针指向数组。

**示例**：

```cpp
#include <memory>
#include <iostream>

int main() {
    // 创建一个动态数组
    std::unique_ptr<int[]> up(new int[10]);

    // 初始化数组
    for (int i = 0; i < 10; ++i) {
        up[i] = i;
    }

    // 使用数组
    for (int i = 0; i < 10; ++i) {
        std::cout << up[i] << " ";
    }
    std::cout << std::endl;

    // 智能指针会自动调用 delete[] 来释放数组
    return 0;
}
```

在这个例子中，`std::unique_ptr<int[]>` 被用来管理一个动态分配的整数数组。注意数组的类型是 `int[]`，不是 `int*`。

### 3.2.使用 `std::shared_ptr` 管理动态数组

`std::shared_ptr` 也提供了对数组的支持。使用 `std::shared_ptr` 管理数组时，它会自动处理引用计数，并在最后一个 `std::shared_ptr` 被销毁时释放数组。

**示例**：

```cpp
#include <memory>
#include <iostream>

int main() {
    // 创建一个动态数组
    std::shared_ptr<int[]> sp(new int[10]);

    // 初始化数组
    for (int i = 0; i < 10; ++i) {
        sp[i] = i;
    }

    // 使用数组
    for (int i = 0; i < 10; ++i) {
        std::cout << sp[i] << " ";
    }
    std::cout << std::endl;

    // 引用计数结束后自动调用 delete[]
    return 0;
}
```

### 3.3.注意事项

1. **不要直接使用 `new[]` 和 `delete[]`**：当你使用智能指针管理数组时，应该避免直接使用 `new[]` 和 `delete[]`，因为智能指针需要正确地处理数组的生命周期。

2. **使用 `std::make_unique` 和 `std::make_shared`**：为了提高代码的安全性和可读性，推荐使用 `std::make_unique` 和 `std::make_shared` 来创建智能指针。

3. **避免裸指针**：尽量不要将裸指针转换为智能指针，因为这会违反智能指针的所有权规则。

通过使用这些智能指针，你可以确保动态数组在不需要时被正确释放，从而避免内存泄漏。

## 4.如何使用智能指针来管理动态分配的字符串数组？

在 C++11 中，智能指针提供了一种自动管理动态内存分配和释放的机制，其中 `std::unique_ptr` 和 `std::shared_ptr` 是最常用的两种智能指针。

当你需要管理动态分配的字符串数组时，可以使用 `std::unique_ptr` 来确保数组在不再需要时被正确释放。`std::unique_ptr` 对于数组有一个特化版本，它使用 `delete[]` 来释放数组。

以下是如何使用 `std::unique_ptr` 来管理动态分配的字符串数组的示例：

```cpp
#include <memory>
#include <string>

int main() {
    // 创建一个动态分配的字符串数组
    std::unique_ptr<std::string[]> strings(new std::string[5]);

    // 初始化数组
    for (int i = 0; i < 5; ++i) {
        strings[i] = "String " + std::to_string(i);
    }

    // 使用数组
    for (int i = 0; i < 5; ++i) {
        std::cout << strings[i] << std::endl;
    }

    // 智能指针会自动调用 delete[] 来释放数组
    return 0;
}
```

在这个例子中，`std::unique_ptr<std::string[]>` 被用来管理一个动态分配的字符串数组。当 `std::unique_ptr` 被销毁时，它会自动调用 `delete[]` 来释放数组。

如果你在多线程环境中使用智能指针，需要确保线程安全。由于 `std::unique_ptr` 不能被复制，它自然适用于避免多线程中的竞态条件。如果你需要在多个线程之间共享资源，可以使用 `std::shared_ptr`，它内部使用引用计数来确保线程安全。

在多线程环境中，智能指针通常用于管理线程局部对象或者作为线程间传递数据的机制。例如，你可以创建一个线程安全的智能指针包装器，或者使用线程安全的容器来存储智能指针。

总之，智能指针是 C++11 提供的一种强大的工具，可以帮助你管理动态分配的资源，并且在多线程环境中确保线程安全。

## 5.在多线程环境下，智能指针有哪些常见的使用场景和注意事项？

在多线程环境中，智能指针的使用需要特别注意，因为它们管理的对象生命周期可能会跨越多个线程的执行。以下是一些关于如何在多线程环境中安全使用 C++11 智能指针的指南：

### 5.1.使用 `std::shared_ptr`

1. **线程安全**：`std::shared_ptr` 的引用计数操作是线程安全的，这意味着你可以在多个线程中安全地共享 `std::shared_ptr` 实例，而不必担心引用计数的一致性问题 。

2. **避免循环引用**：`std::shared_ptr` 可能会导致循环引用问题，使用 `std::weak_ptr` 可以解决这个问题，因为 `std::weak_ptr` 不会增加引用计数 。

3. **读写共享资源**：当多个线程需要读写同一个 `std::shared_ptr` 指向的对象时，需要使用互斥锁来保护这部分共享资源，以避免数据竞争 。

### 5.2.使用 `std::unique_ptr`

1. **独占所有权**：`std::unique_ptr` 表示对资源的独占所有权，因此它不能被复制，只能被移动。这使得它在多线程环境中使用时更加安全，因为它不会有两个线程同时拥有同一个 `std::unique_ptr` 实例的所有权 。

2. **线程间传递**：如果你需要在线程间传递 `std::unique_ptr`，可以使用 `std::move` 来转移所有权。

### 5.3.注意事项

1. **线程局部存储**：如果每个线程都需要有自己的独立对象副本，可以使用 `thread_local` 关键字声明线程局部存储的智能指针 。

2. **资源管理**：在多线程环境中，智能指针应该用来管理线程间共享的资源，如动态分配的内存、文件句柄、网络连接等。

3. **异常安全**：在多线程环境中，智能指针的异常安全尤为重要。确保在抛出异常时，智能指针能够正确释放资源。

4. **避免条件竞争**：当使用条件变量（如 `std::condition_variable`）与智能指针结合时，确保在条件变量等待期间，智能指针仍然有效。

通过使用这些智能指针，你可以确保在多线程环境中安全地管理资源，从而避免资源泄漏、数据竞争和其他并发问题。

## 6.使用智能指针管理动态数组时，如果我想在数组中添加元素，智能指针会自动管理内存分配吗？

当你使用智能指针管理动态数组时，智能指针本身（如 `std::unique_ptr` 和 `std::shared_ptr` 的数组特化版本）并不提供数组的动态扩容功能。这些智能指针在创建时分配了固定大小的内存，并且不会自动重新分配内存以添加更多元素。

如果你需要在数组中添加元素，并且数组的大小是动态变化的，你将需要手动处理内存重新分配和对象复制。以下是一些处理方法：

### 6.1. 手动重新分配内存

你可以创建一个新的更大的数组，将旧数组的元素复制到新数组中，然后替换旧的智能指针。

**示例**：

```cpp
#include <memory>
#include <iostream>

template <typename T>
std::unique_ptr<T[]> resize(std::unique_ptr<T[]>& array, size_t new_size) {
    auto new_array = std::make_unique<T[]>(new_size);
    std::copy(array.get(), array.get() + array.size(), new_array.get());
    array = std::move(new_array);
    return array;
}

int main() {
    auto arr = std::make_unique<int[]>(5);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    arr[4] = 5;

    auto new_arr = resize(arr, 10);
    new_arr[5] = 6;
    new_arr[6] = 7;
    new_arr[7] = 8;
    new_arr[8] = 9;

    for (int i = 0; i < 10; ++i) {
        std::cout << new_arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 6.2. 使用标准库容器

如果你需要一个能够动态增长和收缩的数组，使用标准库容器（如 `std::vector`）可能是更好的选择。`std::vector` 会自动管理内存，并在需要时动态调整大小。

**示例**：

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    vec.push_back(6);
    vec.push_back(7);
    vec.push_back(8);
    vec.push_back(9);

    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 注意事项

- **内存管理**：手动管理动态数组的内存需要谨慎，以避免内存泄漏、野指针和其他错误。
- **性能考虑**：每次重新分配内存和复制元素都可能涉及性能开销，特别是对于大型数组。
- **异常安全**：在执行操作时，确保代码的异常安全性，例如使用 `std::copy` 时，确保在抛出异常时不会泄漏内存。

总的来说，如果你需要一个固定大小的数组，可以使用智能指针；如果你需要一个动态大小的数组，使用 `std::vector` 或其他标准库容器可能更方便、更安全。

## 7.如果我想在智能指针管理的动态数组中删除元素，应该如何操作？

在 C++ 中，使用智能指针管理的动态数组删除元素需要手动操作，因为智能指针本身并不提供数组元素的动态管理功能。以下是一种方法，展示了如何在 `std::unique_ptr` 管理的动态数组中删除特定索引的元素：

### 7.1.使用 `std::unique_ptr` 动态数组删除元素

1. **移动元素**：将待删除元素后面的所有元素向前移动一个位置。
2. **更新大小**：调整数组的大小。

这里有一个示例：

```cpp
#include <iostream>
#include <algorithm> // for std::copy

int main() {
    // 创建一个动态数组
    std::unique_ptr<int[]> arr(new int[5]{1, 2, 3, 4, 5});

    // 要删除的元素索引
    size_t index_to_remove = 2;

    // 删除元素
    // 将待删除元素后面的元素向前移动
    std::copy(arr.get() + index_to_remove + 1, arr.get() + 5, arr.get() + index_to_remove);

    // 更新数组大小
    arr.reset(new int[4]{1, 2, 3, 4}); // 重新分配一个更小的数组

    // 输出结果
    for (size_t i = 0; i < 4; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 7.2.使用 `std::shared_ptr` 动态数组删除元素

处理方式类似，只不过 `std::shared_ptr` 需要额外注意引用计数的管理：

```cpp
#include <iostream>
#include <algorithm> // for std::copy

int main() {
    // 创建一个动态数组
    std::shared_ptr<int[]> arr(new int[5]{1, 2, 3, 4, 5});

    // 要删除的元素索引
    size_t index_to_remove = 2;

    // 删除元素
    // 将待删除元素后面的元素向前移动
    std::copy(arr.get() + index_to_remove + 1, arr.get() + 5, arr.get() + index_to_remove);

    // 更新数组大小
    arr.reset(new int[4]{1, 2, 3, 4}); // 重新分配一个更小的数组

    // 输出结果
    for (size_t i = 0; i < 4; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 7.3.使用标准库容器

如果你需要更灵活的数组管理，比如动态添加或删除元素，使用标准库容器 `std::vector` 可能是更好的选择，因为 `std::vector` 提供了这些功能：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个 vector
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 删除索引为 2 的元素
    vec.erase(vec.begin() + 2);

    // 输出结果
    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 7.4.注意事项

1. **性能考虑**：删除数组元素需要移动内存，这可能导致性能开销。
2. **异常安全**：在执行删除操作时，确保代码的异常安全性，避免内存泄漏。
3. **智能指针和数组**：智能指针并不提供动态数组管理功能，需要手动管理数组元素。

通过这些方法，你可以在智能指针管理的动态数组中删除元素，但使用标准库容器通常更方便、更安全。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
