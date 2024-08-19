# C++面试基础系列-bit_field

## Overview

“ 位域 “ 或 “ 位段 “(Bit field)为一种数据结构，可以把数据以位的形式紧凑的储存，并允许程序员对此结构的位进行操作。

- 优点
  - 它可以使数据单元节省储存空间，当程序需要成千上万个数据单元时，这种方法就显得尤为重要。
  - 位段可以很方便的访问一个整数值的部分内容从而可以简化程序源代码。
- 缺点：
  - 而这种数据结构的缺点在于，位段实现依赖于具体的机器和系统，在不同的平台可能有不同的结果，这导致了位段在本质上是不可移植的。
- 关键点：
  - 位域在内存中的布局是与机器有关的
  - 位域的类型必须是整型或枚举类型，带符号类型中的位域的行为将因具体实现而定
  - 取地址运算符（&）不能作用于位域，任何指针都无法指向类的位域

## 1.bit_field位域

在C和C++编程中，`bit_field`（位字段）是一种数据结构技术，它允许程序员访问和操作内存中存储的整数的特定部分。以下是位字段的一些关键点：

1. **内存节省** ：位字段允许程序员将多个数据项存储在一个小的存储单元内，从而节省内存空间。
2. **数据表示** ：位字段通常用于表示具有固定位宽的数据，例如状态标志、控制位或特定的配置选项。
3. **声明方式** ：
4. **位宽指定** ：在声明位字段时，可以通过冒号(`:`)后跟数字来指定每个字段的位宽。
5. **位操作** ：位字段常用于位操作，如位与(`&`)、位或(`|`)、位异或(`^`)、位非(`~`)和位移操作。
6. **数据对齐** ：位字段可能会影响数据的内存对齐，编译器可能会在位字段结构体中添加填充位以满足对齐要求。
7. **可移植性问题** ：位字段的布局（即位字段在内存中的顺序）可能依赖于编译器和平台，因此可能存在可移植性问题。
8. **访问方式** ：位字段通常作为结构体的成员来访问，可以结合点(`.`)或箭头(`->`)操作符使用。
9. **应用场景** ：
   - 硬件设备寄存器的访问。
   - 状态机的状态表示。
   - 配置选项的存储。
10. **限制** ：位字段的使用应谨慎，因为它们可能会使代码难以理解和维护，且容易出错。
11. **类型安全** ：位字段本身是强类型，但位字段的运算可能导致隐式类型转换。
12. **编译器特性** ：某些编译器可能提供特定的特性或扩展来支持位字段的声明和操作。

位字段是C和C++中一种强大的特性，尤其适用于需要精细控制内存使用和硬件级编程的场合。然而，由于它们可能带来的复杂性和可移植性问题，建议仅在确实需要时才使用位字段。

## 2.bit_field字节对齐

### 2.1.位域的声明

位域通常使用结构体声明， 该结构声明为每个位域成员设置名称，并决定其宽度：

```cpp
struct bit_field_name
{
 type member_name : width;
};
```

| Elements       | Description                                                   |
| -------------- | ------------------------------------------------------------- |
| bit_field_name | 位域结构名                                                    |
| type           | 位域成员的类型，必须为 int、signed int 或者 unsigned int 类型 |
| member_name    | 位域成员名                                                    |
| width          | 规定成员所占的位数                                            |

```cpp
struct BitField {
    unsigned int is_enabled : 1; // 1位用于表示是否启用
    unsigned int            : 3; // 3位用于表示是否启用
    unsigned int has_data   : 1; // 1位用于表示是否有数据
    unsigned int length1    : 3; // 3位用于表示是否有数据
    unsigned int length2    : 8; // 8位用于表示是否有数据
    // 可以继续添加更多位字段
};
```

- length1其容量为 2^3 = 8，即赋值范围应为 [0,7]。
- length2其容量为 2^8 = 256，即赋值范围应为 [0,255]。
- 未命名的位域，表示占位，字节对齐，仅起填充作用，并无实际意义。

### 2.2.位域的对齐

一个位域成员不允许跨越两个 unsigned int 的边界，如果成员声明的总位数超过了一个 unsigned int 的大小， 那么编译器会自动移位位域成员，使其按照 unsigned int 的边界对齐。
例如：

```cpp
struct stuff 
{
 unsigned int field1: 30;
 unsigned int field2: 4;
 unsigned int field3: 3;
};
```

`field1` + `field2` = 34 Bits，超出 32 Bits, 编译器会将 `field2`移位至下一个 unsigned int 单元存放， stuff.field1 和 stuff.field2 之间会留下一个 2 Bits 的空隙， stuff.field3 紧跟在 stuff.field2 之后，该结构现在大小为 2 * 32 = 64 Bits。

这个空洞可以用之前提到的未命名的位域成员填充，我们也可以使用一个宽度为 0 的未命名位域成员令下一位域成员与下一个整数对齐。
例如:

```cpp
struct stuff 
{
 unsigned int field1: 30;
 unsigned int       : 2;
 unsigned int field2: 4;
 unsigned int       : 0;
 unsigned int field3: 3; 
};
```

这里 stuff.field1 与 stuff.field2 之间有一个 2 Bits 的空隙，stuff.field3 则存储在下一个 unsigned int 中，该结构现在大小为 3 * 32 = 96 Bits。

## 3.位域的初始化和位的重映射

### 3.1.初始化

