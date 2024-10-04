# C++ STL源码剖析 1-std::array

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃
- `std::array`的特点包括类型安全、固定大小、内存连续，以及提供了与`std::vector`类似的接口，如`size()`、`at()`、`front()`、`back()`等。`std::array`的元素在内存中是连续存储的，这使得它可以高效地访问元素。
- 大小可为0

---

## 1.std::array 在 C++11 标准中是如何定义的？

在C++11标准中，`std::array`是一个模板类，定义在`<array>`头文件中。它提供了一个固定大小的数组，其大小在编译时确定，并且不允许动态改变。`std::array`模板类的基本语法如下：

```cpp
template <class T, size_t N>
class array {
public:
    // 类型定义
    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef size_t size_type;
    typedef std::ptrdiff_t difference_type;

    // 成员函数
    reference operator[](size_type i);
    const_reference operator[](size_type i) const;
    reference at(size_type i);
    const_reference at(size_type i) const;
    pointer data();
    const_pointer data() const;
    void fill(const T& value);
    void swap(array& other);
    size_type size() const;
    size_type max_size() const;
    bool empty() const;

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
};
```

`std::array`的特点包括类型安全、固定大小、内存连续，以及提供了与`std::vector`类似的接口，如`size()`、`at()`、`front()`、`back()`等。`std::array`的元素在内存中是连续存储的，这使得它可以高效地访问元素。

使用`std::array`时，可以利用下标操作符`[]`或者成员函数`at()`来访问元素，其中`at()`在访问时会进行边界检查。`std::array`也支持使用迭代器进行遍历。

`std::array`的构造函数是隐式定义的，支持聚合初始化，可以使用花括号`{}`来初始化元素。

`std::array`的大小是固定的，可以通过成员函数`size()`获取，它返回一个编译时常量，表示数组中的元素数量。

在C++17中，`std::array`的类型和大小可以被自动推导，而在C++11和C++14中，需要显式指定数组的类型和大小。例如：

```cpp
std::array<int, 5> arr = {1, 2, 3, 4, 5};
```

这行代码创建了一个包含5个整数的`std::array`对象，并使用列表初始化来初始化其元素。如果初始化时提供的元素少于数组的大小，剩余的元素将使用默认值进行初始化，对于整数类型，默认值为0。

`std::array`还提供了成员函数`fill()`来将所有元素设置为相同的值，以及`swap()`函数来交换两个数组的内容。

## 2.std::array 在 C++17 中有哪些新特性？

在C++17中，`std::array`并没有直接的新增特性，因为`std::array`是在C++11中引入的，并且在C++14中已经相对成熟。然而，C++17为C++语言和标准库带来了许多新特性，这些特性间接地影响了`std::array`的使用方式。以下是一些C++17中与`std::array`使用相关的新特性：

1. **类模板参数推导（CTAD）**：C++17引入了类模板参数推导，这使得在使用`std::array`时可以省略模板参数。例如，你可以这样声明一个`std::array`：

   ```cpp
   std::array arr = {1, 2, 3};  // 编译器推导出元素类型为int，数组大小为3
   ```

   这种语法在C++17之前是不支持的。

2. **结构化绑定**：C++17允许使用结构化绑定来解包数组或其他容器。这意味着你可以将`std::array`的元素绑定到单独的变量上：

   ```cpp
   std::array<int, 3> arr = {1, 2, 3};
   auto [a, b, c] = arr;
   ```

   这使得处理数组元素更加方便。

3. **`std::apply`**：虽然`std::apply`并不是直接针对`std::array`的，但它提供了一种方便的方式来调用存储在`std::array`中的函数或函数对象。例如：

   ```cpp
   std::array<std::function<int(int, int)>> arr = {[]{return 0;}, [](int a, int b) {return a + b;}};
   auto result = std::apply(arr[1], std::tuple<int, int>{1, 2});
   ```

   这允许你使用`std::array`存储和调用函数。

4. **`if constexpr`**：`if constexpr`允许在编译时进行条件判断，这可以在模板元编程中与`std::array`一起使用，以生成条件化的代码。

5. **`[[nodiscard]]`属性**：这个属性可以用来标记`std::array`的成员函数，以提醒用户注意不要忽略返回值。

6. **`[[maybe_unused]]`属性**：当声明一个`std::array`变量但未使用时，可以使用这个属性来避免编译器警告。

7. **`[[fallthrough]]`属性**：在`std::array`的循环或条件语句中，这个属性可以用来明确表示开发者有意从一个分支直接跳转到下一个分支。

8. **`inline`变量**：允许在类定义中声明内联变量，这有助于减少模板元编程中`std::array`的使用复杂性。

这些特性虽然不是直接针对`std::array`的，但它们提供了更多灵活性和便利性，使得`std::array`的使用更加高效和简洁。

## 3.std::array 源码剖析

C++标准模板库（STL）中的`std::array`是一个固定大小的数组容器，它封装了C风格的数组。`std::array`在C++11中引入，提供了与C风格数组类似的性能和访问便利性，同时增加了标准容器的特性，比如知道其大小、支持赋值、提供随机访问迭代器等。

### 3.1.`std::array`的实现细节

1. **模板定义**：
   `std::array`是一个模板类，定义如下：

   ```cpp
   template<class T, size_t N>
   struct array {
       // ...
       T _M_elems[N];  // 内部存储数组元素
       // ...
   };
   ```

   其中`T`是元素类型，`N`是数组的大小，`_M_elems`是存储元素的内部数组。

