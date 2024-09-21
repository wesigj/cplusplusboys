# C++ Practical day1

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实

---

## 1.求π

计算圆周率 \(\pi\) 的值可以通过多种算法实现。这里提供一个简单的 C++ 程序，使用莱布尼茨公式（Leibniz formula）来近似计算 \(\pi\) 的值。莱布尼茨公式是一个无穷级数，可以用来计算 \(\pi\)，公式如下：

\[
\pi = 4 \times \left(1 - \frac{1}{3} + \frac{1}{5} - \frac{1}{7} + \frac{1}{9} - \cdots \right)
\]

下面是一个使用莱布尼茨公式计算 \(\pi\) 的 C++ 程序示例：

```cpp
#include <iostream>
#include <iomanip>

double calculatePi(int terms) {
    double sum = 0.0;
    for (int i = 0; i < terms; i++) {
        // 交替加减1/(2n-1)
        if (i % 2 == 0)
            sum += 1.0 / (2 * i + 1);
        else
            sum -= 1.0 / (2 * i + 1);
    }
    return 4 * sum;
}

int main() {
    int terms;
    std::cout << "Enter the number of terms to approximate Pi: ";
    std::cin >> terms;

    double pi = calculatePi(terms);
    std::cout << "Calculated Pi: " << std::setprecision(15) << pi << std::endl;

    return 0;
}
```

### 1.1.程序说明

1. **函数 `calculatePi`**：这个函数接受一个整数 `terms` 作为参数，表示级数的项数。函数通过循环计算莱布尼茨级数的和，然后乘以 4 得到 \(\pi\) 的近似值。
2. **主函数**：程序首先提示用户输入想要使用的项数。然后调用 `calculatePi` 函数，并输出计算得到的 \(\pi\) 值。

### 1.2.注意

- 项数越多，计算结果越精确，但计算时间也会增加。
- 莱布尼茨公式收敛速度非常慢，对于实际应用，通常使用更高效的算法，如高斯-勒让德算法、BBP公式等。

这个程序是一个简单的示例，用于展示如何在 C++ 中实现 \(\pi\) 的计算。对于高精度或性能要求，可能需要更复杂的算法。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
