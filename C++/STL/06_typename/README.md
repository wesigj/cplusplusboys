# C++ STL源码剖析 6-typename

[TOC]

## Overview

---

## 1.typename

在C++中，`typename` 关键字用于指明某个标识符是类型名称。这在模板编程中尤其有用，因为模板代码在编译时需要类型信息来实例化模板。`typename` 的使用可以解决编译器在模板推导过程中可能遇到的名字歧义问题。

以下是 `typename` 的几种常见用法：

### 1.1. 依赖名称的类型

当类型依赖于模板参数时，需要使用 `typename` 来指明。

```cpp
template <typename T>
class MyClass {
    T data;

public:
    template <typename U>
    MyClass(const U& value) : data(value) {}

    typename T::type getElement() const { return data; }  // 依赖名称
};
```

在这个例子中，`T::type` 是一个依赖于模板参数 `T` 的类型。使用 `typename` 来指明 `T::type` 是一个类型。

### 1.2. 嵌套模板依赖名称

在嵌套模板中，编译器可能无法自动推导出依赖类型，需要显式使用 `typename`。

```cpp
template <typename T>
class Outer {
public:
    template <typename U>
    class Inner {
        U data;

    public:
        U getValue() const { return data; }
    };

    typename Inner<T>::U getElement() const { return data; }  // 需要 typename
};
```

在这个例子中，`Inner<T>::U` 是一个依赖于模板参数 `T` 的类型。使用 `typename` 来指明 `Inner<T>::U` 是一个类型。

### 1.3. 指针和引用的类型

当需要通过指针或引用访问嵌套类型时，也需要使用 `typename`。

```cpp
template <typename T>
class Wrapper {
    T data;

public:
    template <typename U>
    Wrapper(const U& value) : data(value) {}

    typename T& get() { return data; }  // 需要 typename
};
```

在这个例子中，`T&` 是一个类型，使用 `typename` 来指明。

### 1.4. 依赖于模板参数的模板参数

当模板参数本身依赖于另一个模板参数时，需要使用 `typename`。

```cpp
template <template <typename> class TT>
class TemplateWrapper {
public:
    template <typename T>
    TT<T> create() const { return TT<T>(); }
};
```

在这个例子中，`TT<T>` 是一个依赖于模板模板参数 `TT` 的类型。使用 `typename` 可以避免编译器的歧义。

### 1.5. 简化类型名称

在某些情况下，`typename` 可以用来简化复杂的类型名称。

```cpp
template <typename T>
class Ptr {
public:
    typedef T* PointerType;

    typename Ptr::PointerType get() const { return nullptr; }  // 简化类型名称
};
```

在这个例子中，使用 `typename` 来简化 `PointerType` 的定义。

### 1.6. C++17 中的类模板参数推导

在 C++17 之前，需要使用 `typename` 来指明依赖名称。从 C++17 开始，编译器可以自动推导这些依赖名称，因此 `typename` 不再是必须的。

```cpp
template <typename T>
class MyClass {
public:
    template <typename U>
    MyClass(const U& value) : data(value) {}

    auto getElement() const -> decltype(data) { return data; }  // C++17 自动推导
};
```

在这个例子中，C++17 的自动类型推导可以识别 `decltype(data)`，因此不需要显式使用 `typename`。

总之，`typename` 在模板编程中非常有用，尤其是在处理复杂的依赖类型时。它帮助编译器正确识别类型名称，从而避免歧义和错误。

## 2.C++17 引入了哪些新特性，它们是如何简化模板编程的？

C++17 引入了许多新特性，这些特性在模板编程方面提供了显著的简化和增强：

1. **类模板参数推导（CTAD）**：C++17 允许编译器从类模板的构造函数参数中自动推导出模板参数类型，这使得在使用模板类时可以省略模板参数的显式指定。

2. **自动类型推导的增强**：`auto` 关键字的类型推导规则得到了扩展和改进，尤其是在模板参数推导和返回类型推导方面。

3. **内联变量**：C++17 允许在头文件中定义内联变量，这意味着可以在多个编译单元中使用相同的变量定义，而不会触发链接错误。

4. **结构化绑定**：C++17 引入了结构化绑定，它允许将元组、对或数组中的值一次性解构并绑定到新的局部变量中，简化了数据结构的访问。

