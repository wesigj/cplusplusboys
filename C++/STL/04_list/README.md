# C++ STL源码剖析 4-std::list

[TOC]

## Overview

---

## 1.list 定义

在C++标准模板库（STL）中，`std::list` 是一个双向链表的容器。它允许在序列的任何位置高效地插入和删除元素。`std::list` 提供了链表的灵活性和动态大小的特性，同时支持快速的插入和删除操作。

以下是 `std::list` 的定义和关键特性：

### 1.1.定义和特性

1. **模板类**：`std::list` 是一个模板类，可以存储任何数据类型。
2. **双向链表**：内部使用双向链表实现，每个元素都有一个前驱指针和一个后继指针。
3. **内存分配**：动态分配内存以存储元素，可以在运行时动态增加和减少大小。
4. **迭代器**：提供双向迭代器，支持正向和反向遍历。
5. **无随机访问**：不支持像 `std::vector` 那样的随机访问，访问元素只能通过迭代器遍历。
6. **空间效率**：由于需要存储额外的指针，相比 `std::vector` 或 `std::deque` 占用更多的内存。

### 1.2.头文件

```cpp
#include <list>
```

### 1.3.基本定义

```cpp
template <class T, class Allocator = std::allocator<T> >
class list {
public:
    // 类型定义
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef std::allocator_traits<Allocator> allocator_traits_type;

    // 迭代器类型
    typedef implementation_defined iterator;
    typedef implementation_defined const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    // 构造函数和析构函数
    explicit list(const Allocator& = Allocator());
    explicit list(size_type n, const Allocator& = Allocator());
    list(size_type n, const value_type& value, const Allocator& = Allocator());
    template <class InputIterator>
    list(InputIterator first, InputIterator last, const Allocator& = Allocator());
    list(const list& other);
    list(list&& other);
    list(std::initializer_list<value_type> init, const Allocator& = Allocator());

    // 析构函数
    ~list();

    // 赋值运算符
    list& operator=(const list& other);
    list& operator=(list&& other);
    list& operator=(std::initializer_list<value_type> init);

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
    size_type size() const;
    size_type max_size() const;
    void resize(size_type new_size);
    void resize(size_type new_size, const value_type& x);

    // 修改器
    void clear() noexcept;
    iterator insert(iterator pos, const value_type& value);
    iterator insert(iterator pos, value_type&& value);
    template <class... Args>
    iterator emplace(iterator pos, Args&&... args);
    void insert(iterator pos, size_type n, const value_type& value);
    template <class InputIterator>
    void insert(iterator pos, InputIterator first, InputIterator last);
    void insert(iterator pos, std::initializer_list<value_type> ilist);
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);
    void swap(list& other) noexcept;

    // 访问器
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    void push_front(const value_type& value);
    void push_front(value_type&& value);
    template <class... Args>
    void emplace_front(Args&&... args);
    void pop_front();
    void push_back(const value_type& value);
    void push_back(value_type&& value);
    template <class... Args>
    void emplace_back(Args&&... args);
    void pop_back();

    // 排序和比较
    void sort();
    template <class Compare>
    void sort(Compare comp);
    void merge(list& other);
    void merge(list&& other);
    template <class Compare>
    void merge(list& other, Compare comp);
    template <class Compare>
    void merge(list&& other, Compare comp);
    void splice(iterator pos, list& other);
    void splice(iterator pos, list&& other);
    iterator splice(iterator pos, list& other, iterator i);
    iterator splice(iterator pos, list&& other, iterator i);
    iterator splice(iterator pos, list& other, iterator first, iterator last);
    iterator splice(iterator pos, list&& other, iterator first, iterator last);
    template <class Compare>
    void splice(iterator pos, list& other, iterator i, Compare comp);
    template <class Compare>
    void splice(iterator pos, list& other, iterator first, iterator last, Compare comp);
    template <class Compare>
    void splice(iterator pos, list&& other, iterator i, Compare comp);
    template <class Compare>
    void splice(iterator pos, list&& other, iterator first, iterator last, Compare comp);
    void remove(const value_type& value);
    template <class UnaryPredicate>
    void remove_if(UnaryPredicate pred);
    void unique();
    template <class BinaryPredicate>
    void unique(BinaryPredicate pred);
    void reverse() noexcept;

    // 特殊操作
    allocator_type get_allocator() const noexcept;
};
```

