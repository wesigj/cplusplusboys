# C++ STL源码剖析 15-unordered_map

[TOC]

## Overview

---

## 1.unordered_map

在 C++ 标准模板库（STL）中，`std::unordered_map` 是一种基于哈希表实现的关联容器，它存储了键值对（key-value pairs），并且允许通过键快速访问对应的值。`std::unordered_map` 不保证元素的顺序，但其提供了平均时间复杂度为 O(1) 的插入、查找和删除操作。

以下是 `std::unordered_map` 的一些主要特性：

1. **键值对存储**：每个元素是一个键值对，键用于索引，值是存储的数据。
2. **无序性**：元素在容器内没有特定的顺序。
3. **唯一的键**：每个键在 `std::unordered_map` 中都是唯一的。
4. **高效的访问**：通过键访问值的操作非常快，因为内部使用哈希表。

### 1.1.如何使用 `std::unordered_map`

**基本用法**：

```cpp
#include <iostream>
#include <unordered_map>

int main() {
    // 创建一个 std::unordered_map 实例
    std::unordered_map<int, std::string> umap;

    // 插入元素
    umap.insert({1, "Kimi"});
    umap.insert({2, "Moonshot AI"});

    // 访问元素
    std::cout << umap[1] << std::endl; // 输出 "Kimi"

    // 检查键是否存在
    if (umap.find(2) != umap.end()) {
        std::cout << "Key 2 exists." << std::endl;
    }

    // 删除元素
    umap.erase(1);

    // 遍历 unordered_map
    for (const auto& pair : umap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}
```

**自定义哈希函数和键比较函数**：

```cpp
struct MyKey {
    int first;
    int second;
};

struct MyHash {
    std::size_t operator()(const MyKey& key) const {
        return std::hash<int>()(key.first) ^ std::hash<int>()(key.second);
    }
};

struct MyKeyEqual {
    bool operator()(const MyKey& lhs, const MyKey& rhs) const {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};

std::unordered_map<MyKey, std::string, MyHash, MyKeyEqual> custom_umap;
```

在这个例子中，我们定义了一个 `MyKey` 结构，它将用作 `std::unordered_map` 的键。我们还提供了自定义的哈希函数 `MyHash` 和键比较函数 `MyKeyEqual`。

**注意**：

- `std::unordered_map` 的迭代器在插入和删除操作后可能会失效。如果需要，在这些操作后更新迭代器。
- 考虑负载因子和哈希表的动态扩容行为，以优化性能。
- 在多线程环境中，`std::unordered_map` 本身不是线程安全的。需要额外的同步机制来保证线程安全。

`std::unordered_map` 是 C++ STL 中非常有用的容器之一，适用于需要快速访问元素的场景。

## 2.如何使用 std::unordered_map 进行高效的数据查找和插入？

`std::unordered_map` 是 C++ 标准库中的一个关联容器，它使用哈希表来存储唯一的键和对应的值。以下是一些使用 `std::unordered_map` 进行高效数据查找和插入的技巧：

1. **使用合适的哈希函数**：
   - 确保为自定义类型提供一个好的哈希函数，这样可以减少哈希冲突，提高查找和插入的效率。

2. **避免哈希碰撞**：
   - 好的哈希函数应该能够均匀分布键值，以减少哈希碰撞。

3. **使用合适的装载因子**：
   - 装载因子是哈希表中元素数量与哈希表容量的比例。保持较低的装载因子可以提高性能，但会增加内存使用。

4. **使用 `reserve` 方法**：
   - 如果你知道将要存储的元素数量，可以使用 `reserve` 方法预先分配足够的空间，以减少动态扩容的次数。

5. **使用 `emplace` 或 `insert` 方法**：
   - 使用 `emplace` 或 `insert` 方法直接在哈希表中构造对象，以避免不必要的复制或移动。

6. **使用 `find` 或 `count` 方法**：
   - 使用 `find` 方法来查找元素，它返回一个迭代器，如果找到了元素，则指向该元素；否则，指向容器末尾。
   - 使用 `count` 方法来获取具有特定键的元素数量，对于 `std::unordered_map` 来说，结果要么是 0 要么是 1。

