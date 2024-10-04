# C++ STL源码剖析 8-iterator

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.iterator 定义

在 C++ 标准模板库（STL）中，迭代器是一种抽象概念，用于提供对容器内元素的访问。迭代器可以视为指向容器中某个位置的指针，它封装了访问容器元素的方法。

迭代器定义了对容器元素进行遍历、访问、插入和删除等操作的方式。STL 定义了多种迭代器类别，每种类别具有不同的能力和效率：

### 1.1.迭代器类别

1. **输入迭代器（Input Iterators）**：
   - 只能单向遍历容器。
   - 只能进行一次读取操作。
   - 不支持 `operator[]`。

2. **输出迭代器（Output Iterators）**：
   - 只能单向遍历容器。
   - 只能进行一次写入操作。

3. **前向迭代器（Forward Iterators）**：
   - 支持向前遍历。
   - 可以进行多次读取或写入操作。

4. **双向迭代器（Bidirectional Iterators）**：
   - 支持向前和向后遍历。

5. **随机访问迭代器（Random Access Iterators）**：
   - 支持在容器中任意位置快速访问（如数组索引）。
   - 支持所有的迭代器操作，包括 `operator[]`、`++`、`--` 等。

### 1.2.迭代器Traits

迭代器通常与类型特征（Type Traits）一起使用，以提供关于迭代器类型的信息。以下是一个迭代器 Traits 的示例定义：

```cpp
#include <iterator>
#include <type_traits>

// 迭代器 Traits 示例
template <typename Iterator>
struct iterator_traits {
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using pointer = typename std::iterator_traits<Iterator>::pointer;
    using reference = typename std::iterator_traits<Iterator>::reference;
    using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
};
```

### 1.3.定义迭代器

迭代器通常由容器提供，以下是定义一个简单迭代器的示例：

```cpp
template <typename T>
class MyContainer {
    T* data;
    size_t size;

public:
    class iterator {
        T* ptr;

    public:
        iterator(T* p) : ptr(p) {}
        T& operator*() const { return *ptr; }
        T* operator->() const { return ptr; }
        iterator& operator++() { ++ptr; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
        bool operator==(const iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }
    };

    iterator begin() const { return iterator(data); }
    iterator end() const { return iterator(data + size); }
};

MyContainer<int> myContainer = { /* ... */ };
for (auto it = myContainer.begin(); it != myContainer.end(); ++it) {
    // 使用 *it 访问元素
}
```

在这个示例中，我们定义了一个简单的容器 `MyContainer`，它包含一个简单的迭代器类。迭代器类提供了 `operator*`、`operator->`、`operator++` 和比较运算符等方法。

### 1.4.注意事项

- 迭代器应该遵循 STL 迭代器的设计原则，以确保与 STL 算法的兼容性。
- 迭代器的实现应该考虑异常安全性和有效性。
- 迭代器的复制和赋值应该正确处理迭代器的状态。

通过使用迭代器，我们可以编写通用的代码来遍历和操作各种类型的容器。

## 2.如何使用迭代器遍历 STL 容器？

在 C++ 中，迭代器提供了一种标准的方法来遍历 STL 容器，如 `std::vector`、`std::list`、`std::map` 等。以下是如何使用迭代器遍历 STL 容器的示例：

### 2.1.使用迭代器遍历 `std::vector`

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 使用迭代器遍历 vector
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " "; // 访问迭代器指向的元素
    }
    std::cout << std::endl;

    // 使用 auto 关键字简化类型
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 使用范围 for 循环 (C++11 及以上)
    for (auto& value : vec) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 2.2.使用迭代器遍历 `std::list`

```cpp
#include <iostream>
#include <list>

int main() {
    std::list<int> lst = {1, 2, 3, 4, 5};

    // 使用迭代器遍历 list
    for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 使用 auto 关键字简化类型
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 使用范围 for 循环 (C++11 及以上)
    for (auto& value : lst) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 2.3.使用迭代器遍历 `std::map`

```cpp
#include <iostream>
#include <map>