位域的初始化与普通结构体初始化的方法相同，这里列举两种，如下:

```cpp
struct stuff s1= {20,8,6};
```

或者直接为位域成员赋值

```cpp
struct stuff s1;
s1.field1 = 20;
s1.field2 = 8;
s1.field3 = 4;
```

### 3.2.位域的重映射 (Re-mapping)

声明一个 大小为 32 Bits 的位域

```cpp
struct box {
 unsigned int ready:     2;
 unsigned int error:     2;
 unsigned int command:   4;
 unsigned int sector_no: 24;
}b1;
```

#### 3.2.1.利用重映射将位域归零

```cpp
int* p = (int *) &b1;  // 将 "位域结构体的地址" 映射至 "整形（int*) 的地址" 
*p = 0;                // 清除 s1，将各成员归零
```

#### 3.2.2.利用联合 (union) 将 32 Bits 位域 重映射至 unsigned int 型

先简单介绍一下联合

> “联合” 是一种特殊的类，也是一种构造类型的数据结构。在一个 “联合” 内可以定义多种不同的数据类型， 一个被说明为该 “联合” 类型的变量中，允许装入该 “联合” 所定义的任何一种数据，这些数据共享同一段内存，以达到节省空间的目的
>
> “联合” 与 “结构” 有一些相似之处。但两者有本质上的不同。在结构中各成员有各自的内存空间， 一个结构变量的总长度是各成员长度之和（空结构除外，同时不考虑边界调整）。而在 “联合” 中，各成员共享一段内存空间， 一个联合变量的长度等于各成员中最长的长度。应该说明的是， 这里所谓的共享不是指把多个成员同时装入一个联合变量内， 而是指该联合变量可被赋予任一成员值，但每次只能赋一种值， 赋入新值则冲去旧值。

我们可以声明以下联合:

```cpp
union u_box {
  struct box st_box;   
  unsigned int ui_box;
};
```

x86 系统中 unsigned int 和 box 都为 32 Bits, 通过该联合使 st_box 和 ui_box 共享一块内存。具体位域中哪一位与 unsigned int 哪一位相对应，取决于编译器和硬件。
利用联合将位域归零，代码如下：

```cpp
union u_box u;
u.ui_box = 0;
```

## 4.C++ std::bitset

- 尽管位字段在某些低级编程或硬件操作中很有用，但现代C++提供了一些替代方案，这些方案可能更加灵活和可移植。例如，
- 可以使用 `std::bitset`来访问和操作位集合，它提供了一种类型安全的方式来处理位字段，而且不依赖于特定的硬件或编译器特性 。
- 此外，对于需要表示多个布尔标志或小数据字段的情况，可以使用联合体（union）和位操作来实现类似的功能，但需要手动管理位的读写操作

std::bitset是C++标准模板库（STL）中的一个类模板，用于表示和操作固定大小的位集合（bit set）。以下是std::bitset的一些关键特性和用法：

- 类型安全：std::bitset提供了一种类型安全的方式来访问和操作位。
- 固定大小：与C语言中的位字段不同，std::bitset的大小在编译时确定，并且是固定的。
- 声明和初始化：

```cpp
std::bitset<N> b;
std::bitset<N> b2(10); // 所有位初始化为 0，除了最后一位设置为 1
std::bitset<N> b3 = ~b2; // 位取反
```

- 访问位：使用operator[]来访问和修改特定的位。

```cpp
bool bit = b[3]; // 获取第 4 位的值
b[3] = 1; // 设置第 4 位为 1
```

- 设置和清除位：提供set()和reset()成员函数来设置或清除特定的位。

```cpp
b.set(3); // 设置第 4 位为 1
b.reset(3); // 清除第 4 位
```

- 翻转位：flip()成员函数用于翻转指定位的状态。

```cpp
b.flip(3); // 翻转第 4 位的状态
```

- 统一操作：提供set()和reset()的重载版本，允许一次性设置或清除多个位。

```cpp
b.set(3, 4, 5); // 同时设置第 4、5、6 位
```

- 位操作：支持位运算符&（与）、|（或）、^（异或）和~（取反）。

```cpp
std::bitset<N> b1, b2;
std::bitset<N> b3 = b1 & b2; // 位与
std::bitset<N> b4 = b1 | b2; // 位或
std::bitset<N> b5 = b1 ^ b2; // 位异或
std::bitset<N> b6 = ~b1; // 位取反
```

- 转换：可以将std::bitset对象转换为整数类型，或从整数类型构造std::bitset对象。

```cpp
int i = 0b11001100;
std::bitset<8> b(i);
std::bitset<8> b2 = b;
int j = static_cast<int>(b2);
```

- 大小和索引：std::bitset的大小由模板参数指定，位的索引从0开始。
- 迭代器：std::bitset不提供迭代器，因为它是一个连续的位集合。
- 效率：对于固定大小的位操作，std::bitset通常比使用数组或向量（vector）更高效。

std::bitset是处理位字段操作的现代C++替代方案，它提供了一个简洁、安全和高效的方式来处理位级别的数据。

---

## 关于作者

- 本文作者:WeSiGJ
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
- GitHub:[https://github.com/wesigj/CPLUSCPLUSBOYS](https://github.com/wesigj/CPLUSCPLUSBOYS)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 微信公众号:WeSiGJ

<html><body><img src="/./img/wechat.jpg" width="60%"></body></html>