5. **编译期 if 语句（`if constexpr`）**：`if constexpr` 允许在编译时根据条件编译代码块，这在模板编程中非常有用，因为它允许在编译时根据类型或值的不同执行不同的代码路径。

6. **折叠表达式**：C++17 引入了折叠表达式，它提供了一种简洁的方式来编写递归模板元编程表达式，尤其是在处理参数包时，能够对参数包中的元素进行统一的操作（如求和、逻辑与/或等）。

7. **`std::optional` 和 `std::variant`**：这两个新的标准库类型为模板编程提供了更多的灵活性和安全性。`std::optional` 用于表示可能存在也可能不存在的值，而 `std::variant` 支持类型安全的多类型容器。

8. **`std::any`**：`std::any` 类型允许存储任意类型的对象，提供了一种类型擦除的机制，这在需要处理多种不同类型的模板编程中非常有用。

9. **`std::filesystem`**：虽然不是直接与模板编程相关，但 `std::filesystem` 提供了跨平台的文件系统操作支持，它使用模板来抽象文件系统操作，使得在不同操作系统上进行文件操作更加一致和简单。

10. **`std::invoke`**：`std::invoke` 函数提供了一种统一的方式来调用函数、函数指针、成员函数指针等可调用对象，这在模板编程中非常有用，尤其是在需要泛化调用不同类型函数时。

11. **`std::string_view`**：`std::string_view` 提供了一种高效的方式来引用字符串字面量或字符串对象的字符序列，它在模板编程中尤其有用，因为它可以避免不必要的字符串复制，提高性能。

12. **`std::shared_mutex` 和 `std::shared_lock`**：这两个新的同步原语提供了共享锁定机制，允许多个线程同时读取，但写入时需要独占访问，这在模板编程中处理并发访问时非常有用。

13. **`std::byte`**：`std::byte` 类型提供了类型安全的字节类型，用于表示原始内存数据，这在处理字节序列的模板编程中非常有用。

这些特性的引入，使得 C++17 在模板编程方面更加强大和灵活，同时也简化了代码的编写和维护。

## 3.在C++中，除了typename，还有哪些关键字或工具可以帮助我避免类型歧义？

在 C++ 中，除了 `typename` 关键字，还有以下关键字和工具可以帮助避免类型歧义：

1. **`template`**：
   使用 `template` 关键字可以定义模板，它允许在编译时对类型参数进行推导，从而减少歧义。

2. **`auto`**：
   `auto` 关键字可以用于自动类型推导，它允许编译器根据初始化表达式来推导变量的类型。

3. **`decltype`**：
   `decltype` 关键字用于推导表达式的类型，它可以用来避免复杂的类型表达式引起的歧义。

4. **`using`**：
   `using` 声明可以定义类型别名或模板别名，它有助于简化复杂的类型表达式。

5. **`static_assert`**：
   `static_assert` 可以用来在编译时检查类型特性，确保类型满足特定的条件，从而避免歧义。

6. **`constexpr`**：
   `constexpr` 关键字用于定义编译时计算的常量表达式，有助于模板元编程中的类型推导和条件编译。

7. **`if constexpr`**：
   `if constexpr` 允许在编译时根据条件判断执行代码，可以用于模板编程中的分支处理。

8. **`std::enable_if`**：
   `std::enable_if` 是一个SFINAE（Substitution Failure Is Not An Error）工具，它可以根据条件启用或禁用模板重载。

9. **`std::disjunction`、`std::conjunction` 和 `std::negation`**：
   这些类型特征可以用来执行编译时的逻辑运算，帮助解决模板编程中的复杂条件。

10. **类型萃取（Type traits）**：
    类型特征（如 `std::is_same`、`std::add_pointer` 等）可以用来在编译时检查和修改类型，有助于解决歧义。

11. **继承和作用域**：
    通过适当的类继承结构和命名空间作用域，可以避免类型名称的冲突和歧义。

12. **重载函数模板**：
    通过重载函数模板，可以为不同的类型提供特定的实现，从而避免歧义。

13. **`std::common_type`**：
    `std::common_type` 类型特征可以用来确定一组类型中最合适的共同类型，有助于解决类型转换中的歧义。

