# C++ Practical-1 day5

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.构造

在C++中，构造函数是一种特殊的成员函数，用于在创建对象时初始化对象的成员变量。构造函数具有与类同名的名称，且没有返回类型，甚至连`void`也不是返回类型。

### 1.1.构造函数的特点

1. **名称与类名相同**。
2. **没有返回类型**，连`void`也不是。
3. **可以重载**，即一个类可以有多个构造函数，只要它们的参数列表不同。
4. **自动调用**，在创建对象时自动调用。

### 1.2.构造函数的类型

1. **默认构造函数**：如果没有定义任何构造函数，编译器会生成一个默认构造函数。
2. **参数化构造函数**：允许传递参数来初始化成员变量。
3. **拷贝构造函数**：用于创建一个对象的新实例，该实例是另一个同类型对象的副本。

### 1.3.示例1：参数化构造函数

```cpp
#include <iostream>

class Point {
public:
    int x, y;

    // 参数化构造函数
    Point(int xValue, int yValue) : x(xValue), y(yValue) {
        std::cout << "Constructor called. (" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    Point point1(10, 20);
    return 0;
}
```

在这个例子中，`Point`类有一个参数化构造函数，它接受两个整数参数，并用它们来初始化成员变量`x`和`y`。

### 1.4.示例2：默认构造函数

```cpp
#include <iostream>

class Point {
public:
    int x, y;

    // 默认构造函数
    Point() : x(0), y(0) {
        std::cout << "Default constructor called. (" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    Point point1;
    return 0;
}
```

在这个例子中，`Point`类有一个默认构造函数，它将成员变量`x`和`y`初始化为0。

### 1.5.示例3：拷贝构造函数

```cpp
#include <iostream>

class Point {
public:
    int x, y;

    // 参数化构造函数
    Point(int xValue, int yValue) : x(xValue), y(yValue) {}

    // 拷贝构造函数
    Point(const Point& other) : x(other.x), y(other.y) {
        std::cout << "Copy constructor called. (" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    Point point1(10, 20);
    Point point2 = point1; // 调用拷贝构造函数
    return 0;
}
```

在这个例子中，`Point`类有一个拷贝构造函数，它用于创建一个对象的新实例，该实例是另一个同类型对象的副本。

### 1.6.示例4：使用成员初始化列表

```cpp
#include <iostream>

class Point {
public:
    int x, y;

    // 使用成员初始化列表
    Point(int xValue, int yValue) : x(xValue), y(yValue) {
        std::cout << "Constructor called. (" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    Point point1(10, 20);
    return 0;
}
```

在这个例子中，构造函数使用成员初始化列表来初始化成员变量`x`和`y`。这是初始化成员变量的首选方法，因为它更高效，特别是对于常量成员和引用成员。

### 1.7.注意事项

- 构造函数可以是显式的，也可以是隐式的。显式构造函数不允许默认值，而隐式构造函数允许。
- 如果类中有成员变量没有在构造函数中初始化，编译器会生成一个默认构造函数来初始化它们。
- 构造函数可以调用其他构造函数来避免代码重复，使用`this->`指针。
- 构造函数不能被声明为`const`，因为它们会修改成员变量。

构造函数是C++类中非常重要的部分，正确地使用构造函数可以确保对象在创建时处于有效状态。

## 2.构造次序

在C++中，当创建一个对象时，构造函数的执行顺序非常重要，尤其是当涉及到成员变量和成员对象的初始化时。以下是构造过程中的步骤和初始化顺序：

1. **成员变量的初始化**：在成员变量的声明中，可以使用默认值，或者在构造函数的初始化列表中进行初始化。

2. **成员对象的初始化**：成员对象是指作为类成员的其他对象。成员对象的构造函数会在包含对象的类的构造函数体执行之前调用。

3. **基类的初始化**：如果类是从另一个类派生的（即存在继承），基类的构造函数会在派生类的构造函数体执行之前调用。

4. **构造函数体**：在所有成员变量和成员对象初始化之后，构造函数体中的代码将被执行。

### 2.1.初始化顺序

1. **基类成员变量**：基类的成员变量按照它们在类中的声明顺序进行初始化。
2. **派生类成员变量**：派生类的成员变量也是按照它们在类中的声明顺序进行初始化。
3. **基类构造函数**：基类的构造函数按照它们在派生类列表中的声明顺序调用。
4. **派生类构造函数**：派生类的构造函数体中的代码在所有基类构造函数之后执行。

