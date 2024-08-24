# C++面试基础系列-assert

[TOC]

## Overview

## 1.assert关键点

在C++中，`assert`宏是断言机制的一部分，用于在开发过程中检查程序的逻辑错误。如果断言的条件不满足，程序将终止执行，并通常会输出相关的错误信息。

以下是一些关于C++中`assert`宏的关键点：

- 定义：`assert`宏定义在`<cassert>`或`<assert.h>`头文件中。

- 语法：`assert`宏的基本语法是`assert(expression)`，其中`expression`是一个在运行时求值的表达式。

- 行为：如果`expression`的值为`true`，程序继续正常执行。如果`expression`的值为`false`，则程序将打印一条错误消息，并终止执行。

- 调试：`assert`宏通常用于调试阶段，以确保程序的某些关键条件得到满足。在发布版本中，可以通过预处理器指令NDEBUG来禁用assert宏。

示例：

```cpp
#include <iostream>
#include <cassert>

int main() {
    int x = 10;
    assert(x > 5);  // 如果x大于5，程序继续执行
    std::cout << "x的值是：" << x << std::endl;
    assert(x < 20);  // 如果x小于20，程序继续执行
    return 0;
}
```

- 自定义消息：C++11开始支持使用`static_assert`进行编译时断言，并且可以传递一个字符串作为错误消息：

```cpp
static_assert(sizeof(int) >= 4, "int类型必须至少占用4个字节");
```

- 编译时断言：`static_assert`是在编译时检查条件是否为真的断言，如果条件为假，编译器将报错并停止编译过程。

- 性能：由于`assert`在运行时检查条件，因此在性能敏感的应用中应谨慎使用，或者在发布版本中禁用。

- 禁用断言：可以通过定义NDEBUG宏来禁用所有`assert`宏：

```cpp
#define NDEBUG
#include <cassert>
```

- 使用断言是一种很好的实践，可以帮助开发者及早发现和修复错误。然而，它们不应该被用作错误处理的主要手段，因为它们在生产环境中可能被禁用。

---

## 关于作者

- 本文作者:WeSiGJ
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 微信公众号:WeSiGJ

<img src=/./img/wechat.jpg width=60% />
