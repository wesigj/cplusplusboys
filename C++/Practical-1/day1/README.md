# C++ Practical-1 day1

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.hello world

```cpp
#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "Hello world!" << std::endl;
    std::cin.get();
    return 0;
}
```

### 1.1.main函数中 argv argv含义

在C++中，`main`函数是一个特殊的函数，它是每个C++程序的入口点。`main`函数可以有两种不同的形式：

1. `int main()`
2. `int main(int argc, char *argv[])`

其中，`argc`和`argv`是可选参数，它们用于处理命令行参数。

- `argc`（argument count）是一个整型变量，表示命令行参数的数量。
- `argv`（argument vector）是一个字符指针数组，包含了命令行参数的值。

当你在命令行（如终端或命令提示符）中运行一个程序时，你可以传递一些参数给程序。这些参数会通过`argc`和`argv`传递给`main`函数。

例如，如果你有一个C++程序，你可以通过以下方式运行它：

```bash
./program arg1 arg2 arg3
```

在这个例子中：

- `argc`的值将是4（包括程序本身的名称，所以实际参数数量是3）。
- `argv`将包含以下元素：
  - `argv[0]`是程序的名称（"program"）。
  - `argv[1]`是第一个参数（"arg1"）。
  - `argv[2]`是第二个参数（"arg2"）。
  - `argv[3]`是第三个参数（"arg3"）。

这是`main`函数使用`argc`和`argv`的一个简单示例：

```cpp
#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "Number of arguments: " << argc << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << "Argument " << i << ": " << argv[i] << std::endl;
    }
    return 0;
}
```

在这个程序中，`main`函数打印出参数的数量和每个参数的值。如果你运行这个程序并传递一些参数，它将输出这些参数的数量和值。

## 2.annotate 注释

```cpp

// #include <iostream>

/* #include <iostream> */

#if 0
#include <iostream>
#endif

#if 1
#include <iostream>
#endif

```

在C++中，有几种不同的注释方法：

1. **单行注释**：
   使用两个斜杠 `//` 开始，直到行尾的所有内容都会被视为注释。

   ```cpp
   // 这是一个单行注释
   int a = 5; // 这也是一个单行注释
   ```

2. **多行注释**：
   使用 `/*` 开始，`*/` 结束。这种注释方式可以跨越多行。

   ```cpp
   /* 这是一个多行注释
      它可以跨越多行。 */
   int a = 5;
   ```

3. **文档注释**（也称为文档化注释）：
   使用 `/**` 开始，`*/` 结束。这种注释方式通常用于生成文档。

   ```cpp
   /**
    * 这是一个文档注释
    * 它通常用于生成文档。
    */
   int a = 5;
   ```

4. **嵌套注释**：
   C++标准不支持在多行注释中嵌套注释。如果你尝试这样做，只有第一个 `*/` 之前的部分会被当作注释，剩下的部分会被当作代码。

   ```cpp
   /* 这是一个注释
   /* 这不是注释，而是代码 */
   int a = 5; // 这会导致编译错误
   ```

5. **条件编译注释**：
   使用 `#if`, `#ifdef`, `#ifndef`, `#else`, `#elif`, `#endif` 指令可以创建条件编译注释，这些指令可以控制代码的编译。

   ```cpp
   #define DEBUG
   #if defined(DEBUG)
   // 调试模式下的代码
   std::cout << "Debug mode" << std::endl;
   #else
   // 非调试模式下的代码
   std::cout << "Release mode" << std::endl;
   #endif
   ```

6. **预处理指令注释**：
   使用 `#` 开头的预处理指令，如 `#include`, `#define`, `#undef` 等，虽然它们不是注释，但它们用于控制编译过程。

   ```cpp
   #include <iostream> // 包含标准输入输出库
   #define PI 3.14159 // 定义常量PI
   ```

在实际编程中，单行注释是最常用的，因为它简洁且易于使用。多行注释则适用于需要注释掉较大块代码的情况。文档注释通常与文档生成工具（如Doxygen）一起使用，以自动提取注释生成程序文档。

## 3.判断闰年

在C++中，判断一个年份是否为闰年可以通过以下规则：

1. 如果年份能被4整除且不能被100整除，则为闰年。
2. 如果年份能被400整除，则也是闰年。

基于这些规则，你可以使用以下C++代码来判断一个年份是否为闰年：

```cpp
#include <iostream>

bool isLeapYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return true;
    } else {
        return false;
    }
}

int main() {
    int year;
    std::cout << "Enter a year: ";
    std::cin >> year;

    if (isLeapYear(year)) {
        std::cout << year << " is a leap year." << std::endl;
    } else {
        std::cout << year << " is not a leap year." << std::endl;
    }

    return 0;
}
```

这段代码定义了一个`isLeapYear`函数，它接受一个整数参数`year`，并返回一个布尔值，指示该年份是否为闰年。然后在`main`函数中，程序会提示用户输入一个年份，然后调用`isLeapYear`函数来判断并输出结果。

这是一个简单且有效的判断闰年的方法。

## 4.union

在C++中，`union`是一种特殊的数据类型，允许在相同的内存位置存储不同的数据类型。`union`可以包含多个成员，但任何时候只能存储其中一个成员的值。`union`的大小由最大的成员决定。

下面是一个`union`的简单示例：

```cpp
#include <iostream>
#include <cstring>
// 定义一个名为Data的union
union Data {
    int    i;
    double f;
    char   str[20];
    struct {
        int x;
        int y;
        int z;
    } u;
    int k;
};

int main() {
    Data data;

    // 存储整数值
    data.i = 10;
    std::cout << "data.i: " << data.i << std::endl; // 输出: data.i: 10

    // 存储浮点数值
    data.f = 220.5;
    std::cout << "data.f: " << data.f << std::endl; // 输出: data.f: 220.5

    // 存储字符串
    strcpy(data.str, "C++ Union");
    std::cout << "data.str: " << data.str << std::endl; // 输出: data.str: C++ Union

    data.u.x = 1;
    data.u.y = 2;
    data.u.z = 3;
    data.k   = 4; // 覆盖掉第一个int空间值
    printf("%d %d %d %d\n", data.u.x, data.u.y, data.u.z, data.k);
    return 0;
}
```

在这个例子中，`Data`是一个`union`，它包含一个整数`i`，一个浮点数`f`和一个字符数组`str`。在`main`函数中，我们创建了一个`Data`类型的变量`data`，并分别给它的成员赋值。

请注意，尽管`data`可以存储不同类型的值，但一次只能存储一个成员的值。这意味着，当你给`data.f`赋值时，`data.i`的值会被覆盖，同样，当你给`data.str`赋值时，`data.i`和`data.f`的值都会被覆盖。

`union`的一个常见用途是处理不同的数据类型，但你知道在任何给定时间只会使用其中一种类型。这可以节省内存，因为不需要为每种可能的类型分配单独的空间。

**注意**：在使用`union`时，需要确保不会同时访问多个成员，因为这会导致未定义的行为。此外，当使用`union`存储和访问数据时，需要格外小心，以避免数据覆盖和内存泄漏等问题。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/img/wechat.jpg width=60% />
