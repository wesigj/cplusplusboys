# C++ Practical-1 day8

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.STL map

在C++中，`std::map` 是 STL（Standard Template Library，标准模板库）中的一个关联容器，它根据键（Key）来存储和组织数据。`std::map` 是基于红黑树实现的，它保证了元素的有序性，并且提供了对元素的高效访问。

### 1.1.`std::map` 的特点

1. **键值对存储**：`std::map` 存储的数据是键值对（`key-value`）的形式。
2. **自动排序**：键会自动根据比较函数进行排序，默认情况下是升序。
3. **唯一键**：每个键都是唯一的，不允许有重复的键。
4. **对数时间复杂度**：插入、查找和删除操作的时间复杂度为 O(log n)。

### 1.2.`std::map` 的基本操作

- **插入**：`insert` 或 `emplace` 用于添加新的键值对。
- **访问**：使用 `operator[]` 或 `at` 方法访问特定键的值。
- **查找**：使用 `find` 方法查找键是否存在。
- **删除**：使用 `erase` 方法删除特定键的元素。
- **遍历**：使用迭代器遍历 `map`。

### 1.3.示例：使用 `std::map`

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> ageMap;

    // 插入元素
    ageMap["Alice"] = 30;
    ageMap["Bob"] = 25;
    ageMap["Carol"] = 35;

    // 访问元素
    std::cout << "Alice's age: " << ageMap["Alice"] << std::endl;

    // 查找元素
    auto it = ageMap.find("Bob");
    if (it != ageMap.end()) {
        std::cout << "Bob's age: " << it->second << std::endl;
    }

    // 删除元素
    ageMap.erase("Carol");

    // 遍历 map
    for (const auto& pair : ageMap) {
        std::cout << pair.first << " is " << pair.second << " years old." << std::endl;
    }

    return 0;
}
```

### 1.4.注意事项

1. **默认排序**：`std::map` 默认使用 `std::less` 对键进行排序，如果需要自定义排序，可以提供自定义比较函数。

2. **键的类型**：键的类型必须支持比较运算符，且不允许修改键的值。

3. **迭代器**：`std::map` 提供了迭代器，可以用于遍历元素。

4. **异常安全**：`std::map` 的操作通常抛出异常时，容器的状态不会被破坏，可以安全地处理异常。

5. **内存管理**：`std::map` 会自动管理内存，不需要手动分配和释放内存。

`std::map` 是 C++ STL 中非常强大的容器之一，它提供了丰富的接口和高效的操作，适用于需要有序存储和快速查找的场景。

## 2.class template 类模板

在C++中，类模板是一种支持泛型编程的工具，允许开发者创建可在多种数据类型间工作的类。类模板通过在类名前加上尖括号`<>`和参数列表来定义，参数可以是类型、值或其他模板。

### 2.1.定义类模板

```cpp
template <typename T>
class MyClass {
private:
    T data;
public:
    MyClass(T value) : data(value) {}
    T getData() const { return data; }
    void setData(T value) { data = value; }
};
```

### 2.2.使用类模板

```cpp
int main() {
    MyClass<int> intObj(10);
    MyClass<std::string> stringObj("Hello, World!");

    std::cout << "intObj data: " << intObj.getData() << std::endl;
    std::cout << "stringObj data: " << stringObj.getData() << std::endl;

    intObj.setData(20);
    std::cout << "intObj data after update: " << intObj.getData() << std::endl;

    return 0;
}
```

### 2.3.类模板的参数

1. **类型参数**：使用`typename`或`class`关键字（C++11之前使用`class`）。
2. **非类型参数**：可以是整数、枚举、指针大小等。
3. **模板模板参数**：允许模板接受另一个模板作为参数。

### 2.4.非类型模板参数示例

```cpp
template <typename T, int size>
class Array {
private:
    T data[size];
public:
    T& operator[](int index) { return data[index]; }
    const T& operator[](int index) const { return data[index]; }
};
```

### 2.5.模板模板参数示例

```cpp
template <template <typename> class TT>
class Wrapper {
    TT<int> var;
public:
    Wrapper() : var() {}
};