### 2.2.示例

```cpp
#include <iostream>

class Base {
public:
    Base() {
        std::cout << "Base constructor called" << std::endl;
    }
};

class Derived : public Base {
public:
    int a;
    int b;

    Derived(int x, int y) : a(x), b(y) {
        std::cout << "Derived constructor called" << std::endl;
    }
};

int main() {
    Derived obj(10, 20);
    return 0;
}
```

在这个例子中，输出将是：

```bash
Base constructor called
Derived constructor called
```

这表明基类的构造函数首先被调用，然后才是派生类的构造函数。

### 2.3.注意事项

- **初始化列表**：成员变量和成员对象应该在构造函数的初始化列表中初始化，而不是在构造函数体中。这是因为初始化列表可以更有效地初始化成员，特别是对于常量成员和引用成员。
- **成员对象的构造**：成员对象的构造函数会自动被调用，不需要在初始化列表中显式调用。
- **继承和初始化**：在派生类中，基类的构造函数总是首先被调用，然后才是派生类成员的初始化。
- **默认构造函数**：如果一个类没有显式定义任何构造函数，编译器会生成一个默认构造函数。这个默认构造函数会调用基类的默认构造函数，并按照成员变量的声明顺序进行默认初始化。

理解构造函数的调用和初始化顺序对于正确地设计和实现类非常重要，特别是在涉及到复杂的继承关系和成员初始化时。

## 3.inherit 继承

在C++中，继承是面向对象编程的一个重要特性，它允许一个类（称为派生类或子类）继承另一个类（称为基类或父类）的属性和方法。继承提供了一种机制，通过这种机制，一个类可以扩展或修改另一个类的行为。

### 3.1.继承的类型

1. **公有继承（public）**：基类的公有成员和保护成员在派生类中保持其原有的访问属性。
2. **保护继承（protected）**：基类的公有成员和保护成员在派生类中成为保护成员。
3. **私有继承（private）**：基类的公有成员和保护成员在派生类中成为私有成员。

### 3.2.访问控制

- **公有成员（public）**：可以被任何对象访问。
- **保护成员（protected）**：只能被类本身和子类访问。
- **私有成员（private）**：只能被类本身访问。

### 3.3.示例1：公有继承

```cpp
#include <iostream>

class Base {
public:
    int publicData = 10;
    void publicFunc() {
        std::cout << "Base public function." << std::endl;
    }
};

class Derived : public Base {
public:
    void derivedFunc() {
        publicFunc(); // 可以访问基类的公有成员
        std::cout << publicData << std::endl; // 可以访问基类的公有成员
    }
};

int main() {
    Derived d;
    d.publicFunc(); // 可以访问派生类的公有继承成员
    std::cout << d.publicData << std::endl; // 可以访问派生类的公有继承成员
    d.derivedFunc();
    return 0;
}
```

### 3.4.示例2：保护继承

```cpp
#include <iostream>

class Base {
protected:
    int protectedData = 20;
    void protectedFunc() {
        std::cout << "Base protected function." << std::endl;
    }
};

class Derived : protected Base {
public:
    void derivedFunc() {
        protectedFunc(); // 可以访问基类的保护成员
        std::cout << protectedData << std::endl; // 可以访问基类的保护成员
    }
};

int main() {
    Derived d;
    // d.protectedFunc(); // 错误：基类的保护成员在派生类外部不可访问
    // std::cout << d.protectedData << std::endl; // 错误：基类的保护成员在派生类外部不可访问
    d.derivedFunc();
    return 0;
}
```

### 3.5.示例3：私有继承

```cpp
#include <iostream>

class Base {
private:
    int privateData = 30;
    void privateFunc() {
        std::cout << "Base private function." << std::endl;
    }
};

class Derived : private Base {
public:
    void derivedFunc() {
        privateFunc(); // 可以访问基类的私有成员
        std::cout << privateData << std::endl; // 可以访问基类的私有成员
    }
};

int main() {
    Derived d;
    // d.privateFunc(); // 错误：基类的私有成员在派生类外部不可访问
    // std::cout << d.privateData << std::endl; // 错误：基类的私有成员在派生类外部不可访问
    d.derivedFunc();
    return 0;
}
```

代码中存在几个问题，主要是因为基类的私有成员在派生类中无法直接访问，即使派生类继承了基类。此外，派生类的`derivedFunc`方法试图访问基类的私有成员，这在私有继承下是不允许的。

