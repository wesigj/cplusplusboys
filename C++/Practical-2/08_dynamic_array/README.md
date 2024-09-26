# C++ Practical-2 day8 动态数组

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.在C++中，除了使用new和delete，还有其他方式可以创建动态数组吗？

在C++中，除了使用`new`和`delete`操作符来创建和销毁动态数组，还有以下几种常见的方法来创建和管理动态数组：

1. **使用`std::vector`**：
   `std::vector`是C++标准库中的一个动态数组容器，它封装了内存管理的细节，提供了动态扩容、元素访问、插入和删除等操作。

   ```cpp
   #include <vector>
   
   std::vector<int> vec;
   vec.push_back(1);
   vec.push_back(2);
   // ...
   ```

2. **使用`std::array`（固定大小）**：
   `std::array`是一个固定大小的数组容器，它存储在栈上，但提供了类似于`std::vector`的接口。

   ```cpp
   #include <array>
   
   std::array<int, 4> arr = {1, 2, 3, 4};
   ```

3. **使用`std::unique_ptr`和自定义删除器**：
   可以使用智能指针`std::unique_ptr`与自定义删除器来管理动态数组。

   ```cpp
   #include <memory>

   std::unique_ptr<int[], void(*)(int*)> uptr(new int[10], [](int* p){ delete[] p; });
   ```

4. **使用`std::shared_ptr`和自定义删除器**：
   类似于`std::unique_ptr`，但`std::shared_ptr`允许多个指针共享同一个动态数组。

   ```cpp
   #include <memory>

   std::shared_ptr<int> sptr(new int[10], [](int* p){ delete[] p; });
   ```

5. **使用`malloc`和`free`**：
   C语言的`malloc`和`free`函数也可以用来分配和释放动态内存。

   ```cpp
   int* arr = (int*)malloc(10 * sizeof(int));
   if (arr != nullptr) {
       // 使用数组...
   }
   free(arr);
   ```

6. **使用`std::allocator`**：
   `std::allocator`是C++标准库中的一个内存分配器，它可以与容器一起使用。

   ```cpp
   #include <memory>

   std::allocator<int> alloc;
   int* arr = alloc.allocate(10);
   // ...
   alloc.deallocate(arr, 10);
   ```

7. **使用`std::make_unique`**：
   `std::make_unique`是一个辅助函数，用于创建`std::unique_ptr`。

   ```cpp
   #include <memory>

   auto uptr = std::make_unique<int[]>(10);
   ```

8. **使用`std::make_shared`**：
   `std::make_shared`是一个辅助函数，用于创建`std::shared_ptr`。

   ```cpp
   #include <memory>

   auto sptr = std::make_shared<int[]>(10);
   ```

9. **使用`std::vector`的`data`成员函数**：
   如果你需要一个指向`std::vector`底层数组的指针，可以使用`data`成员函数。

   ```cpp
   #include <vector>

   std::vector<int> vec(10);
   int* arr = vec.data();
   ```

10. **使用C++17的`std::allocator_traits`**：
    `std::allocator_traits`提供了一种方式来查询和使用分配器的属性和操作。

    ```cpp
    #include <memory>

    template <typename Allocator>
    void deallocate(Allocator& alloc, int* ptr, size_t size) {
        std::allocator_traits<Allocator>::deallocate(alloc, ptr, size);
    }
    ```

在现代C++编程中，推荐使用标准库提供的容器和智能指针，因为它们提供了更好的类型安全性、异常安全性和资源管理。

## 2.动态数组类

在C++中，动态数组通常指的是使用`new`和`delete`操作符动态分配和释放内存的数组。与静态数组（在栈上分配的数组）不同，动态数组的生命周期由程序员控制，可以在运行时确定大小。

以下是如何在C++中实现一个简单的动态数组类：