// 使用Wrapper
Wrapper<std::vector> w;
```

### 2.6.类模板的特化

类模板的特化是为特定类型提供特定实现的方式。

```cpp
// 原始模板
template <typename T>
class MyClass {
public:
    void print() { std::cout << "Generic template" << std::endl; }
};

// 特化模板
template <>
class MyClass<int> {
public:
    void print() { std::cout << "Specialized for int" << std::endl; }
};

int main() {
    MyClass<int> intObj;
    MyClass<double> doubleObj;

    intObj.print();   // 输出: Specialized for int
    doubleObj.print(); // 输出: Generic template

    return 0;
}
```

### 2.7.注意事项

1. **代码复用**：类模板允许代码在多种数据类型间复用。
2. **类型安全**：模板参数可以确保类型安全。
3. **性能**：模板在编译时实例化，不会产生运行时开销。
4. **特化和偏特化**：可以为特定类型或模板参数提供特化版本。
5. **编译分离**：模板定义通常放在头文件中，因为它们在编译时需要对每个使用点都是可见的。

类模板是C++泛型编程的核心，它们提供了一种强大的方式来编写通用且类型安全的代码。

## 3.类模板来创建一个通用的排序算法

在C++中，可以使用类模板和函数模板来创建一个通用的排序算法。以下是一个简单的示例，展示了如何使用模板来实现一个基本的冒泡排序算法：

### 3.1.冒泡排序算法的模板实现

```cpp
#include <iostream>
#include <vector>
#include <functional> // For std::less