2. **成员函数**：
   - `begin()`, `end()`, `rbegin()`, `rend()`: 提供迭代器支持。
   - `front()`, `back()`: 提供访问首尾元素的成员函数。
   - `data()`: 提供直接访问底层数组的指针。
   - `size()`, `max_size()`: 提供数组大小的信息。
   - `fill()`: 用给定值填充数组。
   - `swap()`: 交换两个数组的内容。

3. **构造函数**：
   `std::array`的构造函数是隐式定义的，支持聚合初始化。

4. **赋值操作**：
   赋值操作也是隐式定义的，允许数组间元素的赋值。

5. **元素访问**：
   - `operator[]`: 提供随机访问数组元素。
   - `at()`: 提供边界检查的元素访问。

6. **迭代器**：
   迭代器的类型依赖于实现，但通常是一个指针或指向常量的指针。

### 3.2.`std::array`与C风格数组的比较

- **性能**：`std::array`旨在提供与C风格数组相似的性能，因为它在内存中以连续的方式存储元素。
- **安全性**：`std::array`提供了边界检查，而C风格数组没有。
- **易用性**：`std::array`支持STL算法，可以直接与`std::sort`、`std::for_each`等算法一起使用。

### 3.3.源码剖析

在不同的编译器实现中，`std::array`的内部实现可能会有所不同，但基本概念是一致的。例如，在GCC的实现中，`std::array`内部使用一个C风格数组来存储元素。

### 3.4.使用示例

```cpp
#include <array>
#include <algorithm>
#include <iostream>

int main() {
    std::array<int, 4> arr = {1, 2, 3, 4};

    // 使用STL算法排序
    std::sort(arr.begin(), arr.end());

    // 打印数组内容
    for (int i : arr) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

### 3.5.总结

`std::array`是一个现代C++中的固定大小数组容器，它结合了C风格数组的性能和现代容器的安全性与便利性。通过封装C风格数组，`std::array`提供了一个类型安全且易于使用的数组解决方案。

## 4.如何使用 std::array 进行高效的数据排序？

`std::array` 是 C++ 标准库中的一个容器，它提供了一个固定大小的数组，并支持标准容器的接口。使用 `std::array` 进行数据排序时，可以利用 C++ 标准库中的算法，如 `std::sort`，来高效地对数据进行排序。

以下是使用 `std::array` 进行数据排序的步骤：

1. **包含必要的头文件**：
   为了使用 `std::array` 和 `std::sort`，需要包含 `<array>` 和 `<algorithm>` 头文件。

2. **定义 `std::array`**：
   定义一个 `std::array` 实例，并初始化数据。

3. **使用 `std::sort`**：
   调用 `std::sort` 函数对 `std::array` 中的数据进行排序。

4. **自定义排序规则**（可选）：
   如果需要自定义排序规则，可以向 `std::sort` 传递一个自定义比较函数或 lambda 表达式。

### 4.1.示例代码

以下是一个使用 `std::array` 进行数据排序的示例：

```cpp
#include <iostream>
#include <array>
#include <algorithm>

int main() {
    // 定义并初始化 std::array
    std::array<int, 5> arr = {5, 3, 9, 1, 6};

    // 使用默认排序规则进行排序
    std::sort(arr.begin(), arr.end());

    // 打印排序后的结果
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 使用自定义排序规则（例如：降序排序）
    std::sort(arr.begin(), arr.end(), std::greater<int>());

    // 打印自定义排序后的结果
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 4.2.输出结果

```shell
1 3 5 6 9 
9 6 5 3 1 
```

### 4.3.解释

1. **包含头文件**：

   ```cpp
   #include <iostream>
   #include <array>
   #include <algorithm>
   ```

2. **定义 `std::array`**：

   ```cpp
   std::array<int, 5> arr = {5, 3, 9, 1, 6};
   ```

3. **使用默认排序规则进行排序**：

   ```cpp
   std::sort(arr.begin(), arr.end());
   ```

4. **打印排序后的结果**：

   ```cpp
   for (int num : arr) {
       std::cout << num << " ";
   }
   std::cout << std::endl;
   ```

5. **使用自定义排序规则（例如：降序排序）**：

   ```cpp
   std::sort(arr.begin(), arr.end(), std::greater<int>());
   ```

6. **打印自定义排序后的结果**：

   ```cpp
   for (int num : arr) {
       std::cout << num << " ";
   }
   std::cout << std::endl;
   ```

### 4.4.自定义比较函数示例

如果需要更复杂的排序规则，可以定义一个自定义比较函数：

```cpp
struct CustomCompare {
    bool operator()(int lhs, int rhs) const {
        // 自定义排序逻辑，例如：根据绝对值排序
        return std::abs(lhs) < std::abs(rhs);
    }
};

int main() {
    std::array<int, 5> arr = {-5, 3, -9, 1, 6};

    // 使用自定义比较函数进行排序
    std::sort(arr.begin(), arr.end(), CustomCompare());

    // 打印排序后的结果
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 4.5.输出结果

```shell
-9 3 1 6 -5 
```

通过这些步骤，你可以高效地使用 `std::array` 进行数据排序，并根据需要自定义排序规则。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