```cpp
#include <iostream>
#include <algorithm> // for std::copy
#include <cstddef>   // for std::size_t

template <typename T>
class DynamicArray {
private:
    T* data;       // 指向动态分配数组的指针
    std::size_t size;  // 数组中元素的数量

public:
    // 构造函数
    explicit DynamicArray(std::size_t size) : data(new T[size]), size(size) {}

    // 析构函数
    ~DynamicArray() {
        delete[] data;
    }

    // 拷贝构造函数
    DynamicArray(const DynamicArray& other) : data(new T[other.size]), size(other.size) {
        std::copy(other.data, other.data + other.size, data);
    }

    // 移动构造函数
    DynamicArray(DynamicArray&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    // 拷贝赋值运算符
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            data = new T[other.size];
            size = other.size;
            std::copy(other.data, other.data + other.size, data);
        }
        return *this;
    }

    // 移动赋值运算符
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // 获取数组的大小
    std::size_t getSize() const {
        return size;
    }

    // 获取指定索引的元素
    T& operator[](std::size_t index) {
        return data[index];
    }

    // 获取指定索引的元素（const版本）
    const T& operator[](std::size_t index) const {
        return data[index];
    }
};

int main() {
    DynamicArray<int> arr(5); // 创建一个大小为5的动态数组

    for (std::size_t i = 0; i < arr.getSize(); ++i) {
        arr[i] = i * i;
    }

    for (std::size_t i = 0; i < arr.getSize(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在这个例子中，我们定义了一个`DynamicArray`类模板，它封装了动态数组的分配、使用和释放。类中包含了：

- 一个类型为`T*`的私有成员`data`，它指向动态分配的内存。
- 一个`size`成员，记录数组中元素的数量。
- 构造函数和析构函数，分别用于分配和释放内存。
- 拷贝构造函数和拷贝赋值运算符，用于复制数组内容。
- 移动构造函数和移动赋值运算符，用于支持移动语义。
- `getSize`成员函数，返回数组的大小。
- `operator[]`，重载了下标运算符以访问数组元素。

这个简单的动态数组类模板展示了如何管理动态内存。在实际应用中，你可能还需要添加更多的功能，比如动态扩容、插入和删除元素等操作。

## 3.如何实现动态数组的动态扩容功能？

实现动态数组的动态扩容功能通常涉及以下几个步骤：

1. **初始分配**：创建数组时分配初始容量。
2. **检测容量**：在添加元素前检查是否有足够的空间。
3. **扩容**：如果空间不足，分配更大的内存空间。
4. **复制元素**：将旧数组的元素复制到新数组。
5. **释放旧数组**：删除旧数组以避免内存泄漏。

以下是如何在C++中实现一个具有动态扩容功能的动态数组类：

```cpp
#include <iostream>
#include <algorithm> // for std::copy
#include <cstddef>   // for std::size_t

template <typename T>
class DynamicArray {
private:
    T* data;       // 指向动态分配数组的指针
    std::size_t size;  // 当前数组中元素的数量
    std::size_t capacity; // 数组分配的总容量

