# C++ Practical-2 字典插入与查找

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.字典插入与查找

在 C++ 中，字典通常可以通过 `std::map` 或 `std::unordered_map` 来实现。这两个容器都提供了插入和查找元素的功能。以下是如何使用这两个容器进行插入和查找操作的示例：

### 1.1.使用 `std::map`

`std::map` 是一个基于红黑树实现的有序关联容器，它允许根据键（key）来存储和查找值（value）。

**插入元素**：

```cpp
#include <map>
#include <iostream>

int main() {
    std::map<int, std::string> dictionary;

    // 插入元素
    dictionary.insert(std::make_pair(1, "one"));
    dictionary.insert(std::make_pair(2, "two"));
    dictionary.insert(std::make_pair(3, "three"));

    // 另一种插入方式
    dictionary[4] = "four";

    // 插入已存在键的值，会更新该键的值
    dictionary[2] = "two updated";
}

```

**查找元素**：

```cpp
#include <map>
#include <iostream>

int main() {
    std::map<int, std::string> dictionary = {
        {1, "one"},
        {2, "two"},
        {3, "three"}
    };

    // 查找元素
    int key = 2;
    if (dictionary.find(key) != dictionary.end()) {
        std::cout << "Found: " << dictionary[key] << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }
}
```

### 1.2.使用 `std::unordered_map`

`std::unordered_map` 是一个基于哈希表实现的无序关联容器，它同样允许根据键来存储和查找值，但查找速度通常比 `std::map` 更快。

**插入元素**：

```cpp
#include <unordered_map>
#include <iostream>

int main() {
    std::unordered_map<int, std::string> dictionary;

    // 插入元素
    dictionary.insert(std::make_pair(1, "one"));
    dictionary.insert(std::make_pair(2, "two"));
    dictionary.insert(std::make_pair(3, "three"));

    // 另一种插入方式
    dictionary[4] = "four";

    // 插入已存在键的值，会更新该键的值
    dictionary[2] = "two updated";
}
```

**查找元素**：

```cpp
#include <unordered_map>
#include <iostream>

int main() {
    std::unordered_map<int, std::string> dictionary = {
        {1, "one"},
        {2, "two"},
        {3, "three"}
    };

    // 查找元素
    int key = 2;
    if (dictionary.find(key) != dictionary.end()) {
        std::cout << "Found: " << dictionary[key] << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }
}
```

在这两个例子中，`insert` 函数用于插入新元素，而 `operator[]` 用于插入或更新元素。查找操作是通过 `find` 成员函数进行的，如果找到了元素，它会返回一个指向元素的迭代器；如果没有找到，它会返回一个指向容器末尾的迭代器（`end()`）。

选择 `std::map` 还是 `std::unordered_map` 取决于你的具体需求。如果需要保持元素的排序，或者频繁进行范围查询，那么 `std::map` 可能是更好的选择。如果需要快速的插入和查找，并且不关心元素的顺序，那么 `std::unordered_map` 可能更合适。

## 2.在 C++ 中，除了 std::map 和 std::unordered_map，还有哪些容器可以用于实现字典功能？

在 C++ 中，除了 `std::map` 和 `std::unordered_map`，还有一些其他容器和方法可以实现类似字典的功能：

1. **`std::unordered_multimap`**：
   和 `std::unordered_map` 类似，但它允许多个值与同一个键关联。

2. **`std::map` 和 `std::multimap`**：
   `std::map` 是有序的，而 `std::multimap` 允许多个值与一个键关联。

3. **`std::flat_map`**：
   这是 C++20 中引入的容器，它提供了与 `std::map` 相似的接口，但是它底层使用数组而不是红黑树，这可以减少内存的占用并提高性能。

4. **`std::flat_multimap`**：
   也是 C++20 中引入的，与 `std::flat_map` 类似，但它允许多个值与一个键关联。

5. **`std::array` 或 `std::vector`**：
   如果你的键是连续的整数，你可以使用 `std::array` 或 `std::vector` 来实现字典。例如，你可以使用一个索引数组来存储值，并通过计算键的哈希值来访问数组。

6. **`std::list` 或 `std::forward_list`**：
   这些线性容器可以用来实现字典，特别是当你需要经常在中间插入或删除元素时。

7. **`std::set` 或 `std::unordered_set`**：
   如果你只需要存储键，而不需要存储值，可以使用这些集合容器。

8. **`std::valarray`**：
   如果你需要存储数组的值，并且经常需要对它们进行数学运算，`std::valarray` 可以是一个选择。

9. **自定义哈希表**：
   你可以自己实现一个哈希表，这会给你更多的控制权，但也需要更多的工作。

10. **`std::unordered_multiset`**：
    类似于 `std::unordered_multimap`，但它只存储键，不存储值。