### 1.4.关键特性

1. **构造函数**：支持默认构造、指定大小构造、范围构造、拷贝构造、移动构造和初始化列表构造。
2. **赋值运算符**：支持拷贝赋值、移动赋值和初始化列表赋值。
3. **迭代器**：提供正向和反向迭代器，支持正向和反向遍历。
4. **容量**：提供`empty()`、`size()`和`max_size()`函数来获取容器的状态。
5. **修改器**：提供`clear()`、`insert()`、`emplace()`、`erase()`和`swap()`等函数来修改容器。
6. **访问器**：提供`front()`和`back()`函数来访问首尾元素，以及`push_front()`、`push_back()`、`pop_front()`和`pop_back()`等函数来添加和删除元素。
7. **排序和比较**：提供`sort()`、`merge()`、`splice()`、`remove()`、`unique()`和`reverse()`等函数来操作链表。
8. **特殊操作**：提供`get_allocator()`函数来获取分配器。

### 1.5.示例代码

以下是一个使用 `std::list` 的示例：

```cpp
#include <iostream>
#include <list>

int main() {
    std::list<int> lst = {1, 2, 3, 4, 5};

    // 插入元素
    lst.push_front(0);
    lst.push_back(6);

    // 遍历列表
    for (int num : lst) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 删除元素
    lst.remove(3);

    // 再次遍历列表
    for (int num : lst) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 1.6.输出结果

```shell
0 1 2 4 5 6 
0 1 2 4 5 6 
```

通过这些特性和操作，`std::list` 提供了一个灵活且高效的双向链表实现，适用于需要在序列中间频繁插入和删除元素的场景。

## 2.std::list 在 C++ 中的内存管理是如何实现的？

`std::list` 在 C++ 标准模板库（STL）中是一个双向链表容器，它的内存管理主要通过以下方式实现：

### 2.1. 节点结构

`std::list` 的每个元素都存储在单独的节点中。每个节点至少包含三部分：

- 用户数据（即模板参数 `T` 的实例）
- 两个指针，分别指向前一个节点和后一个节点

这种结构使得在链表的任何位置插入和删除节点都可以非常高效地完成，因为这些操作只涉及节点指针的修改，而不需要移动其他数据。

### 2.2. 动态内存分配

`std::list` 使用动态内存分配来创建和销毁节点。当执行插入操作而需要更多节点时，`std::list` 会请求分配器（默认为 `std::allocator<T>`）分配新的节点。当节点不再需要时（如删除操作或容器被销毁时），`std::list` 会返回这些节点的内存给分配器。

### 2.3. 分配器

`std::list` 接受一个分配器模板参数，通常使用 `std::allocator<T>`。分配器负责节点的内存分配和释放。通过使用不同的分配器，可以定制内存管理策略，例如使用内存池来减少碎片或提高分配速度。

### 2.4. 内存管理操作

- **插入操作**：当在 `std::list` 中插入新元素时，如果需要新节点，`std::list` 会调用分配器来分配内存，并构造节点中的对象。
- **删除操作**：当从 `std::list` 中删除元素时，会调用对象的析构函数（如果对象有的话），然后释放节点占用的内存。
- **移动操作**：`std::list` 提供了移动语义，这意味着它可以接收一个将要被销毁的 `std::list` 的所有权，避免复制数据。

### 2.5. 内存回收

`std::list` 并不像 `std::vector` 那样保留已分配的内存，当内存不再需要时，它立即返回内存给分配器。这意味着 `std::list` 不需要像 `std::vector` 那样进行复杂的内存重新分配。

### 2.6. 异常安全

`std::list` 的操作通常具有强异常安全性。在插入或删除操作过程中，如果发生异常（如分配内存失败），`std::list` 会保证容器处于一致的状态，不会泄露内存。

### 2.7.示例代码

以下是 `std::list` 内存管理的简单示例：

```cpp
#include <list>
#include <memory>

