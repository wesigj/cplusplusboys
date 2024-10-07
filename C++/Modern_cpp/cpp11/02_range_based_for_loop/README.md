# C++11 02-Range-based for loop 范围基于的循环

- [C++11 02-Range-based for loop 范围基于的循环](#c11-02-range-based-for-loop-范围基于的循环)
  - [Overview](#overview)
  - [1.Range-based for loop 范围基于的循环](#1range-based-for-loop-范围基于的循环)
    - [1.1.基本语法](#11基本语法)
    - [1.2.实际例子](#12实际例子)
      - [1.2.1. 遍历数组](#121-遍历数组)
      - [1.2.2. 遍历 `std::vector`](#122-遍历-stdvector)
      - [1.2.3. 遍历 `std::map`](#123-遍历-stdmap)
      - [1.2.4. 遍历字符串](#124-遍历字符串)
    - [1.3.特点和优势](#13特点和优势)
    - [1.4.注意事项](#14注意事项)
  - [2.C++11 中的范围基于的循环和传统的 for 循环相比有哪些优势？](#2c11-中的范围基于的循环和传统的-for-循环相比有哪些优势)
    - [2.1.示例对比](#21示例对比)
  - [3.如何使用范围基于的循环遍历一个多维数组？](#3如何使用范围基于的循环遍历一个多维数组)
    - [3.1.方法 1：使用嵌套的范围基于的循环](#31方法-1使用嵌套的范围基于的循环)
    - [3.2.方法 2：使用标准库算法](#32方法-2使用标准库算法)
    - [3.3.方法 3：使用递归模板函数](#33方法-3使用递归模板函数)
    - [3.4.方法 4：使用循环索引](#34方法-4使用循环索引)
    - [3.5.总结](#35总结)
  - [4.在C++11中，如果我想在循环中修改容器中的元素，应该如何做？](#4在c11中如果我想在循环中修改容器中的元素应该如何做)
    - [4.1.使用迭代器](#41使用迭代器)
    - [4.2.使用下标操作符](#42使用下标操作符)
    - [4.3.使用 `std::transform`](#43使用-stdtransform)
    - [4.4.注意事项](#44注意事项)
  - [关于作者](#关于作者)

## Overview

---

## 1.Range-based for loop 范围基于的循环

C++11 引入了范围基于的循环（Range-based for loop），这是一种新的循环语法，用于简化容器或数组的遍历。与传统的索引基于的循环相比，范围基于的循环更加简洁，且不易出错。

### 1.1.基本语法

范围基于的循环的基本语法如下：

```cpp
for (declaration : range_expression) {
    loop_statement;
}
```

其中：

- `declaration` 是在循环开始时初始化的变量声明，该变量用于引用 `range_expression` 中的每个元素。
- `range_expression` 是一个表达式，它返回一个可以遍历的范围，例如数组、容器或字符串。

### 1.2.实际例子

以下是一些使用范围基于的循环的例子：

#### 1.2.1. 遍历数组

```cpp
#include <iostream>

int main() {
    int arr[] = {1, 2, 3, 4, 5};

    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

#### 1.2.2. 遍历 `std::vector`

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<std::string> vec = {"Kimi", "Moonshot", "AI"};

    for (const std::string& name : vec) {
        std::cout << name << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

#### 1.2.3. 遍历 `std::map`

```cpp
#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> umap = {{1, "Kimi"}, {2, "Moonshot"}, {3, "AI"}};

    for (const auto& pair : umap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}
```

#### 1.2.4. 遍历字符串

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str = "Hello, C++11";

    for (char ch : str) {
        std::cout << ch;
    }
    std::cout << std::endl;

    return 0;
}
```

### 1.3.特点和优势

1. **简洁性**：范围基于的循环语法简洁，易于读写。
2. **安全性**：它避免了索引错误和越界访问的风险。
3. **通用性**：适用于任何可以定义迭代器的数据结构。
4. **灵活性**：可以用于常量和非常量数据，以及引用和值。

### 1.4.注意事项

1. **变量捕获**：在循环中声明的变量是循环的局部变量，不能在循环外使用。
2. **引用类型**：默认情况下，范围基于的循环使用引用捕获元素，以避免不必要的复制。如果需要修改元素，可以使用 `auto&`。
3. **临时对象**：如果范围表达式是一个临时对象，循环结束后，临时对象将被销毁，因此不能在循环外使用循环变量。

范围基于的循环是 C++11 中一个非常有用的新特性，它简化了容器和数组的遍历，使代码更加简洁和安全。

## 2.C++11 中的范围基于的循环和传统的 for 循环相比有哪些优势？

C++11 引入的范围基于的循环提供了一种更简洁、更直观的方式来遍历容器或数组，与传统的 for 循环相比，它有以下几个优势：

1. **代码简洁性**：范围基于的循环不需要显式地编写索引变量和迭代逻辑，使得代码更加简洁和易于理解。

2. **减少错误**：由于不需要手动管理索引，可以减少因索引操作不当造成的错误，如数组越界或错误的索引更新。

3. **提高可读性**：范围基于的循环直接表达了程序员的意图，即“对于容器中的每个元素执行某些操作”，这使得代码更易于阅读和维护。

4. **通用性**：这种循环方式适用于任何类型的容器，包括标准库容器（如 `std::vector`、`std::list`、`std::map` 等）、数组以及任何提供迭代器的自定义数据结构。

5. **自动类型推导**：在循环变量的声明中使用 `auto` 关键字，编译器会自动推导元素的类型，无需程序员显式指定。

6. **避免魔术数字**：在传统的 for 循环中，数组的大小通常作为循环的边界条件，这可能导致魔术数字的产生。范围基于的循环不需要数组大小，减少了魔术数字的出现。

7. **支持容器的动态变化**：如果容器的大小在运行时动态变化，传统的 for 循环需要额外的逻辑来处理这种情况。而范围基于的循环会自动适应容器的变化。

8. **支持引用或值捕获**：默认情况下，范围基于的循环使用引用捕获元素，但如果需要，也可以通过值来捕获元素。

9. **支持常量迭代**：可以安全地遍历常量容器，而不需要担心修改容器的内容。

10. **与现代C++特性协同**：与 C++11 中的其他特性（如自动类型推导、Lambda 表达式、结构化绑定等）协同工作，提高了编写现代C++代码的效率和灵活性。

### 2.1.示例对比

**传统的 for 循环**：

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
for (size_t i = 0; i < v.size(); ++i) {
    std::cout << v[i] << " ";
}
```

**范围基于的循环**：

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
for (int n : v) {
    std::cout << n << " ";
}
```

在这个例子中，范围基于的循环更加简洁，且避免了使用容器的 `.size()` 方法，减少了代码中的数字。

总的来说，范围基于的循环提供了一种更现代、更安全且更易于理解的方式来遍历序列，是处理容器和数组的推荐方法。

## 3.如何使用范围基于的循环遍历一个多维数组？

在 C++ 中，范围基于的循环（Range-based for loop）通常用于遍历一维容器或序列。然而，对于多维数组，这种循环需要一些额外的步骤来实现。由于 C++ 不直接支持多维范围基于的循环，你需要使用嵌套循环来遍历每个维度。

以下是一些遍历多维数组的方法：

### 3.1.方法 1：使用嵌套的范围基于的循环

对于一个二维数组或容器，你可以使用两个嵌套的范围基于的循环：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个 3x3 的二维向量
    std::vector<std::vector<int>> vec = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // 使用嵌套的范围基于的循环遍历二维向量
    for (const auto& row : vec) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl; // 每行结束后换行
    }

    return 0;
}
```

### 3.2.方法 2：使用标准库算法

你可以使用标准库中的算法，如 `std::for_each`，来遍历多维数组：

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

void printElement(int elem) {
    std::cout << elem << " ";
}

int main() {
    std::vector<std::vector<int>> vec = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // 使用 std::for_each 遍历二维向量的每一行
    for (auto& row : vec) {
        std::for_each(row.begin(), row.end(), printElement);
        std::cout << std::endl; // 每行结束后换行
    }

    return 0;
}
```

### 3.3.方法 3：使用递归模板函数

对于任意维度的数组，你可以使用递归模板函数来实现范围基于的遍历：

```cpp
#include <iostream>
#include <vector>

// 递归模板函数
template <typename T>
void print(const T& t) {
    for (const auto& elem : t) {
        print(elem);
    }
}

// 特化版本用于一维数组或向量
template <typename T>
void print(const std::vector<T>& v) {
    for (T elem : v) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<std::vector<int>> vec = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // 使用特化的 print 函数
    print(vec);

    return 0;
}
```

在这个例子中，我们定义了一个递归模板函数 `print` 来处理多维数组的遍历，并且提供了一个特化版本用于一维数组或向量。

### 3.4.方法 4：使用循环索引

虽然这不是范围基于的循环，但使用循环索引是遍历多维数组的传统方法：

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<int>> vec = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // 使用循环索引遍历二维向量
    for (size_t i = 0; i < vec.size(); ++i) {
        for (size_t j = 0; j < vec[i].size(); ++j) {
            std::cout << vec[i][j] << " ";
        }
        std::cout << std::endl; // 每行结束后换行
    }

    return 0;
}
```

尽管这种方法不是范围基于的循环，但它在处理多维数组时非常有效。

### 3.5.总结

虽然 C++ 不直接支持多维范围基于的循环，但通过上述方法，你可以有效地遍历多维数组或容器。选择哪种方法取决于你的具体需求和代码风格。

## 4.在C++11中，如果我想在循环中修改容器中的元素，应该如何做？

在 C++11 中，如果你想在范围基于的循环中修改容器中的元素，你应该使用迭代器或者使用下标操作符（针对支持随机访问的容器，如 `std::vector`、`std::array` 等）。以下是一些示例：

### 4.1.使用迭代器

对于 `std::vector`、`std::list` 或其他提供迭代器的容器，你可以通过迭代器修改元素：

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};

    for (auto it = v.begin(); it != v.end(); ++it) {
        *it += 10; // 使用解引用操作符修改元素
    }

    for (int n : v) { // 再次遍历打印修改后的元素
        std::cout << n << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 4.2.使用下标操作符

对于支持随机访问的容器，如 `std::vector` 或 `std::array`，你可以通过下标访问和修改元素：

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};

    for (size_t i = 0; i < v.size(); ++i) {
        v[i] += 10; // 使用下标操作符修改元素
    }

    for (int n : v) { // 再次遍历打印修改后的元素
        std::cout << n << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 4.3.使用 `std::transform`

你也可以使用 `std::transform` 算法来修改容器中的元素：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};

    std::transform(v.begin(), v.end(), v.begin(), [](int n) {
        return n + 10;
    });

    for (int n : v) { // 遍历打印修改后的元素
        std::cout << n << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在这个例子中，`std::transform` 将每个元素映射到一个新的值，这里简单地将每个元素值增加了10。

### 4.4.注意事项

- 在范围基于的循环中，如果你使用 `auto` 关键字并且通过值捕获元素，那么你将无法修改原始容器中的元素。确保你通过引用捕获元素（即使用 `auto&`），或者使用迭代器。
- 对于不支持修改的容器（如 `std::list`），某些修改操作（如在迭代器指向的元素之前插入或删除元素）可能不可用或行为不同。

使用这些方法，你可以在 C++11 中的范围基于循环中修改容器的元素。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
