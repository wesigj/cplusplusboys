# C++ STL源码剖析 14-myhashtable

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.myhashtable

下面是一个简单的 C++ 实现哈希表的例子，它使用了链地址法来解决哈希冲突。这个哈希表支持基本的插入、查找和删除操作。

```cpp
#include <vector>
#include <list>
#include <functional>
#include <iostream>

template <typename K, typename V>
class HashTable {
public:
    // 构造函数，初始化一个指定大小的哈希表
    explicit HashTable(size_t size) : table(size) {}

    // 插入键值对
    void insert(const K& key, const V& value) {
        auto& bucket = table[bucket_index(key)];
        for (auto& pair : bucket) {
            if (pair.first == key) {
                pair.second = value; // 如果键已存在，则更新值
                return;
            }
        }
        bucket.push_back({key, value}); // 否则，在链表尾部插入新元素
    }

    // 按键查找值
    V* find(const K& key) {
        auto& bucket = table[bucket_index(key)];
        for (auto& pair : bucket) {
            if (pair.first == key) {
                return &pair.second; // 找到键，返回值的指针
            }
        }
        return nullptr; // 未找到键，返回nullptr
    }

    // 删除键值对
    void remove(const K& key) {
        auto& bucket = table[bucket_index(key)];
        auto it = std::find_if(bucket.begin(), bucket.end(),
                               [&key](const std::pair<K, V>& pair) { return pair.first == key; });
        if (it != bucket.end()) {
            bucket.erase(it); // 找到元素，从链表中移除
        }
    }

private:
    // 哈希函数，返回一个键的索引位置
    size_t bucket_index(const K& key) const {
        return std::hash<K>()(key) % table.size();
    }

    // 哈希表的存储，使用链表解决冲突
    std::vector<std::list<std::pair<K, V>>> table;
};

int main() {
    HashTable<int, std::string> hash_table(10); // 创建一个大小为10的哈希表

    hash_table.insert(1, "Kimi");
    hash_table.insert(2, "Moonshot AI");

    if (auto* value = hash_table.find(1)) {
        std::cout << "Found: " << *value << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    hash_table.remove(1);

    if (auto* value = hash_table.find(1)) {
        std::cout << "Found: " << *value << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    return 0;
}
```

这个哈希表使用 `std::vector` 来存储桶，每个桶是一个 `std::list`，用于存储具有相同哈希值的键值对。哈希函数使用 `std::hash` 来计算键的索引位置。

请注意，这个哈希表实现是基本的，没有考虑动态扩容、哈希碰撞优化、内存分配优化、异常安全或线程安全等因素。在实际应用中，你可能需要根据具体需求添加这些高级特性。此外，C++11 标准库已经提供了 `std::unordered_map`，它是一个高效的哈希表实现，通常比手写的哈希表性能更好，且具有更多功能。

## 2.动态扩容、哈希碰撞优化、内存分配优化、异常安全或线程安全等因素

要增加这些高级功能，我们需要对之前的哈希表实现进行扩展。以下是实现这些功能的大致步骤和代码示例：

### 2.1. 动态扩容

动态扩容涉及到在哈希表负载因子过高时增加哈希表的大小，并重新分配现有元素。

```cpp
template <typename K, typename V>
class HashTable {
    // ...
    void rehash() {
        size_t old_size = table.size();
        size_t new_size = std::max(4, 2 * old_size); // 扩容至当前大小的2倍，至少为4
        std::vector<std::list<std::pair<K, V>>> new_table(new_size);

        for (auto& bucket : table) {
            for (auto& pair : bucket) {
                size_t new_index = bucket_index(pair.first, new_size);
                new_table[new_index].push_back(std::move(pair));
            }
        }

        table.swap(new_table);
    }

    size_t bucket_index(const K& key, size_t size) const {
        return std::hash<K>()(key) % size;
    }

    // ...
};
```