7. **使用迭代器而不是索引**：
   - `std::unordered_map` 不支持随机访问，所以使用迭代器而不是索引来遍历元素。

8. **考虑使用 `equal_range` 方法**：
   - 对于需要找到键的范围的情况，可以使用 `equal_range` 方法，它返回一个迭代器对，表示上界和下界。

9. **使用合适的键类型**：
   - 选择一个合适的键类型，最好是轻量级的，并且易于哈希的。

10. **避免频繁的动态扩容**：
    - 动态扩容可能会导致性能下降，因为需要重新计算所有元素的哈希值并重新分配元素。

11. **使用 `try_emplace`**：
    - C++17 引入了 `try_emplace`，它可以直接在容器中构造元素，避免不必要的复制或移动。

12. **考虑多线程环境**：
    - 在多线程环境中，需要考虑线程安全问题，可能需要使用锁或其他同步机制。

以下是一些示例代码：

```cpp
#include <iostream>
#include <unordered_map>

int main() {
    std::unordered_map<int, std::string> umap;

    // 使用 emplace 直接构造元素
    umap.emplace(1, "Kimi");
    umap.emplace(2, "Moonshot AI");

    // 查找元素
    auto it = umap.find(1);
    if (it != umap.end()) {
        std::cout << it->second << std::endl; // 输出 "Kimi"
    }

    // 插入元素
    auto result = umap.insert({3, "New Entry"});
    if (result.second) {
        std::cout << "Insertion successful." << std::endl;
    }

    // 使用 try_emplace (C++17)
    auto it2 = umap.try_emplace(4, "Another Entry");

    return 0;
}
```

通过遵循这些技巧，你可以在使用 `std::unordered_map` 时实现高效的数据查找和插入操作。

## 3.在多线程环境下，std:unordered_map如何保证线程安全？

在多线程环境中，`std::unordered_map` 本身并不是线程安全的。为了保证线程安全，可以采用以下几种策略：

1. **使用互斥锁**：
   - 最简单的方法是使用互斥锁（如 `std::mutex`）来保护所有对 `std::unordered_map` 的访问。在每个操作（插入、查找、删除）之前加锁，在操作完成后解锁。

```cpp
#include <unordered_map>
#include <mutex>
#include <shared_mutex> // C++17 引入的读写锁

std::unordered_map<int, std::string> umap;
std::mutex mtx; // 或者 std::shared_mutex 在 C++17 及更高版本

void safe_insert(int key, const std::string& value) {
    std::lock_guard<std::mutex> lock(mtx);
    umap.insert({key, value});
}

std::string safe_find(int key) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = umap.find(key);
    if (it != umap.end()) {
        return it->second;
    }
    return "";
}
```

2. **使用读写锁**：
   - 对于读多写少的场景，可以使用读写锁（如 `std::shared_mutex`）来允许多个线程同时读取，但写入时需要独占访问。

```cpp
#include <unordered_map>
#include <shared_mutex>

std::unordered_map<int, std::string> umap;
std::shared_mutex rw_mtx;

void safe_insert(int key, const std::string& value) {
    std::unique_lock<std::shared_mutex> lock(rw_mtx);
    umap.insert({key, value});
}

std::string safe_find(int key) {
    std::shared_lock<std::shared_mutex> lock(rw_mtx);
    auto it = umap.find(key);
    if (it != umap.end()) {
        return it->second;
    }
    return "";
}
```

3. **分段锁**：
   - 将哈希表分成多个段，每个段使用独立的锁。这种方法可以提高并发性，但实现起来比较复杂。

4. **无锁编程**：
   - 使用原子操作和CAS（Compare-And-Swap）操作来实现无锁的并发控制。这种方法需要非常小心地设计，以避免死锁和提高性能。

5. **使用线程局部存储**：
   - 每个线程使用独立的 `std::unordered_map` 实例，最后再将它们合并。这种方法适用于某些特定场景。

6. **使用第三方库**：
   - 使用已经设计为线程安全的第三方库，如 Intel Threading Building Blocks (TBB) 中的并发容器。