14. **`std::decay`**：
    `std::decay` 类型特征用于将类型转换为“ Decayed”形式，移除顶层的const、volatile和引用属性，有助于统一类型表达式。

通过使用这些关键字和工具，可以提高模板编程的可读性和可维护性，同时减少类型歧义的发生。

## 4.一个使用C++模板进行多态编程的简单例子？

在 C++ 中，模板为多态编程提供了一种强大的机制。以下是一个使用模板进行多态编程的简单例子，其中定义了一个通用的接口，然后通过不同的派生类来实现这个接口：

```cpp
#include <iostream>
#include <memory>
#include <vector>
#include <typeinfo>

// 基础类接口
template <typename T>
class Interface {
public:
    virtual ~Interface() = default;
    virtual void performAction() = 0;  // 纯虚函数
};

// 具体实现类A
template <typename T>
class ImplementationA : public Interface<T> {
public:
    void performAction() override {
        std::cout << "Implementation A with type: " << typeid(T).name() << std::endl;
    }
};

// 具体实现类B
template <typename T>
class ImplementationB : public Interface<T> {
public:
    void performAction() override {
        std::cout << "Implementation B with type: " << typeid(T).name() << std::endl;
    }
};

// 函数模板，接受任何实现了 Interface 的类型
template <typename Implementation>
void execute(Implementation& impl) {
    impl.performAction();
}

int main() {
    // 使用模板类创建对象
    ImplementationA<int> implA;
    ImplementationB<double> implB;

    // 将具体实现对象传递给函数模板
    execute(implA);
    execute(implB);

    // 存储不同类型的实现到向量
    std::vector<std::unique_ptr<Interface<int>>> implementations;
    implementations.push_back(std::make_unique<ImplementationA<int>>());
    implementations.push_back(std::make_unique<ImplementationB<int>>());

    // 多态调用
    for (auto& impl : implementations) {
        impl->performAction();
    }

    return 0;
}
```

在这个例子中，我们定义了一个名为 `Interface` 的模板类，它有一个纯虚函数 `performAction`。然后我们创建了两个模板类 `ImplementationA` 和 `ImplementationB`，它们都继承自 `Interface` 并重写了 `performAction` 方法。

接着，我们定义了一个函数模板 `execute`，它接受一个 `Interface` 类型的参数，并调用其 `performAction` 方法。

在 `main` 函数中，我们创建了 `ImplementationA` 和 `ImplementationB` 的实例，并使用 `execute` 函数模板来调用它们的 `performAction` 方法。

最后，我们创建了一个 `std::vector`，其中存储了不同类型的 `Interface` 实现的指针，并演示了如何通过基类指针调用派生类的函数，这是多态的一个典型例子。

这个例子展示了模板如何与多态结合使用，提供了代码的复用性和灵活性。

## 5.如何使用C++模板类来实现一个通用的排序算法？

在C++中，可以使用模板类和模板函数来实现一个通用的排序算法。以下是一个使用模板实现简单快速排序算法的例子：

```cpp
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <list>

// 模板类，用于实现排序算法
template <typename T>
class Sorter {
public:
    // 模板函数，执行排序
    void sort(T& collection) {
        std::sort(std::begin(collection), std::end(collection));
    }
};

// 模板函数，打印容器元素
template <typename T>
void print(const T& collection) {
    for (const auto& item : collection) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

int main() {
    // 示例：使用 std::vector<int>
    std::vector<int> vec = {4, 1, 3, 5, 2};
    Sorter<std::vector<int>> intSorter;
    intSorter.sort(vec);
    print(vec); // 输出: 1 2 3 4 5

    // 示例：使用 std::vector<double>
    std::vector<double> vecDouble = {4.5, 1.2, 3.7, 5.1, 2.3};
    Sorter<std::vector<double>> doubleSorter;
    doubleSorter.sort(vecDouble);
    print(vecDouble); // 输出: 1.2 2.3 3.7 4.5 5.1

    // 示例：使用 std::list<int>
    std::list<int> lst = {4, 1, 3, 5, 2};
    Sorter<std::list<int>> listSorter;
    listSorter.sort(lst);
    print(lst.begin(), lst.end()); // 输出: 1 2 3 4 5

    return 0;
}

// 提供 print 特化版本，用于 std::list
template <typename T>
void print(const T& collection, const T& end) {
    for (auto it = collection; it != end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
```

