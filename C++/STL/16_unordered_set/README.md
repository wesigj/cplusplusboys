# C++ STL源码剖析 16-unordered_set

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.unordered_set

在 C++ 标准模板库（STL）中，`std::unordered_set` 是一种基于哈希表实现的容器，用于存储唯一的元素。它允许快速访问、插入和删除操作，而不需要维护元素的顺序。`std::unordered_set` 的性能通常比 `std::set` 更好，尤其是在元素的查找和插入操作中。

以下是 `std::unordered_set` 的一些主要特性：

1. **元素唯一性**：`std::unordered_set` 只存储唯一的元素，不允许有重复。
2. **无序存储**：元素在容器中不保持任何特定的顺序。
3. **快速访问**：提供了平均时间复杂度为 O(1) 的访问、插入和删除操作。
4. **键值相等**：在 `std::unordered_set` 中，键和值是相同的，每个元素既是键也是值。

### 如何使用 `std::unordered_set`

**基本用法**：

```cpp
#include <iostream>
#include <unordered_set>

int main() {
    // 创建一个 std::unordered_set 实例
    std::unordered_set<int> u_set;

    // 插入元素
    u_set.insert(1);
    u_set.insert(2);
    u_set.insert(3);

    // 检查元素是否存在
    if (u_set.find(2) != u_set.end()) {
        std::cout << "Element 2 is in the set." << std::endl;
    }

    // 删除元素
    u_set.erase(1);

    // 遍历 unordered_set
    for (int num : u_set) {
        std::cout << num << ' ';
    }
    std::cout << std::endl;

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

std::unordered_set<MyKey, MyHash, MyKeyEqual> custom_u_set;
```

在这个例子中，我们定义了一个 `MyKey` 结构，它将用作 `std::unordered_set` 的元素。我们还提供了自定义的哈希函数 `MyHash` 和键比较函数 `MyKeyEqual`。

**注意**：

- `std::unordered_set` 的迭代器在插入和删除操作后可能会失效。如果需要，在这些操作后更新迭代器。
- 考虑负载因子和哈希表的动态扩容行为，以优化性能。
- 在多线程环境中，`std::unordered_set` 本身不是线程安全的。需要额外的同步机制来保证线程安全。

`std::unordered_set` 是 C++ STL 中非常有用的容器之一，适用于需要快速访问元素的场景，特别是当元素的顺序不重要时。

## 2.std::unordered_map 和 std::unordered_set 有什么区别？

`std::unordered_map` 和 `std::unordered_set` 都是 C++ 标准模板库（STL）中的关联容器，它们都使用哈希表来实现，但它们之间有几个关键的区别：

1. **存储内容**：
   - `std::unordered_map` 存储键值对（key-value pairs），即每个元素包含一个键和一个与键相关联的值。
   - `std::unordered_set` 只存储键（keys），不存储值，每个元素就是一个键。

2. **用途**：
   - `std::unordered_map` 用于当你需要关联唯一的键和值时，例如，实现一个符号表来查找变量名对应的值。
   - `std::unordered_set` 用于当你只需要存储唯一的键，不需要关联值时，例如，实现一个不包含重复元素的集合。

3. **接口**：
   - `std::unordered_map` 提供了 `insert`、`emplace`、`operator[]`、`at`、`find` 等成员函数来操作键值对。
   - `std::unordered_set` 提供了 `insert`、`emplace`、`find` 等成员函数来操作键。

4. **迭代器**：
   - `std::unordered_map` 的迭代器指向键值对，因此迭代器可以解引用为一个 `std::pair`，其中包含键和值。
   - `std::unordered_set` 的迭代器指向键本身。

5. **默认哈希函数和键比较函数**：
   - `std::unordered_map` 和 `std::unordered_set` 都使用 `std::hash` 作为默认的哈希函数，但 `std::unordered_map` 使用 `std::equal_to` 来比较键是否相等，而 `std::unordered_set` 只比较键。

6. **性能**：
   - 两者在插入、查找和删除操作上都具有平均时间复杂度为 O(1) 的性能，但具体性能可能会因哈希函数的实现和键的分布而有所不同。

