# C++面试基础系列-double_colon(::)

## Overview

- 全局作用域符（::name）：用于类型名称（类、类成员、成员函数、变量等）前，表示作用域为全局命名空间
- 类作用域符（class::name）：用于表示指定类型的作用域范围是具体某个类的
- 命名空间作用域符（namespace::name）:用于表示指定类型的作用域范围是具体某个命名空间的

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
  - 在C++模板编程中，:: 用于指定模板参数的命名空间或类作用域，例如 std::vector`<int>`。
- 匿名空间：
  - 在C++中，:: 还可以用于匿名命名空间，这是一种特殊的命名空间，它提供了文件内唯一的作用域。
- C++11中的统一初始化：
- 从C++11开始，:: 不再是统一初始化（Uniform Initialization）的一部分。统一初始化使用花括号 {} 而不是 ::。

总结来说，:: 在C++中是一个关键的运算符，用于处理作用域相关的问题，而在C语言中，由于作用域规则的不同，:: 的使用相对较少。

## 2.double_colon(::)使用示例

在C++中，双冒号 :: 是作用域解析运算符（scope resolution operator），用于明确指出我们访问的是特定作用域内的实体。以下是 :: 的一些主要用途和示例：

### 2.1.访问类成员

使用 :: 来访问类的成员变量和成员函数。

```cpp
class MyClass {
public:
    int memberVar;
    void memberFunc() {
        // ...
    }
};

int main() {
    MyClass myObj;
    myObj.memberVar = 10; // 访问成员变量
    myObj.memberFunc();   // 访问成员函数
}
```

### 2.2.静态成员访问

使用 :: 来访问类的静态成员，因为静态成员不属于类的任何特定对象。

```cpp
class MyClass {
public:
    static int staticMember;
};

int MyClass::staticMember = 20; // 定义静态成员

int main() {
    cout << MyClass::staticMember << endl; // 访问静态成员
}
```

### 2.3.命名空间中的实体

使用 :: 来访问命名空间中的实体。

```cpp
namespace MyNamespace {
    int myVar = 5;
}

int main() {
    cout << MyNamespace::myVar << endl; // 访问命名空间中的变量
}
```

### 2.4.全局变量和函数

在局部作用域中，使用 :: 来访问全局变量和函数。

```cpp
int globalVar = 10;

void globalFunc() {
    // ...
}

int main() {
    int localVar = 5;
    ::globalVar = localVar; // 访问全局变量
    ::globalFunc();       // 调用全局函数
}
```

### 2.5.友元类

当一个类声明了另一个类为友元时，可以使用 :: 来访问友元类的私有或保护成员。

```cpp
class FriendClass {
public:
    void friendFunc() {
        // ...
    }
};

class MyClass {
public:
    void accessFriend() {
        FriendClass::friendFunc(); // 访问友元类的成员函数
    }
};
```

### 2.6.类型转换

:: 也用于静态类型转换，即 static_cast。

```cpp
class Base {
public:
    virtual void func() {
        // ...
    }
};

class Derived : public Base {
public:
    void func() override {
        // ...
    }
};

void func(Base* basePtr) {
    Derived* derivedPtr = static_cast<Derived*>(basePtr); // 类型转换
    derivedPtr->func();
}
```

### 2.7.枚举类成员访问

当枚举被定义在类中时，使用 :: 来访问枚举成员。

```cpp
class MyClass {
public:
    enum MyEnum { A, B, C };
};

int main() {
    int value = MyClass::A; // 访问枚举成员
}
```

### 2.8.模板参数

使用 :: 来指定模板参数的命名空间或类作用域。

```cpp
template <typename T>
void myFunc(T param) {
    // ...
}

int main() {
    myFunc<std::vector<int>>(10); // 使用 :: 指定模板参数的命名空间
}
```

:: 是C++中一个非常有用的运算符，它帮助我们明确地访问作用域内的实体，提高代码的可读性和清晰度。

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/img/wechat.jpg width=60% />
