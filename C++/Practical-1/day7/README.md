# C++ Practical-1 day7

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.operator 运算符重载

运算符重载在C++中是一种允许已定义的运算符（如+、-、*、/等）用于用户定义的类型的功能。通过运算符重载，可以使得自定义类型的操作更加直观和自然。

### 1.1.运算符重载的规则

1. **不能创建新的运算符**：只能重载已有的运算符。
2. **不能改变运算符的优先级**：运算符重载不会影响运算符的优先级。
3. **不能改变运算符的结合性**：运算符重载不会影响运算符的结合性。
4. **成员函数**：运算符重载通常是成员函数，但也可以是非成员函数（全局函数）。
5. **const修饰**：如果重载的运算符需要返回一个修改了的值，通常需要一个非const的成员函数版本。

### 1.2.示例1：重载加法运算符

```cpp
#include <iostream>

class Point {
public:
    int x, y;

    Point(int px, int py) : x(px), y(py) {}

    // 重载加法运算符
    Point operator+(const Point& rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
};

int main() {
    Point p1(1, 2);
    Point p2(3, 4);
    Point p3 = p1 + p2;
    std::cout << "p3: (" << p3.x << ", " << p3.y << ")" << std::endl;
    return 0;
}
```

在这个例子中，`Point`类重载了加法运算符，使得两个`Point`对象可以相加得到一个新的`Point`对象。

### 1.3.示例2：重载赋值运算符

```cpp
#include <iostream>
#include <string>

class Person {
public:
    std::string name;
    int         age;

    Person(const std::string &n, int a) :
        name(n), age(a) {
    }

    // 重载赋值运算符
    Person &operator=(const Person &rhs) {
        if (this != &rhs) {
            name = rhs.name;
            age  = rhs.age;
        }
        return *this;
    }
};

int main() {
    Person p1("Alice", 30);
    Person p2 = p1;
    std::cout << "p2: " << p2.name << ", " << p2.age << std::endl;
    return 0;
}
```

在这个例子中，`Person`类重载了赋值运算符，允许将一个`Person`对象赋值给另一个`Person`对象。

### 1.4.示例3：重载下标运算符

```cpp
#include <iostream>
#include <vector>

class Matrix {
private:
    std::vector<std::vector<int>> data;
public:
    Matrix(int rows, int cols) {
        data.resize(rows, std::vector<int>(cols));
    }

    // 重载下标运算符
    int& operator[](int index) {
        return data[index][0]; // Simplified for demonstration
    }
};

int main() {
    Matrix mat(2, 2);
    mat[0] = 1;
    mat[1] = 2;
    std::cout << "mat[0]: " << mat[0] << std::endl;
    std::cout << "mat[1]: " << mat[1] << std::endl;
    return 0;
}
```

在这个例子中，`Matrix`类重载了下标运算符，允许使用下标访问矩阵的元素。

### 1.5.注意事项

1. **运算符重载和类型安全**：运算符重载应该保持运算符原有的语义，除非有充分的理由。
2. **友元函数**：运算符重载函数可以是友元函数，这样可以访问类的私有成员。
3. **成员函数和非成员函数**：运算符重载可以是成员函数，也可以是非成员函数（全局函数）。
4. **const限定**：如果重载的运算符不应该修改对象的状态，应该将其声明为`const`。
5. **异常安全**：运算符重载应该考虑异常安全，确保在发生异常时不会导致资源泄漏。

运算符重载是C++中一个强大的特性，但应该谨慎使用，以避免使代码难以理解和维护。

## 2.operator_overload_binary 二元运算符重载

在C++中，二元运算符重载是指为自定义类型提供已有二元运算符（如`+`、`-`、`*`、`/`等）的新意义。二元运算符通常需要两个操作数，因此它们的重载函数可以是非成员函数或成员函数。

### 2.1.二元运算符重载的规则

1. **成员函数**：如果重载为成员函数，它应该接受一个参数，并且不能改变左侧操作数的状态。
2. **非成员函数**：如果重载为非成员函数（通常是友元函数），它可以接受两个参数。
3. **const限定**：如果重载的运算符不应该修改对象的状态，应该将其声明为`const`。
4. **返回类型**：重载函数应该返回一个有意义的值，通常是运算结果。

### 2.2.示例1：重载加法运算符

