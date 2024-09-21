# C++ Practical-1 day3

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.inline

在C++中，`inline` 关键字是一种函数修饰符，用于建议编译器在编译时将函数的代码直接插入到每个函数调用的地方，从而避免函数调用的开销。这通常用于小型函数，特别是那些包含少量指令的函数。

### 1.1.作用和优点

1. **减少函数调用开销**：通过避免函数调用的额外开销，可以提高程序的执行效率。
2. **多个定义**：`inline` 函数允许在程序中有多个定义点，这对于模板元编程特别有用。
3. **模板**：与模板结合使用时，`inline` 函数可以确保模板代码在每个使用点都得到实例化。

### 1.2.示例1：简单的内联函数

```cpp
#include <iostream>

// 内联函数定义
inline int add(int a, int b) {
    return a + b;
}

int main() {
    int result = add(5, 3);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
```

在这个示例中，`add` 函数被定义为内联函数。这意味着编译器将尝试在每次调用 `add` 时直接将其代码替换为 `return a + b;`。

### 1.3.示例2：内联成员函数

```cpp
#include <iostream>

class Calculator {
public:
    // 内联成员函数
    inline int add(int a, int b) const {
        return a + b;
    }
};

int main() {
    Calculator calc;
    int result = calc.add(5, 3);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
```

在这个示例中，`Calculator` 类的 `add` 成员函数被定义为内联函数。

### 1.4.示例3：内联函数与模板

```cpp
#include <iostream>

// 内联模板函数
template <typename T>
inline T max(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    int i = max(3, 7);
    double d = max(6.4, 3.2);
    std::cout << "Max int: " << i << std::endl;
    std::cout << "Max double: " << d << std::endl;
    return 0;
}
```

在这个示例中，`max` 函数是一个模板内联函数，它可以用于不同的数据类型。

### 1.5.注意事项

- **编译器优化**：虽然你可以通过 `inline` 关键字请求内联，但最终是否内联由编译器决定。编译器可能会忽略内联请求，特别是对于较大的函数。
- **定义点**：对于内联函数，定义必须在包含它的每个源文件中可见。对于模板和类内的内联函数，定义通常与声明一起放在头文件中。
- **递归函数**：递归函数通常不会被内联，因为递归调用可能导致大量的代码膨胀。

`inline` 关键字是一个有力的工具，可以帮助优化程序性能，特别是在调用小型函数时。然而，它应该谨慎使用，以避免潜在的代码膨胀和维护问题。

## 2.函数综合练习题

当然，这里有一个C++函数的综合练习题，包括问题描述、代码实现和答案解析。

### 2.1.练习题1：计算阶乘

**问题描述**：
编写一个C++程序，计算并输出一个给定非负整数的阶乘。阶乘函数定义为：n! = n * (n-1) * (n-2) * ... * 3 * 2 * 1。0的阶乘定义为1。

**代码实现**：

```cpp
#include <iostream>

unsigned long long factorial(int n) {
    if (n == 0) return 1;
    unsigned long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int main() {
    int number;
    std::cout << "Enter a non-negative integer: ";
    std::cin >> number;
    if (number < 0) {
        std::cout << "Factorial is not defined for negative numbers." << std::endl;
    } else {
        std::cout << "Factorial of " << number << " = " << factorial(number) << std::endl;
    }
    return 0;
}
```

**答案解析**：
这个程序定义了一个`factorial`函数，它使用一个循环来计算阶乘。主函数读取用户输入的非负整数，并调用`factorial`函数计算阶乘。

### 2.2.练习题2：寻找数组中的最大值和最小值

**问题描述**：
编写一个C++程序，找出一个整数数组中的最大值和最小值，并输出它们。

**代码实现**：

```cpp
#include <iostream>
#include <vector>
#include <limits>

int main() {
    std::vector<int> numbers = {3, 9, 1, 4, 5, 7, 8, 2, 6};
    int max_value = std::numeric_limits<int>::min();
    int min_value = std::numeric_limits<int>::max();

    for (int num : numbers) {
        if (num > max_value) {
            max_value = num;
        }
        if (num < min_value) {
            min_value = num;
        }
    }

    std::cout << "Max value: " << max_value << std::endl;
    std::cout << "Min value: " << min_value << std::endl;

    return 0;
}
```

