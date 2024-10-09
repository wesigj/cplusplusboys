# C++11 27-显式的虚拟函数重写 Explicit rewriting of virtual functions

- [C++11 27-显式的虚拟函数重写 Explicit rewriting of virtual functions](#c11-27-显式的虚拟函数重写-explicit-rewriting-of-virtual-functions)
  - [Overview](#overview)
  - [1.显式的虚拟函数重写 Explicit rewriting of virtual functions](#1显式的虚拟函数重写-explicit-rewriting-of-virtual-functions)
    - [1.1.基本语法](#11基本语法)
    - [1.2.示例](#12示例)
    - [1.3.注意事项](#13注意事项)
  - [2.在 C++ 中，除了使用 'override' 关键字，还有哪些方法可以重写基类的虚函数？](#2在-c-中除了使用-override-关键字还有哪些方法可以重写基类的虚函数)
    - [2.1. 隐式重写](#21-隐式重写)
    - [2.2. 显示使用 `virtual` 关键字](#22-显示使用-virtual-关键字)
    - [2.3. 使用函数指针](#23-使用函数指针)
    - [2.4. 利用基类中的虚函数表（vtable）](#24-利用基类中的虚函数表vtable)
    - [2.5. 利用编译器警告](#25-利用编译器警告)
    - [2.6. 代码审查和单元测试](#26-代码审查和单元测试)
    - [2.7.注意事项](#27注意事项)
  - [3.在C++11标准中，‘override'关键字的工作原理是什么？](#3在c11标准中override关键字的工作原理是什么)
    - [3.1.工作原理](#31工作原理)
    - [3.2.示例](#32示例)
    - [3.3.注意事项](#33注意事项)
  - [4.如何使用'final关键字来防止派生类重写特定的虚函数？](#4如何使用final关键字来防止派生类重写特定的虚函数)
    - [4.1.基本语法](#41基本语法)
    - [4.2.示例](#42示例)
    - [4.3.编译器错误](#43编译器错误)
    - [4.4.使用 `final` 关键字的优点](#44使用-final-关键字的优点)
    - [4.5.注意事项](#45注意事项)
    - [4.6.总结](#46总结)
  - [5.使用‘final关键字会有哪些潜在的性能影响，编译器是如何处理‘final函数的？](#5使用final关键字会有哪些潜在的性能影响编译器是如何处理final函数的)
    - [5.1.性能影响](#51性能影响)
    - [5.2.编译器处理](#52编译器处理)
    - [5.3.示例](#53示例)
    - [5.4.注意事项](#54注意事项)
  - [6.在 C++ 中，除了使用 'final' 关键字，还有哪些方法可以防止派生类重写虚函数？](#6在-c-中除了使用-final-关键字还有哪些方法可以防止派生类重写虚函数)
    - [6.1.注意事项](#61注意事项)
  - [关于作者](#关于作者)

## Overview

---

## 1.显式的虚拟函数重写 Explicit rewriting of virtual functions

在 C++11 及后续标准中，你可以使用 `override` 关键字来显式地指定一个成员函数是重写基类中的虚函数。这有助于提高代码的可读性和安全性，因为编译器会强制检查该函数确实覆盖了基类中的一个虚函数，并且它们的签名完全匹配。

### 1.1.基本语法

当你在派生类中重写基类的虚函数时，可以在函数声明的末尾添加 `override` 关键字：

```cpp
class Base {
public:
    virtual void func();
};

class Derived : public Base {
public:
    void func() override;  // 显式地重写基类的虚函数
};
```

### 1.2.示例

以下是一个完整的示例，演示如何使用 `override` 关键字来重写基类的虚函数：

```cpp
#include <iostream>

class Base {
public:
    virtual void func() {
        std::cout << "Base's func" << std::endl;
    }
    virtual void func(int x) {
        std::cout << "Base's func(int) with value: " << x << std::endl;
    }
};

class Derived : public Base {
public:
    void func() override {
        std::cout << "Derived's func" << std::endl;
    }
    void func(int x) override {
        std::cout << "Derived's func(int) with value: " << x << std::endl;
    }
};

class MoreDerived : public Derived {
public:
    void func() override {
        std::cout << "MoreDerived's func" << std::endl;
    }
};

int main() {
    Base* b = new Derived();
    b->func(); // 输出 "Derived's func"
    b->func(10); // 输出 "Derived's func(int) with value: 10"

    Derived* d = new MoreDerived();
    d->func(); // 输出 "MoreDerived's func"

    delete b;
    delete d;
    return 0;
}
```

### 1.3.注意事项

1. **编译器检查**：使用 `override` 关键字时，编译器会检查派生类的函数是否确实覆盖了基类中的虚函数。如果基类中没有对应的虚函数，或者函数签名不匹配，编译器将报错。

2. **与 `final` 关键字一起使用**：你可以使用 `final` 关键字来阻止进一步重写虚函数：

   ```cpp
   class Base {
   public:
       virtual void func() final = 0;
   };
   ```

   在这个例子中，`func` 函数被声明为 `final`，这意味着它不能被任何派生类重写。

3. **与 `default` 关键字一起使用**：有时你可能想要提供默认实现的虚函数，可以使用 `default` 关键字：

   ```cpp
   class Base {
   public:
       virtual void func() = 0;
   };
   
   class Derived : public Base {
   public:
       void func() override = default;
   };
   ```

   在这个例子中，`Derived` 类提供了 `func` 函数的默认实现。

通过使用 `override` 关键字，你可以提高代码的可读性和安全性，确保虚函数的正确重写。

## 2.在 C++ 中，除了使用 'override' 关键字，还有哪些方法可以重写基类的虚函数？

在 C++ 中，除了使用 `override` 关键字来显式地重写基类的虚函数外，还有其他几种方法可以实现基类虚函数的重写。以下是一些常见的方法：

### 2.1. 隐式重写

在没有 `override` 关键字的情况下，你仍然可以重写基类的虚函数，只需在派生类中声明一个与基类中虚函数具有相同名称和参数的成员函数。

```cpp
class Base {
public:
    virtual void func() {
        std::cout << "Base's func" << std::endl;
    }
};

class Derived : public Base {
public:
    void func() {
        std::cout << "Derived's func" << std::endl;
    }
};
```

在这个例子中，`Derived` 类中的 `func()` 函数隐式地重写了 `Base` 类中的虚函数。

### 2.2. 显示使用 `virtual` 关键字

在派生类中，你可以显式地使用 `virtual` 关键字来重写基类的虚函数。

```cpp
class Derived : public Base {
public:
    virtual void func() {
        std::cout << "Derived's func" << std::endl;
    }
};
```

虽然这种方法明确了函数的虚拟性质，但它不保证编译器会检查函数签名是否与基类中的虚函数匹配。

### 2.3. 使用函数指针

在某些复杂的场景下，如使用模板或多重继承时，可能需要通过函数指针来确保虚函数的正确重写。

```cpp
bool (Base::*baseFunc)() = &Base::func;
bool (Derived::*derivedFunc)() = &Derived::func;

static_assert(std::is_same<decltype(baseFunc), decltype(derivedFunc)>::value, "Function types must be the same");
```

这种方法通常用于编译时的类型检查，确保派生类正确地重写了基类的虚函数。

### 2.4. 利用基类中的虚函数表（vtable）

在 C++ 中，每个具有虚函数的类都有一个虚函数表（vtable），它是一个函数指针数组。在运行时，对象的虚函数调用会通过这个表来解析。通过分析这个表，可以在一定程度上检查虚函数是否被正确重写。

### 2.5. 利用编译器警告

一些编译器提供了警告选项，当派生类的函数没有正确重写基类的虚函数时，编译器会发出警告。例如，GCC 和 Clang 提供了 `-Woverloaded-virtual` 选项。

### 2.6. 代码审查和单元测试

除了技术手段外，代码审查和单元测试也是确保虚函数被正确重写的重要方法。通过代码审查可以发现潜在的问题，而单元测试可以确保函数的行为符合预期。

### 2.7.注意事项

- 使用 `override` 关键字是最推荐的方法，因为它提供了编译时的检查，可以避免很多常见的错误。
- 隐式重写虽然简单，但不推荐，因为它缺乏编译时的检查，容易出错。

通过这些方法，你可以在 C++ 中灵活地重写基类的虚函数，确保代码的正确性和可维护性。

## 3.在C++11标准中，‘override'关键字的工作原理是什么？

在 C++11 标准中，`override` 关键字被引入以提供对虚函数重写过程的显式和明确的编译时检查。当派生类中定义一个成员函数，并且打算重写基类中的虚函数时，可以在函数声明的末尾加上 `override` 关键字。

### 3.1.工作原理

1. **编译时检查**：
   当编译器遇到一个带有 `override` 关键字的成员函数时，它会进行以下检查：
   - 确保该函数确实重写了基类中的一个虚函数。
   - 确保该函数的签名与基类中的虚函数完全匹配（包括函数的名称、参数类型和数量、const 限定符等）。

2. **签名匹配**：
   如果派生类的函数签名与基类中的任何虚函数都不匹配，或者存在多个匹配的虚函数，编译器将报错，这有助于避免意外地隐藏了基类的虚函数。

3. **提升代码清晰度**：
   使用 `override` 关键字可以提高代码的可读性，因为它明确表示该函数旨在重写基类中的虚函数。

### 3.2.示例

```cpp
class Base {
public:
    virtual void func(int x) {
        std::cout << "Base's func with int" << std::endl;
    }
};

class Derived : public Base {
public:
    void func(int x) override {  // 正确重写
        std::cout << "Derived's func with int" << std::endl;
    }

    // 下面的代码将导致编译错误，因为签名不匹配
    // void func(double x) override; 
};

class MoreDerived : public Derived {
public:
    void func(int x) override {  // 正确重写
        std::cout << "MoreDerived's func with int" << std::endl;
    }
    
    // 下面的代码将导致编译错误，因为 MoreDerived 不能重写 Derived 的 func
    // void func(double x) override;
};
```

在这个示例中，`Derived` 类正确地重写了 `Base` 类的 `func(int x)` 函数，并且 `MoreDerived` 类也正确地重写了 `Derived` 类的 `func(int x)` 函数。如果尝试使用不匹配的签名，比如 `func(double x)`，编译器将报错。

### 3.3.注意事项

- 如果基类中的虚函数没有声明为 `virtual`，派生类中使用 `override` 的函数不会被视为重写，编译器也不会进行重写检查。
- 如果派生类中的函数使用了 `override` 关键字，但并没有重写基类中的任何虚函数，编译器将报错。
- `override` 关键字只能在虚函数的声明中使用。

通过使用 `override` 关键字，可以减少因错误重写虚函数而导致的常见错误，提高代码的安全性和可维护性。

## 4.如何使用'final关键字来防止派生类重写特定的虚函数？

在 C++ 中，使用 `final` 关键字可以阻止派生类重写特定的虚函数。当你在类中声明一个虚函数并使用 `final` 关键字时，你告诉编译器这个函数不能被任何进一步派生的类重写。

### 4.1.基本语法

在声明一个虚函数时，将 `final` 关键字放在函数声明的末尾：

```cpp
class Base {
public:
    virtual void func() final {
        std::cout << "Base's func" << std::endl;
    }
};
```

在这个例子中，`Base` 类的 `func()` 函数被声明为 `final`，这意味着它不能被任何派生类重写。

### 4.2.示例

以下是一个完整的示例，演示如何使用 `final` 关键字：

```cpp
#include <iostream>

class Base {
public:
    virtual void func() final {
        std::cout << "Base's func" << std::endl;
    }
};

// 尝试重写 func 函数的派生类
class Derived : public Base {
public:
    void func() override {
        std::cout << "Derived's func" << std::endl;
    }
};

int main() {
    Derived d;
    d.func(); // 编译错误：不允许重写 'Base::func()'
    return 0;
}
```

### 4.3.编译器错误

在上述示例中，尝试在 `Derived` 类中重写 `Base` 类的 `func()` 函数会导致编译错误，因为 `Base` 类中的 `func()` 函数被声明为 `final`。

### 4.4.使用 `final` 关键字的优点

1. **提高代码的可读性**：通过使用 `final` 关键字，你可以明确地告诉其他开发者这个函数不应该被重写。
2. **防止错误的重写**：编译器会强制检查，防止派生类错误地重写函数。
3. **优化**：在某些情况下，编译器可以对 `final` 函数进行优化，因为它们不会被重写。

### 4.5.注意事项

- `final` 关键字只能用于类内部声明的虚函数。
- 如果你使用 `final` 关键字，确保你真的不希望这个函数被重写，因为这是不可逆的。

### 4.6.总结

使用 `final` 关键字是一种明确和有效的方法来防止派生类重写特定的虚函数，有助于提高代码的安全性和可维护性。

## 5.使用‘final关键字会有哪些潜在的性能影响，编译器是如何处理‘final函数的？

在 C++ 中，使用 `final` 关键字可以防止派生类重写特定的虚函数。当你在一个虚函数后面加上 `final` 关键字时，你告诉编译器这个函数在派生类中不应该被重写。这有助于防止错误地重写函数，并且可以提供一定的性能优化。

### 5.1.性能影响

关于 `final` 关键字的性能影响，存在一些讨论。理论上，由于编译器知道一个被标记为 `final` 的函数不会被重写，它可以进行额外的优化，比如内联（inlining）或消除虚函数表（vtable）查找，这可能会提高性能。然而，实际上这种性能提升可能非常微小，并且并不是所有的编译器都会进行这样的优化。

### 5.2.编译器处理

编译器在处理 `final` 函数时，会进行静态检查以确保没有派生类尝试重写这个函数。如果派生类中有尝试重写 `final` 函数的代码，编译器将会报错。这提供了一种编译时的保护机制，以防止不正确的重写。

### 5.3.示例

```cpp
class Base {
public:
    virtual void func() final {
        // ...
    }
};

class Derived : public Base {
public:
    // 下面的声明会导致编译错误，因为 func() 被声明为 final
    // void func() override;
};
```

在这个例子中，`Base` 类中的 `func()` 函数被声明为 `final`，这意味着它不能在任何派生类中被重写。

### 5.4.注意事项

- 使用 `final` 关键字可以提高代码的可读性和可维护性，因为它明确表示某个函数不应该被重写。
- 性能优化的效果取决于编译器的实现和具体情况，不应依赖于 `final` 关键字来获得性能提升。
- 在某些情况下，`final` 关键字可能不会带来任何性能提升，或者提升非常微小，因此不应该为了性能而使用 `final`。

总的来说，`final` 关键字是一个有用的工具，可以帮助你设计更安全和更清晰的类层次结构，并且可能带来一些性能上的好处，但这些好处通常是次要的。

## 6.在 C++ 中，除了使用 'final' 关键字，还有哪些方法可以防止派生类重写虚函数？

在 C++ 中，使用 `final` 关键字是防止派生类重写虚函数的标准和最推荐的方法。然而，如果你出于某些原因不能或不想使用 `final` 关键字，以下是一些替代方法：

1. **非虚函数**：
   将基类中的函数声明为非虚（没有 `virtual` 关键字）。这样，派生类中的同名函数将不是重写，而是隐藏了基类中的函数。

   ```cpp
   class Base {
   public:
       void func() {
           std::cout << "Base's func" << std::endl;
       }
   };

   // 派生类
   class Derived : public Base {
   public:
       void func() {
           std::cout << "Derived's func" << std::endl;
       }
   };
   ```

   在这个例子中，`Derived::func` 隐藏了 `Base::func`，而不是重写它。

2. **私有虚函数**：
   将基类中的虚函数声明为私有（`private`）成员。这样，派生类将无法访问这个函数，因此也无法重写它。

   ```cpp
   class Base {
   private:
       virtual void func() {
           std::cout << "Base's func" << std::endl;
       }
   };

   // 派生类
   class Derived : public Base {
   // 无法重写 func，因为 func 是私有的
   };
   ```

   这种方法的问题是它限制了基类的接口设计，并且可能使得基类更难被正确地继承和扩展。

3. **文档约定**：
   通过文档明确指出某个函数不应该被重写。虽然这不是一个技术手段，但这是防止错误使用的一种方法。

4. **设计限制**：
   设计基类时，限制虚函数的使用，使得不需要在派生类中重写函数。这可能意味着重新考虑类的职责和继承结构。

5. **断言**：
   在基类中使用断言来确保虚函数不会被重写。这种方法并不常见，因为它增加了运行时开销，而且可以被优化掉。

   ```cpp
   class Base {
   public:
       virtual void func() {
           std::cout << "Base's func" << std::endl;
       }
   };

   class Derived : public Base {
   public:
       void func() {
           assert(false); // 确保永远不会被调用
           std::cout << "Derived's func" << std::endl;
       }
   };
   ```

   这种方法并不阻止重写，而是试图防止它的执行。

6. **组合继承**：
   使用组合而不是继承来复用代码。这样，你可以控制访问权限和行为，而不需要担心虚函数的重写问题。

   ```cpp
   class Base {
   public:
       void func() {
           std::cout << "Base's func" << std::endl;
       }
   };

   class Derived {
   private:
       Base base;
   public:
       void func() {
           base.func();
       }
   };
   ```

   在这个例子中，`Derived` 通过组合包含 `Base`，但并没有继承它的虚函数。

### 6.1.注意事项

- 使用 `final` 关键字是最直接和最可靠的方法来防止虚函数被重写。
- 其他方法可能会引入额外的复杂性或限制你的设计。
- 始终考虑代码的可维护性和可扩展性。

在大多数情况下，如果设计允许，推荐使用 `final` 关键字来防止虚函数的重写。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