```cpp
#include <iostream>

class Point {
public:
    int x, y;

    Point(int px, int py) : x(px), y(py) {}

    // 重载加法运算符（成员函数）
    Point operator+(const Point& rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
};

int main() {
    Point p1(1, 2);
    Point p2(3, 4);
    Point p3 = p1 + p2; // 使用重载的加法运算符
    std::cout << "p3: (" << p3.x << ", " << p3.y << ")" << std::endl;
    return 0;
}
```

### 2.3.示例2：重载减法运算符

```cpp
#include <iostream>

class Vector {
public:
    double x, y;

    Vector(double px, double py) : x(px), y(py) {}

    // 重载减法运算符（成员函数）
    Vector operator-(const Vector& rhs) const {
        return Vector(x - rhs.x, y - rhs.y);
    }
};

int main() {
    Vector v1(5.0, 3.0);
    Vector v2(1.0, 2.0);
    Vector v3 = v1 - v2; // 使用重载的减法运算符
    std::cout << "v3: (" << v3.x << ", " << v3.y << ")" << std::endl;
    return 0;
}
```

### 2.4.示例3：重载乘法运算符（与标量）

```cpp
#include <iostream>

class Matrix {
public:
    double m[2][2];

    Matrix(double m11, double m12, double m21, double m22)
    {
        m[0][0] = m11; m[0][1] = m12;
        m[1][0] = m21; m[1][1] = m22;
    }

    // 重载乘法运算符（成员函数，与标量）
    Matrix operator*(double scalar) const
    {
        return Matrix(m[0][0] * scalar, m[0][1] * scalar,
                      m[1][0] * scalar, m[1][1] * scalar);
    }
};

int main() {
    Matrix mat(1.0, 2.0, 3.0, 4.0);
    Matrix result = mat * 2.0; // 使用重载的乘法运算符
    std::cout << "Matrix after multiplication: "
              << result.m[0][0] << ", " << result.m[0][1] << "; "
              << result.m[1][0] << ", " << result.m[1][1] << std::endl;
    return 0;
}
```

### 2.5.注意事项

1. **一致性**：运算符重载应该保持运算符原有的语义，除非有充分的理由。
2. **交换律**：对于如加法和乘法这样的交换律运算符，考虑重载为非成员函数，以允许交换操作数。
3. **异常安全**：运算符重载应该考虑异常安全，确保在发生异常时不会导致资源泄漏。
4. **友元函数**：运算符重载函数可以是友元函数，这样可以访问类的私有成员。

运算符重载是C++中一个强大的特性，但应该谨慎使用，以避免使代码难以理解和维护。

## 3.operator_overload_class 类运算符重载形式

在C++中，运算符重载可以以成员函数或友元函数的形式实现。每种形式都有其特定的语法和使用场景。以下是运算符重载的两种主要形式：

### 3.1.成员函数形式

运算符重载作为成员函数时，它的第一个参数是参与运算的另一个对象（对于二元运算符）。成员函数形式的运算符重载不能改变左侧操作数的状态。

```cpp
class MyClass {
public:
    // 成员函数形式的运算符重载
    MyClass operator+(const MyClass& rhs) const {
        MyClass result(*this); // 复制当前对象
        result += rhs;        // 调用赋值运算符
        return result;
    }
    
    // 赋值运算符
    MyClass& operator+=(const MyClass& rhs) {
        // 实现加法并更新当前对象
        return *this;
    }
};
```

### 3.2.友元函数形式

运算符重载作为友元函数时，它可以访问类的私有成员，并且可以定义为非成员函数。友元函数形式允许运算符左侧的操作数被修改。

```cpp
class MyClass {
public:
    // 友元函数声明
    friend MyClass operator+(const MyClass &lhs, const MyClass &rhs);

    // 其他成员函数和数据
};

// 友元函数定义
MyClass operator+(const MyClass &lhs, const MyClass &rhs) {
    MyClass result(lhs);   // 复制左侧操作数
    result = result + rhs; // 调用赋值运算符
    return result;
}
```

### 3.3.示例：实现加法运算符重载

