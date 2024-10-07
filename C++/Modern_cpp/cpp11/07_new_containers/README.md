# C++11 07-新的容器 new containers

- [C++11 07-新的容器 new containers](#c11-07-新的容器-new-containers)
  - [Overview](#overview)
  - [1.新的容器 new containers](#1新的容器-new-containers)
  - [关于作者](#关于作者)

## Overview

- 详细请看STL专栏

---

## 1.新的容器 new containers

C++11 引入了几种新的容器，以满足更广泛的编程需求。以下是 C++11 中新增的容器：

1. **`std::array`**：
   - 一个固定大小的数组容器，提供了标准容器的接口。
   - 它封装了一个原生数组，提供了范围检查和异常处理。

   ```cpp
   #include <array>
   std::array<int, 4> arr = {1, 2, 3, 4};
   ```

2. **`std::tuple`**：
   - 一个可以存储不同类型值的容器。
   - 它提供了一种方便的方式来打包和传递多个值。

   ```cpp
   #include <tuple>
   std::tuple<int, double, std::string> myTuple = {1, 2.5, "Hello"};
   ```

3. **`std::unordered_set` 和 `std::unordered_multiset`**：
   - 基于哈希表的集合容器，允许快速插入、查找和删除操作。
   - `std::unordered_multiset` 允许容器中存在重复元素。

   ```cpp
   #include <unordered_set>
   std::unordered_set<int> unordSet = {1, 2, 3, 4};
   ```

4. **`std::unordered_map` 和 `std::unordered_multimap`**：
   - 基于哈希表的关联容器，存储键值对。
   - `std::unordered_multimap` 允许容器中存在重复键。

   ```cpp
   #include <unordered_map>
   std::unordered_map<int, std::string> unordMap = {{1, "one"}, {2, "two"}};
   ```

5. **`std::forward_list`**：
   - 一个单向链表容器，提供了比 `std::list` 更高效的迭代器和操作。
   - 它支持快速的插入和删除操作。

   ```cpp
   #include <forward_list>
   std::forward_list<int> flist = {10, 20, 30};
   ```

6. **`std::array` 的变体**：
   - C++17 进一步扩展了 `std::array`，添加了变体类型 `std::byte` 和 `std::optional`。

这些新容器为 C++ 程序员提供了更多的选择和灵活性，使得可以更加方便地处理各种数据集合。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