// 模板函数，用于交换元素
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// 模板函数，实现冒泡排序
template <typename T, typename Compare = std::less<>>
void bubbleSort(T& arr, Compare comp = Compare()) {
    bool swapped = true;
    int n = arr.size();
    while (swapped) {
        swapped = false;
        for (int i = 1; i < n; ++i) {
            if (comp(arr[i - 1], arr[i])) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        --n; // 最大元素已经排在正确的位置
    }
}

int main() {
    std::vector<int> vec = { 5, 3, 8, 4, 2 };
    bubbleSort(vec);
    std::cout << "Sorted vector: ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::vector<std::string> vecStr = { "z", "a", "k", "m" };
    bubbleSort(vecStr, std::greater<>());
    std::cout << "Sorted vector: ";
    for (const auto& str : vecStr) {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在这个示例中，`bubbleSort`函数模板接受一个引用到排序数组的参数和一个比较函数，默认使用`std::less`，这意味着排序是升序的。如果你想降序排序，可以提供`std::greater`作为比较函数。

### 3.2.注意事项

1. **模板参数**：`T`代表数组或容器的元素类型，`Compare`是一个比较函数类型，默认为`std::less<>`。

2. **交换元素**：`swap`函数模板用于交换两个元素的值。

3. **比较函数**：`comp`是一个比较函数，用于比较两个元素的大小。

4. **算法逻辑**：冒泡排序算法的逻辑是重复地遍历数组，比较相邻的元素，并在需要时交换它们。

5. **性能**：冒泡排序的平均和最坏情况时间复杂度都是O(n^2)，对于大数据集来说效率不高。

6. **稳定性**：冒泡排序是一种稳定的排序算法，相同值的元素的相对顺序在排序后保持不变。

7. **通用性**：通过使用模板，这个排序算法可以用于任何可比较的数据类型。

这个通用的排序算法示例展示了如何使用模板来创建灵活且通用的代码。在实际应用中，你可能会使用更高效的排序算法，如快速排序、归并排序或STL中的`std::sort`。

## 4.类模板实现一个稳定的排序算法

在C++中，实现一个稳定的排序算法通常意味着排序后相等的元素应该保持它们原始的顺序。归并排序（Merge Sort）是一种时间复杂度为O(n log n)且稳定的排序算法。以下是使用类模板实现归并排序的示例：

### 4.1.归并排序算法的模板实现

```cpp
#include <iostream>
#include <vector>
#include <algorithm> // For std::copy

// 辅助函数，用于合并两个已排序的子数组
template <typename T>
void merge(T *begin, T *mid, T *end, T *temp) {
    int i = 0, j = 0, k = 0;
    while (begin + i < mid && mid + j < end) {
        if (*(begin + i) <= *(mid + j)) {
            temp[k++] = *(begin + i++);
        } else {
            temp[k++] = *(mid + j++);
        }
    }
    while (begin + i < mid) {
        temp[k++] = *(begin + i++);
    }
    while (mid + j < end) {
        temp[k++] = *(mid + j++);
    }
    std::copy(temp, temp + k, begin);
}

// 归并排序的递归函数
template <typename T>
void mergeSort(T *begin, T *end, T *temp) {
    if (end - begin <= 1) {
        return;
    }
    T *mid = begin + (end - begin) / 2;
    mergeSort(begin, mid, temp);
    mergeSort(mid, end, temp);
    merge(begin, mid, end, temp);
}

// 归并排序的模板类
template <typename T>
class MergeSorter {
public:
    void sort(T *array, int size) {
        T *temp = new T[size];
        mergeSort(array, array + size, temp);
        delete[] temp;
    }
};

int main() {
    std::vector<int> vec = {5, 3, 8, 4, 2, 3, 1};
    MergeSorter<int> sorter;
    sorter.sort(vec.data(), vec.size());
    std::cout << "Sorted vector: ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    MergeSorter<std::string> string_sorter;

    std::vector<std::string> vecStr = {"z", "a", "k", "m", "a", "z"};
    string_sorter.sort(vecStr.data(), vecStr.size());
    std::cout << "Sorted vector: ";
    for (const auto &str : vecStr) {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    return 0;
}

```

在这个示例中，`MergeSorter`类模板包含一个`sort`成员函数，它接受一个数组和数组的大小，然后使用归并排序算法对数组进行排序。`merge`函数模板用于合并两个已排序的子数组，而`mergeSort`递归函数用于递归地将数组分成更小的部分并排序。

### 4.2.注意事项

1. **稳定性**：归并排序通过将相等元素保持在原始顺序来确保稳定性。

2. **递归**：归并排序算法是递归的，它将数组分成两半，直到每一半只有一个元素，然后开始合并。

3. **临时数组**：归并排序需要一个临时数组来合并子数组。在排序完成后，临时数组被释放。

4. **性能**：归并排序的时间复杂度为O(n log n)，这使得它比冒泡排序等简单排序算法更适合处理大数据集。

5. **内存使用**：归并排序需要与输入数组大小相同的额外内存。

6. **泛型编程**：通过使用模板，归并排序算法可以用于任何可比较的数据类型。

归并排序是实现稳定排序的一个很好的选择，特别是当你需要处理大量数据时。在实际应用中，C++标准库提供的`std::sort`函数是一个高效的通用排序算法，它通常使用快速排序、堆排序或插入排序的混合实现，并且是稳定的。

## 5.类模板实现栈

让我们更详细地探讨如何使用类模板实现一个通用的栈（Stack）数据结构，并提供更多的功能和注释。

### 5.1.扩展的栈类模板实现

```cpp
#include <iostream>
#include <vector>
#include <stdexcept> // For std::out_of_range
#include <iterator>  // For std::begin, std::end

// 栈的模板类定义
template <typename T>
class Stack {
private:
    std::vector<T> elements; // 使用标准库中的vector来存储栈元素

public:
    // 默认构造函数
    Stack() = default;

    // 构造函数，接受一个初始化列表
    Stack(std::initializer_list<T> init) : elements(init) {}

    // 将元素压入栈顶
    void push(const T& element) {
        elements.push_back(element);
    }

    // 移除栈顶元素
    void pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::pop(): empty stack");
        }
        elements.pop_back();
    }

    // 获取栈顶元素
    T top() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::top(): empty stack");
        }
        return elements.back();
    }

    // 检查栈是否为空
    bool isEmpty() const {
        return elements.empty();
    }

    // 获取栈的大小
    size_t size() const {
        return elements.size();
    }

    // 获取栈的容量
    size_t capacity() const {
        return elements.capacity();
    }

    // 清空栈
    void clear() {
        elements.clear();
    }

    // 交换两个栈的内容
    void swap(Stack& other) {
        elements.swap(other.elements);
    }

    // 迭代器支持
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    iterator begin() {
        return elements.begin();
    }

    const_iterator begin() const {
        return elements.begin();
    }

    iterator end() {
        return elements.end();
    }

    const_iterator end() const {
        return elements.end();
    }
};

int main() {
    Stack<int> intStack;
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);

    std::cout << "Top of stack: " << intStack.top() << std::endl; // 应该输出 3

    intStack.pop();
    std::cout << "New top of stack: " << intStack.top() << std::endl; // 应该输出 2

    std::cout << "Stack size: " << intStack.size() << std::endl; // 应该输出 2

    // 使用迭代器遍历栈
    std::cout << "Stack contents: ";
    for (const auto& value : intStack) {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    // 清空栈
    intStack.clear();
    std::cout << "Stack size after clear: " << intStack.size() << std::endl; // 应该输出 0

    return 0;
}
```

### 5.2.代码解释

1. **成员变量**：
   - `elements`：一个`std::vector<T>`，用于存储栈中的元素。

2. **构造函数**：
   - 默认构造函数使用默认实现。
   - 一个构造函数接受一个初始化列表，允许在创建栈时使用花括号初始化。

3. **成员函数**：
   - `push`：将一个元素添加到栈的顶部。
   - `pop`：移除栈顶的元素。如果栈为空，则抛出`std::out_of_range`异常。
   - `top`：返回栈顶的元素，但不移除它。如果栈为空，则抛出`std::out_of_range`异常。
   - `isEmpty`：检查栈是否为空。
   - `size`：返回栈中元素的数量。
   - `capacity`：返回栈的容量，即`vector`可以存储的元素数量而不需要重新分配内存。
   - `clear`：清空栈中的所有元素。
   - `swap`：交换两个栈的内容。

4. **迭代器支持**：
   - 提供了迭代器支持，允许使用范围基于的`for`循环或其他算法来遍历栈。

5. **异常处理**：
   - 在`pop`和`top`函数中，如果栈为空，则抛出异常，这是一种常见的错误处理方式。

6. **模板类型**：
   - 模板参数`T`允许栈存储任何类型的数据。

7. **容器选择**：
   - 使用`std::vector`作为底层容器，但它不是实现栈的唯一选择。你也可以使用`std::list`或`std::deque`。

8. **常量成员函数**：
   - `top`和`isEmpty`被声明为`const`成员函数，因为它们不会修改对象的状态。

通过使用类模板，这个栈实现可以用于任何数据类型，并且提供了一个类型安全的通用接口。在实际应用中，你可以根据需要添加更多的功能。

## 6.类模板与多线程

要在C++中使用类模板实现一个通用的栈，并确保其在多线程环境中是线程安全的，你需要考虑以下几点：

1. **互斥锁（Mutex）**：使用互斥锁来保护栈的操作，确保在多线程环境中对栈的访问是互斥的。

2. **条件变量（Condition Variables）**：在某些情况下，你可能需要使用条件变量来同步线程。

3. **原子操作（Atomic Operations）**：对于简单的数据操作，可以考虑使用原子操作来保证操作的原子性。

以下是一个简单的线程安全的栈实现示例：

```cpp
#include <iostream>
#include <vector>
#include <mutex>
#include <stdexcept>

template <typename T>
class ThreadSafeStack {
private:
    std::vector<T> data;
    mutable std::mutex mutex;

public:
    ThreadSafeStack() = default;

    // 将元素压入栈顶
    void push(const T& element) {
        std::lock_guard<std::mutex> lock(mutex);
        data.push_back(element);
    }

    // 移除栈顶元素
    void pop() {
        std::lock_guard<std::mutex> lock(mutex);
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::pop(): empty stack");
        }
        data.pop_back();
    }

    // 获取栈顶元素
    T top() const {
        std::lock_guard<std::mutex> lock(mutex);
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::top(): empty stack");
        }
        return data.back();
    }

    // 检查栈是否为空
    bool isEmpty() const {
        std::lock_guard<std::mutex> lock(mutex);
        return data.empty();
    }

    // 获取栈的大小
    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex);
        return data.size();
    }
};

int main() {
    ThreadSafeStack<int> intStack;

    // 启动多个线程来操作栈
    // ...

    return 0;
}
```

在这个示例中，我们使用了`std::mutex`来保护栈的操作。每次对栈的操作（如`push`、`pop`、`top`等）都会先获取互斥锁，确保同一时间只有一个线程可以操作栈。

### 6.1.注意事项

1. **锁的粒度**：锁的粒度越小，性能越好，但实现越复杂。在上述示例中，我们使用了`std::lock_guard`来自动管理锁的获取和释放。

2. **死锁**：在多线程环境中，需要小心避免死锁的发生。确保在所有情况下锁都能被正确释放。

3. **性能**：频繁的锁定和解锁可能会影响性能。在高并发环境下，可能需要更高级的同步机制，如无锁编程技术。

4. **异常处理**：在多线程环境中，需要考虑异常处理。确保在抛出异常之前释放锁。

5. **测试**：多线程程序的测试通常比单线程程序更复杂。确保对多线程代码进行充分的测试。

通过使用模板，这个线程安全的栈实现可以用于任何数据类型，并且提供了一个类型安全的通用接口。在实际应用中，你可以根据需要添加更多的功能。

## 7.类模板实现队列

探讨如何使用类模板实现一个通用的队列数据结构，并提供更多的功能和注释。

### 7.1.扩展的队列类模板实现

```cpp
#include <iostream>
#include <deque>
#include <stdexcept>
#include <iterator>

// 队列的模板类定义
template <typename T>
class Queue {
private:
    std::deque<T> elements; // 使用标准库中的deque来存储队列元素

public:
    // 默认构造函数
    Queue() = default;

    // 构造函数，接受一个初始化列表
    Queue(std::initializer_list<T> init) : elements(init) {}

    // 将元素添加到队列尾部
    void enqueue(const T& element) {
        elements.push_back(element);
    }

    // 移除队列头部的元素
    void dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("Queue<>::dequeue(): empty queue");
        }
        elements.pop_front();
    }

    // 获取队列头部的元素
    T front() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue<>::front(): empty queue");
        }
        return elements.front();
    }

    // 获取队列尾部的元素
    T back() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue<>::back(): empty queue");
        }
        return elements.back();
    }

    // 检查队列是否为空
    bool isEmpty() const {
        return elements.empty();
    }

    // 获取队列的大小
    size_t size() const {
        return elements.size();
    }

    // 清空队列
    void clear() {
        elements.clear();
    }

    // 交换两个队列的内容
    void swap(Queue& other) {
        elements.swap(other.elements);
    }

    // 迭代器支持
    using iterator = typename std::deque<T>::iterator;
    using const_iterator = typename std::deque<T>::const_iterator;

    iterator begin() {
        return elements.begin();
    }

    const_iterator begin() const {
        return elements.begin();
    }

    iterator end() {
        return elements.end();
    }

    const_iterator end() const {
        return elements.end();
    }
};

int main() {
    Queue<int> intQueue;

    intQueue.enqueue(1);
    intQueue.enqueue(2);
    intQueue.enqueue(3);

    std::cout << "Queue front: " << intQueue.front() << std::endl; // 应该输出 1
    std::cout << "Queue back: " << intQueue.back() << std::endl; // 应该输出 3

    intQueue.dequeue();
    std::cout << "New queue front after one dequeue: " << intQueue.front() << std::endl; // 应该输出 2

    std::cout << "Queue size: " << intQueue.size() << std::endl; // 应该输出 2

    // 使用迭代器遍历队列
    std::cout << "Queue contents: ";
    for (const auto& value : intQueue) {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    // 清空队列
    intQueue.clear();
    std::cout << "Queue size after clear: " << intQueue.size() << std::endl; // 应该输出 0

    return 0;
}
```

### 7.2.代码解释

1. **成员变量**：
   - `elements`：一个`std::deque<T>`，用于存储队列中的元素。

2. **构造函数**：
   - 默认构造函数使用默认实现。
   - 一个构造函数接受一个初始化列表，允许在创建队列时使用花括号初始化。

3. **成员函数**：
   - `enqueue`：将一个元素添加到队列的尾部。
   - `dequeue`：移除队列头部的元素。如果队列为空，则抛出`std::out_of_range`异常。
   - `front`：返回队列头部的元素，但不移除它。如果队列为空，则抛出`std::out_of_range`异常。
   - `back`：返回队列尾部的元素，但不移除它。如果队列为空，则抛出`std::out_of_range`异常。
   - `isEmpty`：检查队列是否为空。
   - `size`：返回队列中元素的数量。
   - `clear`：清空队列中的所有元素。
   - `swap`：交换两个队列的内容。

4. **迭代器支持**：
   - 提供了迭代器支持，允许使用范围基于的`for`循环或其他算法来遍历队列。

5. **异常处理**：
   - 在`dequeue`、`front`和`back`函数中，如果队列为空，则抛出异常，这是一种常见的错误处理方式。

6. **模板类型**：
   - 模板参数`T`允许队列存储任何类型的数据。

7. **容器选择**：
   - 使用`std::deque`作为底层容器，但它不是实现队列的唯一选择。你也可以使用`std::list`或`std::vector`。

8. **常量成员函数**：
   - `front`、`back`和`isEmpty`被声明为`const`成员函数，因为它们不会修改对象的状态。

通过使用类模板，这个队列实现可以用于任何数据类型，并且提供了一个类型安全的通用接口。在实际应用中，你可以根据需要添加更多的功能。

## 8.template max 模板 最大值

在C++中，如果你想编写一个模板函数来获取两个值中的最大值，你可以使用`std::max`函数，这是标准库提供的一个模板函数。但如果你想自己实现一个模板函数来获取最大值，以下是一个简单的示例：

```cpp
#include <iostream>

// 模板函数，用于获取两个值中的最大值
template <typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    int i = 5;
    int j = 10;
    std::cout << "Max of " << i << " and " << j << " is " << max(i, j) << std::endl;

    double f = 5.5;
    double g = 10.7;
    std::cout << "Max of " << f << " and " << g << " is " << max(f, g) << std::endl;

    return 0;
}
```

在这个示例中，`max`函数模板接受两个参数`a`和`b`，并返回较大的那个。它使用了`>`运算符来比较两个值，并使用了三元运算符`? :`来选择返回值。

### 8.1.注意事项

1. **类型限制**：`max`函数模板适用于所有支持`>`运算符的类型。

2. **标准库函数**：实际上，C++标准库已经提供了`std::max`函数，因此通常不需要自己实现。

3. **模板推导**：当使用模板函数时，编译器会自动推导出模板参数的类型。

4. **常量表达式**：如果你的编译器支持C++14或更高版本，你可以使用`constexpr`关键字来定义`max`函数，使其可以在编译时计算常量表达式。

如果你想使用标准库的`std::max`函数，以下是如何使用它的示例：

```cpp
#include <iostream>
#include <algorithm> // 包含std::max

int main() {
    int i = 5;
    int j = 10;
    std::cout << "Max of " << i << " and " << j << " is " << std::max(i, j) << std::endl;

    double f = 5.5;
    double g = 10.7;
    std::cout << "Max of " << f << " and " << g << " is " << std::max(f, g) << std::endl;

    return 0;
}
```

在这个示例中，我们直接使用了`std::max`函数来获取两个值中的最大值。这是推荐的方式，因为它是标准库的一部分，经过了优化和测试。

## 9.template conversion 模板 转化

在C++中，模板特化（Template Specialization）是一种为特定类型提供特定实现的方式。这允许你定制模板类或模板函数的行为，以适应特定的数据类型。

### 9.1.类模板特化

类模板特化是在模板定义的基础上，为特定的类型参数提供不同的实现。

- **示例：特化一个类模板**

```cpp
#include <iostream>

// 普通模板定义
template <typename T>
class MyClass {
public:
    void display() {
        std::cout << "Generic template" << std::endl;
    }
};

// 类模板特化
template <>
class MyClass<int> {
public:
    void display() {
        std::cout << "Specialized for int" << std::endl;
    }
};

// 类模板部分特化
template <typename T>
class MyClass<T*> {
public:
    void display() {
        std::cout << "Specialized for pointer" << std::endl;
    }
};

int main() {
    MyClass<double> myClassDouble;
    myClassDouble.display(); // 输出: Generic template

    MyClass<int> myClassInt;
    myClassInt.display(); // 输出: Specialized for int

    MyClass<char*> myClassCharPtr;
    myClassCharPtr.display(); // 输出: Specialized for pointer

    return 0;
}
```

在这个例子中，我们有一个通用的`MyClass`模板，然后为`int`类型提供了一个特化的实现。此外，我们还提供了一个部分特化，用于所有指针类型。

### 9.2.函数模板特化

函数模板特化允许你为特定的类型参数提供特定的函数实现。

- **示例：特化一个函数模板**

```cpp
#include <iostream>

// 普通模板定义
template <typename T>
void print(T value) {
    std::cout << "Generic template: " << value << std::endl;
}

// 函数模板特化，针对 int 类型
template <>
void print<int>(int value) {
    std::cout << "Specialized for int: " << value << std::endl;
}

// 函数模板特化，针对 const char* 类型
template <>
void print<const char*>(const char* value) {
    std::cout << "Specialized for const char*: " << value << std::endl;
}

// 函数模板特化，针对 char* 类型
template <>
void print<char*>(char* value) {
    std::cout << "Specialized for char*: " << value << std::endl;
}

int main() {
    print(3.14);       // 输出: Generic template: 3.14
    print(42);         // 输出: Specialized for int: 42
    print("Hello");    // 输出: Specialized for const char*: Hello

    char greeting[] = "Hi";
    print(greeting);   // 输出: Specialized for char*: Hi

    return 0;
}
```

在这个例子中，我们为`print`函数模板提供了一个通用实现，然后为`int`类型提供了一个特化的实现。此外，我们还提供了一个部分特化，用于引用类型。

### 9.3.注意事项

1. **特化和重载**：特化是为特定类型提供定制实现，而重载是为不同参数提供多个实现。

2. **特化和偏特化**：特化是为特定类型提供实现，而偏特化是为模板参数的某些值提供实现。

3. **特化和继承**：特化不应该与继承混淆。特化是模板概念，而继承是类概念。

4. **编译器查找**：当模板实例化时，编译器会查找最适合的特化版本。

5. **头文件**：特化通常应该放在头文件中，因为它们需要在每次模板实例化时都是可见的。

6. **链接问题**：由于特化可能在多个编译单元中定义，确保特化的定义在所有编译单元中都是一致的，以避免链接问题。

通过使用模板特化，你可以为特定类型提供优化的实现，从而提高代码的性能和灵活性。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