int main() {
    std::list<int> lst;
    
    // 插入元素，动态分配内存
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    // 删除元素，释放内存
    lst.pop_back();

    // 清空列表，释放所有内存
    lst.clear();

    return 0;
}
```

在这个示例中，`std::list` 动态地分配和释放内存来存储整数。当列表不再需要时，`clear()` 方法会释放所有分配的内存。

通过这种方式，`std::list` 提供了灵活的内存管理，使得链表操作非常高效，尤其是在需要频繁插入和删除的场景中。

## 3.如何使用自定义分配器来优化 std::list 的内存管理？

在C++中，`std::list`使用的是标准分配器`std::allocator`，但可以通过自定义分配器来优化其内存管理。自定义分配器可以提供更高效的内存分配和释放机制，例如使用内存池来减少频繁的小块内存分配和释放的开销。

### 3.1.如何使用自定义分配器

1. **定义自定义分配器**：创建一个继承自`std::allocator`的模板类，并重写`allocate`和`deallocate`方法。

   ```cpp
   template <typename T>
   class MyAllocator : public std::allocator<T> {
   public:
       using typename std::allocator<T>::size_type;
       using typename std::allocator<T>::pointer;
       
       template <class U>
       struct rebind {
           typedef MyAllocator<U> other;
       };

       pointer allocate(size_type n, const void* hint = 0) {
           // 实现自定义的内存分配逻辑
           return static_cast<pointer>(malloc(n * sizeof(T)));
       }

       void deallocate(pointer p, size_type n) {
           // 实现自定义的内存释放逻辑
           free(p);
       }
   };
   ```

2. **使用自定义分配器**：在创建`std::list`时，指定自定义分配器作为第二个模板参数。

   ```cpp
   std::list<int, MyAllocator<int>> my_list;
   ```

### 3.2.优化策略

1. **内存池**：实现一个内存池分配器，预先分配大块内存，并从中分配和回收小块内存，减少系统调用。

2. **对象池**：对于特定类型的对象，可以使用对象池来管理对象的创建和销毁，提高效率。

3. **减少锁竞争**：在多线程环境中，可以通过实现无锁或减少锁使用的分配器来提高并发性能。

4. **内存对齐**：合理地对齐内存可以提高内存访问效率。

5. **监控和调优**：使用性能分析工具监控内存分配和释放的性能，根据分析结果进行调优。

### 3.3.示例

以下是一个使用自定义分配器的`std::list`示例：

```cpp
#include <list>
#include <memory>

template <typename T>
class MyAllocator : public std::allocator<T> {
public:
    using typename std::allocator<T>::size_type;
    using typename std::allocator<T>::pointer;

    template <class U>
    struct rebind {
        typedef MyAllocator<U> other;
    };

    pointer allocate(size_type n, const void* hint = 0) {
        // 实现自定义的内存分配逻辑
        return static_cast<pointer>(malloc(n * sizeof(T)));
    }

    void deallocate(pointer p, size_type n) {
        // 实现自定义的内存释放逻辑
        free(p);
    }
};

