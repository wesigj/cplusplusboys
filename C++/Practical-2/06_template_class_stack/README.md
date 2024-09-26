# C++ Practical-2 day6 类模板之栈

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.类模板之栈

在C++中，使用类模板来实现一个栈（Stack）是一种常见的做法，因为它可以提供类型安全和灵活性。下面是一个简单的栈类模板的实现：

```cpp
#include <iostream>
#include <stdexcept> // for std::out_of_range

template <typename T>
class Stack {
private:
    // 使用动态数组来存储栈的元素
    T* elements;
    size_t size;
    size_t capacity;

    // 动态数组扩容函数
    void resize() {
        capacity = (capacity == 0) ? 1 : (capacity * 2);
        T* newElements = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
    }

public:
    // 构造函数
    Stack() : size(0), capacity(0), elements(nullptr) {}

    // 析构函数
    ~Stack() {
        delete[] elements;
    }

    // 拷贝构造函数
    Stack(const Stack& other) : size(other.size), capacity(other.capacity) {
        elements = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            elements[i] = other.elements[i];
        }
    }

    // 赋值运算符
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            delete[] elements;
            size = other.size;
            capacity = other.capacity;
            elements = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                elements[i] = other.elements[i];
            }
        }
        return *this;
    }

    // 检查栈是否为空
    bool isEmpty() const {
        return size == 0;
    }

    // 获取栈的大小
    size_t getSize() const {
        return size;
    }

    // 入栈操作
    void push(const T& element) {
        if (size == capacity) {
            resize();
        }
        elements[size++] = element;
    }

    // 出栈操作
    void pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::pop(): empty stack");
        }
        elements[--size] = T();
    }

    // 获取栈顶元素
    T& top() {
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::top(): empty stack");
        }
        return elements[size - 1];
    }

    // 获取栈顶元素（const版本）
    const T& top() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::top(): empty stack");
        }
        return elements[size - 1];
    }
};

int main() {
    Stack<int> intStack;
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);

    std::cout << "Top element: " << intStack.top() << std::endl; // 输出 3

    intStack.pop();
    std::cout << "New top element: " << intStack.top() << std::endl; // 输出 2

    return 0;
}
```

这个栈类模板实现了基本的栈操作，包括入栈（push）、出栈（pop）、获取栈顶元素（top）、检查栈是否为空（isEmpty）以及获取栈的大小（getSize）。它使用动态数组来存储元素，并在需要时自动扩容。

请注意，这个实现是一个简单的示例，实际应用中可能需要更多的错误检查和优化。

## 2.如何为这个栈类模板添加一个迭代器接口？

为栈类模板添加迭代器接口，首先需要定义一个迭代器类，该类能够遍历栈中的元素。由于栈的特性是后进先出（LIFO），迭代器通常不是栈数据结构的一部分，但为了演示如何实现，我们可以添加一个简单的迭代器。

下面是一个简单的迭代器实现：