#### 3.5.1.问题

1. **私有继承**：当`Derived`类以私有方式继承`Base`类时，`Base`类的私有成员在`Derived`类中仍然是私有的，这意味着它们不能在`Derived`类的公共接口中被访问。

2. **访问限制**：在`Derived`类的`derivedFunc`方法中，尝试访问`Base`类的私有成员`privateData`和`privateFunc`是不允许的，因为它们在`Derived`类中是私有的。

#### 3.5.2.解决方案

1. **更改继承类型**：如果需要在派生类中访问基类的私有成员，可以将继承类型改为保护继承或公有继承。

2. **提供访问器方法**：在`Base`类中提供公共的访问器方法来访问私有成员。

3. **友元类**：如果需要在派生类中访问基类的私有成员，可以将派生类声明为基类的友元类。

#### 3.5.3.修改后的代码

```cpp
#include <iostream>

class Base {
private:
    int privateData = 30;
    void privateFunc() {
        std::cout << "Base private function." << std::endl;
    }
public:
    // 提供访问器方法
    int getPrivateData() const { return privateData; }
    void privateFuncPublic() { privateFunc(); }
};

class Derived : public Base { // 改为公有继承
public:
    void derivedFunc() {
        privateFuncPublic(); // 调用公共接口访问私有成员函数
        std::cout << getPrivateData() << std::endl; // 调用访问器方法
    }
};

int main() {
    Derived d;
    d.derivedFunc(); // 正确调用
    return 0;
}
```

在这个修改后的代码中，`Base`类提供了两个公共方法`getPrivateData`和`privateFuncPublic`来访问私有成员。`Derived`类通过公有继承`Base`类，可以访问这些公共方法。这样，`Derived`类的`derivedFunc`方法可以间接访问`Base`类的私有成员。

#### 3.5.4.注意事项

- **封装性**：应该谨慎地暴露类的内部实现细节，以保持封装性。
- **继承和访问控制**：继承不会改变成员的访问级别，但会影响它们在派生类中的可访问性。
- **友元类**：使用友元类时要小心，因为它破坏了封装性，应该谨慎使用。

### 3.6.注意事项

- **继承访问控制**：继承不会改变基类成员的访问控制属性，它只是影响成员在派生类中的访问控制。
- **友元**：基类的友元在派生类中不是自动成为友元。
- **构造函数和析构函数**：基类的构造函数和析构函数不能被继承，需要在派生类中显式调用。
- **多重继承**：C++支持多重继承，但可能导致复杂的访问控制问题。

正确使用继承和访问控制可以提高代码的可重用性和可维护性，但也需要注意避免访问控制问题和设计上的复杂性。

## 4.derive 派生

在C++中，"derive"通常指的是派生类的概念，即一个类（称为派生类或子类）继承另一个类（称为基类或父类）的过程。派生类可以继承基类的属性和方法，并且可以添加或修改自己的属性和方法。

以下是派生类的一些关键点：

1. **公有继承（public）**：这是最常见的继承类型。在公有继承中，基类的公有成员和保护成员在派生类中保持相同的访问级别。

2. **保护继承（protected）**：在保护继承中，基类的公有成员和保护成员在派生类中都成为保护成员。这意味着它们只能在派生类及其子类中被访问。

3. **私有继承（private）**：在私有继承中，基类的公有成员和保护成员在派生类中都成为私有成员。这意味着它们只能在派生类内部被访问。

4. **多重继承**：C++允许一个类从多个基类继承属性和方法。

5. **虚拟继承**：用于解决多重继承中的菱形继承问题（钻石继承）。

### 4.1.示例：公有继承

```cpp
#include <iostream>

// 基类
class Base {
public:
    Base() { std::cout << "Base constructor called.\n"; }
    virtual void print() const { std::cout << "Base print function.\n"; }
};

// 派生类
class Derived : public Base {
public:
    Derived() { std::cout << "Derived constructor called.\n"; }
    void print() const override { std::cout << "Derived print function.\n"; }
};

int main() {
    Derived d;
    d.print(); // 调用派生类的print函数

    Base* b = &d;
    b->print(); // 调用派生类的print函数，因为print函数是虚函数

    return 0;
}
```

在这个例子中，`Derived`类从`Base`类公有继承。`Derived`类有自己的`print`函数，覆盖了基类的`print`函数。

### 4.2.示例：保护继承

