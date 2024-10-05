# C++ STL源码剖析 2-std::deque 双端队列

[TOC]

## Overview

- 双端队列，它支持在序列的前端和后端快速插入和删除元素

---

## 1.std::deque 定义

`std::deque`（double-ended queue，双端队列）是C++标准模板库（STL）中的一个序列容器，定义在`<deque>`头文件中。它支持在序列的前端和后端快速插入和删除元素。

`std::deque`的定义如下：

```cpp
#include <deque>

template <class T, class Allocator = std::allocator<T> >
class deque {
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
    typedef implementation_defined iterator;
    typedef implementation_defined const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    // 构造函数和析构函数
    explicit deque(const Allocator& = Allocator());
    explicit deque(size_type n, const Allocator& = Allocator());
    deque(size_type n, const value_type& value, const Allocator& = Allocator());
    template <class InputIterator>
    deque(InputIterator first, InputIterator last, const Allocator& = Allocator());
    deque(const deque& other);
    deque(deque&& other);
    deque(std::initializer_list<value_type> init, const Allocator& = Allocator());
    ~deque();

    // 赋值运算符
    deque& operator=(const deque& other);
    deque& operator=(deque&& other);
    deque& operator=(std::initializer_list<value_type> init);

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
    size_type size() const noexcept;
    size_type max_size() const noexcept;
    void resize(size_type new_size);
    void resize(size_type new_size, const value_type& x);

    // 修改器
    void clear() noexcept;
    void push_back(const value_type& value);
    void push_back(T&& value);
    template <class... Args>
    void emplace_back(Args&&... args);
    void push_front(const value_type& value);
    void push_front(T&& value);
    template <class... Args>
    void emplace_front(Args&&... args);
    void pop_back();
    void pop_front();

    // 访问器
    reference operator[](size_type n);
    const_reference operator[](size_type n) const;
    reference at(size_type n);
    const_reference at(size_type n) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    // 插入器和移除器
    iterator insert(iterator pos, const value_type& value);
    iterator insert(iterator pos, T&& value);
    template <class... Args>
    iterator emplace(iterator pos, Args&&... args);
    void insert(iterator pos, size_type n, const value_type& value);
    template <class InputIterator>
    void insert(iterator pos, InputIterator first, InputIterator last);
    void insert(iterator pos, std::initializer_list<value_type> ilist);
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);

    // 特殊操作
    void swap(deque& other) noexcept(/* see below */);
};
```

### 1.1.关键点

1. **模板参数**：
   - `T`：存储在`deque`中的元素类型。
   - `Allocator`：分配器类型，默认为`std::allocator<T>`。

2. **类型定义**：
   - `value_type`：元素类型。
   - `allocator_type`：分配器类型。
   - `size_type`：无符号整数类型，用于表示大小。
   - `difference_type`：带符号整数类型，用于表示索引差。
   - `reference`：元素的引用类型。
   - `const_reference`：常量元素的引用类型。
   - `pointer`和`const_pointer`：元素的指针类型。

3. **迭代器**：
   - `iterator`和`const_iterator`：分别表示可变和不可变的迭代器。
   - `reverse_iterator`和`const_reverse_iterator`：分别表示可变和不可变的反向迭代器。

4. **构造函数**：
   - 提供多种构造函数，包括默认构造、指定大小构造、范围构造等。

5. **赋值运算符**：
   - 支持拷贝赋值、移动赋值和初始化列表赋值。

6. **迭代器操作**：
   - 提供`begin()`和`end()`函数来获取迭代器。

7. **容量操作**：
   - 提供`size()`和`max_size()`函数来获取容器的大小。

8. **修改器**：
   - 提供`push_back()`、`push_front()`、`pop_back()`和`pop_front()`函数来在两端添加和删除元素。

9. **访问器**：
   - 提供`operator[]`和`at()`函数来访问元素。

10. **插入器和移除器**：
    - 提供`insert()`和`erase()`函数来插入和删除元素。

11. **特殊操作**：
    - 提供`swap()`函数来交换两个`deque`的内容。

`std::deque`的内部实现通常使用多个固定大小的数组块来存储元素，这些块在需要时动态分配和释放。这种设计使得`std::deque`在两端的插入和删除操作非常高效。

## 2.std::deque 解析

在C++标准模板库（STL）中，`std::deque`（双端队列）是一个容器，它支持高效的元素插入和移除操作，无论是在序列的前端还是后端。`std::deque`的全称是“double-ended queue”，即双端队列。

### 2.1.特点

1. **高效的插入和删除**：可以在序列的前端和后端快速插入和删除元素。
2. **内存分配**：`std::deque`通常使用多个固定大小的数组块来存储元素，这些块在需要时动态分配和释放。
3. **迭代器**：提供随机访问迭代器。
4. **大小**：动态的，可以在运行时改变。
5. **异常安全**：大部分操作都是异常安全的。