7. **避免共享**：
   - 如果可能，避免在多个线程之间共享同一个 `std::unordered_map` 实例。

8. **细粒度锁**：
   - 对哈希表的每个桶或元素使用独立的锁，以减少锁的粒度，提高并发性。

选择哪种方法取决于你的具体需求，包括对并发性能的要求、实现的复杂度以及对读操作和写操作的相对频率。在实际应用中，可能需要权衡各种因素来选择最合适的线程安全策略。

## 4.在多线程环境下，除了使用互斥锁，还有哪些其他方法可以保证 std::unordered_map 的线程安全？

在多线程环境下，除了使用互斥锁，以下是一些保证 `std::unordered_map` 线程安全的方法：

1. **读写锁**：使用读写锁（`std::shared_mutex`）来允许多个线程同时读取，但写入时需要独占访问。这样可以在读取操作多于写入操作的场景下提高并发性能。

2. **分段锁**：将哈希表分成多个段，每个段使用独立的锁。这样，不同线程可以同时操作不同的段，从而提高并发性能。

3. **乐观锁**：使用乐观锁，如通过版本号或时间戳来确保在扩容过程中数据的一致性。

4. **无锁编程**：使用原子操作和CAS（Compare-And-Swap）操作来实现无锁的并发控制。这种方法需要非常小心地设计，以避免死锁和提高性能。

5. **线程局部存储**：每个线程使用独立的 `std::unordered_map` 实例，最后再将它们合并。

6. **使用第三方库**：使用已经设计为线程安全的第三方库，如 Intel Threading Building Blocks (TBB) 中的并发容器。

7. **细粒度锁**：对哈希表的每个桶或元素使用独立的锁，以减少锁的粒度，提高并发性。

8. **使用 `std::atomic`**：对于某些简单的哈希表操作，可以使用 `std::atomic` 类型来保证操作的原子性，从而避免使用锁。

9. **避免共享**：如果可能，避免在多个线程之间共享同一个 `std::unordered_map` 实例。

10. **自定义线程安全哈希表**：可以创建一个自定义的线程安全哈希表，该哈希表内部使用 `std::unordered_map` 并添加必要的同步机制，如使用读写锁来保护数据。

选择哪种方法取决于你的具体需求，包括对并发性能的要求、实现的复杂度以及对读操作和写操作的相对频率。在实际应用中，可能需要权衡各种因素来选择最合适的线程安全策略。

## 5.如何使用std:shared_mutex实现std:unordered_map的线程安全操作？

std::shared_mutex 是 C++17 引入的一种新的互斥机制，它支持共享所有权的锁，允许多个线程同时对同一个资源进行读取，但写入时需要独占访问权。使用 std::shared_mutex 可以实现高效的线程安全的 std::unordered_map，特别是在读多写少的场景下。

以下是使用 std::shared_mutex 实现线程安全的 std::unordered_map 操作的示例：

1. 包含必要的头文件

    ```cpp
    #include <unordered_map>
    #include <shared_mutex>
    #include <string>
    #include <iostream>
    ```

2. 定义线程安全的 unordered_map 包装器

    ```cpp
    template <typename K, typename V>
    class ThreadSafeUnorderedMap {
    private:
        std::unordered_map<K, V> map;
        mutable std::shared_mutex mutex;

    public:
        // 插入或更新元素
        void insert(const K& key, const V& value) {
            std::unique_lock<std::shared_mutex> lock(mutex);
            map[key] = value;
        }

        // 查找元素
        bool find(const K& key, V& value) const {
            std::shared_lock<std::shared_mutex> lock(mutex);
            auto it = map.find(key);
            if (it != map.end()) {
                value = it->second;
                return true;
            }
            return false;
        }

        // 删除元素
        bool erase(const K& key) {
            std::unique_lock<std::shared_mutex> lock(mutex);
            return map.erase(key) > 0;
        }

        // 遍历元素（只读）
        void foreach(std::function<void(const K&, const V&)> fn) const {
            std::shared_lock<std::shared_mutex> lock(mutex);
            for (const auto& pair : map) {
                fn(pair.first, pair.second);
            }
        }
    };
    ```