```cpp
#include <iostream>

// 基类
class Base {
protected:
    int baseValue = 10;
};

// 派生类
class Derived : protected Base {
public:
    int getBaseValue() const { return baseValue; }
};

int main() {
    Derived d;
    std::cout << d.getBaseValue() << std::endl; // 访问基类的保护成员

    return 0;
}
```

在这个例子中，`Derived`类从`Base`类保护继承，基类的公有成员在派生类中成为保护成员。

### 4.3.示例：私有继承

```cpp
#include <iostream>

// 基类
class Base {
public:
    void baseFunction() const { std::cout << "Base function.\n"; }
};

// 派生类
class Derived : private Base {
public:
    void derivedFunction() const {
        baseFunction(); // 派生类可以访问基类的私有成员
    }
};

int main() {
    Derived d;
    // d.baseFunction(); // 错误：基类的私有成员在派生类外部不可访问
    d.derivedFunction(); // 调用派生类的函数

    return 0;
}
```

在这个例子中，`Derived`类从`Base`类私有继承，基类的公有成员在派生类中成为私有成员。

### 4.4.注意事项

- 派生类应该谨慎使用继承来，只有当存在"是一个(is-a)"关系时才使用继承。
- 虚函数在基类中声明，在派生类中可以被覆盖，以实现多态。
- 构造函数和析构函数不会自动从基类继承，需要在派生类中显式定义。
- 在派生类中，使用`override`关键字来明确指出要覆盖基类的虚函数。
- 使用`final`关键字可以防止类被进一步继承，或使用`final`关键字阻止虚函数被覆盖。

继承是C++中一个强大的特性，但应该谨慎使用，以避免复杂的继承层次结构和潜在的设计问题。

### 4.5.虚继承

在C++中，虚继承（Virtual Inheritance）是一种解决多重继承中菱形继承问题（钻石继承结构）的机制。在没有虚继承的情况下，派生类会从基类继承两份相同的成员，这会导致数据冗余和不一致性。虚继承通过为基类创建一个单一的共享实例来解决这个问题。

#### 4.5.1.菱形继承问题

考虑以下情况，有两个基类`B`和`C`，它们都是从基类`A`派生而来，而派生类`D`又从`B`和`C`派生。如果没有虚继承，`A`的成员会被继承两次，一次来自`B`，一次来自`C`。

```shell
  A
 / \
B   C
 \ /
  D
```

#### 4.5.2.虚继承的语法

在C++中，通过在继承列表中使用`virtual`关键字来实现虚继承。

#### 4.5.3.示例：虚继承

```cpp
#include <iostream>

class A {
public:
    int data;
    A() { data = 10; }
    virtual void printData() { std::cout << "A: " << data << std::endl; }
};

// 虚继承 A
class B : virtual public A {
public:
    B() { std::cout << "B Constructor called" << std::endl; }
};

// 虚继承 A
class C : virtual public A {
public:
    C() { std::cout << "C Constructor called" << std::endl; }
};

// 继承 B 和 C
class D : public B, public C {
public:
    D() { std::cout << "D Constructor called" << std::endl; }
    void printData() {
        std::cout << "D: " << data << std::endl; // 直接访问 A 的成员
    }
};

int main() {
    D d;
    d.printData(); // 输出 A 的数据成员
    // d.B::printData(); // 错误：B 的 A 子对象是私有的
    // d.C::printData(); // 错误：C 的 A 子对象是私有的
    return 0;
}
```

在这个例子中，`B`和`C`都虚继承自`A`，这意味着`A`的成员在`D`中只有一个共享实例。`D`可以直接访问`A`的成员。

#### 4.5.4.注意事项

1. **虚基类**：在虚继承中，基类`A`被称为虚基类。

2. **构造函数**：虚基类的构造函数需要在派生类的构造函数中显式调用。

3. **访问控制**：虚基类的访问级别在派生类中可能会改变。

4. **菱形继承**：虚继承主要用于解决菱形继承问题，但也可以用于更复杂的继承结构。

5. **性能开销**：虚继承可能会增加程序的复杂性和性能开销，因为需要维护虚基类的映射。

6. **虚继承和虚析构函数**：虚基类的析构函数也应该声明为虚函数，以确保在删除派生类对象时正确释放资源。

虚继承是C++中处理复杂继承关系的重要工具，但应该谨慎使用，以避免不必要的复杂性和性能问题。

## 5.构造函数和析构函数的构造规则

在C++中，构造函数和析构函数是特殊的成员函数，它们在创建和销毁对象时自动调用。它们有一些特定的规则和特点：

