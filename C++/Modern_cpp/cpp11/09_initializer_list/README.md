# C++11 09-初始化列表 initializer list

- [C++11 09-初始化列表 initializer list](#c11-09-初始化列表-initializer-list)
  - [Overview](#overview)
  - [1.初始化列表 initializer list](#1初始化列表-initializer-list)
    - [1.1. 直接初始化](#11-直接初始化)
    - [1.2. 统一初始化](#12-统一初始化)
    - [1.3. 默认初始化](#13-默认初始化)
    - [1.4. 初始化基础类和成员](#14-初始化基础类和成员)
    - [1.5. 用于聚合类型](#15-用于聚合类型)
    - [1.6. 用于数组和复杂数据结构](#16-用于数组和复杂数据结构)
    - [1.7. 初始化常量和静态成员](#17-初始化常量和静态成员)
    - [1.8. 用于函数参数](#18-用于函数参数)
    - [1.9. 初始化Lambda表达式](#19-初始化lambda表达式)
    - [1.10. 结构化绑定](#110-结构化绑定)
  - [2.C++11 初始化列表在多态类中是如何工作的？](#2c11-初始化列表在多态类中是如何工作的)
  - [3.如何使用初始化列表来初始化一个自定义的类？](#3如何使用初始化列表来初始化一个自定义的类)
    - [3.1. 定义类](#31-定义类)
    - [3.2. 初始化列表的顺序](#32-初始化列表的顺序)
    - [3.3. 初始化常量成员](#33-初始化常量成员)
    - [3.4. 初始化基类](#34-初始化基类)
    - [3.5. 初始化列表与聚合类](#35-初始化列表与聚合类)
    - [3.6. 使用 `std::initializer_list`](#36-使用-stdinitializer_list)
    - [3.7. 初始化列表与委托构造函数](#37-初始化列表与委托构造函数)
  - [4.在C++11中，初始化列表和普通初始化有什么区别？](#4在c11中初始化列表和普通初始化有什么区别)
    - [4.1.示例](#41示例)
  - [5.在C++中，除了使用初始化列表，还有哪些方法可以初始化类成员变量？](#5在c中除了使用初始化列表还有哪些方法可以初始化类成员变量)
  - [6.在C++中，如何使用默认成员初始化来初始化类成员变量？](#6在c中如何使用默认成员初始化来初始化类成员变量)
    - [6.1.基本语法](#61基本语法)
    - [6.2.示例代码](#62示例代码)
    - [6.3.注意事项](#63注意事项)
  - [关于作者](#关于作者)

## Overview

---

## 1.初始化列表 initializer list

在 C++11 中，初始化列表（也称为统一初始化或列表初始化）是一种新的初始化对象的方式，它提供了比旧的语法更加清晰和灵活的语法。初始化列表允许你使用花括号 `{}` 来初始化对象，支持直接初始化、统一初始化和默认初始化。

以下是 C++11 初始化列表的一些关键特性：

### 1.1. 直接初始化

可以直接使用初始化列表来初始化变量：

```cpp
#include <vector>
#include <string>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::string s = "Hello, C++11";

    for (int i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << s << std::endl;

    return 0;
}
```

### 1.2. 统一初始化

C++11 允许使用统一初始化来初始化不同类型的变量：

```cpp
#include <iostream>

int main() {
    auto x = {1, 2.5, "text"};
    std::cout << x.first << ", " << x.second << ", " << x third << std::endl;

    return 0;
}
```

### 1.3. 默认初始化

初始化列表中的元素可以省略，它们将被默认初始化：

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {};
    std::cout << v.size() << std::endl; // 输出 0

    return 0;
}
```

### 1.4. 初始化基础类和成员

初始化列表可以用于初始化类的基类和非静态成员：

```cpp
#include <iostream>
#include <string>

class Base {
public:
    Base(int x) : value(x) {}
    int value;
};

class Derived : public Base {
public:
    Derived(int x, std::string str) : Base(x), text(str) {}
    std::string text;
};

int main() {
    Derived obj(10, "Hello");
    std::cout << obj.value << ", " << obj.text << std::endl;

    return 0;
}
```

### 1.5. 用于聚合类型

初始化列表可以用于聚合类型（没有用户自定义构造函数的类）：

```cpp
#include <iostream>

struct Point {
    int x;
    double y;
};

int main() {
    Point p = {1, 2.5};
    std::cout << p.x << ", " << p.y << std::endl;

    return 0;
}
```

### 1.6. 用于数组和复杂数据结构

初始化列表可以用于初始化数组和复杂数据结构：

```cpp
#include <iostream>
#include <array>

int main() {
    std::array<int, 4> arr = {1, 2, 3, 4};
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 1.7. 初始化常量和静态成员

初始化列表也适用于初始化常量和静态成员：

```cpp
#include <iostream>
#include <string>

const int importantNumber = {42};
static std::string greeting = {"Hello, World!"};

int main() {
    std::cout << importantNumber << std::endl;
    std::cout << greeting << std::endl;

    return 0;
}
```

### 1.8. 用于函数参数

初始化列表可以用于函数参数：

```cpp
#include <iostream>
#include <vector>
#include <string>

void printVector(const std::vector<std::string>& v) {
    for (const auto& str : v) {
        std::cout << str << " ";
    }
    std::cout << std::endl;
}

int main() {
    printVector({"one", "two", "three"});

    return 0;
}
```

### 1.9. 初始化Lambda表达式

初始化列表可以用于初始化Lambda表达式的捕获列表：

```cpp
#include <iostream>
#include <vector>

int main() {
    int x = 10;
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto lambda = [&x, v]() {
        x += 5;
        for (int i : v) {
            std::cout << i << " ";
        }
        std::cout << ", x: " << x << std::endl;
    };
    lambda();

    return 0;
}
```

### 1.10. 结构化绑定

初始化列表可以与结构化绑定一起使用：

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <tuple>

int main() {
    std::vector<std::tuple<int, std::string, double>> data = {
        {1, "one", 1.1},
        {2, "two", 2.2},
        {3, "three", 3.3}
    };

    for (const auto& [id, name, value] : data) {
        std::cout << id << ", " << name << ", " << value << std::endl;
    }

    return 0;
}
```

通过使用 C++11 的初始化列表，你可以编写更简洁、更易读和更安全的代码。

## 2.C++11 初始化列表在多态类中是如何工作的？

在 C++11 中，初始化列表提供了一种更为直观和高效的方式来初始化对象，包括多态类的对象。以下是如何在多态类中使用初始化列表的一些关键点：

1. **直接初始化**：在构造函数中，可以使用初始化列表直接初始化基类和成员变量。

   ```cpp
   class Base {
   public:
       Base(int x) : value(x) {}
       int value;
   };

   class Derived : public Base {
   public:
       Derived(int x, double y) : Base(x), y(y) {}
       double y;
   };

   int main() {
       Derived obj(10, 3.14);
       return 0;
   }
   ```

2. **统一初始化**：C++11 允许使用统一初始化（也称为列表初始化），即使用花括号 `{}` 来初始化对象。

   ```cpp
   Derived obj{10, 3.14};
   ```

3. **避免窄化转换**：C++11 规定，使用初始化列表时，不允许窄化转换。这意味着初始化列表中的值必须能够精确匹配成员变量的类型。

   ```cpp
   double pi = 3.14;
   int main() {
       int mainPi = {pi}; // 错误：窄化转换
       return 0;
   }
   ```

4. **聚合类型**：对于聚合类型，初始化列表可以用于直接初始化成员变量。

   ```cpp
   struct Point {
       int x;
       double y;
   };

   int main() {
       Point p{1, 2.5};
       return 0;
   }
   ```

5. **std::initializer_list**：C++11 引入了 `std::initializer_list` 类型，它是一个轻量级的容器，用于存储初始化列表中的值。这在自定义类的构造函数中非常有用，尤其是当你需要接收一个不确定数量的参数时。

   ```cpp
   class MyClass {
   public:
       MyClass(std::initializer_list<int> init) {
           for (int value : init) {
               // 处理初始化列表中的每个值
           }
       }
   };

   int main() {
       MyClass obj = {1, 2, 3, 4, 5};
       return 0;
   }
   ```

6. **构造函数的委托**：C++11 允许一个构造函数委托给另一个构造函数，这在多态类中尤其有用。

   ```cpp
   class Derived : public Base {
   public:
       Derived(int x) : Base(x) {}
       Derived(int x, double y) : Base(x), y(y) {}
       double y;
   };
   ```

7. **异常安全**：使用初始化列表可以提高代码的异常安全性，因为它们避免了在构造函数体内进行赋值操作，从而减少了发生异常的可能性。

通过这些方法，你可以在 C++11 中的多态类中有效地使用初始化列表，以提高代码的清晰度、效率和安全性。

## 3.如何使用初始化列表来初始化一个自定义的类？

在 C++11 及更高版本中，使用初始化列表来初始化自定义类是一种推荐的做法，特别是对于类中包含常量成员或者需要高效初始化的场景。初始化列表确保成员变量按照声明的顺序进行初始化，并且可以在构造函数体内直接初始化成员变量。

以下是如何使用初始化列表来初始化自定义类的步骤：

### 3.1. 定义类

首先，定义你的类，并在构造函数中使用初始化列表来初始化成员变量。

```cpp
#include <iostream>
#include <string>

class Person {
public:
    std::string name;
    int age;
    double height;

    // 构造函数使用初始化列表
    Person(std::string n, int a, double h) : name(n), age(a), height(h) {
        std::cout << "Constructor is called." << std::endl;
    }
};

int main() {
    Person person("John Doe", 30, 175.5);
    return 0;
}
```

### 3.2. 初始化列表的顺序

在初始化列表中，成员变量的初始化顺序是根据它们在类定义中的声明顺序，而不是它们在初始化列表中出现的顺序。

### 3.3. 初始化常量成员

对于常量成员变量，必须使用初始化列表，因为常量成员必须在构造函数体内被初始化。

```cpp
class Person {
public:
    std::string name;
    int age;
    const double height;

    // 构造函数使用初始化列表
    Person(std::string n, int a, double h) : name(n), age(a), height(h) {
        std::cout << "Constructor is called." << std::endl;
    }
};

int main() {
    Person person("John Doe", 30, 175.5);
    return 0;
}
```

### 3.4. 初始化基类

如果你的类继承自一个基类，可以在初始化列表中初始化基类。

```cpp
class Base {
public:
    Base(int x) : value(x) {
        std::cout << "Base constructor is called." << std::endl;
    }
    int value;
};

class Derived : public Base {
public:
    double y;

    // 构造函数使用初始化列表
    Derived(int x, double y) : Base(x), y(y) {
        std::cout << "Derived constructor is called." << std::endl;
    }
};

int main() {
    Derived obj(10, 3.14);
    return 0;
}
```

### 3.5. 初始化列表与聚合类

对于聚合类（Aggreggate Type），初始化列表可以直接用于初始化成员变量。

```cpp
struct Point {
    int x;
    double y;
};

int main() {
    Point p{1, 2.5};
    std::cout << "Point x: " << p.x << ", y: " << p.y << std::endl;
    return 0;
}
```

### 3.6. 使用 `std::initializer_list`

对于需要接收不确定数量参数的构造函数，可以使用 `std::initializer_list`。

```cpp
class Point {
public:
    int x;
    double y;

    // 使用 std::initializer_list 进行初始化
    Point(std::initializer_list<double> init) {
        if (init.size() >= 2) {
            x = init.begin()[0];
            y = init.begin()[1];
        }
    }
};

int main() {
    Point p = {1.0, 2.5};
    std::cout << "Point x: " << p.x << ", y: " << p.y << std::endl;
    return 0;
}
```

### 3.7. 初始化列表与委托构造函数

C++11 允许一个构造函数委托给另一个构造函数。

```cpp
class Person {
public:
    std::string name;
    int age;
    double height;

    // 委托构造函数
    Person() : Person("Unknown", 0, 0.0) {}

    // 主构造函数
    Person(std::string n, int a, double h) : name(std::move(n)), age(a), height(h) {
        std::cout << "Constructor is called." << std::endl;
    }
};

int main() {
    Person person1("John Doe", 30, 175.5);
    Person person2{};
    return 0;
}
```

通过使用初始化列表，你可以确保类成员按照正确的顺序和方式进行初始化，从而提高代码的效率和可读性。

## 4.在C++11中，初始化列表和普通初始化有什么区别？

在 C++11 中，初始化列表和普通初始化（也称为默认初始化）主要有以下几个区别：

1. **初始化顺序**：
   - **初始化列表**：成员变量按照它们在类定义中的声明顺序进行初始化，而不是按照它们在初始化列表中出现的顺序。
   - **普通初始化**：成员变量是在构造函数体内按顺序赋值的，按照它们在初始化列表或构造函数体内出现的顺序。

2. **效率**：
   - **初始化列表**：通常更高效，特别是对于内置类型，因为它们可以直接初始化而不需要调用赋值操作。
   - **普通初始化**：可能涉及额外的赋值操作，特别是当使用复杂的对象类型时，这可能导致不必要的拷贝或构造调用。

3. **常量成员**：
   - **初始化列表**：是初始化常量成员的唯一方式，因为常量成员必须在构造函数体内初始化，而不能通过赋值。
   - **普通初始化**：不能用于初始化常量成员，因为它们需要在构造函数体外进行初始化。

4. **聚合类**：
   - **初始化列表**：可以直接用于聚合类（Aggreggate Class），这是一种没有用户自定义构造函数、基类或虚函数的类。
   - **普通初始化**：不能用于聚合类，因为聚合类需要使用初始化列表来初始化其成员。

5. **基类**：
   - **初始化列表**：用于初始化基类，必须在成员变量之前初始化。
   - **普通初始化**：不能用于初始化基类，因为基类的构造函数必须在派生类的构造函数体内调用。

6. **异常安全性**：
   - **初始化列表**：提供了更好的异常安全性，因为它们减少了构造函数体内发生异常的可能性。
   - **普通初始化**：如果赋值操作可能抛出异常，那么使用普通初始化可能会影响异常安全性。

7. **语法**：
   - **初始化列表**：使用冒号 `:` 后跟一个或多个要初始化的成员变量和它们的值。
   - **普通初始化**：在构造函数体内使用赋值操作符 `=` 进行初始化。

### 4.1.示例

以下是使用初始化列表和普通初始化的示例：

```cpp
#include <iostream>
#include <string>

class Person {
public:
    std::string name;
    int age;
    const double height;

    // 使用初始化列表
    Person(std::string n, int a, double h) : name(n), age(a), height(h) {
        std::cout << "Person constructed." << std::endl;
    }

    // 使用普通初始化
    void setDetails(std::string n, int a, double h) {
        name = n;
        age = a;
        height = h;
        std::cout << "Details set." << std::endl;
    }
};

int main() {
    Person person1("John Doe", 30, 175.5); // 使用初始化列表

    Person person2;
    person2.setDetails("Jane Doe", 25, 165.0); // 使用普通初始化

    return 0;
}
```

在这个例子中，`Person` 类的构造函数使用初始化列表来初始化成员变量，而 `setDetails` 成员函数使用普通初始化。

总的来说，初始化列表在 C++11 中是首选的初始化方式，因为它们提供了更好的效率、类型安全性和异常安全性。

## 5.在C++中，除了使用初始化列表，还有哪些方法可以初始化类成员变量？

在 C++ 中，除了使用初始化列表，还有几种方法可以初始化类成员变量：

1. **默认成员初始化**：
   在类定义中，你可以为成员变量提供默认值。

   ```cpp
   class MyClass {
   public:
       int value = 10; // 默认初始化
       std::string name = "Default"; // 默认初始化
   };
   ```

2. **构造函数体内赋值**：
   在构造函数体内直接赋值给成员变量。

   ```cpp
   class MyClass {
   public:
       int value;
       std::string name;
       MyClass() : value(10), name("Default") {
           // 也可以在这里赋值
           value = 20;
           name = "Modified";
       }
   };
   ```

3. **使用委托构造函数**：
   一个构造函数可以委托给另一个构造函数来执行初始化。

   ```cpp
   class MyClass {
   public:
       int value;
       MyClass() : value(10) {
           // 默认构造
       }
       MyClass(int v) : value(v) {
           // 委托给默认构造函数
       }
   };
   ```

4. **使用工厂函数**：
   可以编写一个工厂函数来创建和初始化对象。

   ```cpp
   class MyClass {
   public:
       int value;
   private:
       MyClass() {}
   public:
       static MyClass create(int v) {
           MyClass obj;
           obj.value = v;
           return obj;
       }
   };
   ```

5. **使用 `std::optional`**：
   从 C++17 开始，可以使用 `std::optional` 来初始化对象，只有在有有效值时才进行初始化。

   ```cpp
   #include <optional>
   
   class MyClass {
   public:
       int value;
       std::optional<MyClass> maybeCreate(int v) {
           if (v > 0) {
               return MyClass{v};
           }
           return std::nullopt;
       }
   };
   ```

6. **使用 `std::initializer_list`**：
   对于接受可变数量参数的构造函数，可以使用 `std::initializer_list`。

   ```cpp
   class MyClass {
   public:
       std::vector<int> values;
       MyClass(std::initializer_list<int> init) : values(init) {}
   };
   ```

7. **使用聚合类初始化**：
   对于聚合类（没有自定义构造函数、基类或虚函数的类），可以直接使用花括号 `{}` 进行初始化。

   ```cpp
   struct MyStruct {
       int a;
       double b;
   };
   
   MyStruct myStruct{10, 20.5};
   ```

8. **使用 `std::tuple`**：
   可以使用 `std::tuple` 来存储初始化数据，然后传递给构造函数。

   ```cpp
   #include <tuple>
   
   class MyClass {
   public:
       int value;
       std::string name;
       MyClass(const std::tuple<int, std::string>& init) : value(std::get<0>(init)), name(std::get<1>(init)) {}
   };
   ```

9. **使用 `std::pair`**：
   对于包含两个成员的类，可以使用 `std::pair` 来初始化。

   ```cpp
   #include <utility>
   
   class MyClass {
   public:
       int first;
       double second;
       MyClass(const std::pair<int, double>& init) : first(init.first), second(init.second) {}
   };
   ```

10. **使用列表初始化**：
    C++11 允许使用花括号 `{}` 进行列表初始化，这适用于内置类型、标准库类型和用户自定义类型。

    ```cpp
    class MyClass {
    public:
        std::string name;
        int age;
        MyClass() : name{"Default"}, age{0} {}
    };
    ```

这些方法提供了灵活性来初始化类成员变量，可以根据不同的使用场景选择合适的初始化方式。

## 6.在C++中，如何使用默认成员初始化来初始化类成员变量？

在 C++ 中，你可以在类定义中直接为成员变量指定默认值，这种方式称为默认成员初始化。这种方式特别适合为那些不需要在构造函数中进行复杂初始化的成员变量设置初始值。

### 6.1.基本语法

在类定义中，直接在成员变量声明时赋予默认值：

```cpp
class MyClass {
public:
    int defaultInt = 10;      // 默认值为 10
    double defaultDouble = 3.14;  // 默认值为 3.14
    std::string defaultString = "Hello"; // 默认值为 "Hello"
};
```

### 6.2.示例代码

下面是一个更完整的示例，展示了如何在类定义中使用默认成员初始化：

```cpp
#include <iostream>
#include <string>

class Person {
public:
    std::string name;
    int age;
    double height;

    // 在类定义中直接初始化成员变量
    Person() : age(0), height(0.0) {
        std::cout << "Person default constructor called." << std::endl;
    }

    // 可以有多个构造函数，每个构造函数都可以有自己的初始化列表
    Person(std::string n, int a, double h) : name(n), age(a), height(h) {
        std::cout << "Person parameterized constructor called." << std::endl;
    }

    // 成员函数
    void display() const {
        std::cout << "Name: " << name 
                  << ", Age: " << age 
                  << ", Height: " << height << " meters" << std::endl;
    }
};

int main() {
    // 使用默认成员初始化
    Person person1;
    person1.display(); // 输出默认值

    // 使用构造函数初始化
    Person person2("John Doe", 30, 175.5);
    person2.display(); // 输出 John Doe 的信息

    return 0;
}
```

### 6.3.注意事项

1. **常量成员**：
   常量成员必须在初始化列表中初始化，不能使用默认成员初始化。

2. **引用成员**：
   引用成员也必须在初始化列表中初始化，因为引用一旦初始化后就不能更改。

3. **类类型成员**：
   对于类类型的成员，如果它们有自己的默认构造函数，可以使用默认成员初始化。

4. **顺序问题**：
   成员变量的初始化顺序是根据它们在类定义中的声明顺序，而不是它们在初始化列表中出现的顺序。

5. **与构造函数的关系**：
   即使使用了默认成员初始化，仍然可以提供构造函数来处理更复杂的初始化逻辑。

通过使用默认成员初始化，你可以简化类的构造函数，使得代码更加清晰和易于维护。这种方式特别适合为那些有明确默认值的成员变量提供初始值。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
