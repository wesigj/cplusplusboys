# C++ Practical-1 day4

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.operator

在C++中，运算符重载（Operator Overloading）是一种使得开发者可以为自定义类型（如类和结构体）提供已有运算符的新意义的功能。这使得自定义类型的使用更加直观和自然。

### 1.1.运算符重载的规则

1. 除了`.*`和`::`，几乎所有的C++运算符都可以被重载。
2. 运算符重载函数必须是类的成员函数。
3. `=`（赋值运算符）和`[]`（下标运算符）不能为const成员函数。
4. `=`（赋值运算符）必须为类的成员函数。
5. 不能创建新的运算符。
6. 不能改变运算符的优先级和结合性。

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

### 1.3.示例2：重载赋值运算符

```cpp
#include <iostream>
#include <string>

class Person {
public:
    std::string name;
    int age;

    Person(const std::string& n, int a) : name(n), age(a) {}

    // 重载赋值运算符
    Person& operator=(const Person& rhs) {
        if (this != &rhs) {
            name = rhs.name;
            age = rhs.age;
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

### 1.5.示例4：重载递增运算符

```cpp
#include <iostream>

class Counter {
private:
    int count;
public:
    Counter() : count(0) {}

    // 重载前置递增运算符
    Counter& operator++() {
        ++count;
        return *this;
    }

    // 重载后置递增运算符
    Counter operator++(int) {
        Counter temp = *this;
        ++(*this);
        return temp;
    }

    void display() const {
        std::cout << count << std::endl;
    }
};

int main() {
    Counter c;
    std::cout << "Before increment: ";
    c.display();

    ++c;
    std::cout << "After prefix increment: ";
    c.display();

    c++;
    std::cout << "After postfix increment: ";
    c.display();
    return 0;
}
```

### 1.6.注意事项

- 运算符重载应该保持运算符原有的语义，除非有充分的理由。
- 运算符重载应该保持一致性，例如，如果你重载了`+`，可能也需要重载`-`、`*`和`/`。
- 运算符重载应该考虑效率，避免不必要的对象创建和复制。
- 对于复杂的类，考虑重载流插入运算符`<<`和流提取运算符`>>`，以方便地输出和输入对象。

运算符重载是C++中一个强大的特性，但应该谨慎使用，以避免使代码难以理解和维护。

## 2.const

在C++中，`const`关键字用于定义常量值，保证数据的安全性和稳定性。使用`const`可以防止数据被意外修改，同时也有助于代码的自我说明。

### 2.1.`const`的用途

1. **定义常量**：确保变量的值不会改变。
2. **修饰函数参数**：防止函数内部修改参数值。
3. **修饰函数返回值**：确保返回值不会被修改。
4. **修饰成员函数**：表明成员函数不会修改对象的状态。
5. **修饰指针**：定义指向常量的指针或常指针。

### 2.2.示例1：定义常量

```cpp
#include <iostream>

int main() {
    const int hours = 24; // 定义一个常量
    std::cout << "Number of hours in a day: " << hours << std::endl;
    // hours = 25; // 错误：不能修改常量
    return 0;
}
```

### 2.3.示例2：修饰函数参数

```cpp
#include <iostream>
#include <string>

void printMessage(const std::string& message) {
    std::cout << message << std::endl;
    // message = "Hello"; // 错误：不能修改const引用
}

int main() {
    printMessage("Hello, World!");
    return 0;
}
```

### 2.4.示例3：修饰函数返回值

```cpp
#include <iostream>
#include <string>

const std::string getCurrentTime() {
    // 假设这是一个获取当前时间的函数
    return "14:00";
}

int main() {
    std::string time = getCurrentTime();
    // time = getCurrentTime(); // 错误：不能修改const返回值
    std::cout << "Current time: " << time << std::endl;
    return 0;
}
```

### 2.5.示例4：修饰成员函数

```cpp
#include <iostream>
#include <string>

class Clock {
private:
    int hour;
    int minute;

public:
    Clock(int h, int m) : hour(h), minute(m) {}

    void setTime(int h, int m) {
        hour = h;
        minute = m;
    }

    // const成员函数
    void displayTime() const {
        std::cout << "Current time: " << hour << ":" << minute << std::endl;
        // setTime(12, 0); // 错误：不能在const成员函数中调用非const成员函数
    }
};

int main() {
    Clock myClock(11, 59);
    myClock.displayTime(); // 可以调用const成员函数
    return 0;
}
```

### 2.6.示例5：修饰指针

```cpp
#include <iostream>