7. **内存使用**：
   - 由于 `std::unordered_map` 需要存储键和值，所以通常比 `std::unordered_set` 使用更多的内存。

8. **应用场景**：
   - 如果你需要存储额外的数据或者需要通过键快速查找值，`std::unordered_map` 是更好的选择。
   - 如果你只需要存储唯一的元素并且关注插入和查找的速度，`std::unordered_set` 可能更适合。

选择使用 `std::unordered_map` 还是 `std::unordered_set` 取决于你的具体需求和应用场景。

## 3.在多线程环境中，std:unordered_set应该如何保证线程安全？

在多线程环境中，`std::unordered_set` 本身不是线程安全的。为了保证线程安全，可以采用以下几种策略：

1. **使用互斥锁**：
   - 使用 `std::mutex` 在每次访问 `std::unordered_set` 时进行加锁和解锁，以确保任何时候只有一个线程可以修改集合。

    ```cpp
    #include <unordered_set>
    #include <mutex>

    std::unordered_set<int> u_set;
    std::mutex mtx;

    void safe_insert(int value) {
        std::lock_guard<std::mutex> lock(mtx);
        u_set.insert(value);
    }

    bool safe_find(int value) {
        std::lock_guard<std::mutex> lock(mtx);
        return u_set.find(value) != u_set.end();
    }
    ```

2. **使用读写锁**

   - 对于读多写少的场景，使用 `std::shared_mutex` 来允许多个线程同时读取，但写入时需要独占访问。

    ```cpp
    #include <unordered_set>
    #include <shared_mutex>

    std::unordered_set<int> u_set;
    std::shared_mutex rw_mtx;

    void safe_insert(int value) {
        std::unique_lock<std::shared_mutex> lock(rw_mtx);
        u_set.insert(value);
    }

    bool safe_find(int value) {
        std::shared_lock<std::shared_mutex> lock(rw_mtx);
        return u_set.find(value) != u_set.end();
    }
    ```

3. **线程局部存储**

   - 使用线程局部变量 (`thread_local`) 为每个线程创建独立的 `std::unordered_set` 实例，最后再将它们合并或同步。

4. **避免共享**

   - 如果可能，避免在多个线程之间共享同一个 `std::unordered_set` 实例。

5. **使用第三方库**

   - 使用已经设计为线程安全的第三方库，如 Intel Threading Building Blocks (TBB) 中的并发容器。

6. **细粒度锁**

   - 对哈希表的每个桶或元素使用独立的锁，以减少锁的粒度，提高并发性。

7. **无锁编程**

   - 使用原子操作和CAS（Compare-And-Swap）操作来实现无锁的并发控制。这种方法需要非常小心地设计，以避免死锁和提高性能。

8. **使用 `std::atomic`**

   - 对于某些简单的 `std::unordered_set` 操作，可以使用 `std::atomic` 类型来保证操作的原子性，从而避免使用锁。

选择哪种方法取决于你的具体需求，包括对并发性能的要求、实现的复杂度以及对读操作和写操作的相对频率。在实际应用中，可能需要权衡各种因素来选择最合适的线程安全策略。

## 4.std:unordered_map和std:unordered_set在内存使用上具体有哪些差异？

`std::unordered_map` 和 `std::unordered_set` 在内存使用上的差异主要体现在以下几个方面：

1. **存储内容**：
   - `std::unordered_map` 存储键值对，即每个元素包含一个键和一个与之关联的值。
   - `std::unordered_set` 只存储键，没有与之关联的值。

2. **内存占用**：
   - 由于 `std::unordered_map` 需要存储额外的值，因此其内存占用通常比 `std::unordered_set` 大。
   - `std::unordered_set` 仅存储键，因此其内存占用相对较小。

3. **哈希表结构**：
   - 两者都基于哈希表实现，但在哈希表的每个桶（bucket）中，`std::unordered_map` 存储的是键值对的列表，而 `std::unordered_set` 存储的是键的列表。