### 5.1.构造函数的规则

1. **名称与类名相同**：构造函数的名称必须与类名完全相同。

2. **没有返回类型**：构造函数没有返回类型，也不返回任何值。

3. **可以被重载**：一个类可以有多个构造函数，只要它们的参数列表不同。

4. **自动调用**：当使用`new`运算符或在创建对象时，构造函数会被自动调用。

5. **初始化成员变量**：构造函数可以使用成员初始化列表来初始化成员变量。

6. **调用基类构造函数**：如果类继承自另一个类，构造函数会调用基类的构造函数。

7. **不能声明为`const`或`volatile`**：构造函数用于创建对象，因此不能声明为`const`或`volatile`。

### 5.2.析构函数的规则

1. **名称**：析构函数的名称是在类名前加上`~`符号。

2. **没有返回类型**：析构函数没有返回类型，也不返回任何值。

3. **不能被重载**：一个类只能有一个析构函数。

4. **自动调用**：当对象离开作用域、被删除或程序结束时，析构函数会被自动调用。

5. **释放资源**：析构函数通常用于释放对象占用的资源，如动态分配的内存、文件句柄、网络连接等。

6. **调用基类析构函数**：如果类继承自另一个类，析构函数会调用基类的析构函数。

7. **可以声明为`virtual`**：如果基类的析构函数声明为`virtual`，派生类的析构函数也会是虚函数。这允许通过基类指针或引用删除派生类对象时正确调用派生类的析构函数。

### 5.3.示例

```cpp
#include <iostream>

class Base {
public:
    Base() {
        std::cout << "Base constructor called" << std::endl;
    }
    virtual ~Base() {
        std::cout << "Base destructor called" << std::endl;
    }
};

class Derived : public Base {
public:
    Derived() {
        std::cout << "Derived constructor called" << std::endl;
    }
    ~Derived() {
        std::cout << "Derived destructor called" << std::endl;
    }
};

int main() {
    {
        Derived d; // 调用 Derived 的构造函数，然后调用 Base 的构造函数
    } // d 离开作用域，调用 Derived 的析构函数，然后调用 Base 的析构函数

    return 0;
}
```

在这个例子中，当`Derived`对象`d`被创建时，首先调用`Base`类的构造函数，然后调用`Derived`类的构造函数。当`d`离开作用域时，首先调用`Derived`类的析构函数，然后调用`Base`类的析构函数。

### 5.4.注意事项

- **成员初始化顺序**：成员变量的初始化顺序是根据它们在类中声明的顺序，而不是它们在构造函数初始化列表中的顺序。

- **构造函数和析构函数的匹配**：每个对象的生命周期内，构造函数和析构函数都只调用一次。

- **异常安全**：构造函数不应该抛出异常，如果抛出异常，析构函数将不会被调用。

- **资源管理**：构造函数应该避免分配资源，以防止在构造过程中发生异常，导致资源泄漏。

- **继承和构造函数**：在派生类中，应该调用基类的构造函数来初始化基类部分。

- **继承和析构函数**：在派生类中，应该小心处理资源释放，确保基类的析构函数能够正确调用。

理解和正确实现构造函数和析构函数对于确保对象的正确初始化和资源的正确释放至关重要。

## 6.virtual

在C++中，`virtual`关键字用于声明虚函数，它允许在派生类中覆盖（override）基类的函数，并实现多态性。多态性是指允许不同类的对象对同一消息做出不同的响应。

### 6.1.虚函数的特点

1. **基类中声明**：虚函数通常在基类中声明，并使用`virtual`关键字。

2. **派生类中覆盖**：派生类可以覆盖基类的虚函数，提供特定的实现。

3. **动态绑定**：在运行时，根据对象的实际类型调用相应的函数，而不是在编译时确定。

4. **使用`override`**：在派生类中覆盖虚函数时，使用`override`关键字可以明确指出函数的覆盖意图，有助于编译器检查错误。

5. **使用`virtual`在析构函数**：如果基类的析构函数声明为`virtual`，那么通过基类指针或引用删除派生类对象时，将正确调用派生类的析构函数。

### 6.2.示例1：虚函数和覆盖