**答案解析**：
这个程序使用`std::vector`存储整数数组。它初始化两个变量`max_value`和`min_value`来存储数组中的最大值和最小值，然后遍历数组，使用条件语句来更新这两个变量的值。

### 2.3.练习题3：计算字符串中字符的出现次数

**问题描述**：
编写一个C++程序，计算并输出一个给定字符串中每个字符的出现次数。

**代码实现**：

```cpp
#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    std::string text;
    std::cout << "Enter a string: ";
    std::getline(std::cin, text);

    std::unordered_map<char, int> char_count;
    for (char c : text) {
        char_count[c]++;
    }

    std::cout << "Character counts:" << std::endl;
    for (const auto &kv : char_count) {
        std::cout << kv.first << ": " << kv.second << std::endl;
    }

    return 0;
}
```

**答案解析**：
这个程序使用`std::unordered_map`来存储每个字符及其出现的次数。它遍历字符串中的每个字符，并使用字符作为键来更新计数器。最后，它遍历映射并输出每个字符及其计数。

### 2.4.练习题4：实现一个简单的计算器

**问题描述**：
编写一个C++程序，实现一个简单的计算器，能够执行加、减、乘、除四种运算。

**代码实现**：

```cpp
#include <iostream>

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b != 0) {
        return a / b;
    } else {
        std::cerr << "Error: Division by zero" << std::endl;
        return 0;
    }
}

int main() {
    double num1, num2;
    char operation;
    std::cout << "Enter first number: ";
    std::cin >> num1;
    std::cout << "Enter second number: ";
    std::cin >> num2;
    std::cout << "Enter operation (+, -, *, /): ";
    std::cin >> operation;

    switch (operation) {
        case '+':
            std::cout << num1 << " + " << num2 << " = " << add(num1, num2) << std::endl;
            break;
        case '-':
            std::cout << num1 << " - " << num2 << " = " << subtract(num1, num2) << std::endl;
            break;
        case '*':
            std::cout << num1 << " * " << num2 << " = " << multiply(num1, num2) << std::endl;
            break;
        case '/':
            std::cout << num1 << " / " << num2 << " = " << divide(num1, num2) << std::endl;
            break;
        default:
            std::cerr << "Invalid operation" << std::endl;
    }

    return 0;
}
```

**答案解析**：
这个程序定义了四个函数来执行基本的算术运算。主函数读取用户输入的两个数字和一个运算符，然后根据运算符调用相应的函数并输出结果。如果用户尝试除以零，程序会输出错误消息。

这些练习题覆盖了函数定义、循环、条件语句、输入输出和基本的算术运算，适合用来练习C++函数的使用。

## 3.前向声明

在C++中，类前向声明（forward declaration）是一种声明类的方式，而不定义类的具体内容。这在你需要引用某个类，但又不想包含定义该类的头文件时非常有用。前向声明通常用于类的指针或引用，以及当两个或多个类相互引用时。

### 3.1.为什么需要前向声明？

1. **避免头文件的循环依赖**：当两个或多个类相互引用时，可能会导致头文件的循环依赖问题。前向声明可以打破这种循环依赖。

2. **减少包含头文件**：如果你只需要使用类的指针或引用，而不是完整的类定义，前向声明可以减少包含头文件的需要，从而减少编译时间。

### 3.2.如何前向声明一个类？

使用`class`关键字加上类名来进行前向声明，如下所示：

```cpp
class MyClass; // 前向声明
```

### 3.3.示例1：避免循环依赖

假设有两个类`A`和`B`，类`A`有一个类`B`的成员，而类`B`有一个类`A`的成员。下面是如何使用前向声明来解决这个问题：

```cpp
// A.h
#ifndef A_H
#define A_H

class B; // 前向声明类B

class A {
    B* b_ptr; // 类B的指针
public:
    A(B* b);
    // ...
};

#endif // A_H
```

