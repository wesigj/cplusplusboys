# C++面试基础系列-static

---

## 1.static含义

static关键字

- 静态变量和静态类
- 类中的静态成员

在C++中，static 关键字有多个用途，包括定义静态变量、静态成员函数、静态数据成员、静态常量成员以及在函数中定义静态局部变量。以下是对 static 在C++中的详细描述：

## 2.普通静态变量

### 2.1.静态全局变量

当 static 用于全局变量时，它限制了变量的链接范围，使其只在定义它的文件内部可见，其他文件无法访问。

### 2.2.静态局部变量

在函数内部定义的 static 变量具有静态存储期。这意味着它们在程序的整个运行期间都存在，而不是仅在函数调用期间。每次函数调用时，static 局部变量都会保留上一次调用的值。

## 3.类中静态变量

### 3.1.静态成员变量

类的静态成员变量属于类本身，而不是类的任何特定对象。它们在所有对象之间共享。静态成员变量在所有实例之前或之后初始化，在程序的整个生命周期内保持其值。

### 3.2.静态常量成员

静态常量成员是类的一个特殊成员，它不仅具有静态存储期，还具有 const 特性。它们在定义时必须被初始化，并且不能被修改。

### 3.3.静态成员函数

静态成员函数属于类本身，而不是类的任何对象。它们可以访问类的静态成员，但不能访问非静态成员，因为它们没有 this 指针。静态成员函数可以在没有创建类的对象的情况下被调用。

### 3.4.静态类

从C++11开始，可以定义一个静态类，它只能包含静态成员，不能有构造函数、析构函数或基类。

### 3.5.模板中的静态

在类模板中，静态成员具有特殊的行为。每个实例化的模板类都有自己的静态成员，它们不是共享的。

### 3.6.嵌套静态类

在C++中，可以在类中定义静态类（也称为嵌套类），这些类在定义它们的类的外部是不可访问的。

- 初始化：

静态数据成员通常在类的定义外部进行初始化，而不是在类内部。

- 作用域：

静态成员的作用域是整个程序，它们可以在类的任何对象上通过类名直接访问。

- 内存分配：

静态成员变量和静态局部变量存储在静态存储区，而不是堆栈或堆上。
以下是一些示例来说明 static 的使用：

```cpp
// 静态全局变量
static int globalVar = 42; // 只在定义它的文件内可见

void function() {
    // 静态局部变量
    static int staticVar = 0; // 函数调用间保留值
    staticVar++;
}

class MyClass {
public:
    // 静态成员变量
    static int staticMember;

    // 静态常量成员
    static const int staticConstMember = 10;

    // 静态成员函数
    static void staticMemberFunction() {
        staticMember++; // 可以访问静态成员变量
    }
};

// 在类外初始化静态成员变量
int MyClass::staticMember = 0;

void functionWithStatic() {
    // 使用静态成员
    MyClass::staticMemberFunction();
    const int localStaticConst = 5; // 局部静态常量，作用域限制在函数内
}
```

---

## 关于作者

- 本文作者:WeSiGJ
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 微信公众号:WeSiGJ

<html><body><img src="/./img/wechat.jpg" width="60%"></body></html>
