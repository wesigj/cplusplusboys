# C++面试基础系列-union

- [C++面试基础系列-union](#c面试基础系列-union)
  - [1.union含义](#1union含义)
  - [2.union的关键点1](#2union的关键点1)
  - [3.union的关键点2](#3union的关键点2)
  - [4.union与struct的区别](#4union与struct的区别)
  - [关于作者](#关于作者)

---

## 1.union含义

在C++中，union是一种特殊的数据类型，它允许在相同的内存位置存储不同的数据类型。union与struct类似，但它的所有成员都共享相同的内存地址。这意味着在任意时刻只能访问union中的一个成员，如果访问了一个新的成员，那么之前存储的值将被覆盖。

```cpp
union UnionName {
    type1 member1;
    type2 member2;
    ...
    typeN memberN;
};
```

这里的type1到typeN是数据类型，member1到memberN是成员变量。

使用union的例子：

```cpp
union Data {
    int i;
    char c;
    double d;
};

int main() {
    Data data;

    // 存储一个整数
    data.i = 10;
    std::cout << "Integer: " << data.i << "\n";

    // 存储一个字符，这将覆盖data.i的值
    data.c = 'a';
    std::cout << "Character: " << data.c << "\n";

    // data.i的值已经被覆盖，所以输出将不是10
    std::cout << "Integer after storing character: " << data.i << "\n";

    return 0;
}
```

## 2.union的关键点1

- union的所有成员始于相同的内存地址。
- union的大小等于其最大成员的大小。在上面的例子中，Data的大小将等于一个double的大小，因为double通常比int和char占用更多的字节。
- union可用于内存对齐和打包，以及访问字节级数据。
- union不允许有引用类型的成员，也不能有继承或虚函数。
- union可以用于位域操作，尽管这通常不是推荐的做法。

## 3.union的关键点2

联合（union）是一种节省空间的特殊的类，一个 union 可以有多个数据成员，但是在任意时刻只有一个数据成员可以有值。当某个成员被赋值后其他成员变为未定义状态。联合有如下特点：

- 默认访问控制符为 public
- 可以含有构造函数、析构函数
- 不能含有引用类型的成员
- 不能继承自其他类，不能作为基类
- 不能含有虚函数
- 匿名 union 在定义所在作用域可直接访问 union 成员
- 匿名 union 不能包含 protected 成员或 private 成员
- 全局匿名联合必须是静态（static）的

## 4.union与struct的区别

- struct的每个成员都有自己的内存位置，而union的所有成员共享一个内存位置。
- struct可以有构造函数、析构函数和成员函数，而union不能。
- struct可以用于继承，而union不能。

union在需要节约内存或需要通过同一个内存位置访问不同类型的数据时非常有用，但使用时需要小心，以避免数据被意外覆盖。

---

## 关于作者

- 本文作者:WeSiGJ
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 微信公众号:WeSiGJ

<html><body><img src="/./img/wechat.jpg" width="60%"></body></html>