int main() {
    const int  value = 42;
    const int *ptr   = &value; // 指针ptr可以改变指向，但通过ptr不能修改value的值
    // *ptr = 100; // 错误：尝试修改const变量

    const int *constPtr = &value; // constPtr是一个指向const值的const指针，既不能改变指向，也不能通过constPtr修改值
    // *constPtr = 100; // 错误：尝试修改const变量
    // constPtr = &value; // 错误：尝试改变const指针的指向

    int        anotherValue = 24;
    int *const constPtr2    = &anotherValue; // constPtr2是一个指向int的const指针，不能改变指向，但可以通过constPtr2修改值
    constPtr2               = &value;        // 错误：尝试改变const指针的指向

    return 0;
}
```

### 2.7.注意事项

- `const`修饰的变量必须在定义时初始化。
- `const`成员函数不能修改对象的任何成员变量（除非成员变量也是`mutable`）。
- `const`指针可以有多种组合，如指向常量的指针（`const int*`）、常指针（`int* const`）和指向常量的常指针（`const int* const`）。
- `const`在函数参数中使用时，通常为引用或指针，以避免不必要的复制。

使用`const`可以帮助保证程序的稳定性，防止意外修改，同时也有助于提高代码的可读性和可维护性。

## 3.拷贝构造函数

在C++中，拷贝构造函数是一种特殊的构造函数，它用于创建一个对象的新实例，该实例是另一个同类型对象的副本。拷贝构造函数在多种情况下会被自动调用，例如：

1. 当一个对象作为函数的返回值时。
2. 当一个对象被用作函数参数传递时（通过值传递，而不是引用）。
3. 当创建一个对象的副本时（例如，使用`new`运算符）。

### 3.1.拷贝构造函数的语法

```cpp
class ClassName {
public:
    ClassName(const ClassName& other); // 声明拷贝构造函数
    // ...
};
```

### 3.2.示例1：简单的拷贝构造函数

```cpp
#include <iostream>

class Point {
public:
    int x, y;

    Point() : x(0), y(0) {}
    
    // 拷贝构造函数
    Point(const Point& other) : x(other.x), y(other.y) {
        std::cout << "Copy constructor called" << std::endl;
    }
};

int main() {
    Point p1;
    Point p2 = p1; // 调用拷贝构造函数
    return 0;
}
```

在这个例子中，`Point`类有一个拷贝构造函数，它接受一个对`Point`类型的引用，并初始化成员变量`x`和`y`。

### 3.3.示例2：使用`std::copy`算法

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

class Point {
public:
    int x, y;

    Point() :
        x(0), y(0) {
        // 默认构造函数
    }

    // 拷贝构造函数
    Point(const Point &other) :
        x(other.x), y(other.y) {
        std::cout << "Copy constructor called" << std::endl;
    }
};

int main() {
    std::vector<Point> vec1;
    vec1.emplace_back(1, 2); // 使用emplace_back避免不必要的拷贝
    vec1.emplace_back(3, 4);

    // 创建一个新的向量，包含vec1中所有元素的副本
    std::vector<Point> vec2(vec1.begin(), vec1.end());
    return 0;
}
```

在这个例子中，我们使用了`std::copy`算法（通过`vector`的构造函数）来复制`vec1`中的所有元素到`vec2`。

### 3.4.示例3：深拷贝和浅拷贝

```cpp
#include <iostream>
#include <cstring>

class StringHolder {
public:
    StringHolder() : data(nullptr) {}
    
    // 拷贝构造函数
    StringHolder(const StringHolder& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }
    
    ~StringHolder() {
        delete[] data;
    }
    
private:
    char* data;
};

int main() {
    StringHolder holder1;
    holder1.data = new char[6];
    strcpy(holder1.data, "Hello");
    
    StringHolder holder2 = holder1; // 调用拷贝构造函数
    
    std::cout << holder1.data << std::endl;
    std::cout << holder2.data << std::endl;
    
    return 0;
}
```

在这个例子中，`StringHolder`类有一个指向动态分配的字符数组的指针。拷贝构造函数确保了数据被正确复制，这是一个深拷贝的例子。

上面代码中存在几个问题，需要修正：

1. **成员变量`data`应该是`public`**：为了让`main`函数能够访问`data`成员变量，你需要将其访问权限改为`public`。但是，通常我们不建议这样做，因为这样会破坏封装性。更好的做法是在类内部提供访问和修改成员变量的方法。

2. **深拷贝问题**：在`StringHolder`的拷贝构造函数中，你正确地实现了深拷贝。但是，由于`data`是`private`成员，你不能在`main`函数中直接访问它。