int main() {
    std::map<std::string, int> mp = {{"apple", 1}, {"banana", 2}, {"cherry", 3}};

    // 使用迭代器遍历 map
    for (std::map<std::string, int>::iterator it = mp.begin(); it != mp.end(); ++it) {
        std::cout << it->first << " : " << it->second << std::endl; // 使用 -> 访问成员
    }

    // 使用 auto 关键字简化类型
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        std::cout << it->first << " : " << it->second << std::endl;
    }

    // 使用范围 for 循环 (C++11 及以上)
    for (const auto& pair : mp) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }

    return 0;
}
```

### 2.4.注意事项

1. **迭代器的解引用**：使用 `*it` 来解引用迭代器并访问其指向的元素。
2. **成员访问**：对于 `std::map` 和 `std::pair` 等容器，使用 `it->first` 和 `it->second` 来访问成员。
3. **迭代器的增加**：使用 `++it` 来移动迭代器到下一个元素。
4. **范围 for 循环**：C++11 引入的范围 for 循环提供了一种更简洁的遍历容器的方法。
5. **使用 `auto`**：使用 `auto` 关键字可以简化迭代器的类型声明。

通过使用迭代器，我们可以编写通用的代码来遍历不同的 STL 容器，而不需要关心底层数据结构的细节。

## 3.如何使用迭代器在 STL 容器中进行元素的添加和删除操作？

在 STL 容器中使用迭代器进行元素的添加和删除操作是常见的任务。以下是一些基本操作的示例：

### 3.1.添加元素

#### 3.1.1.使用 `push_back` 和 `push_front`（针对序列容器）

```cpp
#include <iostream>
#include <vector>
#include <list>

int main() {
    // 对于 vector
    std::vector<int> vec = {1, 2, 3};
    vec.push_back(4); // 添加元素到末尾

    // 对于 list
    std::list<int> lst = {1, 2, 3};
    lst.push_back(4); // 添加元素到末尾
    lst.push_front(0); // 添加元素到开头

    return 0;
}
```

#### 3.1.2.使用 `insert`

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 4, 5};
    auto it = std::find(vec.begin(), vec.end(), 3); 

    // 在迭代器指向的位置之前插入元素
    if (it!= vec.end()) {
        vec.insert(it, 3);
    } else {
        // 如果没找到要插入的位置，将元素插入到末尾
        vec.push_back(3);
    }

    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 3.2.删除元素

#### 3.2.1.使用 `erase`

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 删除元素 3
    auto it = std::find(vec.begin(), vec.end(), 3);
    if (it != vec.end()) {
        vec.erase(it);
    }

    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 删除区间 [2, 4)
    vec.erase(vec.begin() + 1, vec.begin() + 3);

    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 3.3.注意事项

1. **添加元素**：对于序列容器（如 `std::vector`、`std::deque`、`std::list`），可以使用 `push_back` 和 `push_front` 在序列的开头或末尾添加元素。使用 `insert` 成员函数可以在任意位置插入元素。

2. **删除元素**：使用 `erase` 成员函数可以删除迭代器指向的元素，或者删除迭代器指定的区间内的元素。

3. **性能考虑**：对于 `std::vector` 和 `std::string` 等连续存储的容器，非末尾位置的插入和删除操作可能导致大量元素的移动，从而影响性能。对于 `std::list` 和 `std::forward_list` 等非连续存储的容器，插入和删除操作通常更高效。

4. **迭代器失效**：在插入和删除操作之后，指向被操作元素的迭代器可能会失效。因此，通常建议在执行插入和删除操作后重新获取迭代器。

5. **返回值**：`insert` 函数返回一个指向插入元素的迭代器。

通过使用迭代器，我们可以灵活地在 STL 容器中添加和删除元素，同时保持代码的通用性和效率。

## 4.在C++中，如何定义一个自定义迭代器？

在 C++ 中，定义一个自定义迭代器需要实现一组标准的迭代器操作和类型定义。自定义迭代器通常是为了与标准库算法一起工作或为自定义容器提供迭代功能。

以下是定义自定义迭代器的基本步骤：

### 4.1. 定义迭代器类

自定义迭代器类需要至少部分实现以下操作和类型：

- `value_type`：迭代器访问元素的类型。
- `difference_type`：表示迭代器之间距离的带符号整数类型。
- `pointer`：指向 `value_type` 的指针类型。
- `reference`：迭代器访问元素的引用类型。
- `iterator_category`：迭代器的类别（如 `std::input_iterator_tag`、`std::forward_iterator_tag` 等）。

### 4.2. 实现迭代器操作

迭代器类需要实现以下操作：

- 构造函数
- 解引用操作符 `operator*`
- 递增操作符 `operator++`
- 相等比较操作符 `operator==`
- 不等比较操作符 `operator!=`

### 4.3.示例代码

以下是为一个简单的数组类定义自定义迭代器的示例：

```cpp
#include <iostream>
#include <iterator>
#include <cstddef>