int main() {
    std::list<int, MyAllocator<int>> my_list;
    my_list.push_back(1);
    my_list.push_back(2);
    my_list.push_back(3);

    return 0;
}
```

通过这种方式，你可以为你的`std::list`提供一个高效的内存管理策略，从而优化程序的性能。

## 4.如何确保自定义分配器的内存分配和释放操作是线程安全的？

要确保自定义分配器在多线程环境中的内存分配和释放操作是线程安全的，可以采取以下措施：

1. **使用互斥锁**：在分配器的`allocate`和`deallocate`方法中使用互斥锁，确保同一时间只有一个线程可以执行这些操作。这可以防止多个线程同时修改分配器的内部状态，从而避免数据竞争和不一致性问题。

2. **无锁编程**：如果可能，可以使用无锁编程技术，如原子操作（`std::atomic`），来管理内存分配和释放。无锁编程可以减少锁的开销，提高性能。

3. **内存池**：实现一个内存池分配器，预先分配一大块内存，并从中分配和回收小块内存。这样可以减少系统调用的次数，提高内存分配的效率。

4. **线程局部存储**：使用线程局部存储（`thread_local`）为每个线程提供一个独立的内存池，这样可以避免多个线程之间的竞争。

5. **异常安全**：确保分配器的操作是异常安全的，即使在抛出异常的情况下也不会泄露内存或留下不一致的状态。

6. **同步原语**：使用同步原语（如互斥量、信号量、临界区等）来控制对共享资源的访问。

7. **避免虚假唤醒**：在使用条件变量时，要注意虚假唤醒的问题，始终在循环中检查条件是否满足。

8. **测试和验证**：使用多线程测试工具和压力测试来验证分配器在多线程环境中的行为，确保没有死锁、竞态条件或内存泄漏。

9. **资源管理**：使用RAII（资源获取即初始化）原则来管理资源，确保资源在构造函数中获取，在析构函数中释放。

10. **文档和代码审查**：编写清晰的文档，说明分配器的线程安全策略，并进行代码审查以确保实现的正确性。

通过这些方法，可以设计和实现一个线程安全的自定义分配器，从而在多线程程序中安全地管理内存。

## 5.如何使用std:：list进行高效的数据删除操作？

`std::list` 是 C++ 标准模板库中的一个容器，它实现了一个双向链表。由于其结构特点，`std::list` 在进行数据删除操作时非常高效，特别是针对非连续的内存空间或者需要从中间删除元素的情况。以下是一些使用 `std::list` 进行高效数据删除操作的技巧：

1. **使用迭代器直接删除**：
   当你需要删除特定的元素时，可以直接使用迭代器来删除。`std::list` 允许你通过迭代器来擦除元素。

   ```cpp
   std::list<int> lst = {1, 2, 3, 4, 5};
   auto it = std::find(lst.begin(), lst.end(), 3);
   if (it != lst.end()) {
       lst.erase(it);
   }
   ```

2. **删除特定区间的元素**：
   如果你需要删除一个区间内的多个元素，可以一次调用 `erase` 来删除整个区间，而不是一个接一个地删除。

   ```cpp
   std::list<int> lst = {1, 2, 3, 4, 5, 6};
   lst.erase(lst.begin(), std::next(lst.begin(), 3)); // 删除前三个元素
   ```

3. **使用 `remove` 若无删除**：
   如果你想删除满足特定条件的所有元素，可以使用 `remove` 成员函数，然后调用 `pop_back` 来删除那些元素。`remove` 函数将条件不满足的元素移到容器的末端，并返回新的逻辑结尾迭代器。

   ```cpp
   std::list<int> lst = {1, 2, 3, 4, 5, 3, 2};
   lst.remove(3);  // 移除所有值为3的元素
   ```

4. **使用 `unique` 后删除**：
   如果列表中存在连续重复的元素，并且你想要删除这些重复的元素，可以使用 `unique` 成员函数，然后调用 `pop_back` 来删除那些元素。`unique` 会移除所有除了第一个之外的连续重复元素。

   ```cpp
   std::list<int> lst = {1, 2, 2, 3, 3, 3, 4};
   lst.unique();  // 移除连续重复元素
   ```

5. **清空整个列表**：
   如果你需要删除所有元素，使用 `clear` 函数是最高效的。

   ```cpp
   std::list<int> lst = {1, 2, 3, 4, 5};
   lst.clear();  // 清空整个列表
   ```

6. **考虑使用 `splice`**：
   `splice` 可以用来将另一个 `std::list` 的元素移动到当前列表，或者将当前列表的一部分移动到另一个列表。这种方式不涉及删除操作，但可以重新排列元素。

   ```cpp
   std::list<int> lst1 = {1, 2, 3};
   std::list<int> lst2 = {4, 5, 6};
   lst1.splice(lst1.end(), lst2);  // 将lst2的所有元素移动到lst1的末尾
   ```

7. **避免频繁的删除操作**：
   尽管 `std::list` 在删除操作上非常高效，但如果有大量的删除操作，性能仍然可能受到影响。如果可能，考虑批量处理或重新设计数据结构。

8. **使用 `reverse_iterator`**：
   如果你需要从末尾开始删除元素，使用 `reverse_iterator` 可以更高效。

   ```cpp
    std::list<int> lst = {1, 2, 3, 4, 5};
    auto rit = std::find(lst.rbegin(), lst.rend(), 3);  // 在反向迭代器范围内查找
    if (rit != lst.rend()) {
        // 将反向迭代器转换为正向迭代器，以调用erase()
        auto it = std::prev(lst.end(), (rit - lst.rbegin()));
        lst.erase(it);
    }
   ```

    在提供的代码片段中，试图使用 `std::list` 的反向迭代器来查找值为 `3` 的元素，并将其删除。

    1. `rit` 已经是 `std::find` 的结果，所以不需要再赋值。

    2. `std::find` 返回的是找到的元素的反向迭代器，如果找到了的话。如果没有找到，则返回 `lst.rend()`。

    3. 在 `if` 语句中，我们检查 `rit` 是否不等于 `lst.rend()`，以确定是否找到了值为 `3` 的元素。

    4. 如果找到了，我们需要将反向迭代器 `rit` 转换为对应的正向迭代器，才能使用 `erase` 方法删除元素。我们通过计算 `rit` 与 `lst.rbegin()` 之间的距离，然后使用 `std::prev` 从 `lst.end()` 向后移动相应的距离来获得对应的正向迭代器。

    5. 最后，我们调用 `lst.erase(it);` 来删除找到的元素。

    反向迭代器的索引计算可能有些复杂，因此通常更简单的方法是将反向迭代器转换为正向迭代器，然后进行删除操作。

    这段代码在找到值为 `3` 的元素后将其从列表中删除。如果列表中存在多个 `3`，则只会删除第一个找到的 `3`。

使用这些技巧可以确保在使用 `std::list` 时，数据删除操作尽可能高效。

## 6.在使用 std::list 时，如何避免内存泄漏？

在使用 `std::list`（或任何动态数据结构）时，避免内存泄漏主要依赖于正确管理内存分配和释放。`std::list` 容器会自动管理其元素的内存，但在某些情况下，你可能需要额外注意以确保没有内存泄漏。以下是一些避免内存泄漏的建议：

1. **使用值类型**：如果你存储在 `std::list` 中的对象是指向动态分配内存的指针，确保在删除元素时相应地释放内存。

    ```cpp
    std::list<int*> list;
    list.push_back(new int(42)); // 错误：存储了动态分配的指针

    // 正确的做法是存储对象而非指针
    std::list<int> list;
    list.push_back(42);
    ```

2. **使用智能指针**：如果 `std::list` 存储了指向动态分配内存的智能指针，如 `std::unique_ptr` 或 `std::shared_ptr`，智能指针会自动为你管理内存。

    ```cpp
    #include <memory>
    std::list<std::unique_ptr<int>> list;
    list.push_back(std::make_unique<int>(42));
    ```

3. **确保容器本身被正确销毁**：当 `std::list` 被销毁时，其元素也会自动被销毁。确保没有悬垂引用指向已被销毁的 `std::list` 对象。

4. **使用 `clear` 方法**：在 `std::list` 不再需要时，使用 `clear` 方法来清除所有元素，然后销毁容器本身。

    ```cpp
    std::list<int> myList;
    // ...
    myList.clear(); // 清除所有元素
    ```

5. **避免手动内存操作**：尽量不要手动在 `std::list` 中进行内存分配和释放操作，除非你有特定的内存管理需求。

6. **使用容器的析构函数**：当 `std::list` 对象的生命周期结束时（例如，离开其作用域），其析构函数会被调用，元素会被自动销毁。

7. **注意循环引用**：如果 `std::list` 存储的对象之间存在循环引用，考虑使用 `std::weak_ptr` 来打破循环。

8. **定期检查**：使用内存泄漏检测工具（如 Valgrind、Visual Leak Detector）定期检查你的程序，以确保没有内存泄漏。

9. **遵循 RAII 原则**：确保资源的获取即是初始化，这样可以保证在对象生命周期结束时资源被正确释放。

10. **避免在容器中存储裸指针**：裸指针不会自动释放内存，存储在容器中的裸指针可能导致内存泄漏。

通过遵循这些建议，你可以最大限度地减少使用 `std::list` 时发生内存泄漏的风险。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