```cpp
#include <iostream>

class Point {
public:
    int x, y;

    Point(int px, int py) : x(px), y(py) {}

    // 成员函数形式的加法运算符重载
    Point operator+(const Point& rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }

    // 友元函数形式的加法运算符重载
    friend Point operator+(const Point& lhs, const Point& rhs);
};

// 友元函数定义
Point operator+(const Point& lhs, const Point& rhs) {
    return Point(lhs.x + rhs.x, lhs.y + rhs.y);
}

int main() {
    Point p1(1, 2);
    Point p2(3, 4);
    Point p3 = p1 + p2; // 使用重载的加法运算符
    std::cout << "p3: (" << p3.x << ", " << p3.y << ")" << std::endl;
    return 0;
}
```

在这个例子中，`Point`类重载了加法运算符，提供了成员函数和友元函数两种形式。

### 3.4.注意事项

1. **成员函数**：作为成员函数时，左侧操作数是隐式传递的`this`指针，只能重载二元运算符。
2. **友元函数**：作为友元函数时，可以重载所有运算符，包括一元运算符。
3. **const限定**：如果运算符重载不应该修改对象的状态，应该将其声明为`const`。
4. **返回类型**：运算符重载应该返回一个有意义的值，通常是运算结果。
5. **异常安全**：运算符重载应该考虑异常安全，确保在发生异常时不会导致资源泄漏。

运算符重载提供了一种强大的机制，使得自定义类型的操作更加直观和自然。然而，应该谨慎使用，以避免使代码难以理解和维护。

## 4.operator_overload_unary 一元运算符重载

在C++中，一元运算符重载是指为自定义类型提供已有一元运算符（如`+`、`-`、`*`、`&`等）的新意义。一元运算符只需要一个操作数，因此它们的重载函数不需要额外的参数。

以下是一些常见的一元运算符及其重载示例：

### 4.1.示例1：重载一元加和减运算符

```cpp
#include <iostream>

class Number {
public:
    int value;

    Number(int val) : value(val) {}

    // 重载一元加运算符
    Number operator+() const {
        return *this; // 返回当前对象的一个副本
    }

    // 重载一元减运算符
    Number operator-() const {
        return Number(-value); // 返回当前对象的相反数
    }
};

int main() {
    Number num(10);
    Number pos = +num; // 调用一元加运算符
    Number neg = -num; // 调用一元减运算符

    std::cout << "Positive: " << pos.value << std::endl;
    std::cout << "Negative: " << neg.value << std::endl;

    return 0;
}
```

### 4.2.示例2：重载一元取地址运算符

```cpp
#include <iostream>

class Pointer {
private:
    int* ptr;
public:
    Pointer(int* p) : ptr(p) {}

    // 重载一元取地址运算符
    operator int*() const {
        return ptr;
    }
};

int main() {
    int data = 42;
    Pointer ptr(&data);
    int* pdata = ptr; // 使用重载的取地址运算符
    std::cout << "Value: " << *pdata << std::endl;

    return 0;
}
```

### 4.3.示例3：重载一元逻辑非运算符

```cpp
#include <iostream>

class Boolean {
private:
    bool value;
public:
    Boolean(bool val) : value(val) {}

    // 重载一元逻辑非运算符
    bool operator!() const {
        return !value;
    }
};

int main() {
    Boolean trueBool(true);
    Boolean falseBool(false);

    std::cout << "TrueBool: " << (!trueBool ? "False" : "True") << std::endl;
    std::cout << "FalseBool: " << (!falseBool ? "False" : "True") << std::endl;

    return 0;
}
```

### 4.4.注意事项

1. **一元运算符**：一元运算符只需要一个操作数，因此它们的重载函数不需要额外的参数。

2. **const限定**：如果重载的运算符不应该修改对象的状态，应该将其声明为`const`。

3. **返回类型**：运算符重载应该返回一个有意义的值，通常是运算结果。

4. **转换运算符**：一元运算符`operator+`和`operator-`通常用于实现数值转换，而`operator*`用于实现指针转换。

5. **异常安全**：运算符重载应该考虑异常安全，确保在发生异常时不会导致资源泄漏。

6. **逻辑非运算符**：逻辑非运算符`operator!`通常用于实现布尔值的逻辑取反。

一元运算符重载是C++中一个有用的特性，它使得自定义类型的操作更加直观和自然。然而，应该谨慎使用，以避免使代码难以理解和维护。

## 5.operator_overload_equal 重载运算符=