### 2.2.常用操作

- `push_back()`: 在序列的末尾添加一个元素。
- `pop_back()`: 移除序列末尾的元素。
- `push_front()`: 在序列的开头添加一个元素。
- `pop_front()`: 移除序列开头的元素。
- `erase()`: 删除指定位置的元素或一系列元素。
- `insert()`: 在指定位置插入一个或多个元素。
- `clear()`: 清空整个容器。
- `size()`: 返回容器中元素的数量。

### 2.3.示例代码

```cpp
#include <iostream>
#include <deque>

int main() {
    std::deque<int> d;

    // 在deque的末尾添加元素
    d.push_back(10);
    d.push_back(20);
    d.push_back(30);

    // 在deque的开头添加元素
    d.push_front(5);
    d.push_front(3);

    // 打印deque中的元素
    std::cout << "Deque contains: ";
    for (int num : d) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 删除deque开头的元素
    d.pop_front();

    // 再次打印deque中的元素
    std::cout << "Deque contains after pop_front: ";
    for (int num : d) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 2.4.输出结果

```shell
Deque contains: 3 5 10 20 30 
Deque contains after pop_front: 5 10 20 30 
```

### 2.5.注意事项

- `std::deque`的随机访问性能可能不如`std::vector`，因为`std::deque`可能由多个数组块组成，随机访问可能需要更多的指针跳转。
- `std::deque`在序列中间插入和删除元素的性能通常不如在两端操作，因为中间操作可能需要移动多个元素。
- `std::deque`的迭代器在插入和删除操作后可能会失效，因此需要谨慎处理迭代器。

`std::deque`适用于需要在序列的两端频繁插入和删除元素的场景，例如实现队列或双端队列的数据结构。

## 3.std::deque 源码剖析

`std::deque`（双端队列）是C++标准模板库（STL）中的一个序列容器，它提供了在两端快速插入和删除元素的能力。`std::deque`的实现通常使用一个或多个动态分配的数组块，这些块可以提高插入和删除操作的效率，尤其是在序列的前端和后端。

以下是`std::deque`的一些关键实现细节：

1. **内存分配**：`std::deque`内部使用一个数组的数组（称为"map"），每个数组块存储固定数量的元素。当需要更多空间时，会分配新的块，并将旧块的元素复制到新块中。这种设计允许在两端快速插入和删除元素，而不需要像`std::vector`那样可能需要复制整个序列。

2. **迭代器**：`std::deque`提供了随机访问迭代器，这意味着你可以像使用`std::vector`一样，通过索引来访问`std::deque`中的元素。

3. **构造函数**：`std::deque`有多个构造函数，包括默认构造、复制构造、移动构造以及使用初始化列表的构造等。

4. **赋值操作**：`std::deque`支持拷贝赋值和移动赋值。

5. **插入和删除操作**：`std::deque`提供了`push_back`、`push_front`、`pop_back`、`pop_front`、`insert`和`erase`等成员函数来修改容器。

6. **容量和大小**：`std::deque`提供了`size`、`max_size`和`resize`等成员函数来处理容器的容量和大小。

7. **特殊操作**：`std::deque`还提供了`swap`和`clear`等成员函数来交换和清除容器内容。

8. **迭代器失效**：在`std::deque`中，插入和删除操作可能会导致迭代器失效，尤其是在序列中间进行操作时。

9. **性能**：`std::deque`在两端的插入和删除操作是高效的，但随机访问性能通常不如`std::vector`。

10. **内存管理**：`std::deque`使用分配器（allocator）来管理内存，这允许使用自定义的内存分配策略。

`std::deque`的实现细节可能会根据不同的编译器和其版本有所不同，但上述提到的是一些普遍的特性和行为。如果你需要查看特定编译器的实现，可以查看编译器的源代码，例如GCC的libstdc++或Clang的libc++。

在实际使用中，`std::deque`非常适合需要在序列两端进行快速插入和删除操作的场景，例如实现队列或双端队列的数据结构。

## 4.如何使用 C++ 标准库中的容器进行高效的数据结构设计？

使用C++标准库中的容器进行高效的数据结构设计，需要根据具体问题选择合适的容器类型，并了解每种容器的特性和适用场景。以下是一些常见容器及其高效使用的方法：

### 4.1. `std::vector`

- **用途**：动态数组，适用于需要随机访问元素的场景。
- **高效使用**：
  - 尽量避免频繁的插入和删除操作，特别是在容器的开始部分。
  - 利用`reserve()`预先分配足够的容量，以减少重新分配内存的次数。
  - 使用`emplace_back()`直接在容器中构造对象，避免额外的拷贝或移动操作。

### 4.2. `std::deque`

- **用途**：双端队列，适用于需要在两端进行插入和删除操作的场景。
- **高效使用**：
  - 利用`push_back()`和`push_front()`在两端快速插入元素。
  - 注意，`std::deque`的中间插入和删除操作可能较慢，因为需要移动元素。

### 4.3. `std::list`

- **用途**：双向链表，适用于需要在序列中间频繁插入和删除的场景。
- **高效使用**：
  - 利用`splice()`高效地合并两个列表或移动元素。
  - 由于没有随机访问能力，避免使用索引访问元素。

### 4.4. `std::forward_list`

- **用途**：单向链表，适用于内存使用非常关键的场景。
- **高效使用**：
  - 与`std::list`类似，但因为是单向链表，所以操作稍微简单一些。
  - 适用于只需要在链表头部或尾部操作的情况。

### 4.5. `std::set` 和 `std::map`

- **用途**：基于红黑树实现的关联容器，适用于需要保持元素有序或快速查找的场景。
- **高效使用**：
  - 利用`lower_bound()`和`upper_bound()`进行范围查找。
  - 使用`insert()`或`emplace()`直接在容器中构造对象。

### 4.6. `std::unordered_set` 和 `std::unordered_map`

- **用途**：基于哈希表实现的关联容器，适用于需要快速插入和查找的场景。
- **高效使用**：
  - 确保一个好的哈希函数以减少冲突。
  - 适当调整装载因子以平衡内存使用和查找性能。

### 4.7. `std::array`

- **用途**：固定大小的数组，适用于数组大小在编译时已知的场景。
- **高效使用**：
  - 利用固定大小的特性进行性能优化。
  - 使用`std::array`的成员函数进行元素访问。

### 4.8. `std::tuple`

- **用途**：存储固定数量的不同类型数据。
- **高效使用**：
  - 使用`std::get<N>()`访问元素，其中`N`是元素的索引。
  - 结合`std::apply()`使用，对元组中的元素应用函数。

### 4.9. `std::optional`

- **用途**：用于表示可选值，即可能存在也可能不存在的值。
- **高效使用**：
  - 避免使用指针来表示可选值，减少空指针检查。
  - 使用`std::make_optional()`来创建对象。

### 4.10. `std::variant`

- **用途**：用于在多种类型中选择一种。
- **高效使用**：
  - 避免使用联合体和`enum`来表示类型标签。
  - 使用`std::visit()`来访问存储的值。

### 4.11其他注意事项

- **迭代器失效**：了解容器操作如何影响迭代器的有效性。
- **异常安全**：确保容器操作不会在抛出异常时导致资源泄露。
- **内存管理**：考虑使用自定义分配器来优化内存使用。

通过了解每种容器的特性和适用场景，并结合上述高效使用的方法，你可以设计出既高效又符合需求的数据结构。

## 5.如何优化 C++ 容器的内存管理以减少内存泄漏的风险？

要优化C++容器的内存管理以减少内存泄漏的风险，可以采取以下措施：

1. **使用智能指针**：利用`std::unique_ptr`、`std::shared_ptr`和`std::weak_ptr`自动管理内存，它们会在适当的时候自动释放内存，从而减少内存泄漏的风险。

2. **遵循RAII原则**：确保资源在对象构造时获取，在对象析构时释放。这样即使发生异常，资源也能得到正确释放，从而避免内存泄漏。

3. **容器管理内存**：使用STL容器（如`std::vector`、`std::list`、`std::map`等）来自动管理内存，避免手动分配和释放内存。

4. **避免裸指针**：尽量不使用裸指针来管理内存。如果必须使用裸指针，请确保在合适的时机使用`delete`或`delete[]`来释放内存。

5. **使用内存池**：对于频繁的小块内存分配和释放，可以使用内存池来管理内存，这样可以减少内存碎片，提高内存分配和释放的效率。

6. **利用标准库算法**：使用标准库提供的算法（如`std::sort`、`std::for_each`等）来操作容器，这些算法不会导致容器内部的内存泄漏。

7. **异常安全**：确保容器操作在异常抛出时仍然安全，避免因异常导致的资源泄露。

8. **定期代码审查**：通过代码审查来识别潜在的内存泄漏问题，并使用内存泄漏检测工具（如 Valgrind、Visual Studio 的内存检测工具等）来测试代码。

9. **避免循环引用**：在使用智能指针时，注意避免循环引用，这会导致引用计数永远不为零，从而造成内存泄漏。

10. **析构函数为虚**：如果你的类继承自某个容器类，确保基类的析构函数为虚，以确保在删除派生类对象时能正确调用基类的析构函数释放资源。

通过这些方法，可以有效地减少内存泄漏的风险，并提高程序的稳定性和可靠性。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