在这个例子中，我们定义了一个名为 `Sorter` 的模板类，它有一个模板成员函数 `sort`，用于对传入的集合进行排序。我们使用了标准库中的 `std::sort` 函数来执行实际的排序操作。

我们还定义了一个模板函数 `print` 来打印容器中的元素。对于 `std::list`，由于它不支持随机访问迭代器，我们提供了 `print` 函数的一个特化版本，它接受开始和结束迭代器作为参数。

在 `main` 函数中，我们展示了如何使用 `Sorter` 类对不同类型的容器（如 `std::vector<int>`、`std::vector<double>` 和 `std::list<int>`）进行排序，并使用 `print` 函数打印排序后的结果。

这个例子展示了如何使用模板类和模板函数来实现一个通用的排序算法，它可以对不同类型的容器进行排序。

## 6.如何使用C++模板类来实现一个通用的搜索算法？

在C++中，使用模板类实现一个通用的搜索算法是一个很好的练习，这可以帮助你理解模板的灵活性和功能强大之处。这里，我们将实现一个模板类，该类提供了一个通用的搜索方法，可以使用线性搜索算法来查找元素。虽然标准库已经提供了很多查找算法（如 `std::find`），但自己实现可以加深对模板和算法的理解。

### 6.1.定义模板类

我们将创建一个名为 `Searcher` 的模板类，它包含一个静态模板方法 `search`，用于在给定的容器中搜索特定值。

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

// 通用搜索类模板
template <typename Container, typename ValueType>
class Searcher {
public:
    // 搜索容器中的值
    static auto search(const Container& container, const ValueType& value) -> decltype(auto) {
        auto it = std::find(std::begin(container), std::end(container), value);
        if (it != std::end(container)) {
            return std::distance(std::begin(container), it);  // 返回找到元素的索引
        } else {
            return -1;  // 如果未找到，返回-1
        }
    }
};

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    int index = Searcher<std::vector<int>, int>::search(vec, 3);
    std::cout << "Index of 3 in vector: " << index << std::endl;  // 输出: Index of 3 in vector: 2

    std::list<int> lst = {1, 2, 3, 4, 5};
    index = Searcher<std::list<int>, int>::search(lst, 3);
    std::cout << "Index of 3 in list: " << index << std::endl;  // 输出: Index of 3 in list: 2

    return 0;
}
```

### 6.2.解释

1. **模板类 `Searcher`**：
   - 我们定义了一个名为 `Searcher` 的模板类，它接受两个模板参数：`Container` 是容器的类型，`ValueType` 是要搜索的值的类型。

2. **静态方法 `search`**：
   - `search` 方法是静态的，因此可以在没有 `Searcher` 对象的情况下调用。
   - 它使用 `std::find` 来查找值，这是标准库中的一个算法，用于在范围内查找第一个匹配的值。
   - `std::distance` 用来计算找到的迭代器和容器开始之间的距离，这基本上就是元素的索引。

3. **返回类型**：
   - `search` 方法返回找到元素的索引。如果元素未找到，它返回 `-1`。
   - 使用 `decltype(auto)` 自动推导返回类型，这使得方法可以灵活地处理任何类型的容器。

4. **使用示例**：
   - 在 `main` 函数中，我们创建了一个 `std::vector` 和一个 `std::list`，并使用 `Searcher` 类来搜索特定的值。
   - 注意我们是如何使用 `Searcher<std::vector<int>, int>::search` 和 `Searcher<std::list<int>, int>::search` 的，这显示了模板类如何被用于不同的容器类型。

这个例子展示了如何使用模板类来实现一个通用且灵活的搜索算法，它可以适用于任何类型的容器。通过这种方式，你可以在不同的数据结构和类型上重用相同的搜索逻辑。

## 7.一个使用C++模板进行泛型编程的复杂例子？

当然可以。以下是一个使用 C++ 模板进行泛型编程的复杂例子，它展示了如何实现一个通用的二分搜索算法，该算法可以用于任何支持随机访问迭代器的容器：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>

// 二分搜索的模板函数
template <typename RandomAccessIterator, typename T>
typename std::enable_if_t<
    std::is_base_of<std::random_access_iterator_tag,
                    typename std::iterator_traits<
                        RandomAccessIterator>::iterator_category>::value,
    RandomAccessIterator>
binary_search_my(RandomAccessIterator first, RandomAccessIterator last,
                 const T &value) {
    // 当前搜索区间的长度
    auto len = std::distance(first, last);

    // 如果区间为空，返回末尾迭代器
    if (len == 0) { return last; }

    while (len > 0) {
        // 计算当前搜索区间的中间位置
        auto half = len / 2;
        auto mid  = first + half;

        if (*mid < value) {
            // 如果中间的元素小于 value，忽略左半边
            first = mid + 1;
            len -= half + 1;
        } else if (*mid > value) {
            // 如果中间的元素大于 value，忽略右半边
            len = half;
        } else {
            // 如果中间的元素等于 value，返回当前迭代器
            return mid;
        }
    }

    // 如果没有找到，返回末尾迭代器
    return last;
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // 搜索 5
    auto it = binary_search_my(vec.begin(), vec.end(), 5);
    if (it != vec.end()) {
        std::cout << "Element 5 found at position: "
                  << std::distance(vec.begin(), it) << std::endl;
    } else {
        std::cout << "Element 5 not found." << std::endl;
    }

    // 搜索 10
    it = binary_search_my(vec.begin(), vec.end(), 10);
    if (it != vec.end()) {
        std::cout << "Element 10 found at position: "
                  << std::distance(vec.begin(), it) << std::endl;
    } else {
        std::cout << "Element 10 not found." << std::endl;
    }

    return 0;
}
```

