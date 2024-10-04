# C++ STL源码剖析 5-std::vector

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.std::vector 定义

在C++标准模板库（STL）中，`std::vector` 是一个序列容器，它封装了动态大小数组的接口，提供了随机访问能力，以及在数组尾部高效地插入和删除元素的能力。

以下是 `std::vector` 的定义和关键特性：

### 1.1.头文件

```cpp
#include <vector>
```

### 1.2.基本定义

```cpp
template <class T, class Allocator = std::allocator<T> >
class vector {
public:
    // 类型定义
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef std::allocator_traits<Allocator> allocator_traits_type;
    
    // 迭代器类型
    typedef pointer iterator;
    typedef const_pointer const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    // 构造函数和析构函数
    explicit vector(const Allocator& alloc = Allocator());
    explicit vector(size_type n, const T& value = T(), const Allocator& alloc = Allocator());
    template <class InputIterator>
    vector(InputIterator first, InputIterator last, const Allocator& alloc = Allocator());
    vector(const vector& other);
    vector(const vector& other, const Allocator& alloc);
    vector(vector&& other);
    vector(vector&& other, const Allocator& alloc);
    vector(std::initializer_list<T> init, const Allocator& alloc = Allocator());

    // 析构函数
    ~vector();

    // 赋值运算符
    vector& operator=(const vector& other);
    vector& operator=(vector&& other);
    vector& operator=(std::initializer_list<T> init);

    // 迭代器
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    // 容量
    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;
    void resize(size_type new_size);
    void resize(size_type new_size, const T& value);

    // 修改器
    void clear();
    iterator insert(iterator pos, const T& value);
    iterator insert(iterator pos, T&& value);
    template <class... Args>
    iterator emplace(iterator pos, Args&&... args);
    void insert(iterator pos, size_type n, const T& value);
    template <class InputIterator>
    void insert(iterator pos, InputIterator first, InputIterator last);
    void insert(iterator pos, std::initializer_list<T> ilist);
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);
    void swap(vector& other);

    // 数据访问
    reference operator[](size_type n);
    const_reference operator[](size_type n) const;
    reference at(size_type n);
    const_reference at(size_type n) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    // 填充和复制
    void assign(size_type n, const T& value);
    template <class InputIterator>
    void assign(InputIterator first, InputIterator last);
    void assign(std::initializer_list<T> init);

    // 容量和内存
    void reserve(size_type new_cap);
    void shrink_to_fit();

    // 特殊操作
    template <class... Args>
    void emplace_back(Args&&... args);
    void push_back(const T& value);
    void push_back(T&& value);
    template <class... Args>
    void pop_back();

    // 比较
    bool operator==(const vector& other) const;
    bool operator!=(const vector& other) const;
    bool operator<(const vector& other) const;
    bool operator>(const vector& other) const;
    bool operator<=(const vector& other) const;
    bool operator>=(const vector& other) const;

    // allocator
    allocator_type get_allocator() const noexcept;
};
```

### 1.2.关键特性

1. **动态数组**：`std::vector` 内部使用动态数组来存储元素，当元素数量超出当前容量时，会进行扩容操作。
2. **随机访问**：提供了快速的随机访问能力，允许通过下标直接访问元素。
3. **内存连续**：元素在内存中是连续存储的，这使得可以高效地使用缓存，提高访问效率。
4. **可调整大小**：可以在运行时动态调整大小，插入和删除操作可以在尾部高效完成。
5. **异常安全**：大部分操作都是异常安全的，如果操作失败，容器会保持原有的状态不变。

### 1.4.示例代码

以下是一个使用 `std::vector` 的示例：

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 在尾部添加元素
    vec.push_back(6);

    // 访问元素
    std::cout << "Element at index 2: " << vec[2] << std::endl;

    // 遍历 vector
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 删除特定索引的元素
    vec.erase(vec.begin() + 2);

    // 再次遍历 vector
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 1.5.输出结果

```shell
Element at index 2: 3
1 2 3 4 5 6 
1 2 3 4 6 
```

通过这些特性和操作，`std::vector` 提供了一个灵活且高效的动态数组实现，适用于需要随机访问元素和动态调整大小的场景。

## 2.std::vector 的内存管理是如何实现的？

`std::vector` 在 C++ 标准模板库（STL）中是实现动态数组的容器，其内存管理策略如下：

### 2.1. 动态数组

`std::vector` 内部使用一个动态数组来存储元素。这个数组的容量通常比当前存储的元素数量大，以便于在数组末尾添加新元素时避免频繁重新分配内存。

### 2.2. 容量和重新分配

- **容量（Capacity）**：指 `std::vector` 内部分配的存储空间所能容纳的元素数量。
- **大小（Size）**：指 `std::vector` 当前实际包含的元素数量。

当添加元素使 `std::vector` 的大小达到其容量时，`std::vector` 会进行扩容操作：