```cpp
#include <iostream>
#include <stdexcept> // for std::out_of_range

template <typename T>
class Stack {
private:
    T* elements;
    size_t size;
    size_t capacity;

    void resize() {
        capacity = (capacity == 0) ? 1 : (capacity * 2);
        T* newElements = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
    }

public:
    Stack() : size(0), capacity(0), elements(nullptr) {}
    ~Stack() {
        delete[] elements;
    }
    Stack(const Stack& other) : size(other.size), capacity(other.capacity) {
        elements = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            elements[i] = other.elements[i];
        }
    }
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            delete[] elements;
            size = other.size;
            capacity = other.capacity;
            elements = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                elements[i] = other.elements[i];
            }
        }
        return *this;
    }

    bool isEmpty() const {
        return size == 0;
    }

    size_t getSize() const {
        return size;
    }

    void push(const T& element) {
        if (size == capacity) {
            resize();
        }
        elements[size++] = element;
    }

    void pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::pop(): empty stack");
        }
        elements[--size] = T();
    }

    T& top() {
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::top(): empty stack");
        }
        return elements[size - 1];
    }

    const T& top() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::top(): empty stack");
        }
        return elements[size - 1];
    }

    // 迭代器接口
    class Iterator {
    private:
        const Stack* stack;
        size_t index;

    public:
        Iterator(const Stack* s, size_t idx) : stack(s), index(idx) {}

        T& operator*() const {
            return stack->elements[index];
        }

        T* operator->() const {
            return &stack->elements[index];
        }

        Iterator& operator++() {
            if (index > 0) index--;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return index == other.index && stack == other.stack;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

    Iterator begin() const {
        return Iterator(this, size - 1);
    }

    Iterator end() const {
        return Iterator(this, -1);
    }
};

int main() {
    Stack<int> intStack;
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);

    std::cout << "Stack elements: ";
    for (Stack<int>::Iterator it = intStack.begin(); it != intStack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在这个实现中，我们定义了一个嵌套的`Iterator`类，它包含了指向栈对象的指针和当前索引。迭代器提供了`operator*`、`operator->`、`operator++`和比较运算符`operator==`和`operator!=`，以支持基本的迭代器操作。

`begin()`和`end()`成员函数分别返回指向栈顶元素和栈底元素（即栈外一个位置）的迭代器。

请注意，这个迭代器实现是反向迭代的，因为它从栈顶开始遍历到栈底。在实际应用中，栈通常不提供迭代器，因为迭代器与栈的LIFO特性不相符。如果你需要迭代器，可能需要考虑使用其他数据结构，如列表或向量。

## 3.这个栈类模板在性能上有哪些优化空间？

栈类模板的性能优化可以从多个方面进行考虑，以下是一些常见的优化策略：

1. **减少内存重新分配**：
   - 当栈的容量不足以容纳新元素时，需要重新分配内存并复制现有元素到新的内存区域。这个过程是昂贵的。可以通过增加初始容量或使用更大的扩容因子来减少扩容的次数。

2. **使用更高效的内存分配策略**：
   - 可以使用内存池来管理内存分配，这样可以减少系统调用和内存碎片。

3. **避免不必要的复制**：
   - 如果元素类型支持移动语义，使用`std::move`来避免不必要的复制操作。

4. **优化迭代器**：
   - 如果迭代器使用频繁，可以考虑实现更高效的迭代器，比如使用延迟初始化。

5. **减少动态内存分配**：
   - 如果栈的大小是固定的，可以使用静态数组而不是动态数组来存储元素。

6. **使用自定义内存分配器**：
   - 如果栈是程序中频繁使用的数据结构，可以考虑使用自定义的内存分配器来优化性能。

7. **优化数据结构**：
   - 考虑使用链表而不是动态数组来实现栈，这样可以避免内存重新分配的问题。

8. **减少异常抛出**：
   - 在`pop`和`top`函数中，如果栈为空，则抛出异常。如果程序中栈为空是一个常见情况，可以考虑返回一个特殊值或使用错误码来避免抛出异常。

9. **使用无锁并发访问**：
   - 如果栈需要在多线程环境中使用，可以考虑实现无锁的数据结构来提高并发性能。

10. **避免使用虚函数**：
    - 如果栈类需要继承，避免使用虚函数，因为它们会增加额外的开销。

11. **减少成员函数的调用**：
    - 对于频繁调用的成员函数，可以考虑内联函数以减少函数调用的开销。

12. **使用模板特化**：
    - 对于特定的数据类型，可以提供特化的实现来优化性能。

13. **减少内存访问**：
    - 优化数据结构的内存布局，减少缓存未命中的可能性。

14. **使用引用计数**：
    - 如果栈中存储的是智能指针，可以考虑使用引用计数来减少内存使用。

15. **避免使用异常处理**：
    - 如果栈操作中可能会抛出异常，可以考虑使用错误码或返回特殊值来处理错误，以避免异常处理的开销。

请注意，优化应该基于实际的性能瓶颈进行。在进行优化之前，最好使用性能分析工具来确定程序的瓶颈所在。

## 4.我想在栈中实现一个优先队列，需要对栈类模板做哪些修改？

实现一个优先队列通常需要根据元素的优先级来出队，而不是遵循先进先出（FIFO）的原则。这意味着我们需要对栈的元素进行排序或者使用其他方法来保证每次出队时都是优先级最高的元素。

以下是实现优先队列的一些方法：

### 4.1. 使用最小堆

最小堆是一种常用的实现优先队列的数据结构。在最小堆中，父节点的值总是小于或等于其子节点的值。这样，堆顶元素就是优先级最高的元素。

### 4.2. 使用有序数组或链表

每次插入元素时，将元素插入到数组或链表中的适当位置，以保持元素的有序性。

### 4.3. 使用二叉搜索树

使用二叉搜索树（BST），并对其进行平衡，如AVL树或红黑树，可以快速插入、删除和查找元素。

### 4.4. 使用斐波那契堆

斐波那契堆是一种高级的数据结构，它在执行减少键值和合并堆操作时非常高效。

### 4.5.修改栈类模板

以下是如何修改你的栈类模板以实现一个简单的最小堆优先队列：

```cpp
#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T>
class PriorityQueue {
private:
    std::vector<T> elements;