// 自定义容器
class Array {
    int* data_;
    size_t size_;

public:
    Array(size_t size) : data_(new int[size]), size_(size) {}
    ~Array() { delete[] data_; }

    // 元素访问
    int& operator[](size_t index) { return data_[index]; }
    const int& operator[](size_t index) const { return data_[index]; }

    // 迭代器支持
    class iterator {
        int* ptr_;

    public:
        iterator(int* ptr) : ptr_(ptr) {}
        iterator& operator++() { ++ptr_; return *this; }
        int& operator*() const { return *ptr_; }
        bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }

        // 用于 std::iterator_traits
        using iterator_category = std::random_access_iterator_tag;
        using value_type = int;
        using difference_type = std::ptrdiff_t;
        using pointer = int*;
        using reference = int&;
    };

    iterator begin() const { return iterator(data_); }
    iterator end() const { return iterator(data_ + size_); }
};

int main() {
    Array arr(5);

    // 使用自定义迭代器
    for (Array::iterator it = arr.begin(); it != arr.end(); ++it) {
        *it = 1; // 设置所有元素为 1
    }

    // 验证结果
    for (Array::iterator it = arr.begin(); it != arr.end(); ++it) {
        std::cout << *it << " "; // 应该输出 "1 1 1 1 1"
    }
    std::cout << std::endl;

    return 0;
}
```

### 4.4.解释

1. **自定义容器 `Array`**：
   - 一个简单的动态数组类，具有基本的构造函数、析构函数和元素访问操作符。

2. **自定义迭代器**：
   - 实现了递增操作符 `operator++`、解引用操作符 `operator*`、相等比较操作符 `operator==` 和不等比较操作符 `operator!=`。
   - 定义了迭代器的类别 `iterator_category` 为 `std::random_access_iterator_tag`，表示迭代器支持随机访问。

3. **迭代器支持**：
   - `begin` 和 `end` 成员函数返回指向数组开始和结束的迭代器。

4. **使用自定义迭代器**：
   - 在 `main` 函数中，使用自定义迭代器遍历 `Array` 类的实例，并设置所有元素的值为 `1`。

通过这种方式，您可以为自定义容器实现自定义迭代器，从而提供灵活的元素访问和操作。

## 5.在C++中，自定义迭代器的迭代器类别有哪些，它们有什么区别？

在 C++ 中，迭代器类别定义了迭代器支持的操作集合。STL 使用迭代器类别来决定如何有效地遍历容器。以下是 C++ 中常见的迭代器类别以及它们的区别：

1. **输入迭代器（Input Iterators）**：
   - 只能单向遍历容器。
   - 只能对每个元素进行一次读取操作。
   - 不支持 `operator[]`。
   - 例子：`std::istream_iterator`。

2. **输出迭代器（Output Iterators）**：
   - 只能单向遍历容器。
   - 只能对每个元素进行一次写入操作。
   - 例子：`std::ostream_iterator`。

3. **前向迭代器（Forward Iterators）**：
   - 支持至少一次向前遍历。
   - 可以进行多次读取或写入操作。
   - 不支持向后遍历或随机访问。
   - 例子：`std::list` 的迭代器。

4. **双向迭代器（Bidirectional Iterators）**：
   - 支持向前和向后遍历。
   - 可以进行多次读取或写入操作。
   - 不支持随机访问。
   - 例子：`std::set` 和 `std::map` 的迭代器。

5. **随机访问迭代器（Random Access Iterators）**：
   - 支持在容器中任意位置快速访问。
   - 支持所有的迭代器操作，包括 `operator[]`、`++`、`--` 等。
   - 可以进行高效的索引访问和距离计算。
   - 例子：`std::vector` 和 `std::deque` 的迭代器。

### 5.1.区别

- **遍历方向**：输入迭代器只能向前遍历，双向迭代器支持向前和向后遍历，而随机访问迭代器可以在任意位置访问。
- **读写次数**：输入迭代器和输出迭代器通常只允许对每个元素进行一次操作，而前向迭代器和双向迭代器允许多次操作。
- **性能**：随机访问迭代器提供了最快的访问速度，因为它们允许直接通过索引访问元素。
- **操作支持**：不同类别的迭代器支持的操作不同，例如，只有随机访问迭代器支持 `operator[]`。

### 5.2.实现自定义迭代器类别

以下是如何为自定义迭代器指定迭代器类别的示例：

```cpp
template <typename T>
class MyContainer {
public:
    // 迭代器定义
    class iterator {
        T* ptr;
    public:
        iterator(T* p) : ptr(p) {}
        iterator& operator++() { ++ptr; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
        T& operator*() const { return *ptr; }
        T* operator->() const { return ptr; }
        bool operator==(const iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }

        // 指定迭代器类别为随机访问迭代器
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
    };

