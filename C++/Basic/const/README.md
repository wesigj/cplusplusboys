# C++面试基础系列-const

---

## 1.const含义

const表示常类型，其值不可更改。

## 2.const作用

- 修饰常量
  
```cpp
const int a = 66;
```

- 类型检查
  - const具有类型，并支持所有类型
  - const修饰，名为常量，具备不可更改属性
- 防更改，保护作用，增加程序健壮性
- 节省空间，内存
  - 从汇编上看，const实质是使用内存地址访问，#define是立即数
  - const常量存储在内存中，只有一个内存地址，#define是预编译时，拷贝到代码中，不占用内存空间（RAM），占用ROM。

## 3.const作用域

- const 常量具有块作用域（如果定义在函数或代码块内部）或文件作用域（如果定义在所有函数外部），遵循C语言的普通作用域规则。
- #define 定义的宏在预处理阶段展开，没有作用域的概念，除非使用 #undef 取消定义。

## 4.修饰常量

```cpp
const int a =66;
a = 0; //ERROR can not change const constant
```

## 5.const与指针

```cpp
const int *p; //指向const常类型的普通指针
int const *p; //同上
int * const p;//指向int类型的常指针
const int *const p;//指向const常类型的常指针
```

有趣的解析方法

```cpp
const char * p; //p is a pointer to const char
char const * p; //同上
char * const p; //p is a const pointer to char
const char * const p; //p is a const pointer to const char
```

### 5.1.指向常量的指针

- 指向常量的指针，其中常量不可修改

```cpp
const int *p;
# *p=10; //error 不能修改常量
```

```cpp
const int a=10;
const int *p = &a;
// int *p = &a; //error 常量必须用常指针指向
```

- 允许把非const对象的地址赋给指向const对象的指针

```cpp
int a=10;
const int *p = &a;
```

```cpp
const int *p;
int a=10;
p= &a;
```

### 5.2.常指针

const指针定义时，必须初始化，const指针不可变，但指向的值可变。

```cpp
#include<iostream>
int main(){
    int a =66;
    int b =88;
    int * const p = &a;
    // p = &b; //error
    std::cout<<*p<<std::endl;
    a=100;
    std::cout<<*p<<std::endl;
}
```

const指针不能指向常量

```cpp
#include<iostream>
using namespace std;
int main(){
    const int a=0;
    //"const int *" 类型的值不能用于初始化 "int *const" 类型的实体
    // int * const p=&a; // error! can not const int* -> int*const
}
```

### 5.3.指向常量的常指针

```cpp
const int a = 10;
const int * const p = &a;
```

## 6.const与函数

- const修饰函数返回值
  - const int fun();
函数返回const常量，但是函数返回后通常会拷贝。

  - const int *fun();
函数返回指向常量的指针，指针指向的内容不能更改。

  - int *const fun();
指针不能更改。
- const修饰函数参数
  - 函数参数或函数参数指针在函数内不能更改

```cpp
void fun1(const int a);//参数不可变
void fun2(int *const a);//指针不能变
void fun(char *dest, const char *src);//防止常类型src被更改
```

主要功能：
保护参数和指针不被更改。
保护常类型不被更改。

- CPP中引用，增加效率，防止更改

```cpp
void fun(const T &a);//T为模板，任意类型
```

**cpp，增加了引用(reference)**：

> C语言本身没有引用（reference）的概念，引用是C++等其他编程语言中的一个特性。在C语言中，参数传递通常通过值传递（pass by value）或指针传递（pass by pointer）实现。
> 如果T为基础类型，理论来说，基础数据类型的参数不存在构造、析构的过程，而复制也非常快，“值传递”和“引用传递”的效率几乎相当。

**面试问题**：

- 如果函数需要传入一个指针，是否需要为该指针加上const，把const加在指针不同的位置有什么区别?
- 如果写的函数需要传入的参数是一个复杂类型的实例，传入值参数或者引用参数有什么区别，什么时候需要为传入的引用参数加上const?

## 7.const与类

- 在类中，任何不会修改数据成员的函数都应该声明为const类型。如果在编写const成员函数时，不慎修改 数据成员，或者调用了其它非const成员函数，编译器将指出错误，这无疑会提高程序的健壮性。
例如：

```cpp
class MyClass {
public:
    void normalFunction() {
        // 可以修改成员变量
    }

    void constantFunction() const {
        // 不能修改任何成员变量，除非它们被声明为 mutable
    }
};
```

>在这个示例中，normalFunction 是一个非常成员函数，可以修改对象的状态；而 constantFunction 是一个常成员函数，承诺不修改对象的状态，并且可以被用于操作常量对象。
---

- 使用const关键字进行修饰的成员函数，称为常成员函数。~~只有常成员函数才有资格操作常量或常对象~~，没有使用const关键字进行说明的成员函数不能用来操作常对象。
- const对象只能访问const成员函数,而非const对象可以访问任意的成员函数,包括const成员函数.

简单来说

- 常对象才能调用常函数和常量，不可调用非常函数或变量。
- 常函数不能调用，修改任何成员函数，成员变量，除非它们被声明为 mutable

例如：

```cpp
#include <iostream>

class MyClass
{
private:
    int value;

public:
    // 构造函数
    MyClass(int val) : value(val) {}

    // 非const成员函数，可以修改成员变量
    void modifyValue(int newValue)
    {
        value = newValue;
        std::cout << "Value modified to: " << value << std::endl;
    }

    // const成员函数，不能修改成员变量，但可以读取
    void displayValue() const
    {
        std::cout << "Current value: " << value << std::endl;
    }
};

int main()
{
    const MyClass constObject(10); // 创建一个const对象

    // 下面的调用是允许的，因为displayValue()是一个const成员函数
    constObject.displayValue();

    // 下面的调用将导致编译错误，因为modifyValue()不是一个const成员函数
    // constObject.modifyValue(20); // 错误：不能在const对象上调用non-const成员函数

    // 创建一个非const对象
    MyClass nonConstObject(20);

    // 可以调用非const成员函数来修改非const对象的状态
    nonConstObject.modifyValue(30); // 正确调用

    // 也可以调用const成员函数来读取非const对象的状态
    nonConstObject.displayValue(); // 正确调用

    return 0;
}
```

> 从中可以看出，const对象只能调用const函数和const常量，

---

- 于类中的const成员变量必须通过初始化列表进行初始化，如下所示：

```cpp
class Apple{
private:
    int people[100];
public:
    Apple(int i); 
    const int apple_number;
};

Apple::Apple(int i):apple_number(i)
{

}
```

## 8.const与static

### 8.1.将常量定义与static结合

```cpp
static const int apple_number
```

### 8.2.在类外面初始化

```cpp
const int Apple::apple_number=10;
```

使用c++11进行编译，可以在定义出初始化：

```cpp
static const int apple_number=10;
// 或者
const int apple_number=10;
```

这两种都在c++11中支持！

编译的时候加上`-std=c++11`即可！

在C++中，static静态成员变量不能在类的内部初始化。在类的内部只是声明，定义必须在类定义体的外部，通常在类的实现文件中初始化。

在类中声明：

```cpp
static int ap;
```

在类实现文件中使用：

```cpp
int Apple::ap=666
```

对于此项，c++11不能进行声明并初始化，也就是上述使用方法。

---

## 关于作者

- 本文作者:WeSiGJ
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 微信公众号:WeSiGJ

<html><body><img src="/./img/wechat.jpg" width="60%"></body></html>