在C++中，重载赋值运算符`=`是一种常见的做法，用于定义对象之间赋值时的行为。默认情况下，编译器会生成一个赋值运算符，但如果类包含动态分配的资源（如动态内存），则通常需要自定义赋值运算符以确保资源被正确管理。

### 5.1.自定义赋值运算符的规则

1. **检查自赋值**：首先检查是否发生自赋值，即对象赋值给自己的情况。

2. **释放现有资源**：在分配新资源之前，释放对象当前持有的资源。

3. **复制资源**：复制源对象的资源到当前对象。

4. **交换指针**：如果使用指针管理资源，可以直接交换指针，但这种做法不适用于包含动态分配内存的复合类型。

5. **返回当前对象的引用**：返回当前对象的引用，以便支持链式赋值。

### 5.2.示例：重载赋值运算符

```cpp
#include <iostream>
#include <cstring>

class String {
private:
    char *data;

public:
    String(const char *str = "") {
        if (str) {
            data = new char[strlen(str) + 1];
            strcpy(data, str);
        } else {
            data = new char[1];
            *data = '\0';
        }
    }

    // 拷贝构造函数
    String(const String &other) {
        if (other.data) {
            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
        } else {
            data = new char[1];
            *data = '\0';
        }
    }

    // 重载赋值运算符
    String &operator=(const String &other) {
        if (this != &other) { // 检查自赋值
            delete[] data;    // 释放现有资源

            if (other.data) {
                data = new char[strlen(other.data) + 1];
                strcpy(data, other.data);
            } else {
                data = new char[1];
                *data = '\0';
            }
        }
        return *this; // 返回当前对象的引用
    }

    ~String() {
        delete[] data;
    }

    // 输出字符串内容的函数
    const char *c_str() const {
        return data;
    }
};

int main() {
    String str1("Hello");
    String str2 = str1; // 调用拷贝构造函数
    String str3;
    str3 = str1; // 调用赋值运算符

    std::cout << "str1: " << str1.c_str() << std::endl;
    std::cout << "str2: " << str2.c_str() << std::endl;
    std::cout << "str3: " << str3.c_str() << std::endl;

    return 0;
}
```

在这个例子中，`String`类重载了赋值运算符。它首先检查自赋值，然后释放现有资源，并复制源对象的资源。

### 5.3.注意事项

1. **自赋值**：在执行赋值操作之前，应该检查并处理自赋值的情况。

2. **异常安全**：赋值运算符应该确保在发生异常时，对象仍然处于有效状态。

3. **深拷贝**：如果类包含指针，应该确保进行深拷贝，而不是仅仅复制指针。

4. **返回类型**：赋值运算符应该返回对当前对象的引用，以支持链式赋值。

5. **规则一致性**：赋值运算符的行为应该与类的其他成员函数一致。

6. **虚函数**：不要在赋值运算符中调用虚函数，因为这时对象可能还没有完全构造好。

通过正确实现赋值运算符，可以确保对象在赋值过程中资源被正确管理，避免资源泄漏和其他问题。

## 6.重载下标运算符`[]`

在C++中，重载下标运算符`[]`允许对象像数组一样被访问。这通常用于提供对对象中元素的访问，例如，容器类或字符串类。

### 6.1.下标运算符重载的规则

1. **成员函数**：下标运算符通常作为成员函数重载，并且不接受任何参数，或者接受一个参数表示索引。

2. **常量性**：如果重载的下标运算符不应该修改对象的状态，应该将其声明为`const`。

3. **返回类型**：返回类型通常是对内部数据的引用，以允许链式赋值。

### 6.2.示例1：重载下标运算符用于访问元素

```cpp
#include <iostream>
#include <vector>
#include <stdexcept> // 用于标准异常

class IntArray {
private:
    std::vector<int> data;

public:
    // 带参数的下标运算符，用于修改元素
    int &operator[](size_t index) {
        // 简单的边界检查
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // 带参数的下标运算符，用于读取元素
    const int &operator[](size_t index) const {
        // 简单的边界检查
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // 添加元素的方法
    void push_back(int value) {
        data.push_back(value);
    }
};

int main() {
    IntArray arr;
    arr.push_back(10);
    arr.push_back(20);

    std::cout << "Element at index 0: " << arr[0] << std::endl; // 读取元素
    std::cout << "Element at index 1: " << arr[1] << std::endl;

    // 修改元素
    arr[0] = 30;

    std::cout << "Element at index 0 after modification: " << arr[0] << std::endl;

    return 0;
}
```