在这个例子中，我们定义了一个名为 `binary_search` 的模板函数，它接受一对迭代器和一个要搜索的值作为参数，并返回一个指向找到的元素的迭代器。如果未找到元素，则返回一个指向容器末尾的迭代器。

### 7.1.关键点

1. **模板参数**：
   - `RandomAccessIterator` 是迭代器的类型，它必须是随机访问迭代器。
   - `T` 是要搜索的值的类型。

2. **`std::enable_if_t`**：
   - 我们使用 `std::enable_if_t` 和 `std::is_base_of` 来确保只有当迭代器是随机访问迭代器时，函数模板才有效。

3. **迭代器算术**：
   - 我们使用迭代器算术来计算中间位置，并更新搜索区间。

4. **返回值**：
   - 如果找到元素，返回指向该元素的迭代器；否则返回指向容器末尾的迭代器。

5. **`main` 函数**：
   - 在 `main` 函数中，我们创建了一个 `std::vector<int>` 并使用 `binary_search` 函数搜索特定的值。

这个例子展示了如何使用模板、迭代器、类型特征和条件编译来实现一个通用且高效的二分搜索算法。通过这种方式，你可以在不同的数据结构和类型上重用相同的搜索逻辑。

## 8.一个使用C++模板类实现的图算法示例？

在C++中，使用模板类实现图算法可以提供灵活性和通用性。以下是一个简单的例子，展示了如何使用模板类实现图的存储以及深度优先搜索（DFS）算法。

### 8.1.图的表示

我们使用邻接表来表示图。`Graph` 模板类存储了图的边，并且提供了添加边和执行DFS的方法。

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <stack>

// 模板类，表示图
template <typename T>
class Graph {
private:
    std::vector<std::list<T>> adj;  // 邻接表

public:
    // 构造函数
    Graph(int numVertices) : adj(numVertices) {}

    // 添加边
    void addEdge(T src, T dest) {
        adj[src].push_back(dest);  // 为无向图添加双向边
        adj[dest].push_back(src);
    }

    // 深度优先搜索
    void DFS(T vertex, std::stack<T>& stack, std::vector<bool>& visited) {
        // 访问当前节点
        std::cout << vertex << " ";
        visited[vertex] = true;

        // 访问所有未被访问的邻接节点
        for (auto adjVertex : adj[vertex]) {
            if (!visited[adjVertex]) {
                DFS(adjVertex, stack, visited);
            }
        }
    }

