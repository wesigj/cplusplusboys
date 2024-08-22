# C++面试基础系列-enum

## 1.enum关键点

enum（枚举）是一种数据类型，在C和C++语言中用来定义命名的整数值集合。枚举为一组相关的常量提供了一种更加清晰和易于理解的表示方式。

以下是enum的一些关键点：

### 1.1.定义枚举类型

  使用enum关键字定义枚举类型，可以指定底层的整数类型（如int、unsigned int等），如果不指定，默认为`int。

```cpp
enum Color { RED, GREEN, BLUE };
```

### 1.2.枚举成员

  枚举成员是枚举类型的值，它们在定义时自动从0开始编号，每个成员依次加1。

### 1.3.指定底层类型

  可以为枚举成员指定底层类型，改变它们的存储大小和范围。

```cpp
enum Color : uint8_t { RED = 1, GREEN, BLUE };
```

### 1.4.前向声明

  在C++中，可以对枚举类型进行前向声明，但需要在后续的定义中指定其成员。

```cpp
// C++前向声明
enum Color;
// ... 后续定义
enum Color { RED, GREEN, BLUE };
```

### 1.5.作用域

  在C++中，枚举类型具有作用域，其成员名称在枚举类型的作用域内有效。C语言中的枚举成员是全局的，除非使用enum { member1, member2, ... }语法。

### 1.6.类型安全

  枚举提供了类型安全，不同枚举类型的值不能互相赋值或比较，除非显式地进行类型转换。

### 1.7.与整数的兼容性

  枚举类型可以与整数类型进行比较和赋值，但这样做可能会破坏类型安全。

### 1.8.迭代器

  C++11标准引入了基于范围的for循环，可以方便地遍历枚举类型的所有值。

```cpp
for (Color c : {RED, GREEN, BLUE}) {
    // 使用c
}
```

### 1.9.强类型枚举（C++11）

  C++11引入了强类型枚举，使用enum class关键字定义，增强了类型安全。

```cpp
enum class Color { RED, GREEN, BLUE };
```

### 1.10.位字段枚举

  枚举类型可以用于定义位字段，表示一组标志位的组合。

### 1.11.枚举作为函数参数和返回类型

  枚举类型可以作为函数的参数和返回类型，提供清晰的函数接口。

枚举是一种非常有用的语言特性，它提高了代码的可读性和可维护性，特别是在处理一组相关的常量时。在嵌入式编程、状态机实现、配置选项等方面都有广泛应用。

## 2.enum与namespace

- 解决作用域不受限带来的命名冲突问题
  - 给枚举变量命名时加前缀
  - C 程序中，为了一致性我们会把所有常量统一加上前缀。但是这样定义枚举变量的代码就显得累赘。
  - C 程序中可能不得不这样做。不过 C++ 程序员恐怕都不喜欢这种方法。替代方案是命名空间:
  - 下面代码可以用 `Color::Type c = Color::RED;` 来定义新的枚举变量

```c++
namespace Color 
{
    enum Type
    {
        RED=15,
        YELLOW,
        BLUE
    };
};
```

不过，因为命名空间是可以随后被扩充内容的，所以它提供的作用域封闭性不高。在大项目中，还是有可能不同人给不同的东西起同样的枚举类型名。

## 3.enum与struct

- 解决作用域不受限带来的命名冲突问题
  - 更“有效”的办法是用一个类或结构体来限定其作用域，例如：定义新变量的方法和上面命名空间的相同。
  - 不过这样就不用担心类在别处被修改内容。
  - 这里用结构体而非类，是因为本身希望这些常量可以公开访问。（struct默认位public类型的，class默认是private）

```c++
struct Color1
{
    enum Type
    {
        RED=102,
        YELLOW,
        BLUE
    };
};
```

## 4.C++11 的枚举类（enum class）

在C++11中，`enum class`（强类型枚举）提供了相比传统 `enum`类型更多的优势，主要表现在以下几个方面：

1. **类型安全性** ：`enum class`提供了更强的类型检查，枚举成员不能隐式转换为整数类型，这避免了隐式类型转换错误和潜在的bug。例如，在 `enum class`中声明的枚举值，它们的作用域被限定在其类型内部，不同 `enum class`中的同名枚举值不会引起冲突 。
2. **底层类型指定** ：`enum class`允许明确指定枚举成员的底层整数类型，如 `uint8_t`、`int16_t`等，提供了更多的灵活性和精确性，允许开发者根据需要选择最合适的整数类型来存储枚举成员，优化内存使用和性能 。
3. **自动枚举值** ：C++11允许 `enum class`成员自动从0开始赋值，并依次递增，简化了枚举类型的声明，减少了代码冗余 。
4. **枚举类型字面量** ：`enum class`的成员可以作为编译时常量使用，提高了代码的表达能力和可读性，使得枚举类型可以在模板元编程和编译时决策中发挥作用 。
5. **基于 `std::underlying_type`的范围** ：C++11通过提供 `std::underlying_type`模板，使得对枚举类型的值进行迭代和比较变得更加容易，提供了更多的灵活性 。
6. **枚举类型的比较操作** ：C++11标准库提供了对枚举类型的比较操作的支持，允许枚举类型的值与布尔值或其他枚举类型的值进行比较，提高了枚举类型的实用性 。

强类型枚举的引入主要是为了提高代码的安全性、清晰性、易用性和性能，这些改进反映了C++社区对于编写更安全、更高效和更易于理解的代码的持续追求 。

- 划重点
  - 新的enum的作用域不在是全局的
  - 不能隐式转换成其他类型

```c++
/**
 * @brief C++11的枚举类
 * 下面等价于enum class Color2:int
 */
enum class Color2
{
    RED=2,
    YELLOW,
    BLUE
};
Color2 c2 = Color2::RED;
cout << static_cast<int>(c2) << endl; //必须转！
```

- 可以指定用特定的类型来存储enum

```c++
enum class Color3:char;  // 前向声明

// 定义
enum class Color3:char 
{
    RED='r',
    BLUE
};
char c3 = static_cast<char>(Color3::RED);
```

## 5.class中enum常量

类的构造函数的初始化列表中进行：

```c++
class A 
{
  A(int size);  // 构造函数 
  const int SIZE ;  
}; 
A::A(int size) : SIZE(size)  // 构造函数的定义
{ 

} 
A  a(100); // 对象 a 的 SIZE 值为 100 
A  b(200); // 对象 b 的 SIZE 值为 200 
```

怎样才能建立在整个类中都恒定的常量呢？

类中的枚举常量

```cpp
class Day{
public:
    typedef enum {
        Monday= 0,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    }DayType;
};
//访问的时候通过，Day::Monday或者Person::Tuesday来进行访问。
```

枚举常量不会占用对象的存储空间，它们在编译时被全部求值。

枚举常量的缺点是：它的隐含数据类型是整数，其最大值有限，且不能表示浮点。


## 关于作者

- 本文作者:WeSiGJ
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 微信公众号:WeSiGJ

<html><body><img src="/./img/wechat.jpg" width="60%"></body></html>