    // 交换元素
    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    // 上浮调整
    void siftUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (elements[index] < elements[parentIndex]) {
                swap(elements[index], elements[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    // 下沉调整
    void siftDown(int index) {
        int size = elements.size();
        int leftChildIndex, rightChildIndex, smallestIndex;

        while (true) {
            leftChildIndex = 2 * index + 1;
            rightChildIndex = 2 * index + 2;
            smallestIndex = index;

            if (leftChildIndex < size && elements[leftChildIndex] < elements[smallestIndex]) {
                smallestIndex = leftChildIndex;
            }
            if (rightChildIndex < size && elements[rightChildIndex] < elements[smallestIndex]) {
                smallestIndex = rightChildIndex;
            }
            if (smallestIndex != index) {
                swap(elements[index], elements[smallestIndex]);
                index = smallestIndex;
            } else {
                break;
            }
        }
    }

public:
    void push(const T& element) {
        elements.push_back(element);
        siftUp(elements.size() - 1);
    }

    void pop() {
        if (elements.empty()) {
            throw std::out_of_range("PriorityQueue<>::pop(): empty queue");
        }
        elements[0] = elements.back();
        elements.pop_back();
        siftDown(0);
    }

    T top() const {
        if (elements.empty()) {
            throw std::out_of_range("PriorityQueue<>::top(): empty queue");
        }
        return elements[0];
    }

    bool isEmpty() const {
        return elements.empty();
    }

    size_t getSize() const {
        return elements.size();
    }
};

int main() {
    PriorityQueue<int> pq;
    pq.push(10);
    pq.push(30);
    pq.push(20);

    std::cout << "Top element: " << pq.top() << std::endl; // 输出 10

    pq.pop();
    std::cout << "New top element: " << pq.top() << std::endl; // 输出 20

    return 0;
}
```

### 4.6.解释

1. **最小堆的表示**：
   - 使用一个动态数组（`std::vector`）来存储元素。

2. **上浮调整（`siftUp`）**：
   - 当新元素插入时，将其放在数组的末尾，然后与父节点比较，如果新元素的优先级更高，则与父节点交换位置，直到找到合适的位置。

3. **下沉调整（`siftDown`）**：
   - 当元素被删除（通常是堆顶元素）时，将数组的第一个元素替换为最后一个元素，然后与子节点比较，如果当前元素的优先级较低，则与子节点交换位置，直到找到合适的位置。

4. **`push`操作**：
   - 将新元素插入数组的末尾，然后进行上浮调整。

5. **`pop`操作**：
   - 将数组的第一个元素替换为最后一个元素，然后删除最后一个元素，并对新的第一个元素进行下沉调整。

6. **`top`操作**：
   - 返回数组的第一个元素，即优先级最高的元素。

7. **`isEmpty`和`getSize`操作**：
   - 分别检查队列是否为空和返回队列的大小。

这个实现提供了一个基本的优先队列功能，可以根据需要进行进一步的优化和扩展。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