4. **负载因子和扩容**：
   - `std::unordered_map` 和 `std::unordered_set` 都会根据负载因子（元素数量与桶数量的比例）进行动态扩容，但扩容时 `std::unordered_map` 可能需要更多的内存，因为它需要为更多的数据（键和值）分配空间。

5. **内存分配策略**：
   - 两者都使用内存分配器（allocator）来管理内存，但 `std::unordered_map` 的内存分配器需要处理更复杂的数据结构（存储键值对）。

6. **内存局部性**：
   - `std::unordered_set` 由于只存储键，可能会有更好的内存局部性，因为键通常比键值对更紧凑。

7. **内存碎片**：
   - 在频繁的插入和删除操作中，两者都可能产生内存碎片，但 `std::unordered_map` 由于存储结构更复杂，可能会有更多的内存碎片。

8. **自定义类型**：
   - 如果存储的键或值是自定义类型，那么这些类型的内存占用也会影响 `std::unordered_map` 和 `std::unordered_set` 的内存使用。

9. **预留空间**：
   - 使用 `reserve` 方法可以预先分配足够的空间，减少动态扩容的次数，从而减少内存使用的波动。

总的来说，`std::unordered_map` 由于需要存储键和值，通常会使用更多的内存。而 `std::unordered_set` 只存储键，因此在相同数量的元素下，内存占用通常更少。然而，具体的内存差异还取决于键和值的大小以及哈希表的负载因子。

## 5.在实际编程中，如何根据项目需求选择使用std:unordered_map还是std:unordered_set?

在实际编程中，选择使用 `std::unordered_map` 还是 `std::unordered_set` 取决于项目需求和特定的应用场景。以下是一些指导原则：

1. **存储需求**：
   - 如果你需要存储关联数据，即每个键都需要关联一个或多个值，则使用 `std::unordered_map`。
   - 如果你只需要存储唯一的键，不需要关联值，则使用 `std::unordered_set`。

2. **元素唯一性**：
   - `std::unordered_set` 保证存储的元素是唯一的，适用于需要去重的场景。
   - `std::unordered_map` 保证存储的键是唯一的，但每个键可以关联多个值（如果值是标准容器）。

3. **访问模式**：
   - 如果你需要根据键快速查找、插入或删除数据，则 `std::unordered_map` 更适合。
   - 如果你只需要检查元素是否存在，或者需要频繁地添加和删除元素，则 `std::unordered_set` 更适合。

4. **性能要求**：
   - 如果对插入和查找性能有极高要求，且不关心元素之间的关联，则 `std::unordered_set` 可能更合适，因为它通常比 `std::unordered_map` 使用更少的内存。
   - 如果需要频繁地更新和访问关联值，`std::unordered_map` 可能更有优势。

5. **内存使用**：
   - 如果内存使用是一个关键问题，且不需要存储关联值，则 `std::unordered_set` 可能更合适，因为它只存储键。
   - 如果关联值是必要的，那么 `std::unordered_map` 是必需的，即使它使用更多的内存。

6. **操作复杂度**：
   - `std::unordered_map` 提供了更多操作，如 `insert_or_assign`、`emplace`、`try_emplace` 等，如果这些操作对你的项目很重要，那么选择 `std::unordered_map`。

7. **迭代器稳定性**：
   - 如果你需要在迭代过程中修改容器，且需要迭代器保持稳定，`std::unordered_map` 和 `std::unordered_set` 都可以满足要求，但需要注意迭代器可能会在插入操作后失效。

8. **多线程环境**：
   - 如果你的项目在多线程环境中运行，需要考虑线程安全问题。两者都不是线程安全的，需要额外的同步机制。

9. **自定义数据类型**：
   - 如果你使用的是自定义数据类型作为键，需要确保为这些类型提供了合适的哈希函数和键比较函数。

10. **标准库替代品**：
    - 考虑是否有现成的标准库容器更适合你的需求，比如 `std::set`、`std::map` 或其他容器。

根据上述指导原则，权衡你的项目需求，选择最适合的容器类型。在某些情况下，可能需要对性能进行实际测试，以确定哪种容器在特定用例下表现更好。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