```cpp
#include <iostream>

class Base {
public:
    virtual void print() const {
        std::cout << "Base print function." << std::endl;
    }
    virtual ~Base() {} // 虚析构函数
};

class Derived : public Base {
public:
    void print() const override { // 使用override关键字
        std::cout << "Derived print function." << std::endl;
    }
};

int main() {
    Base* b = new Derived();
    b->print(); // 调用Derived的print函数
    delete b; // 调用Derived的析构函数
    return 0;
}
```

在这个例子中，`Base`类有一个虚函数`print`，`Derived`类覆盖了这个函数。在`main`函数中，通过基类指针`b`调用`print`函数时，实际上调用的是`Derived`类的`print`函数。

### 6.3.示例2：虚析构函数

```cpp
#include <iostream>

class Base {
public:
    virtual ~Base() {
        std::cout << "Base destructor called." << std::endl;
    }
};

class Derived : public Base {
public:
    ~Derived() {
        std::cout << "Derived destructor called." << std::endl;
    }
};

int main() {
    Base* b = new Derived();
    delete b; // 调用Derived的析构函数，然后调用Base的析构函数
    return 0;
}
```

在这个例子中，`Base`类的析构函数被声明为虚函数。当删除基类指针`b`时，首先调用`Derived`类的析构函数，然后调用`Base`类的析构函数。

在C++中，虚析构函数是一种重要的设计选择，特别是在处理继承体系时。它确保了当一个对象是通过基类的指针或引用被删除时，正确的析构函数链被调用，从而保证了资源的正确释放。

#### 6.3.1.为什么需要虚析构函数？

在多重继承或简单的继承体系中，如果基类的析构函数不是虚的，那么在删除派生类对象时，基类的析构函数可能不会被调用。这可能导致资源泄漏，因为派生类的析构函数通常负责释放它分配的资源。

#### 6.3.2.示例1：没有虚析构函数的问题

```cpp
#include <iostream>

class Base {
public:
    ~Base() {
        std::cout << "Base destructor called." << std::endl;
    }
};

class Derived : public Base {
public:
    ~Derived() {
        std::cout << "Derived destructor called." << std::endl;
    }
};

int main() {
    Base* b = new Derived();
    delete b; // 问题：Derived的析构函数没有被调用
    return 0;
}
```

在这个例子中，当`b`被删除时，只有`Base`的析构函数被调用，而`Derived`的析构函数没有被调用。

#### 6.3.3.示例2：使用虚析构函数

```cpp
#include <iostream>

class Base {
public:
    virtual ~Base() {
        std::cout << "Base destructor called." << std::endl;
    }
};

class Derived : public Base {
public:
    ~Derived() {
        std::cout << "Derived destructor called." << std::endl;
    }
};

int main() {
    Base* b = new Derived();
    delete b; // 正确：Derived的析构函数首先被调用，然后是Base的析构函数
    return 0;
}
```

在这个修正后的代码中，`Base`的析构函数被声明为虚函数。当`b`被删除时，首先调用`Derived`的析构函数，然后调用`Base`的析构函数。

#### 6.3.4.注意事项

1. **声明虚析构函数**：在基类中，将析构函数声明为`virtual`，以确保在删除派生类对象时，正确的析构函数链被调用。

2. **多重继承**：在多重继承中，每个基类都应该有一个虚析构函数，以确保所有基类的析构函数都能被正确调用。

3. **资源管理**：确保在派生类的析构函数中正确释放资源。

4. **虚析构函数和纯虚函数**：虚析构函数通常与纯虚函数一起使用，以实现多态和确保正确的资源释放。

5. **虚析构函数和对象切片**：在处理对象切片时，虚析构函数可以确保派生类的部分被正确销毁。

虚析构函数是C++中实现良好面向对象设计的关键部分，它有助于避免资源泄漏并确保资源的正确管理。

### 6.4.注意事项

- **虚函数和继承**：只有公有继承的虚函数才能在派生类中被覆盖。

- **虚函数和静态类型**：虚函数的调用依赖于对象的静态类型，而不是动态类型。如果通过基类类型的引用或指针调用虚函数，将调用对象实际类型的函数。

- **虚函数和构造函数**：构造函数不能是虚函数，因为对象在构造过程中尚未完全构造好。

- **纯虚函数**：使用`= 0`可以声明一个纯虚函数，它没有实现，并且使得类成为抽象类。派生类必须覆盖所有的纯虚函数才能创建对象。

- **`final`关键字**：可以使用`final`关键字阻止虚函数被进一步覆盖。

正确使用虚函数可以提高代码的灵活性和可扩展性，但也需要仔细设计，以避免滥用和复杂的继承关系。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