### 2.2. 哈希碰撞优化

使用更好的哈希函数或引入二级哈希来优化哈希碰撞。

```cpp
struct BetterHash {
    size_t operator()(const K& key) const {
        // 实现一个更好的哈希函数
    }
};

template <typename K, typename V>
class HashTable {
    // ...
    BetterHash hash_function;
    // ...
    size_t bucket_index(const K& key) const {
        return hash_function(key) % table.size();
    }
    // ...
};
```

### 2.3. 内存分配优化

使用内存池来优化内存分配。

```cpp
template <typename K, typename V>
class MemoryPool {
    // 实现一个简单的内存池
    // ...
};

template <typename K, typename V>
class HashTable {
    MemoryPool<std::pair<K, V>> pool;
    // ...
    void insert(const K& key, const V& value) {
        // 使用内存池来分配内存
    }
    // ...
};
```

### 2.4. 异常安全

确保哈希表的操作不会在抛出异常时导致资源泄露。

```cpp
template <typename K, typename V>
class HashTable {
    // ...
    void insert(const K& key, const V& value) {
        auto index = bucket_index(key);
        auto& bucket = table[index];
        for (auto& pair : bucket) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }

        bucket.push_back(pool.allocate(std::piecewise_construct, std::forward_as_tuple(key), std::forward_as_tuple(value)));
    }

    void rehash() {
        size_t old_size = table.size();
        size_t new_size = std::max(4, 2 * old_size);
        std::vector<std::list<std::pair<K, V>>> new_table(new_size);

        for (auto& bucket : table) {
            for (auto& pair : bucket) {
                auto& new_pair = *pool.allocate(std::piecewise_construct, std::forward_as_tuple(pair.first), std::forward_as_tuple(pair.second));
                size_t new_index = bucket_index(pair.first, new_size);
                new_table[new_index].push_back(std::move(new_pair));
            }
        }

        pool.release();
        table.swap(new_table);
    }
    // ...
};
```

### 2.5. 线程安全

引入互斥锁来确保线程安全。

```cpp
template <typename K, typename V>
class HashTable {
    // ...
    mutable std::mutex mutex;
    // ...
    void insert(const K& key, const V& value) {
        std::lock_guard<std::mutex> lock(mutex);
        // 插入操作
    }
    V* find(const K& key) {
        std::shared_lock<std::mutex> lock(mutex);
        // 查找操作
    }
    void remove(const K& key) {
        std::lock_guard<std::mutex> lock(mutex);
        // 删除操作
    }
    // ...
};
```

这些示例提供了一个基本的框架，但实现细节需要根据具体情况进行调整和优化。在实际应用中，你可能需要考虑更多的边界情况和性能问题。

## 3.如何确保哈希表在动态扩容过程中不会丢失数据？

确保哈希表在动态扩容过程中不会丢失数据的关键在于如何在扩容时重新分配现有元素到新的哈希表中。以下是一些关键步骤和技巧：

1. **使用临时哈希表**：在扩容时，可以创建一个新的哈希表，并将旧哈希表中的所有元素重新插入到这个临时哈希表中。这样可以确保在扩容过程中不会丢失任何数据。

2. **重新计算哈希值**：在将元素从旧哈希表迁移到新哈希表时，需要重新计算每个元素的哈希值，以确定它们在新哈希表中的位置。

3. **保持链表结构**：如果使用链表来解决哈希冲突，那么在迁移过程中，需要确保链表的顺序和结构得以保持，以避免数据丢失。

4. **同步操作**：在多线程环境中，确保扩容操作是线程安全的。可以使用锁或其他同步机制来确保在扩容过程中不会有其他线程修改哈希表。

5. **扩容策略**：可以选择在插入操作时，如果发现负载因子超过预设阈值，就先进行扩容，然后再插入新元素。这样可以避免集中一次性迁移数据导致的耗时问题。

