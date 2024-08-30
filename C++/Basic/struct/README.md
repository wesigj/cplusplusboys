# C++面试基础系列-struct

---

## 1.C中struct

- struct里面只能放数据类型（基本数据类型，自定义数据类型，指针等），不能放置函数
- C中不存在public、protected、private，
- C中，定义结构体变量，定义必须加struct。
- C不存在继承
- 结构体与函数的名称可以相同

## 2.C++中struct

C++中strcut基本和class一致

- C++中，struct默认是public，class默认是private
- C++中，存在public、protected、private
- C++中，使用时，可以不带strcut
- C++中，可以继承
- C++中，若结构体的名字与函数名相同，可以正常调用！但是定义结构体变量时候只能用带struct的！

### 2.1.同名函数

```cpp
struct A {
    
};
A(){}
struct A s; //ok
A s;  //error
```

### 2.2.typedef定义结构体别名

A自带struct，不可以直接调用函数

```cpp
typedef struct a{
    int a;
}A;

int main()
{
    A a;
    return 0;
}
```

### 2.3.继承

struct继承和class是一致

```cpp
#include <iostream>
struct Base
{
    int a;

    virtual void print()
    {
        std::cout << "print" << std::endl;
    }
};
struct Derived : public Base
{
public:
    int v2;
    void print()
    {
        printf("%s\n", "Derived");
    };
};
int main()
{
    Derived *b = new Derived();
    b->print();
    return 0;
}
```

## 3.总结

### 3.1.C和C++中的Struct区别

| C                                                      | C++                                                          |
| ------------------------------------------------------ | ------------------------------------------------------------ |
| 不能将函数放在结构体声明                               | 能将函数放在结构体声明                                       |
| 在C结构体声明中不能使用C++访问修饰符。                 | public、protected、private 在C++中可以使用。                 |
| 在C中定义结构体变量，如果使用了下面定义必须加struct。  | 可以不加struct                                               |
| 结构体不能继承（没有这一概念）。                       | 可以继承                                                     |
| 若结构体的名字与函数名相同，可以正常运行且正常的调用！ | 若结构体的名字与函数名相同，使用结构体，只能使用带struct定义！ |

在C++中，struct和class都可以用来定义自定义数据类型，但它们之间存在一些关键的区别：

- 默认访问权限：
  - struct的成员默认是public，即可以被任何外部代码访问。
  - class的成员默认是private，即只能在类的内部访问。
- 继承访问权限：
  - 当一个struct继承自另一个struct时，基类的public成员在派生类中默认也是public。
  - 当一个class继承自另一个class时，基类的public成员在派生类中默认是private。
- 设计意图：
  - struct通常用于简单的数据结构，如纯数据的聚合，没有太多的封装和抽象。
  - class通常用于创建具有封装、继承和多态性的面向对象结构。
- 构造函数和析构函数：
  - struct可以有构造函数和析构函数，但它们默认是public的。
  - class也可以有构造函数和析构函数，但它们默认是private的，除非显式指定。
- 继承：
  - struct可以被继承，并且基类的成员在派生类中保持原有的访问级别。
  - class也可以被继承，但基类的public成员在派生类中默认是private的。
- 多态：
  - struct支持多态，但通常不会用struct来实现多态性，因为它通常不包含虚函数。
  - class支持多态，并且可以包含虚函数和抽象类。
- 语法：
  - struct和class在语法上几乎相同，都可以包含数据成员、成员函数、继承等。
- 使用场景：
  - struct通常用于类似C语言的简单记录结构，没有方法或行为。
  - class用于定义具有封装、继承和多态性的复杂数据类型。
- C++11及以后：
  - 从C++11开始，struct和class在使用上更加一致，struct也可以包含成员函数和构造函数。
- 在实际使用中，struct和class的区别主要在于默认的访问权限和设计意图。struct更适合简单的数据结构，而class更适合需要封装和继承的面向对象设计。然而，这种区分更多是传统和风格上的，技术上两者几乎可以互换使用。

## 4.struct字节对齐

结构体占用内存空间大小，结构体存在字节对齐现象，实际使用空间往往大于结构体内部定义的数据的大小总和。

```cpp
#include<iostream>
struct A{
    int a;
    char b;
    double c;
};
int main()
{
    std::cout<<"A size is" << sizeof(A)<<std::endl;
}
```

在64位系统中，实际占用空间为16字节，a,b共同占用8字节，c占用8字节

## 5.struct与const

```cpp
#include "stdio.h"
#include <string.h>

#define ADDRESS_USER 0x1000000
#define ADDRESS_LENGTH 100

unsigned char buffer1[ADDRESS_LENGTH];
unsigned char buffer2[ADDRESS_LENGTH];
unsigned char buffer3[ADDRESS_LENGTH];
unsigned char buffer4[ADDRESS_LENGTH];

typedef struct buffer
{
    unsigned int address;
    unsigned int address_length;
    unsigned char *pbuffer;
} Buffer;

// const Buffer test1 = {ADDRESS_USER, ADDRESS_LENGTH, &buffer1[0]};
// const Buffer test2 = {ADDRESS_USER, ADDRESS_LENGTH, &buffer2[0]};
// const Buffer test3 = {ADDRESS_USER, ADDRESS_LENGTH, &buffer3[0]};
// const Buffer test4 = {ADDRESS_USER, ADDRESS_LENGTH, &buffer4[0]};

const Buffer test[4] = {
    {ADDRESS_USER, ADDRESS_LENGTH, &buffer1[0]},
    {ADDRESS_USER, ADDRESS_LENGTH, &buffer2[0]},
    {ADDRESS_USER, ADDRESS_LENGTH, &buffer3[0]},
    {ADDRESS_USER, ADDRESS_LENGTH, &buffer4[0]}};

const Buffer *pstructbuffers[4] = {
    &test[0],
    &test[1],
    &test[2],
    &test[3]};

const Buffer **get_buffer()
{
    return pstructbuffers;
}

int main()
{

    // Buffer **tests = (Buffer **)pstructbuffers;
    const Buffer **tests;

    tests = get_buffer();

    for (int i = 0; i < 4; i++)
    {
        memcpy(tests[i]->pbuffer, "testestes", i + 1);
    }
    for (int i = 0; i < 4; i++)
    {
        printf("buffer = %s\r\n", tests[i]->pbuffer);
    }

    return 0;
}

```

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
