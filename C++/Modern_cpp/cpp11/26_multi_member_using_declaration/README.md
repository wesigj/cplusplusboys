# C++11 26-多成员的 `using` 声明 Multi member using declaration

- [C++11 26-多成员的 `using` 声明 Multi member using declaration](#c11-26-多成员的-using-声明-multi-member-using-declaration)
  - [Overview](#overview)
  - [1.多成员的 `using` 声明 Multi member using declaration](#1多成员的-using-声明-multi-member-using-declaration)
    - [1.1.基本用法](#11基本用法)
    - [1.2.示例](#12示例)
    - [1.3.多成员 `using` 声明](#13多成员-using-声明)
    - [1.4.注意事项](#14注意事项)
  - [2.在 C++11 中，除了多成员的 `using` 声明，还有哪些其他方式可以解决基类成员的继承问题？](#2在-c11-中除了多成员的-using-声明还有哪些其他方式可以解决基类成员的继承问题)
  - [3.如何使用~using声明来解决基类成员的重载问题？](#3如何使用using声明来解决基类成员的重载问题)
    - [3.1.示例](#31示例)
    - [3.2.注意事项](#32注意事项)
  - [4.在C++11中，using声明在模板编程中有哪些应用场景？](#4在c11中using声明在模板编程中有哪些应用场景)
  - [5.在 C++11 中，如何使用 using 声明来定义模板别名？](#5在-c11-中如何使用-using-声明来定义模板别名)
    - [5.1.基本语法](#51基本语法)
    - [5.2.示例](#52示例)
    - [5.3.使用示例](#53使用示例)
    - [5.4.优点](#54优点)
    - [5.5.注意事项](#55注意事项)
  - [6.能否举例说明如何使用using声明来显式指定模板参数？](#6能否举例说明如何使用using声明来显式指定模板参数)
    - [6.1.示例 1: 引入类型定义](#61示例-1-引入类型定义)
    - [6.2.示例 2: 继承构造函数](#62示例-2-继承构造函数)
    - [6.3.示例 3: 引入成员函数](#63示例-3-引入成员函数)
  - [关于作者](#关于作者)

## Overview

---

## 1.多成员的 `using` 声明 Multi member using declaration

在 C++11 中，`using` 声明可以用于引入基类成员到派生类中，这使得派生类可以访问基类的成员。这种声明特别有用，当基类中的成员由于命名空间或继承体系的不同而不直接可见时。

### 1.1.基本用法

在 C++11 之前，如果一个类继承自多个基类，并且这些基类有同名的成员，那么在派生类中访问这些成员可能会变得复杂。C++11 引入了多成员的 `using` 声明，允许派生类明确地指定它想要使用的基类成员。

### 1.2.示例

假设有两个基类 `A` 和 `B`，它们都有一个名为 `foo` 的成员函数，而派生类 `C` 继承自这两个基类：

```cpp
#include <iostream>

class A {
public:
    void foo() { std::cout << "A's foo\n"; }
};

class B {
public:
    void foo() { std::cout << "B's foo\n"; }
};

class C : public A, public B {
public:
    // 使用 using 声明来指定使用 A 的 foo
    using A::foo;

    void test() {
        foo();  // 调用 A 的 foo
    }
};

int main() {
    C obj;
    obj.foo();  // 输出 "A's foo"
    obj.test(); // 输出 "A's foo"
    return 0;
}
```

在这个例子中，`C` 使用 `using A::foo;` 声明来指定它想要使用 `A` 的 `foo` 函数。这样，在 `C` 的作用域内，`foo` 将直接引用 `A` 的 `foo` 函数。

### 1.3.多成员 `using` 声明

如果需要在派生类中引入多个成员，可以连续使用多个 `using` 声明：

```cpp
class C : public A, public B {
public:
    using A::foo;
    using B::foo;

    void testA() {
        foo();  // 调用 A 的 foo，因为 A 在 B 之前被继承
    }

    void testB() {
        B::foo();  // 明确调用 B 的 foo
    }
};
```

在这个例子中，`C` 通过两个 `using` 声明引入了 `A` 和 `B` 的 `foo` 函数。在没有明确指定的情况下，如果两个基类的成员具有相同的名称，派生类将根据继承的顺序来决定调用哪个基类的成员。

### 1.4.注意事项

- 使用 `using` 声明时，如果基类成员有同名函数，需要明确指定使用哪个基类的成员。
- `using` 声明可以减少名称查找的歧义，使得代码更加清晰。
- 在复杂的继承体系中，合理使用 `using` 声明可以提高代码的可读性和维护性。

这种特性在处理复杂的类继承关系时非常有用，尤其是在涉及多个基类有同名成员的情况下。

## 2.在 C++11 中，除了多成员的 `using` 声明，还有哪些其他方式可以解决基类成员的继承问题？

在 C++11 中，除了使用多成员的 `using` 声明来解决基类成员的继承问题，还有其他几种方法可以处理或避免继承中的名称冲突和访问问题：

1. **显式作用域分辨**：
   在派生类中调用成员函数时，可以使用基类的作用域解析运算符（`::`）来明确指定要调用的基类成员。

   ```cpp
   class Derived : public Base {
   public:
       void func() {
           Base::memberFunction();  // 显式调用基类的成员函数
       }
   };
   ```

2. **虚拟继承**：
   当多个基类继承自同一个基类，并且你希望消除歧义时，可以使用虚拟继承（虚继承），这样派生类将只有一个实例的该基类。

   ```cpp
   class Base {
   public:
       void func() { std::cout << "Base func\n"; }
   };

   class Middle : virtual public Base {};
   class Derived1 : public Middle {};
   class Derived2 : public Middle {};
   class MostDerived : public Derived1, public Derived2 {
   public:
       void callBaseFunc() {
           Base::func();  // 调用 Base 的 func
       }
   };
   ```

3. **覆盖（Override）**：
   在派生类中覆盖基类的虚函数，这样可以确保派生类的行为。

   ```cpp
   class Base {
   public:
       virtual void func() { std::cout << "Base func\n"; }
   };

   class Derived : public Base {
   public:
       void func() override { std::cout << "Derived func\n"; }  // 覆盖基类的 func
   };
   ```

4. **隐藏规则**：
   如果派生类有一个与基类成员同名的成员（不一定是函数），派生类的成员将隐藏（而不是覆盖）基类的成员。

   ```cpp
   class Base {
   public:
       int value = 10;
   };

   class Derived : public Base {
   public:
       int value = 20;
       void printValue() {
           std::cout << value;  // 打印派生类的 value
       }
   };
   ```

5. **构造函数初始化列表**：
   使用构造函数初始化列表来调用基类的构造函数，确保基类的成员被正确初始化。

   ```cpp
   class Base {
   public:
       Base() { std::cout << "Base constructor\n"; }
   };

   class Derived : public Base {
   public:
       Derived() : Base() { std::cout << "Derived constructor\n"; }
   };
   ```

6. **友元类**：
   如果需要，可以将一个类声明为另一个类的友元，这样它就可以访问其私有或受保护的成员。

   ```cpp
   class Base {
   friend class Derived;
   private:
       int secret = 42;
   };

   class Derived : public Base {
   public:
       int revealSecret() {
           return secret;
       }
   };
   ```

7. **聚合类**：
   如果基类的成员不需要封装，可以使用聚合类（没有用户自定义构造函数、基类或虚函数的类），这样成员的访问就不会受到限制。

8. **委托构造函数**：
   在类中使用委托构造函数来调用其他构造函数，以减少代码重复。

   ```cpp
   class MyClass {
   public:
       MyClass(int x) : value(x) {}
       MyClass() : MyClass(0) {}
   private:
       int value;
   };
   ```

9. **利用命名空间**：
   如果成员函数名称冲突是由于命名空间引起的，可以将成员函数放在不同的命名空间中。

每种方法都有其适用场景，选择合适的方法可以解决继承中的各种问题。

## 3.如何使用~using声明来解决基类成员的重载问题？

在 C++ 中，并没有 `~using` 声明这样的语法。您可能是想询问如何使用 `using` 声明来解决基类成员的重载问题。

当派生类从多个基类继承成员函数时，如果这些基类中有同名的重载函数，那么在派生类中直接使用这些函数可能会引起歧义。为了解决这个问题，可以使用 `using` 声明来指定派生类中要使用的是哪个基类的哪个重载版本。

### 3.1.示例

假设有两个基类 `A` 和 `B`，它们都有一个名为 `foo` 的重载成员函数：

```cpp
#include <iostream>

class A {
public:
    void foo(int x) { std::cout << "A's foo(int)\n"; }
    void foo(double x) { std::cout << "A's foo(double)\n"; }
};

class B {
public:
    void foo(int x) { std::cout << "B's foo(int)\n"; }
    void foo(double x) { std::cout << "B's foo(double)\n"; }
};

class C : public A, public B {
public:
    // 使用 using 声明来指定使用 A 的 foo
    using A::foo;

    void test() {
        foo(10);    // 调用 A 的 foo(int)
        foo(2.5);   // 调用 A 的 foo(double)
        B::foo(10); // 明确调用 B 的 foo(int)
    }
};

int main() {
    C obj;
    obj.foo(10);    // 调用 A 的 foo(int)
    obj.foo(2.5);   // 调用 A 的 foo(double)
    obj.test();
    return 0;
}
```

在这个例子中，`C` 使用 `using A::foo;` 声明来指定它想要使用 `A` 的 `foo` 函数。这样，在 `C` 的作用域内，`foo` 将直接引用 `A` 的 `foo` 函数。如果需要调用 `B` 的 `foo` 函数，可以使用 `B::foo` 来明确指定。

### 3.2.注意事项

- 使用 `using` 声明时，如果基类成员有同名函数，需要明确指定使用哪个基类的成员。
- `using` 声明可以减少名称查找的歧义，使得代码更加清晰。
- 在复杂的继承体系中，合理使用 `using` 声明可以提高代码的可读性和维护性。

这种特性在处理复杂的类继承关系时非常有用，尤其是在涉及多个基类有同名成员的情况下。

## 4.在C++11中，using声明在模板编程中有哪些应用场景？

在 C++11 中，`using` 声明在模板编程中的应用主要体现在以下几个方面：

1. **模板别名（Template Aliases）**：
   C++11 引入了 `using` 来定义模板别名，这使得定义模板类型更加直观和方便。例如，可以为复杂的模板类型定义一个简短的别名。

   ```cpp
   template<typename T>
   using Ptr = std::shared_ptr<T>;
   ```

   这种方式比传统的 `typedef` 更为清晰和直观。

2. **类型别名模板（Type Alias Templates）**：
   `using` 声明可以用于定义类型别名模板，这在需要为模板参数创建别名时非常有用。

   ```cpp
   template<typename T>
   using Vector = std::vector<T>;
   ```

   这样，就可以使用 `Vector<int>` 来代替 `std::vector<int>`，代码更加简洁。

3. **解决基类成员的重载问题**：
   当派生类从多个基类继承成员函数时，如果这些基类中有同名的重载函数，派生类可以使用 `using` 声明来指定使用哪个基类的哪个重载版本。

   ```cpp
   class Base1 {
   public:
       void foo(int);
       void foo(double);
   };

   class Base2 {
   public:
       void foo(int);
       void foo(double);
   };

   class Derived : public Base1, public Base2 {
   public:
       using Base1::foo; // 引入 Base1 的 foo 重载
       using Base2::foo; // 引入 Base2 的 foo 重载
   };
   ```

   这样，派生类就可以通过 `using` 声明来解决基类成员的重载问题，使得派生类中可以访问到所有的重载版本。

4. **显式指定模板参数**：
   在模板编程中，有时需要显式指定模板参数，以确保模板实例化的正确性。

   ```cpp
   template<class T1, class T2, class T3>
   T1 sum(T2 a, T3 b) {
       return a + b;
   }

   auto result = sum<int, int, int>(1, 2);
   ```

   这种方式可以避免模板参数的歧义，确保模板的正确实例化。

5. **类的成员函数模板**：
   类的成员函数也可以是模板函数，这在需要对不同的数据类型执行相同的操作时非常有用。

   ```cpp
   class Test {
   public:
       template<typename T>
       T add(T a, T b) {
           return a + b;
       }
   };
   ```

   这种方式允许类对不同的数据类型提供相同的功能，增加了类的灵活性。

6. **模板显式实例化**：
   为了避免多个.cpp文件实例化相同的类模板的开销，C++11 提出了 "模板显式实例化"。

   ```cpp
   // 实例化定义
   template class std::vector<int>;
   // 实例化声明
   extern template class std::vector<int>;
   ```

   这种方式可以提高程序的效率，减少重复实例化的开销。

通过这些应用，`using` 声明在模板编程中提供了更大的灵活性和便利性，使得模板的使用更加直观和高效。

## 5.在 C++11 中，如何使用 using 声明来定义模板别名？

在 C++11 中，`using` 声明可以被用来定义模板别名，这是一种为模板创建简短名称的方法。这在处理复杂的模板类型时非常有用，因为它可以使得代码更加简洁和可读。

### 5.1.基本语法

模板别名的基本语法如下：

```cpp
template<typename... Ts>
using Alias = Template<Ts...>;
```

这里，`Alias` 是你定义的别名，而 `Template<Ts...>` 是被别名替换的模板。

### 5.2.示例

假设我们有一个标准库中的 `std::vector` 模板，我们想要为它创建一个别名，使其专门用于存储 `int` 类型的数据：

```cpp
#include <vector>
#include <memory>

// 定义一个模板别名 'IntVector'，它是一个存储 int 的 vector
template<typename T = int>
using IntVector = std::vector<T>;

// 定义一个模板别名 'SharedPtr'，它是一个智能指针
template<typename T>
using SharedPtr = std::shared_ptr<T>;
```

### 5.3.使用示例

定义了别名之后，你可以在代码中使用这些别名，就像使用普通的类型一样：

```cpp
IntVector auto vec = {1, 2, 3, 4, 5};
SharedPtr<int> ptr = std::make_shared<int>(10);

std::cout << "Vector contains: ";
for (int num : vec) {
    std::cout << num << " ";
}
std::cout << "\nShared pointer value: " << *ptr << std::endl;
```

### 5.4.优点

使用 `using` 声明定义模板别名的优点包括：

1. **代码简洁**：别名可以简化复杂的模板表达式。
2. **提高可读性**：为复杂的类型提供有意义的名称，使代码更易于理解。
3. **易于维护**：如果需要更改底层类型，只需在别名定义处更改，而不需要修改每个实例化的位置。

### 5.5.注意事项

- 别名定义应该放在头文件中，以确保它们在包含该头文件的每个源文件中都可用。
- 使用 `using` 声明定义模板别名时，可以指定默认模板参数，如 `template<typename T = int>`。

这种特性在现代 C++ 编程中非常常见，特别是在使用标准库模板时，它提供了一种优雅的方式来简化模板的使用。

## 6.能否举例说明如何使用using声明来显式指定模板参数？

在 C++ 中，使用 `using` 声明来显式指定模板参数的情况通常出现在继承体系中，尤其是当涉及到从基类模板显式地引入类型或成员函数到派生类模板时。

以下是一些示例，说明如何使用 `using` 声明来显式指定模板参数：

### 6.1.示例 1: 引入类型定义

假设我们有一个基类模板，它定义了一个与模板参数相关的类型别名，我们希望在派生类中引入这个类型别名。

```cpp
// 基类模板
template<typename T>
class Base {
public:
    // 类型别名
    using ValueType = T;
};

// 派生类模板
template<typename T>
class Derived : public Base<T> {
public:
    // 使用 using 声明显式地从基类引入类型别名
    using typename Base<T>::ValueType;

    ValueType value;
    
    void printValue() {
        std::cout << value << std::endl;
    }
};

int main() {
    Derived<int> d;
    d.value = 42;
    d.printValue(); // 输出 42
    return 0;
}
```

在这个例子中，`Derived` 类模板使用 `using typename Base<T>::ValueType;` 来显式地从 `Base` 类模板引入 `ValueType` 类型别名。

### 6.2.示例 2: 继承构造函数

C++11 允许使用 `using` 声明来继承构造函数。

```cpp
// 基类模板
template<typename T>
class Base {
public:
    Base(T value) : value_(value) {}
    T value_;
};

// 派生类模板
template<typename T>
class Derived : public Base<T> {
public:
    // 使用 using 声明显式地从基类继承构造函数
    using Base<T>::Base; // 继承 Base 的所有构造函数

    void printValue() const {
        std::cout << Base<T>::value_ << std::endl;
    }
};

int main() {
    Derived<int> d(42);
    d.printValue(); // 输出 42
    return 0;
}
```

在这个例子中，`Derived` 类模板使用 `using Base<T>::Base;` 来显式地从 `Base` 类模板继承构造函数。

### 6.3.示例 3: 引入成员函数

假设我们有一个基类模板，它定义了一个成员函数，我们希望在派生类模板中引入这个成员函数。

```cpp
// 基类模板
template<typename T>
class Base {
public:
    void printValue(T value) {
        std::cout << value << std::endl;
    }
};

// 派生类模板
template<typename T>
class Derived : public Base<T> {
public:
    // 使用 using 声明显式地从基类引入成员函数
    using Base<T>::printValue;

    void execute() {
        printValue(42); // 调用继承的成员函数
    }
};

int main() {
    Derived<int> d;
    d.execute(); // 输出 42
    return 0;
}
```

在这个例子中，`Derived` 类模板使用 `using Base<T>::printValue;` 来显式地从 `Base` 类模板引入 `printValue` 成员函数。

这些示例展示了如何在模板类中使用 `using` 声明来显式地指定和引入模板参数、类型定义、构造函数和成员函数。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