1. **扩容**：`std::vector` 通常会将容量增加一倍，这是通过分配一块新的更大的内存区域并移动现有元素到新内存来完成的。
2. **复制/移动**：在扩容过程中，现有元素通过复制或移动语义复制到新的内存区域。
3. **释放旧内存**：完成复制后，旧内存会被释放。

### 2.3. 内存分配器

`std::vector` 使用一个分配器（默认为 `std::allocator<T>`）来管理内存分配和释放。分配器封装了内存分配和释放的细节，使得 `std::vector` 的实现可以独立于具体的内存管理策略。

### 2.4. 构造和析构

- **构造**：当 `std::vector` 被构造时，可以指定初始的元素数量和值，或者通过初始化列表、复制或移动构造。
- **析构**：当 `std::vector` 被析构时，其内部的元素会被销毁，内存会被释放。

### 2.5. 内存管理操作

- **`push_back`**：在数组尾部添加元素，如有必要，触发扩容。
- **`pop_back`**：移除数组尾部的元素。
- **`erase`**：删除指定迭代器或迭代器范围内的元素。
- **`clear`**：销毁所有元素，并释放内存。

### 2.6. 异常安全

`std::vector` 的内存管理操作是异常安全的。如果在扩容过程中抛出异常（例如，由于内存不足），`std::vector` 会保证内部状态的一致性，不会泄漏内存。

### 2.7. 示例代码

以下是 `std::vector` 内存管理的简单示例：

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> vec;

    // 添加元素
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }

    // 显示当前容量
    std::cout << "Capacity: " << vec.capacity() << std::endl;

    // 添加更多元素以触发扩容
    for (int i = 10; i < 20; ++i) {
        vec.push_back(i);
    }

    // 显示扩容后的容量
    std::cout << "New Capacity: " << vec.capacity() << std::endl;

    return 0;
}
```

在这个示例中，随着元素的添加，`std::vector` 可能会进行扩容操作，以确保有足够的空间存储新元素。

通过这种方式，`std::vector` 提供了灵活的内存管理，使得动态数组操作非常高效，特别是在需要动态调整大小的场景中。

## 3.std::vector 的内存管理与 C++ 中的其他容器，如 std::list 或 std::deque 相比有何不同？

`std::vector`、`std::list` 和 `std::deque` 都是 C++ 标准模板库中的容器，但它们在内存管理上有着显著的不同。以下是它们之间的主要区别：

### 3.1.`std::vector`

- **连续内存**：`std::vector` 使用一块连续的内存来存储其元素，这使得它能够提供快速的随机访问能力。
- **动态扩容**：当添加元素超出当前容量时，`std::vector` 会进行扩容操作，这通常涉及分配一块新的更大的内存区域，将现有元素复制或移动到新内存，然后释放旧内存。
- **容量管理**：`std::vector` 维护一个容量的概念，该容量通常大于当前元素的数量，以便于在尾部添加元素时避免频繁的内存分配。
- **异常安全性**：`std::vector` 的内存管理操作是异常安全的，如果在扩容过程中发生异常，`std::vector` 会保证不会泄漏内存。

### 3.2.`std::list`

- **非连续内存**：`std::list` 实现了一个双向链表，每个元素可以位于内存中的任何位置，元素之间通过指针连接。
- **节点内元素存储**：每个元素存储在单独的节点中，节点包含数据和用于链接到其他节点的指针。
- **插入和删除高效**：在任意位置插入和删除元素都非常高效，因为这些操作只涉及修改指针，而不需要移动其他元素。
- **内存分配**：`std::list` 在需要时为每个新元素分配内存，通常使用分配器来管理内存。

### 3.3.`std::deque`

- **多个连续内存块**：`std::deque`（双端队列）通常使用多个固定大小的连续内存块来存储元素，这些块称为“chunks”。
- **动态内存块管理**：当元素被添加到 `std::deque` 的末端，且当前内存块已满时，`std::deque` 会分配新的内存块。
- **快速两端操作**：在两端插入和删除元素非常高效，但中间插入和删除可能涉及移动多个元素。
- **迭代器失效**：与 `std::vector` 相比，`std::deque` 的迭代器在插入和删除操作中更容易失效。

### 3.4.总结

- **内存布局**：`std::vector` 使用连续内存，`std::list` 使用分散的内存块通过指针链接，而 `std::deque` 使用多个连续的内存块。
- **内存分配策略**：`std::vector` 采用动态扩容策略，`std::list` 采用按需分配策略，`std::deque` 采用固定大小块的动态分配策略。
- **随机访问**：`std::vector` 提供快速的随机访问，而 `std::list` 和 `std::deque` 不支持快速随机访问。
- **插入和删除效率**：`std::vector` 在尾部插入和删除高效，但在中间插入和删除可能较慢；`std::list` 在任何位置插入和删除都很高效；`std::deque` 在两端插入和删除高效，但在中间插入和删除可能较慢。

根据具体的应用场景，不同的内存管理和性能特点使得这些容器各有优势。

## 4.std::vector 在扩容时通常如何分配新的内存？

`std::vector` 在扩容时的内存分配策略通常是将当前容量增加一倍，这是一种常见的实现方式，虽然不同的标准库实现可能会有所差异。以下是 `std::vector` 扩容过程中内存分配的一般步骤：

1. **计算新容量**：当 `std::vector` 的大小达到当前容量时，它会触发扩容操作。在多数实现中，新容量通常是当前容量的两倍，但这个增长因子不是固定的，有的实现可能会使用其他增长策略。

2. **分配新内存**：`std::vector` 使用其关联的分配器来请求一块新的、更大的内存区域。分配器会负责实际的内存分配工作。

3. **构造新元素**：如果 `std::vector` 存储的是复杂对象，新内存区域会逐个调用对象的构造函数来初始化元素。如果存储的是简单类型（如 `int`、`double` 等），则可能使用值初始化。

4. **复制或移动现有元素**：`std::vector` 会将现有元素从旧内存区域复制或移动到新内存区域。复制或移动操作取决于元素类型是否支持移动语义。

5. **销毁旧元素**：在旧内存区域中的元素会被逐一析构。

6. **释放旧内存**：一旦所有元素都被移动到新内存区域，`std::vector` 会使用分配器释放旧内存区域。

7. **更新迭代器和其他成员**：`std::vector` 会更新其内部的指针和成员变量，以指向新的内存区域，并更新容量和大小等信息。

8. **处理异常**：如果在扩容过程中抛出异常（例如内存分配失败），`std::vector` 必须确保容器处于稳定状态，不会发生内存泄漏。

这个过程是异常安全的。如果新元素的构造或旧元素的移动/复制过程中抛出异常，`std::vector` 会回滚到原来的状态，并释放已经分配的新内存。

以下是扩容操作的示例伪代码：

```cpp
void vector::reserve(size_type new_cap) {
    if (new_cap <= capacity()) return;

    // 分配新内存
    pointer new_data = allocator.allocate(new_cap);

    // 构造新元素
    for (pointer p = data(); p != data() + size(); ++p) {
        allocator.construct(new_data + (p - data()), std::move(*p));
    }

    // 销毁旧元素
    for (pointer p = data(); p != data() + size(); ++p) {
        allocator.destroy(p);
    }

    // 释放旧内存
    allocator.deallocate(data(), capacity());

    // 更新内部状态
    data() = new_data;
    capacity() = new_cap;
}
```

请注意，具体的实现可能会有所不同，取决于标准库的实现细节。

## 5.如何使用std::vector进行高效的数据排序？

使用 `std::vector` 进行高效的数据排序可以通过以下几种方式实现：

### 5.1. 使用标准库排序算法

C++ 标准库提供了 `std::sort` 函数，可以高效地对 `std::vector` 中的数据进行排序。

```cpp
#include <algorithm> // std::sort
#include <vector>
#include <iostream>