3. **析构函数问题**：析构函数应该确保释放分配的内存。这部分代码是正确的。

4. **使用`new`和`delete[]`**：在`main`函数中，你使用了`new`来分配内存，这是正确的。但是，你应该在`StringHolder`类中封装这些操作，以保持资源的获取和释放的一致性。

5. **缺少赋值运算符**：你的类缺少赋值运算符，这可能会导致意外的行为，特别是当对象作为函数参数传递时。

6. **缺少拷贝赋值运算符**：为了避免浅拷贝问题，你应该实现一个拷贝赋值运算符。

下面是修正后的代码：

```cpp
#include <iostream>
#include <cstring>

class StringHolder {
public:
    StringHolder() :
        data(nullptr) {
    }

    // 拷贝构造函数
    StringHolder(const StringHolder &other) {
        if (other.data) {
            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
        } else {
            data = nullptr;
        }
    }

    // 赋值运算符
    StringHolder& operator=(const StringHolder &other) {
        if (this != &other) {
            delete[] data;
            if (other.data) {
                data = new char[strlen(other.data) + 1];
                strcpy(data, other.data);
            } else {
                data = nullptr;
            }
        }
        return *this;
    }

    ~StringHolder() {
        delete[] data;
    }

    // 添加一个方法来设置字符串
    void setString(const char* str) {
        delete[] data;
        if (str) {
            data = new char[strlen(str) + 1];
            strcpy(data, str);
        } else {
            data = nullptr;
        }
    }

    // 添加一个方法来获取字符串
    const char* getString() const {
        return data;
    }

private:
    char *data;
};

int main() {
    StringHolder holder1;
    holder1.setString("Hello");

    StringHolder holder2 = holder1; // 调用拷贝构造函数

    std::cout << holder1.getString() << std::endl;
    std::cout << holder2.getString() << std::endl;

    return 0;
}
```

在这个修正后的代码中，我添加了`setString`和`getString`方法来安全地设置和获取`data`成员变量的值。同时，我也实现了赋值运算符来确保对象可以通过赋值操作正确地复制。这样，你就不需要直接访问`data`成员变量了。

### 3.5.注意事项

- 如果没有提供拷贝构造函数，编译器会生成一个默认的拷贝构造函数，它进行逐成员的拷贝，但对于含有指针成员的类，这可能会导致浅拷贝问题。
- 拷贝构造函数通常应该进行深拷贝，特别是当类包含指向动态分配资源的指针时。
- 在实现拷贝构造函数时，应该检查自赋值的情况，即当新对象是从它自身的副本创建时。
- C++11引入了`default`关键字，可以用来显式地告诉编译器生成默认的拷贝构造函数：`ClassName(const ClassName&) = default;`。

正确实现拷贝构造函数对于确保资源的正确管理和避免内存泄漏非常重要。

## 4.friend

在C++中，`friend`关键字用于声明友谊关系，使得一个函数或类能够访问另一个类的私有（`private`）或保护（`protected`）成员。这通常用于当一个类需要访问另一个类的内部数据，或者当需要优化性能时，比如在实现某些操作时避免使用成员函数。

### 4.1.`friend`的用途

1. **访问类的私有成员**：允许非成员函数或另一个类的成员函数访问类的私有成员。
2. **优化性能**：允许函数直接访问数据成员，避免使用成员函数的开销。
3. **实现操作符重载**：允许非成员函数重载操作符，以便访问类的私有数据。

### 4.2.示例1：使用`friend`函数访问私有数据

```cpp
#include <iostream>

class Account {
private:
    double balance;

public:
    Account(double initialBalance) : balance(initialBalance) {}

    // 声明friend函数
    friend void displayBalance(const Account& account);
};

// friend函数定义
void displayBalance(const Account& account) {
    std::cout << "The balance is: $" << account.balance << std::endl;
}

int main() {
    Account myAccount(1000.0);
    displayBalance(myAccount);
    return 0;
}
```

在这个例子中，`displayBalance`是一个`friend`函数，它可以直接访问`Account`类的私有成员`balance`。

### 4.3.示例2：使用`friend`类实现互操作

```cpp
#include <iostream>

class Date; // 前向声明

class Newspaper {
private:
    Date publicationDate; // Newspaper依赖于Date类
    std::string headline;
public:
    friend class Date; // 声明Date为友元类
    void printHeadline() const {
        std::cout << headline << std::endl;
    }
};

class Date {
private:
    int day;
    int month;
    int year;
public:
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    // 访问Newspaper的私有成员
    void printPublicationDate(const Newspaper& newspaper) const {
        std::cout << "Published on: " << day << "/" << month << "/" << year << std::endl;
    }
};

int main() {
    Newspaper newspaper(Date(25, 12, 2023));
    newspaper.printHeadline();
    newspaper.publicationDate.printPublicationDate(newspaper);
    return 0;
}
```

