# C++面试基础系列-double_colon(::)

## Overview

## 1.double_colon(::)关键点

在C和C++中，双冒号 :: 被称为作用域解析运算符（scope resolution operator），但它在两种语言中的使用和含义略有不同：

- C语言中的::
  - 在C语言中，:: 几乎不被使用，因为它主要用于指定全局作用域，而C语言中大部分变量和函数默认就是全局作用域的。不过，:: 可以用来明确指出全局变量或函数，尤其是在与静态成员函数一起使用时。
- C++中的::
  - 在C++中，:: 的使用要普遍得多，因为它用于解决作用域的问题，尤其是在类（class）和命名空间（namespace）中。
  - 用于访问类的静态成员变量或静态成员函数：ClassName::staticMember。
  - 用于访问命名空间中的成员：NamespaceName::member。
  - 用于在类内部访问全局变量或函数，避免与局部变量或成员变量的名称冲突：::globalVariable。
  - 用于在派生类中访问基类的成员：BaseClassName::member。
- 全局作用域：
  - 在C++中，如果需要明确指出某个实体属于全局作用域，可以使用 ::。例如，在一个函数内部，如果你想要访问全局变量，可以使用 ::globalVariable。
- 类型转换：
  - 在C++中，:: 也用于类型转换，称为静态类型转换或类类型转换，例如 Type::pointer。
- 模板参数：
  - 在C++模板编程中，:: 用于指定模板参数的命名空间或类作用域，例如 std::vector<int>。
- 匿名空间：
  - 在C++中，:: 还可以用于匿名命名空间，这是一种特殊的命名空间，它提供了文件内唯一的作用域。
- C++11中的统一初始化：
- 从C++11开始，:: 不再是统一初始化（Uniform Initialization）的一部分。统一初始化使用花括号 {} 而不是 ::。

总结来说，:: 在C++中是一个关键的运算符，用于处理作用域相关的问题，而在C语言中，由于作用域规则的不同，:: 的使用相对较少。

## 关于作者

- 本文作者:WeSiGJ
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
- GitHub:[https://github.com/wesigj/CPLUSCPLUSBOYS](https://github.com/wesigj/CPLUSCPLUSBOYS)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 微信公众号:WeSiGJ

<html><body><img src="/./img/wechat.jpg" width="60%"></body></html>