3. 使用示例

    ```cpp
    int main() {
        ThreadSafeUnorderedMap<int, std::string> ts_map;

        // 插入元素
        ts_map.insert(1, "Kimi");
        ts_map.insert(2, "Moonshot AI");

        // 查找元素
        std::string value;
        if (ts_map.find(1, value)) {
            std::cout << "Found: " << value << std::endl;
        } else {
            std::cout << "Not found" << std::endl;
        }

        // 删除元素
        if (ts_map.erase(1)) {
            std::cout << "Element deleted" << std::endl;
        }

        // 遍历元素
        ts_map.foreach([](const int& key, const std::string& value) {
            std::cout << key << ": " << value << std::endl;
        });

        return 0;
    }
    ```

4. 解释
   1. std::shared_mutex：
      1. std::shared_mutex 支持共享锁和独占锁。共享锁允许多个线程同时读取，而独占锁则在写入时使用。
   2. insert 方法：
      1. 使用 std::unique_lock 来获取独占锁，确保在插入或更新元素时不会有其他线程干扰。
   3. find 方法：
      1. 使用 std::shared_lock 来获取共享锁，允许多个线程同时查找元素。
   4. erase 方法：
      1. 使用 std::unique_lock 来获取独占锁，确保在删除元素时不会有其他线程干扰。
   5. foreach 方法：
      1. 使用 std::shared_lock 来获取共享锁，允许多个线程同时遍历元素，但不允许修改。

通过这种方式，你可以确保 std::unordered_map 在多线程环境中的线程安全，同时在读多写少的场景下提高并发性能。

## 6.在设计多线程程序时，如何避免死锁和提高性能？

在设计多线程程序时，避免死锁和提高性能是两个关键目标。以下是一些有效的方法：

### 6.1.避免死锁

1. **锁定顺序**：确保所有线程获取锁时都按照相同的顺序来获取。

2. **锁定时间**：尽量减少持有锁的时间，例如，获取所有需要的锁后再开始临界区代码的执行。

3. **超时尝试**：使用尝试锁定（如 `try_lock`）并设置超时时间，避免一个线程无限期地等待锁。

4. **避免嵌套锁**：尽量不要在持有一个锁的情况下等待另一个锁。

5. **使用锁等级**：为不同的锁分配不同的等级，并规定所有线程必须按照从低到高的顺序获取锁。

6. **使用死锁检测工具**：使用动态分析工具来检测死锁。

7. **减少锁的使用**：使用无锁编程技术，如原子操作，或者使用高级并发数据结构。

### 6.2.提高性能

1. **使用合适的锁**：选择最适合你需求的锁，如互斥锁、读写锁、自旋锁等。

2. **锁粒度**：减小锁的粒度，如使用细粒度锁或分段锁，以减少线程间的等待时间。

3. **锁分离**：对于读多写少的场景，使用读写锁来允许多个读者同时访问。

4. **线程池**：使用线程池来管理和复用线程，减少线程创建和销毁的开销。

5. **缓存局部性**：优化数据结构和算法以提高缓存局部性，减少内存访问延迟。

6. **并行算法**：使用标准库中的并行算法（如 `std::for_each` 与 `execution policies`），或者并发数据结构来简化并行编程。

7. **避免过度同步**：尽量减少同步机制的使用，只在必要时进行同步。

8. **使用原子操作**：对于简单的数据操作，使用 `std::atomic` 类型来避免重量级锁的开销。

9. **负载均衡**：确保工作负载在多个线程之间均匀分配，避免某些线程过载而其他线程空闲。

10. **避免伪共享**：在多核处理器上，避免多个线程频繁更新同一缓存行的数据，以减少缓存伪共享。

11. **测试和调优**：使用性能分析工具定期测试和调优你的多线程程序。

通过上述方法，可以在设计多线程程序时有效地避免死锁并提高性能。记住，不同的应用场景可能需要不同的策略，因此需要根据具体情况进行调整。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
