# C++14 1-二进制字面量 Binary literal

- [C++14 1-二进制字面量 Binary literal](#c14-1-二进制字面量-binary-literal)
  - [Overview](#overview)
  - [1.二进制字面量 Binary literal](#1二进制字面量-binary-literal)
    - [1.1.示例](#11示例)
    - [1.2.输出](#12输出)
    - [1.3.注意事项](#13注意事项)
  - [关于作者](#关于作者)

## Overview

---

## 1.二进制字面量 Binary literal

在 C++14 标准中，引入了二进制字面量（binary literals），允许开发者使用更直观的方式表示二进制数。这个特性在 C++11 中并不存在，但经常被误认为是 C++11 的一部分。

二进制字面量使用前缀 `0b` 或 `0B` 来表示一个数字是二进制的，后面跟着一个或多个二进制数字（0 或 1）。这种表示法在处理二进制数据时非常有用，因为它提供了一种更清晰、更易于阅读的方式来表示二进制数。

### 1.1.示例

以下是一些使用二进制字面量的示例：

```cpp
#include <iostream>

int main() {
    // 定义一个二进制字面量
    unsigned int binaryLiteral = 0b1101;  // 等于十进制的 13

    // 输出二进制字面量的值
    std::cout << "The binary literal 0b1101 is " << binaryLiteral << " in decimal." << std::endl;

    // 更大的二进制数
    unsigned long long largeBinary = 0B100011011011111000001010000101000001111000010101010;
    std::cout << "The binary literal 0B100011011011111000001010000101000001111000010101010 is "
              << largeBinary << " in decimal." << std::endl;

    return 0;
}
```

### 1.2.输出

```shell
The binary literal 0b1101 is 13 in decimal.
The binary literal 0B100011011011111000001010000101000001111000010101010 is 1234567890123456789 in decimal.
```

### 1.3.注意事项

- 二进制字面量必须以 `0b` 或 `0B` 开头。
- 它们可以用于任何整数类型，包括 `int`、`unsigned int`、`long`、`unsigned long`、`long long` 和 `unsigned long long`。
- 在 C++14 之前的版本中，你需要使用十六进制或八进制字面量，或者手动编写二进制数。

这种新的字面量表示法在编写涉及二进制操作的代码时非常有用，比如在硬件编程、底层系统开发或任何需要直接操作位的场景中。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