在这个例子中，`Date`类被声明为`Newspaper`类的`friend`类，这样`Date`类就可以访问`Newspaper`类的私有成员`publicationDate`。

代码中存在几个问题，需要修正：

1. **前向声明问题**：`Date` 类在 `Newspaper` 类中被前向声明，这是正确的。但是，前向声明不允许你使用 `Date` 类型的成员变量，除非它是指针或引用。

2. **友元类声明问题**：你不能在 `Newspaper` 类中声明 `Date` 为友元类，因为 `Date` 类还没有被完整定义。友元声明应该在 `Date` 类中进行。

3. **成员访问问题**：`Date` 类的成员变量是私有的，所以 `Newspaper` 类不能直接访问它们。你需要在 `Date` 类中提供访问器方法。

4. **`Date` 类的构造函数问题**：在 `main` 函数中，你尝试使用 `Date(25, 12, 2023)` 来初始化 `newspaper` 对象，但是 `Date` 类的构造函数需要三个参数，而且 `newspaper` 的初始化应该使用 `Date` 类型的对象。

5. **`printPublicationDate` 方法的参数问题**：`printPublicationDate` 方法尝试打印 `Newspaper` 对象的私有成员，但是它没有 `const` 修饰的引用参数。

6. **`main` 函数中的调用错误**：`newspaper.publicationDate.printPublicationDate(newspaper);` 这行代码是错误的，因为 `publicationDate` 是 `Date` 类型的对象，而不是 `Newspaper` 类型的对象。

下面是修正后的代码：

```cpp
#include <iostream>

class Date; // 前向声明

class Newspaper {
private:
    Date publicationDate; // Newspaper依赖于Date类
    std::string headline;

public:
    Newspaper(const Date& date, const std::string& head) : publicationDate(date), headline(head) {}
    
    void printHeadline() const {
        std::cout << headline << std::endl;
    }

    // 允许Date类访问Newspaper的私有成员
    friend class Date;
};

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    // 访问Newspaper的私有成员
    void printPublicationDate(const Newspaper& newspaper) const {
        std::cout << "Published on: " << day << "/" << month << "/" << year << std::endl;
    }

    // 友元函数声明
    friend void displayDate(const Date& date, const Newspaper& newspaper);
};

// 友元函数定义
void displayDate(const Date& date, const Newspaper& newspaper) {
    std::cout << "Newspaper published on: " << date.day << "/" << date.month << "/" << date.year
              << " with headline: " << newspaper.headline << std::endl;
}

int main() {
    Date date(25, 12, 2023);
    Newspaper newspaper(date, "Hello, World!");
    newspaper.printHeadline();
    displayDate(date, newspaper);
    return 0;
}
```

在这个修正后的代码中，我添加了一个友元函数 `displayDate`，它可以接受 `Date` 和 `Newspaper` 对象作为参数，并打印出日期和标题。同时，我也修正了 `Newspaper` 类的构造函数，以便正确地初始化 `publicationDate` 和 `headline` 成员变量。最后，我在 `main` 函数中正确地初始化了 `date` 和 `newspaper` 对象，并调用了 `displayDate` 友元函数。

### 4.4.示例3：重载`<<`操作符

```cpp
#include <iostream>

class Person {
private:
    std::string name;
public:
    Person(const std::string& n) : name(n) {}

    // 声明友元函数
    friend std::ostream& operator<<(std::ostream& os, const Person& person);
};

// 重载<<操作符
std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << "Name: " << person.name;
    return os;
}

int main() {
    Person person("Alice");
    std::cout << person << std::endl;
    return 0;
}
```

在这个例子中，`operator<<`被重载以允许直接将`Person`对象输出到`std::ostream`（如`std::cout`）。

### 4.5.注意事项

- 过度使用`friend`可能会导致代码的封装性变差，因为`friend`破坏了类之间的封装界限。
- `friend`函数不是类的成员函数，因此它们不能直接访问类的成员，而是需要通过参数传递对象。
- `friend`声明应该放在类的公共（`public`）部分。
- `friend`声明不会继承，每个需要访问私有成员的类或函数都必须显式声明为`friend`。

使用`friend`时应该谨慎，以保持代码的清晰性和封装性。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