    // 迭代器访问
    iterator begin() const { return iterator(data); }
    iterator end() const { return iterator(data + size); }
    
private:
    T* data;
    size_t size;
};
```

在这个示例中，我们定义了一个 `MyContainer` 的迭代器，并指定其迭代器类别为 `std::random_access_iterator_tag`，这意味着它支持随机访问。

通过正确指定迭代器类别，您可以确保 STL 算法和函数正确、高效地与您的自定义迭代器一起工作。

## 6.在定义自定义迭代器时，有哪些常见的错误我需要避免？

在定义自定义迭代器时，确实存在一些常见的错误和陷阱，你应该避免这些以确保迭代器的正确性和效率。以下是一些你应该避免的常见错误：

### 6.1. **不完整的迭代器接口**

自定义迭代器至少需要实现以下操作：

- 构造函数
- `operator*`（解引用操作符）
- `operator++`（前置递增操作符）
- `operator==` 和 `operator!=`（等于和不等于操作符）

如果你的迭代器不支持这些基本操作，它可能无法与 STL 算法正常工作。

### 6.2. **错误的迭代器类别**

迭代器类别告诉 STL 算法你的迭代器能做什么。如果错误地指定了迭代器类别，可能会导致算法表现不佳或行为不正确。例如，将迭代器类别错误地标记为 `std::random_access_iterator_tag`，而迭代器实际上不支持随机访问，会导致问题。

### 6.3. **未处理迭代器失效的情况**

在容器修改（如插入或删除元素）后，指向已修改元素的迭代器可能会失效。确保你的容器在修改操作后使相关的迭代器失效，并提供一种方式来获取新的有效迭代器。

### 6.4. **不支持迭代器比较**

如果迭代器不支持比较操作（`operator==` 和 `operator!=`），在某些算法中可能会导致问题，特别是在需要检查迭代器是否相等时。

### 6.5. **未定义 `operator->`**

对于需要通过迭代器访问成员的场景，如果你的迭代器没有实现 `operator->`，那么用户将无法使用 `it->member` 语法。

### 6.6. **未考虑线程安全**

在多线程环境中，迭代器可能需要特别的处理来保证线程安全。如果多个线程同时访问和修改容器，迭代器的实现需要确保迭代器的一致性和稳定性。

### 6.7. **性能问题**

- **无效率的迭代器操作**：例如，对于需要线性时间复杂度的迭代器递增操作，如果可以通过更简单的方式实现，就应该优化。
- **不必要的数据复制**：在迭代器的复制和赋值操作中，确保只复制必要的数据。

### 8. **违反迭代器的通用约定**

例如，前置递增（`operator++`）和后置递增（`operator++(int)`）的行为应该符合用户的预期，前置递增应该返回递增后的迭代器，而后置递增应该返回递增前的迭代器。

### 示例：修正迭代器定义

以下是一个修正后的迭代器定义示例，考虑了上述一些常见错误：

```cpp
template <typename T>
class MyContainer {
public:
    class iterator {
        T* ptr_;
    public:
        iterator(T* ptr) : ptr_(ptr) {}

        // 解引用
        T& operator*() const { return *ptr_; }
        T* operator->() const { return ptr_; }

        // 递增
        iterator& operator++() { ++ptr_; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

        // 相等和不等比较
        bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }

        // 迭代器类别
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
    };

    // 迭代器访问
    iterator begin() const { return iterator(data_); }
    iterator end() const { return iterator(data_ + size_); }

private:
    T* data_;
    size_t size_;
};
```

确保你的迭代器实现考虑了所有基本操作，并正确指定了迭代器类别，以避免常见的迭代器错误。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