11. **`std::bst`**：
    如果你需要一个有序的字典，你可以自己实现一个二叉搜索树（Binary Search Tree）。

12. **`std::priority_queue`**：
    如果你需要一个有序的字典，其中每次删除都是最大或最小元素，你可以使用优先队列。

13. **`std::queue` 或 `std::stack`**：
    这些容器可以用于实现字典，特别是当你需要保持元素的插入顺序时。

选择哪种容器取决于你的具体需求，比如是否需要排序、是否允许多个值与同一个键关联、性能要求等。在某些情况下，你可能需要组合使用不同的容器或者自定义数据结构来满足特定的需求。

## 3.如何优化std:map的查找性能，以应对大量数据的快速查找？

要优化 `std::map` 的查找性能以应对大量数据的快速查找，可以考虑以下几个方面：

1. **确保键类型的比较效率高**：`std::map` 基于红黑树实现，查找操作的效率依赖于键类型的比较操作。如果键类型是自定义的，确保比较操作（如 `operator<`）高效且不会引入额外开销。

2. **避免使用 `operator[]` 进行查找**：使用 `operator[]` 访问不存在的键会插入一个默认构造的元素。如果只是查找，应该使用 `find` 方法，它在找不到元素时会返回 `end` 迭代器，而不是插入新元素。

3. **使用更合适的容器**：如果查找性能仍然不满足要求，可以考虑使用 `std::unordered_map`，它基于哈希表实现，平均时间复杂度为 O(1)，但缺点是不支持有序迭代。

4. **预计算和缓存**：对于某些查找操作，如果键的计算成本很高，可以考虑预计算并缓存结果，以避免重复计算。

5. **优化数据结构设计**：有时候，对数据结构的设计进行优化可以减少查找次数，例如通过增加辅助索引或使用更适合查询模式的数据结构。

6. **并行查找**：在多核处理器上，对于独立的查找任务，可以考虑使用并行处理来提高性能。

7. **避免频繁的插入和删除**：`std::map` 的插入和删除操作可能需要重新平衡树，这在大量数据时会影响性能。如果可能，尽量批量处理这些操作。

8. **使用自定义比较器**：通过提供一个自定义比较器，可以改变 `std::map` 的排序方式，有时这可以提高查找效率。

9. **减少内存分配**：对于值类型是对象的情况，考虑使用指针或引用来减少内存分配和复制的开销。

10. **使用标准库算法**：对于静态数据，可以使用标准库排序算法（如 `std::sort`）预先排序，然后使用二分查找算法（如 `std::binary_search` 或 `std::lower_bound`）进行查找。

通过这些方法，可以显著提高 `std::map` 在大量数据下的查找性能。不过，优化时应该根据具体情况进行性能测试，以确保所做的优化是有效的。

## 4.std:unordered_map在什么情况下比std:map更有优势，反之亦然？

`std::unordered_map` 和 `std::map` 在 C++ 中都是用来实现字典功能的容器，但它们在性能方面有各自的优势，适用于不同的场景。

### 4.1.`std::unordered_map` 的优势

- **查找速度快**：平均时间复杂度接近 O(1)，因此在查找操作频繁的场景下更有优势。
- **插入速度快**：插入操作通常也是 O(1)，但可能会因为哈希冲突而变慢。
- **内存占用**：通常比 `std::map` 占用更多内存，因为需要存储哈希桶和可能的链表或红黑树节点。

### 4.2.`std::map` 的优势

- **有序性**：元素会按照键的顺序自动排序，如果需要有序遍历，`std::map` 更合适。
- **稳定性**：查找和插入的时间复杂度稳定在 O(log n)，不会因为哈希冲突而性能下降。
- **内存占用**：相比 `std::unordered_map`，通常占用更少的内存，因为不需要额外的哈希表结构。

### 4.3.使用场景

- **选择 `std::unordered_map`**：
  - 当元素的顺序不重要，而查找速度是关键时。
  - 当插入和查找操作非常频繁，且对性能要求较高时。
  - 当对内存使用不是非常敏感时。

- **选择 `std::map`**：
  - 当需要有序遍历元素时。
  - 当对查找性能的稳定性有要求时。
  - 当内存使用是需要考虑的因素时。

### 4.4.性能测试

在实际的性能测试中 ，`std::unordered_map` 在插入和查找操作上通常会比 `std::map` 表现得更好，尤其是在数据量较大时。但是，这也取决于具体的使用情况和数据分布。

总结来说，如果应用程序对查找速度有较高要求且不关心元素的排序，`std::unordered_map` 是更好的选择。如果需要有序的元素或者对性能稳定性有要求，那么 `std::map` 可能更适合。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