    void resize(std::size_t newCapacity) {
        T* newData = new T[newCapacity];
        std::copy(data, data + size, newData);
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    // 构造函数
    explicit DynamicArray(std::size_t initialCapacity = 10) : data(new T[initialCapacity]), size(0), capacity(initialCapacity) {}

    // 析构函数
    ~DynamicArray() {
        delete[] data;
    }

    // 禁止拷贝构造函数
    DynamicArray(const DynamicArray&) = delete;

    // 禁止拷贝赋值运算符
    DynamicArray& operator=(const DynamicArray&) = delete;

    // 移动构造函数
    DynamicArray(DynamicArray&& other) noexcept : data(other.data), size(other.size), capacity(other.capacity) {
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    // 移动赋值运算符
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            capacity = other.capacity;
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // 添加元素
    void pushBack(const T& value) {
        if (size == capacity) {
            std::size_t newCapacity = capacity == 0 ? 1 : (capacity * 2);
            resize(newCapacity);
        }
        data[size++] = value;
    }

    // 获取数组的大小
    std::size_t getSize() const {
        return size;
    }

    // 获取指定索引的元素
    T& operator[](std::size_t index) {
        return data[index];
    }

    // 获取指定索引的元素（const版本）
    const T& operator[](std::size_t index) const {
        return data[index];
    }
};

int main() {
    DynamicArray<int> arr;

    for (int i = 0; i < 15; ++i) {
        arr.pushBack(i);
    }

    for (std::size_t i = 0; i < arr.getSize(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 3.1.解释

1. **初始分配**：
   - 构造函数中分配初始容量（默认为10）。

2. **检测容量**：
   - 在`pushBack`方法中，检查当前数组的大小是否等于容量。如果是，则需要扩容。

3. **扩容**：
   - `resize`方法分配新的容量（默认为当前容量的两倍），并将旧数组的元素复制到新数组。

4. **复制元素**：
   - 使用`std::copy`将旧数组的元素复制到新数组。

5. **释放旧数组**：
   - 删除旧数组以避免内存泄漏。

### 3.2.注意事项

- **初始容量**：可以根据需要调整初始容量和扩容策略。
- **异常安全**：在实际应用中，需要考虑异常安全，确保在分配新内存或复制元素时不会发生内存泄漏。
- **内存管理**：确保正确管理内存，避免内存泄漏和野指针。

通过这种方式，你可以实现一个具有动态扩容功能的动态数组类，使其在需要时自动扩展容量。


## 4.动态数组在内存管理方面有哪些潜在的风险，我应该如何避免？

动态数组在内存管理方面主要存在以下潜在风险：

1. **内存泄漏**：如果分配了内存但没有正确释放，会导致内存泄漏。例如，忘记使用 `delete[]` 释放动态数组 。

2. **双重释放**：多次释放同一块内存会导致未定义行为，可能引发程序崩溃。

3. **悬挂指针**：释放内存后没有将指针置为 `nullptr`，使其仍然指向已被释放的内存区域，后续对这片区域的访问是非法的。

4. **越界访问**：在动态分配的内存区域内进行不合法的读写操作，例如索引超出数组边界。

5. **内存分配失败**：`new` 分配内存失败时会抛出 `std::bad_alloc` 异常，而 `malloc` 会返回 `NULL` 指针。如果不正确处理，可能会导致程序异常终止。

6. **内存碎片**：频繁的内存分配和释放可能导致内存碎片，降低内存使用效率。

为了避免这些风险，可以采取以下措施：

1. **使用智能指针**：如 `std::unique_ptr` 和 `std::shared_ptr`，它们可以自动管理内存的释放，避免内存泄漏和悬挂指针 。

2. **确保异常安全**：在动态内存分配时使用异常处理机制，确保即使在异常发生时也能正确释放内存。

3. **使用 RAII 技术**：确保资源在对象生命周期结束时自动释放，这是一种常用的避免资源泄漏的方法。

4. **避免越界访问**：在访问数组元素时，始终检查索引是否在有效范围内。

5. **检查内存分配结果**：每次使用 `new` 或 `malloc` 后，检查返回值是否为空，确保内存分配成功。

6. **内存池**：对于频繁的内存分配和释放，可以使用内存池来减少内存碎片和提高内存分配效率。

7. **使用标准库容器**：如 `std::vector`，它内部管理内存，并提供了自动扩容和缩容的功能，减少了内存管理的复杂性。

通过这些方法，可以有效地管理动态数组的内存，避免常见的内存管理问题，提高程序的稳定性和性能。

## 5.如何使用'std:vector'进行高效的动态数组管理？

`std::vector` 是 C++ 标准库中的一个动态数组容器，它封装了动态内存管理的细节，提供了动态扩容、元素访问、插入和删除等操作。以下是如何使用 `std::vector` 进行高效的动态数组管理的一些关键点：

1. **自动内存管理**：
   `std::vector` 自动管理内存的分配和释放，无需手动使用 `new` 和 `delete`。

2. **动态扩容**：
   当添加元素超出当前容量时，`std::vector` 会自动分配更大的内存空间，并移动现有元素到新内存。

3. **提供异常安全性**：
   如果内存分配失败，`std::vector` 会抛出异常，而不会泄漏内存。

4. **随机访问**：
   `std::vector` 提供了随机访问迭代器，允许快速访问任何元素。

5. **范围检查**：
   使用 `at()` 成员函数可以提供边界检查，当访问超出范围的元素时会抛出 `std::out_of_range` 异常。

6. **迭代器**：
   提供迭代器支持，可以用于循环遍历 `std::vector`。

7. **容量和大小**：
   `size()` 返回当前元素数量，`capacity()` 返回当前分配的内存可以容纳的元素数量。

8. **插入和删除操作**：
   提供 `push_back()`, `pop_back()`, `insert()`, `erase()` 等成员函数进行元素的插入和删除。

9. **内存优化**：
   `shrink_to_fit()` 可以请求减小内存使用量，`reserve()` 可以预先分配足够的内存。

10. **数据访问**：
    使用 `operator[]` 或 `at()` 访问元素，`front()` 和 `back()` 获取首尾元素。

11. **构造和复制**：
    提供拷贝构造函数和拷贝赋值运算符，支持移动语义，使用 `std::move` 进行高效复制。

12. **空值检查**：
    使用 `empty()` 检查 `std::vector` 是否为空。

13. **析构**：
    当 `std::vector` 被销毁时，会自动释放其管理的内存。

以下是一些使用 `std::vector` 的示例代码：

```cpp
#include <vector>
#include <iostream>

int main() {
    // 创建一个空的 vector
    std::vector<int> vec;

    // 添加元素
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    // 访问元素
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    // 插入元素
    vec.insert(vec.begin() + 1, 5);

    // 删除元素
    vec.erase(vec.begin() + 1);

    // 使用迭代器遍历
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 范围检查
    try {
        std::cout << vec.at(10) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    // 内存优化
    vec.shrink_to_fit();

    return 0;
}
```

使用 `std::vector` 可以大大简化动态数组的管理，减少内存泄漏和悬挂指针的风险，并提高代码的可读性和维护性。

## 6.在C++中，'std:unique_ptr'和'std:shared_ptr'在动态数组管理上有什么不同？

在 C++ 中，`std::unique_ptr` 和 `std::shared_ptr` 都是智能指针，用于自动管理动态分配的内存，但它们在管理动态数组时有一些关键的区别：

1. **`std::unique_ptr` 与动态数组**：
   - `std::unique_ptr` 是独占所有权的智能指针，意味着同一时间只能有一个 `std::unique_ptr` 指向特定资源。
   - 它不能被复制，但可以被移动，这允许在不同对象之间传递所有权。
   - `std::unique_ptr` 可以被用来管理动态数组，但需要使用特殊的数组删除器 `std::default_delete`，因为数组的删除需要使用 `delete[]` 而不是 `delete`。
   - 使用 `std::unique_ptr` 管理动态数组时，可以使用 `std::make_unique`（C++14 引入）来创建实例。

   示例：

   ```cpp
   std::unique_ptr<int[]> uptr(new int[10]);
   ```

2. **`std::shared_ptr` 与动态数组**：
   - `std::shared_ptr` 是共享所有权的智能指针，允许多个 `std::shared_ptr` 实例共享同一资源。
   - 它使用引用计数机制来跟踪有多少个 `std::shared_ptr` 实例共享同一个资源。
   - 当最后一个引用被销毁时，资源会被释放。
   - `std::shared_ptr` 也可以管理动态数组，但同样需要使用数组删除器，因为它也需要使用 `delete[]`。
   - `std::shared_ptr` 管理动态数组时，通常需要提供一个自定义删除器。

   示例：

   ```cpp
   std::shared_ptr<int> sptr(new int[10], [](int* p){ delete[] p; });
   ```

### 6.1.主要区别

- **所有权**：
  - `std::unique_ptr` 强调独占所有权，适合于那些不需要共享资源的场景。
  - `std::shared_ptr` 允许多个指针共享同一个资源，适合于资源需要在多个对象间共享的情况。

- **删除器**：
  - `std::unique_ptr` 和 `std::shared_ptr` 在管理动态数组时都需要指定数组删除器，因为默认的删除器是 `delete`，而数组需要 `delete[]`。

- **性能**：
  - `std::unique_ptr` 通常比 `std::shared_ptr` 更轻量级，因为它不涉及引用计数的开销。
  - `std::shared_ptr` 由于需要维护引用计数，所以在性能上可能稍微逊色，尤其是在多线程环境中。

- **线程安全性**：
  - `std::shared_ptr` 的引用计数操作是原子的，适合于多线程环境。
  - `std::unique_ptr` 在多线程环境中使用时，通常不需要考虑线程安全问题，因为它的设计就是用于单线程或所有权明确转移的场景。

- **使用场景**：
  - 当你不需要共享资源时，推荐使用 `std::unique_ptr`，因为它更高效。
  - 当资源需要在多个对象间共享，或者所有权不明确时，使用 `std::shared_ptr`。

在选择使用 `std::unique_ptr` 还是 `std::shared_ptr` 时，应该根据实际的资源管理和所有权需求来决定。

## 7.C++17标准中有哪些新特性可以优化动态数组的内存管理？

在 C++17 标准中，有几个新特性可以优化动态数组的内存管理：

1. **std::shared_ptr 对动态数组的支持**：
   C++17 之前，`std::shared_ptr` 不支持动态数组类型。在 C++17 中，`std::shared_ptr` 可以模板化动态数组，并且可以直接使用数组类型的模板参数。这意味着可以直接创建一个 `std::shared_ptr<int[]>` 来管理动态数组，并且可以使用 `std::shared_ptr` 的内置函数，如 `operator[]` 来访问数组元素。

2. **std::unique_ptr 的改进**：
   `std::unique_ptr` 已经支持动态数组，并且在 C++17 中继续提供对动态数组的优化管理。它确保同一时间只能有一个 `std::unique_ptr` 指向特定资源，从而避免内存泄漏。

3. **std::pmr 内存资源库**：
   C++17 引入了 polymorphic memory resources (PMR)，它是一个多态内存分配器的库，允许开发者自定义内存分配策略，这可以用于优化动态数组的内存管理。

4. **结构化绑定**：
   C++17 引入了结构化绑定，它允许从数组或元组中提取多个成员到不同变量中，这可以简化数组元素的访问和操作。

5. **if 常量表达式**：
   `if constexpr` 允许在编译时根据条件编译代码块，这可以用来优化模板代码中的条件逻辑，包括动态数组的处理。

6. **编译时的类型推导**：
   C++17 允许在函数模板中使用 `auto` 进行类型推导，这简化了模板代码的编写，尤其是在处理动态数组时。

7. **constexpr lambda 表达式**：
   C++17 允许在编译时构建 lambda 表达式，这可以用来创建复杂的编译时计算，包括数组操作。

8. **std::apply**：
   `std::apply` 函数允许调用一个可调用对象，并将一个元组或数组作为参数传递，这可以简化数组或元组的函数调用。

通过这些特性，C++17 提供了更灵活和高效的方式来管理动态数组的内存，同时减少了内存泄漏的风险，并提高了代码的可读性和可维护性。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