int main() {
    std::vector<int> vec = {4, 1, 3, 5, 2};
    std::sort(vec.begin(), vec.end());
    
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

### 5.2. 预分配内存

如果事先知道将要排序的数据量，可以先使用 `vector` 的 `reserve` 方法预分配足够的内存，以避免在添加元素时进行额外的内存分配。

```cpp
std::vector<int> vec;
vec.reserve(1000000); // 假设我们知道有大约1,000,000个元素需要排序
```

### 5.3. 使用自定义比较函数

如果需要按照特定的规则排序，可以向 `std::sort` 传递一个自定义比较函数。

```cpp
struct Compare {
    bool operator()(int lhs, int rhs) const {
        return lhs > rhs; // 降序排序
    }
};

std::vector<int> vec = {4, 1, 3, 5, 2};
std::sort(vec.begin(), vec.end(), Compare());
```

### 5.4. 确保数据局部性

对于大量数据的排序，确保数据在内存中的局部性可以提高缓存命中率，从而提高排序效率。

### 5.5. 使用适当的数据结构

如果排序操作非常频繁，考虑使用可以自排序的数据结构，如 `std::set` 或 `std::map`，它们可以在插入时保持元素有序。

### 5.6. 避免不必要的复制

如果排序后的 `vector` 不再需要原始数据，可以在原地进行排序以避免不必要的数据复制。

### 5.7. 使用并行算法

如果环境支持并发，并有多个处理器可用，可以使用并行算法来加速排序过程。

```cpp
#include <algorithm> // std::sort
#include <vector>
#include <iostream>
#include <execution> // C++17平行算法支持

int main() {
    std::vector<int> vec = {4, 1, 3, 5, 2};
    std::sort(std::execution::par, vec.begin(), vec.end());
    
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

### 5.8. 选择合适的排序算法

对于小型数据集，`std::sort` 默认的快速排序算法可能不是最优的。在这种情况下，可以考虑使用插入排序或其他更适合小数据集的排序算法。

通过使用这些方法，可以确保在使用 `std::vector` 进行排序时实现高效的数据处理。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