6. **避免数据覆盖**：在迁移数据时，确保不会覆盖新哈希表中已有的元素。如果新旧哈希表的索引位置相同，则需要将旧哈希表中的元素追加到新哈希表的链表尾部。

7. **测试和验证**：在实现动态扩容后，进行彻底的测试以确保没有数据丢失。可以设计测试用例来模拟大量插入、删除和扩容操作，验证哈希表的完整性。

通过上述方法，可以确保哈希表在动态扩容过程中的数据完整性和一致性。

## 4.在哈希表扩容过程中，如何优化链表结构以提高性能？

在哈希表扩容过程中，优化链表结构以提高性能的关键在于如何有效地重新分配现有元素到新的哈希表中。以下是一些优化策略：

1. **使用更好的哈希函数**：选择或设计一个好的哈希函数，以减少哈希冲突和提高键值对的均匀分布。

2. **链表与红黑树的转换**：在Java 8及以后的版本中，`ConcurrentHashMap` 使用红黑树替换了链表，当链表长度超过一定阈值时自动转换，以降低查找时间复杂度并提高性能。

3. **动态调整哈希表大小**：当负载因子超过预设阈值时，哈希表会扩容，这有助于减少冲突和提高性能。

4. **优化内存使用**：使用内存池来管理内存分配，以减少动态内存分配的开销。

5. **避免数据覆盖**：在迁移数据时，确保不会覆盖新哈希表中已有的元素。如果新旧哈希表的索引位置相同，则需要将旧哈希表中的元素追加到新哈希表的链表尾部。

6. **扩容策略**：可以选择在插入操作时，如果发现负载因子超过预设阈值，就先进行扩容，然后再插入新元素。这样可以避免集中一次性迁移数据导致的耗时问题。

7. **测试和验证**：在实现动态扩容后，进行彻底的测试以确保没有数据丢失。可以设计测试用例来模拟大量插入、删除和扩容操作，验证哈希表的完整性。

通过上述方法，可以确保哈希表在动态扩容过程中的数据完整性和一致性，同时提高性能。

## 5.在多线程环境下，除了使用锁，还有哪些方法可以保证哈希表扩容的线程安全？

在多线程环境下，除了使用锁，以下是一些保证哈希表扩容线程安全的方法：

1. **无锁编程**：使用原子操作（如CAS - Compare-and-Swap）来实现无锁的哈希表扩容。这种方法可以避免锁的开销，提高并发性能，但实现复杂度较高 。

2. **分段锁（Segmentation Locks）**：将哈希表分成多个段，每个段使用独立的锁。这样，不同线程可以同时操作不同的段，从而提高并发性能 。

3. **乐观锁**：使用乐观锁，如通过版本号或时间戳来确保在扩容过程中数据的一致性。

4. **读写锁**：使用读写锁（`std::shared_mutex`）来允许多个读线程同时访问，但写线程需要独占访问 。

5. **锁分离**：将读操作和写操作锁分开，使得读操作不需要等待写操作完成，从而提高并发性 。

6. **使用`std::atomic`**：对于某些简单的哈希表操作，可以使用`std::atomic`类型来保证操作的原子性，从而避免使用锁 。

7. **扩容时的线程协作**：在扩容过程中，多个线程可以协作，每个线程负责迁移一部分数据，通过原子操作和同步机制来协调各个线程的工作 。

8. **使用`Lock-Free Data Structures`**：采用无锁数据结构库，如Intel TBB（Threading Building Blocks）库中的并发哈希表。

9. **避免共享**：如果可能，避免在多个线程之间共享同一个哈希表实例。每个线程可以使用独立的哈希表，然后通过合并结果来实现线程安全。

10. **细粒度锁**：为哈希表的每个桶或元素使用独立的锁，这样可以减少锁的粒度，提高并发性 。

通过这些方法，可以在不同的场景下提高哈希表的线程安全性，使其在多线程环境中更加高效和稳定。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