    // 执行DFS的公共方法
    void performDFS(T startVertex) {
        std::vector<bool> visited(adj.size(), false);  // 跟踪访问的节点
        std::stack<T> stack;  // 使用堆栈来保存节点

        // 访问起始节点
        stack.push(startVertex);
        while (!stack.empty()) {
            T currentVertex = stack.top();
            stack.pop();
            if (!visited[currentVertex]) {
                DFS(currentVertex, stack, visited);
            }
        }
    }
};

int main() {
    // 创建一个图实例，假设有5个顶点
    Graph<int> graph(5);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);

    // 执行深度优先搜索
    graph.performDFS(0);

    return 0;
}
```

### 8.2.解释

1. **Graph 类**：
   - `Graph` 类模板使用类型参数 `T` 来表示图中的顶点。
   - 成员变量 `adj` 是一个二维 `std::list`，表示图的邻接表。

2. **添加边**：
   - `addEdge` 方法添加一条边，因为是无向图，所以添加的是双向边。

3. **深度优先搜索（DFS）**：
   - `DFS` 方法是一个递归方法，用于遍历图的节点。
   - 它接受当前节点、一个节点堆栈和一个访问标记的向量。

4. **执行DFS**：
   - `performDFS` 方法初始化一个访问标记的向量和一个节点堆栈。
   - 它从起始节点开始遍历图。

5. **main 函数**：
   - 在 `main` 函数中，我们创建了一个图实例并添加了一些边。
   - 然后调用 `performDFS` 方法从节点0开始执行DFS。

这个例子展示了如何使用模板类来实现图的存储和遍历。通过这种方式，你可以在不同的数据类型上重用图的逻辑。

## 9.如何使用C++模板类实现图的广度优先搜索（BFS）算法？

在C++中，使用模板类实现图的广度优先搜索（BFS）算法可以提供灵活性和通用性。以下是一个例子，展示了如何使用模板类实现图的存储以及BFS算法。

### 8.3.图的表示

我们使用邻接表来表示图。`Graph` 模板类存储了图的边，并提供了添加边和执行BFS的方法。

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <queue>

// 模板类，表示图
template <typename T>
class Graph {
private:
    std::vector<std::list<T>> adj;  // 邻接表

public:
    // 构造函数
    Graph(int numVertices) : adj(numVertices) {}

    // 添加边
    void addEdge(T src, T dest) {
        adj[src].push_back(dest);  // 为无向图添加双向边
        adj[dest].push_back(src);
    }

    // 广度优先搜索
    void BFS(T startVertex) {
        std::vector<bool> visited(adj.size(), false);  // 跟踪访问的节点
        std::queue<T> queue;  // 用于BFS的队列

        // 标记起始节点为已访问并入队
        visited[startVertex] = true;
        queue.push(startVertex);

        while (!queue.empty()) {
            T currentVertex = queue.front();
            queue.pop();
            std::cout << currentVertex << " ";

            // 访问所有未被访问的邻接节点
            for (auto adjVertex : adj[currentVertex]) {
                if (!visited[adjVertex]) {
                    visited[adjVertex] = true;
                    queue.push(adjVertex);
                }
            }
        }
    }
};

int main() {
    // 创建一个图实例，假设有5个顶点
    Graph<int> graph(5);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);

    // 执行广度优先搜索
    std::cout << "Starting BFS from vertex 0:" << std::endl;
    graph.BFS(0);

    return 0;
}
```

### 8.4.解释

1. **Graph 类**：
   - `Graph` 类模板使用类型参数 `T` 来表示图中的顶点。
   - 成员变量 `adj` 是一个二维 `std::list`，表示图的邻接表。

2. **添加边**：
   - `addEdge` 方法添加一条边，因为是无向图，所以添加的是双向边。

3. **广度优先搜索（BFS）**：
   - `BFS` 方法使用一个队列来实现BFS算法。
   - 它接受一个起始节点，然后从该节点开始遍历图。

4. **访问标记**：
   - 使用一个布尔向量 `visited` 来跟踪已访问的节点。

5. **main 函数**：
   - 在 `main` 函数中，我们创建了一个图实例并添加了一些边。
   - 然后调用 `BFS` 方法从节点0开始执行BFS。

这个例子展示了如何使用模板类来实现图的存储和遍历。通过这种方式，你可以在不同的数据类型上重用图的逻辑。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