在这个例子中，`IntArray`类重载了下标运算符，允许用户使用下标访问和修改`std::vector`中的元素。

### 6.3.示例2：重载下标运算符用于自定义字符串类

```cpp
#include <iostream>
#include <cstring>
#include <cctype> // 包含toupper函数

class String {
private:
    char *data;

public:
    String(const char *str = "") {
        if (str) {
            data = new char[strlen(str) + 1];
            strcpy(data, str);
        } else {
            data = new char[1];
            *data = '\0';
        }
    }

    ~String() {
        delete[] data;
    }

    // 重载下标运算符
    char &operator[](size_t index) {
        // 边界检查
        if (index >= strlen(data)) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const char &operator[](size_t index) const {
        // 边界检查
        if (index >= strlen(data)) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // 获取字符串数据的访问器
    const char *c_str() const {
        return data;
    }
};

int main() {
    String str("Hello");

    std::cout << "Original string: " << str.c_str() << std::endl;

    // 修改字符串中的字符
    for (size_t i = 0; i < strlen(str.c_str()); ++i) {
        str[i] = toupper(str[i]);
    }

    std::cout << "Modified string: " << str.c_str() << std::endl;

    return 0;
}
```

在这个例子中，`String`类重载了下标运算符，允许用户使用下标访问和修改字符串中的字符。

### 6.4.注意事项

1. **边界检查**：在实现下标运算符时，应该考虑添加边界检查，以防止越界访问。

2. **异常安全**：如果下标运算符可能会抛出异常，应该确保异常发生时对象仍然处于有效状态。

3. **返回引用**：通常返回对元素的引用，以允许链式赋值。

4. **常量成员函数**：如果下标运算符用于读取元素，应该将其声明为`const`。

5. **虚函数**：下标运算符不应该声明为虚函数，因为它通常用于非多态场景。

通过正确实现下标运算符，可以使得自定义类型的元素访问更加直观和自然。然而，应该谨慎使用，以避免使代码难以理解和维护。

## 7.重载函数调用运算符`()`

在C++中，重载函数调用运算符`()`允许对象像函数一样被调用。这在设计模式中非常有用，特别是在实现工厂模式或者需要模拟函数指针时。

### 7.1.重载函数调用运算符的规则

1. **成员函数**：运算符`()`必须作为成员函数重载。
2. **无参数**：运算符`()`不接受任何参数。
3. **返回值**：必须指定返回类型，通常是类本身或者一个函数指针。

### 7.2.示例1：重载`()`运算符用于模拟函数指针

```cpp
#include <iostream>
#include <functional>

class FunctionWrapper {
public:
    // 存储一个可调用对象
    std::function<void()> func;

    // 构造函数
    FunctionWrapper(std::function<void()> f) : func(f) {}

    // 重载函数调用运算符
    void operator()() {
        func();
    }
};

int main() {
    // 创建一个lambda表达式
    auto lambda = []() { std::cout << "Hello, World!" << std::endl; };

    // 创建FunctionWrapper对象
    FunctionWrapper wrapper(lambda);

    // 使用重载的()运算符调用
    wrapper(); // 输出: Hello, World!

    return 0;
}
```

### 7.3.示例2：重载`()`运算符用于创建工厂对象

```cpp
#include <iostream>
#include <string>

class StringFactory {
public:
    // 重载函数调用运算符
    std::string operator()(const std::string& str) const {
        return str;
    }
};

int main() {
    StringFactory factory;

    std::string result = factory("Hello, Factory!");

    std::cout << result << std::endl; // 输出: Hello, Factory!

    return 0;
}
```

### 7.4.注意事项

1. **返回类型**：根据需要返回适当的类型，如果需要链式调用，则返回对象本身的引用。

2. **const成员函数**：如果重载的`()`运算符不应该修改对象的状态，应该将其声明为`const`。

3. **异常安全**：确保在调用过程中即使发生异常，对象也保持有效状态。

4. **资源管理**：如果运算符`()`涉及到资源管理，确保资源被正确分配和释放。

通过重载函数调用运算符`()`，可以使对象的使用更加灵活和表达式更加简洁。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