```cpp
// B.h
#ifndef B_H
#define B_H

#include "A.h" // 包含A.h以获取A的前向声明

class B {
    A* a_ptr; // 类A的指针
public:
    B(A* a);
    // ...
};

#endif // B_H
```

在这个例子中，`A.h`前向声明了类`B`，而`B.h`包含了`A.h`以获取类`A`的前向声明。这样，两个类就可以相互引用，而不会直接包含对方的完整定义。

### 3.4.示例2：使用类指针或引用

如果你只需要使用类的指针或引用，而不需要完整的类定义，可以使用前向声明：

```cpp
// ForwardDeclaration.h
#ifndef FORWARDDECLARATION_H
#define FORWARDDECLARATION_H

class ForwardClass; // 前向声明

void function(ForwardClass& obj); // 使用前向声明的类的引用

#endif // FORWARDDECLARATION_H
```

```cpp
// ForwardDeclaration.cpp
#include "ForwardDeclaration.h"
#include "ForwardClass.h" // 实际定义

void function(ForwardClass& obj) {
    // ...
}
```

在这个例子中，`ForwardDeclaration.h`前向声明了`ForwardClass`，而`ForwardDeclaration.cpp`包含了`ForwardClass.h`以获取完整的类定义。

### 3.5.注意事项

- 前向声明只能用于声明类的指针、引用或作为参数传递对象。如果你需要创建类的对象实例或访问其成员，就必须包含完整的类定义。

- 前向声明不适用于需要知道类大小或布局的情况。

- 过度使用前向声明可能会使代码难以理解和维护，因为它隐藏了类的实际定义，所以在使用时应该谨慎。

## 4.swap函数

在C++中，`swap`函数是一个非常有用的函数，它用于交换两个变量的值。C++标准库提供了`std::swap`函数，但你也可以自己实现一个简单的`swap`函数来加深理解。

以下是一个简单的`swap`函数实现，以及如何在程序中使用它：

### 4.1.示例1：自定义`swap`函数

```cpp
#include <iostream>

// 自定义swap函数
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 10;
    int y = 20;

    std::cout << "Before swap: x = " << x << ", y = " << y << std::endl;

    swap(x, y);

    std::cout << "After swap: x = " << x << ", y = " << y << std::endl;

    return 0;
}
```

### 4.2.示例2：使用`std::swap`

C++标准库提供了一个`std::swap`函数，你可以使用它来交换两个变量的值：

```cpp
#include <iostream>
#include <algorithm> // 包含std::swap

int main() {
    int x = 10;
    int y = 20;

    std::cout << "Before swap: x = " << x << ", y = " << y << std::endl;

    std::swap(x, y);

    std::cout << "After swap: x = " << x << ", y = " << y << std::endl;

    return 0;
}
```

### 4.3.示例3：交换类对象

如果你有一个类，并希望交换两个对象，你可以在你的类中提供`swap`成员函数：

```cpp
#include <iostream>

class MyClass {
public:
    int value;

    MyClass(int val) : value(val) {}

    friend void swap(MyClass& a, MyClass& b) {
        using std::swap;
        swap(a.value, b.value);
    }
};

int main() {
    MyClass obj1(10);
    MyClass obj2(20);

    std::cout << "Before swap: obj1 = " << obj1.value << ", obj2 = " << obj2.value << std::endl;

    swap(obj1, obj2);

    std::cout << "After swap: obj1 = " << obj1.value << ", obj2 = " << obj2.value << std::endl;

    return 0;
}
```

在这个例子中，`MyClass`有一个`value`成员变量。我们定义了一个`swap`友元函数来交换两个`MyClass`对象的`value`成员。

### 4.4.注意事项

- 当使用`std::swap`时，如果类型提供了自己的`swap`特化版本，编译器将使用该特化版本而不是标准库中的通用版本。

- 自定义`swap`函数时，使用模板可以使其适用于任何类型的数据。

- 在实现类时，提供一个`swap`成员函数或友元函数可以确保你的类对象可以正确地使用`std::swap`。

- 交换操作应该尽可能地高效，避免不必要的复制，特别是对于大型对象。这就是为什么在自定义`swap`函数时通常使用`std::swap`或临时变量来减少复制次数。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
