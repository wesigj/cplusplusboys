# C++11 22-新的转换运算符 New conversion operator

- [C++11 22-新的转换运算符 New conversion operator](#c11-22-新的转换运算符-new-conversion-operator)
  - [Overview](#overview)
  - [1.新的转换运算符 New conversion operator](#1新的转换运算符-new-conversion-operator)
  - [2.C++11 中的 static\_cast 和 const\_cast 有什么区别？](#2c11-中的-static_cast-和-const_cast-有什么区别)
  - [3.在C++中，除了static\_cast和const\_cast，还有哪些其他类型的类型转换运算符？](#3在c中除了static_cast和const_cast还有哪些其他类型的类型转换运算符)
  - [4.const\_cast在哪些情况下是必要的，能否给出一个使用const\_cast的典型场景？](#4const_cast在哪些情况下是必要的能否给出一个使用const_cast的典型场景)
  - [5.如果我想在C++中进行更安全的类型转换，我应该使用哪种类型转换运算符，为什么？](#5如果我想在c中进行更安全的类型转换我应该使用哪种类型转换运算符为什么)
  - [6.dynamic\_cast在多态类转换中是如何工作的?](#6dynamic_cast在多态类转换中是如何工作的)
    - [6.1.工作原理](#61工作原理)
    - [6.2.使用场景](#62使用场景)
    - [6.3.示例](#63示例)
    - [6.4.注意事项](#64注意事项)
  - [7.在C++11中，如何使用explicit关键字来避免隐式类型转换？](#7在c11中如何使用explicit关键字来避免隐式类型转换)
    - [7.1.使用`explicit`关键字](#71使用explicit关键字)
    - [7.2.示例](#72示例)
    - [7.3.转换运算符与`explicit`](#73转换运算符与explicit)
    - [7.4.注意事项](#74注意事项)
  - [8.在C++中，除了使用explicit关键字外，还有哪些方法可以防止隐式类型转换？](#8在c中除了使用explicit关键字外还有哪些方法可以防止隐式类型转换)
  - [9.如果我想在类中同时使用explicit和noexcept关键字，应该怎么做？](#9如果我想在类中同时使用explicit和noexcept关键字应该怎么做)
    - [9.1.注意事项](#91注意事项)
  - [10.能否给我一个使用explicit关键字的多参数构造函数的例子？](#10能否给我一个使用explicit关键字的多参数构造函数的例子)
    - [10.1.为什么多参数构造函数不能使用`explicit`？](#101为什么多参数构造函数不能使用explicit)
    - [10.2.多参数构造函数](#102多参数构造函数)
    - [10.3.示例](#103示例)
    - [10.4.结论](#104结论)
  - [关于作者](#关于作者)

## Overview

---

## 1.新的转换运算符 New conversion operator

C++11引入了新的类型转换运算符，主要包括以下几种：

1. `static_cast`：用于基本的非多态类型转换，包括将派生类指针转换为基类指针（上转型）和非多态类型的转换。它不进行运行时类型检查。

2. `const_cast`：用于修改值的`const`或`volatile`属性。它不改变表达式的值类型。

3. `reinterpret_cast`：用于进行低层次的重新解释转换，比如将指针类型转换为整数类型，或者反过来。这种转换不安全，因为它不检查转换的合理性。

4. `dynamic_cast`：用于类层次结构中的向下转型（将基类指针或引用转换为派生类指针或引用），它在运行时进行类型检查，如果转换失败会返回`nullptr`或抛出异常。

C++11还引入了显示的类型转换运算符，即使用`explicit`关键字修饰的转换运算符，这样可以避免编译器进行隐式类型转换，提高代码的安全性。例如：

```cpp
class SmallInt {
public:
    explicit operator int() const { return val; }
};
```

这样的定义可以防止像`SmallInt si = 3;`这样的隐式转换，而需要使用`static_cast<int>(si)`来显式转换。

## 2.C++11 中的 static_cast 和 const_cast 有什么区别？

在C++中，`static_cast`和`const_cast`是两种不同的类型转换运算符，它们用于不同的目的：

1. **`static_cast`**：
   - 用于执行非多态类型的转换，这意味着它不会在运行时检查转换的安全性。
   - 可以用于基本数据类型之间的转换，如将`int`转换为`float`，或者将一种指针类型转换为另一种指针类型。
   - 可以用于向上转型（将派生类指针转换为基类指针）和向下转型（将基类指针转换为派生类指针），但后者需要是合法的，否则可能会得到未定义的行为。
   - 不能用于去除对象的`const`或`volatile`属性。

2. **`const_cast`**：
   - 专门用于修改值的`const`或`volatile`属性。
   - 不能改变表达式的值类别（例如，不能将非常量引用转换为常量引用）。
   - 不能用于转换不同类型的数据，只能用于改变对象的`const`或`volatile`属性。
   - 通常用于接口函数中，当需要传递一个`const`对象的非`const`指针或引用时。

**例子**：

```cpp
const int ci = 10;
int& ri = const_cast<int&>(ci); // 移除const属性，使ci可以被修改

int* pi = new int(20);
const int*pci = static_cast<const int*>(pi); // 将非常量指针转换为常量指针
```

在使用这些转换运算符时，应该尽量使用`static_cast`，因为它在某些情况下可以提供类型安全检查。而`const_cast`应该谨慎使用，因为它只是改变了对象的`const`或`volatile`属性，并没有进行类型检查。

## 3.在C++中，除了static_cast和const_cast，还有哪些其他类型的类型转换运算符？

在C++中，除了`static_cast`和`const_cast`，还有以下类型转换运算符：

1. **`dynamic_cast`**：
   - 用于类层次结构中的向下转型（将基类指针或引用转换为派生类指针或引用）。
   - 在运行时进行类型检查，如果转换失败，对于指针会返回`nullptr`，对于引用会抛出`std::bad_cast`异常。
   - 只能用于含有虚函数的类的指针或引用之间的转换，因为需要运行时类型信息（RTTI）。

2. **`reinterpret_cast`**：
   - 用于进行低层次的重新解释转换，可以将任何指针转换为任何其他指针类型，甚至可以将指针转换为足够大的整数类型。
   - 也可以用于将任何整数类型转换为任何指针类型。
   - 这种转换不安全，因为它不检查转换的合理性，可能会导致未定义行为。

3. **C++11 新增的类型转换运算符**：
   - **`std::static_pointer_cast`**：用于智能指针之间的转换，等同于`static_cast`，但适用于`std::shared_ptr`和`std::unique_ptr`。
   - **`std::dynamic_pointer_cast`**：用于智能指针之间的转换，等同于`dynamic_cast`，但适用于`std::shared_ptr`。
   - **`std::const_pointer_cast`**：用于智能指针之间的转换，等同于`const_cast`，但适用于`std::shared_ptr`。
   - **`std::reinterpret_pointer_cast`**：用于智能指针之间的转换，等同于`reinterpret_cast`，但适用于`std::shared_ptr`。

这些类型转换运算符提供了不同级别的类型安全检查和不同的转换能力，以满足不同的需求。在使用时，应该根据具体情况选择最合适的转换运算符。

## 4.const_cast在哪些情况下是必要的，能否给出一个使用const_cast的典型场景？

`const_cast`在C++中主要用于修改类型的`const`或`volatile`属性。它通常用于以下情况：

1. **接口函数**：当一个函数需要修改传入的参数，但参数本身是`const`的。例如，某些库函数可能需要非`const`参数来修改数据。

2. **临时修改对象的`const`属性**：当你需要临时移除对象的`const`属性以进行某些操作，然后再恢复其`const`属性。

3. **与旧代码或库的兼容性**：在与旧代码或第三方库交互时，可能需要移除`const`属性以调用某些不接受`const`参数的函数。

4. **多态行为的修改**：在多态情况下，基类指针可能指向一个`const`对象，但需要调用派生类的非`const`成员函数。

**典型场景**：

假设你有一个函数，它接受一个非`const`引用参数，但是你需要将一个`const`对象传递给这个函数。在这种情况下，你可以使用`const_cast`来移除`const`属性。

```cpp
void modifyInt(int& n) {
    n += 5; // 修改传入的整数
}

const int ci = 10;
int main() {
    // 需要将const对象ci传递给modifyInt函数
    modifyInt(const_cast<int&>(ci)); // 使用const_cast移除const属性
    return 0;
}
```

在这个例子中，`modifyInt`函数需要一个非`const`引用参数，但是`ci`是一个`const`对象。通过使用`const_cast<int&>(ci)`，我们可以临时移除`ci`的`const`属性，使其可以被`modifyInt`函数修改。

**注意**：使用`const_cast`时应该非常小心，因为它可以绕过`const`的保护，可能会导致未定义行为，特别是当你修改了原本不应该被修改的`const`对象时。因此，只有在确信这样做是安全的情况下才使用`const_cast`。

## 5.如果我想在C++中进行更安全的类型转换，我应该使用哪种类型转换运算符，为什么？

在C++中，为了进行更安全的类型转换，你应该根据转换的上下文和需求选择合适的类型转换运算符。以下是一些指导原则：

1. **`static_cast`**：
   - 当你需要进行基本的、非多态的类型转换时，如将`int`转换为`float`，或者将派生类指针转换为基类指针（上转型），使用`static_cast`。
   - `static_cast`在编译时执行，不进行运行时检查，但它是类型安全的，因为它不会转换不兼容的类型。

2. **`dynamic_cast`**：
   - 当你需要进行多态的向下转型（将基类指针或引用转换为派生类指针或引用）时，使用`dynamic_cast`。
   - `dynamic_cast`在运行时执行，如果转换失败，对于指针会返回`nullptr`，对于引用会抛出`std::bad_cast`异常，因此它提供了类型安全。

3. **`const_cast`**：
   - 当你需要修改对象的`const`或`volatile`属性时，使用`const_cast`。
   - 虽然`const_cast`可以绕过`const`限制，但它不应用于改变对象的值类型，只用于改变对象的属性。

4. **`reinterpret_cast`**：
   - 当你需要进行低层次的重新解释转换，如将指针转换为整数，或者反过来，使用`reinterpret_cast`。
   - 这种转换非常不安全，因为它不检查转换的合理性，可能会导致未定义行为。

5. **C++11智能指针转换**：
   - 当你需要在智能指针之间进行转换时，使用`std::static_pointer_cast`、`std::dynamic_pointer_cast`、`std::const_pointer_cast`和`std::reinterpret_pointer_cast`。
   - 这些转换提供了与原始转换运算符相同的安全性，但适用于智能指针。

**为什么**：

- **安全性**：`dynamic_cast`在运行时检查类型兼容性，提供了最高的安全性。
- **明确性**：使用`static_cast`和智能指针转换可以明确你的意图，让代码更易于理解。
- **避免未定义行为**：避免使用`reinterpret_cast`进行不安全的转换，可以减少未定义行为的风险。

**最佳实践**：

- 尽可能使用`static_cast`进行基本的类型转换。
- 对于需要多态行为的转换，使用`dynamic_cast`。
- 仅在必要时使用`const_cast`，并且要确保这样做是安全的。
- 避免使用`reinterpret_cast`，除非你完全理解你在做什么。

记住，每种转换运算符都有其适用场景，选择正确的转换运算符可以提高代码的安全性和可读性。

## 6.dynamic_cast在多态类转换中是如何工作的?

在C++中，`dynamic_cast`是一种运行时类型识别（RTTI）机制，它在多态类转换中用于安全地将基类指针或引用转换为派生类指针或引用。`dynamic_cast`在执行转换时会检查转换的有效性，确保转换是安全的。

### 6.1.工作原理

1. **虚函数的存在**：
   - `dynamic_cast`要求基类至少有一个虚函数。这是因为虚函数的存在使得类具有多态性质，并且允许C++运行时系统维护一个类型信息表（通常称为vtable），用于在运行时确定对象的实际类型。

2. **运行时检查**：
   - 当使用`dynamic_cast`进行转换时，C++运行时系统会检查目标类型是否确实是源类型（基类指针或引用）的合法派生类型。
   - 如果转换是合法的，即目标类型确实是源类型的派生类，那么转换成功，返回指向派生类对象的指针或引用。
   - 如果转换不合法，即目标类型不是源类型的派生类，那么：
     - 如果是指针转换，返回`nullptr`。
     - 如果是引用转换，抛出`std::bad_cast`异常。

### 6.2.使用场景

`dynamic_cast`通常用于以下场景：

- **向下转型**：将基类指针或引用转换为派生类指针或引用。
- **交叉转换**：在继承体系中，将一个派生类的指针或引用转换为另一个派生类的指针或引用。

### 6.3.示例

假设有以下类结构：

```cpp
class Base {
public:
    virtual ~Base() {}  // 确保有虚析构函数
};

class Derived1 : public Base {};
class Derived2 : public Base {};
```

使用`dynamic_cast`进行转换：

```cpp
Base* b = new Derived1();
Derived1* d1 = dynamic_cast<Derived1*>(b);  // 转换成功，d1非nullptr
Derived2* d2 = dynamic_cast<Derived2*>(b);  // 转换失败，d2为nullptr
```

### 6.4.注意事项

- **性能**：`dynamic_cast`需要运行时检查，因此可能会影响性能。在性能敏感的应用中，应谨慎使用。
- **安全性**：虽然`dynamic_cast`提供了类型安全，但使用不当（如在没有虚函数的类上使用）会导致编译错误。
- **异常处理**：在使用引用形式的`dynamic_cast`时，应考虑异常处理机制，以避免程序因`std::bad_cast`异常而崩溃。

通过这种方式，`dynamic_cast`确保了类型转换的安全性，避免了因类型不匹配而导致的未定义行为。

## 7.在C++11中，如何使用explicit关键字来避免隐式类型转换？

在C++11中，`explicit`关键字用于构造函数，以防止编译器对单参数构造函数进行隐式类型转换。使用`explicit`可以增加代码的安全性，因为它阻止了编译器自动进行可能不期望的类型转换。

### 7.1.使用`explicit`关键字

要使用`explicit`关键字，只需在构造函数声明之前添加`explicit`关键字。这样，构造函数就不能再用于隐式转换了。

### 7.2.示例

假设你有一个类`SmallInt`，你希望避免它从`int`隐式转换：

```cpp
class SmallInt {
public:
    explicit SmallInt(int value) : value_(value) {}

    int getValue() const { return value_; }

private:
    int value_;
};
```

在这个例子中，`SmallInt`的构造函数使用了`explicit`关键字，因此以下隐式转换将不再被允许：

```cpp
SmallInt a = 5;        // 错误：不允许隐式转换
SmallInt b(5);         // 正确：显式转换
```

### 7.3.转换运算符与`explicit`

`explicit`关键字也可以用于转换运算符：

```cpp
class StringWrapper {
public:
    explicit operator std::string() const {
        return "Hello, World!";
    }
};
```

在这个例子中，`StringWrapper`类定义了一个转换运算符，该运算符被标记为`explicit`。这意味着以下隐式转换将不再被允许：

```cpp
StringWrapper sw;
std::string s = sw;    // 错误：不允许隐式转换
std::string s2 = static_cast<std::string>(sw); // 正确：显式转换
```

### 7.4.注意事项

- **单参数构造函数**：如果构造函数只有一个参数（除了`this`指针），并且没有默认参数，那么这个构造函数可能会被用于隐式转换。使用`explicit`可以防止这种情况。
- **转换运算符**：转换运算符也可以被隐式调用，使用`explicit`可以避免这种情况。
- **模板构造函数**：即使模板构造函数只有一个参数，`explicit`关键字也不能阻止隐式转换，因为模板的匹配可能会引入额外的参数。

使用`explicit`关键字是一种很好的实践，可以帮助你避免不期望的类型转换，从而提高代码的安全性和可读性。

## 8.在C++中，除了使用explicit关键字外，还有哪些方法可以防止隐式类型转换？

在C++中，除了使用`explicit`关键字来防止隐式类型转换外，还有其他几种方法可以控制或防止隐式转换：

1. **私有或受保护的构造函数**：
   - 将构造函数声明为私有或受保护的，可以阻止类的实例化，除非通过类内部的成员函数或友元函数。

2. **删除不需要的转换**：
   - 使用`delete`关键字可以显式地删除不需要的隐式转换。例如，如果你不希望类与`int`类型隐式转换，可以删除单参数构造函数。

   ```cpp
   class NonImplicit {
   public:
       explicit NonImplicit(int value) {}
   public:
       // 删除隐式转换为int的转换运算符
       operator int() = delete;
   };
   ```

3. **使用`constexpr`构造函数**：
   - 如果构造函数是`constexpr`，它不能用于隐式转换，因为`constexpr`要求在编译时求值。

   ```cpp
   class ConstexprOnly {
   public:
       constexpr ConstexprOnly(int value) : value_(value) {}
       int value_;
   };
   // ConstexprOnly co = 42; // 错误：constexpr构造函数不能用于隐式转换
   ```

4. **使用`struct`而不是`class`**：
   - 在C++中，`struct`默认继承是`public`的，而`class`默认继承是`private`的。如果你不希望一个类型能够被隐式转换，可以将其定义为`struct`，并且提供一个私有或受保护的构造函数。

5. **自定义转换运算符**：
   - 如果你想要控制转换行为，可以自定义转换运算符，并在其中添加逻辑来决定是否允许转换。

6. **使用`static_assert`**：
   - 在构造函数或类型转换运算符中使用`static_assert`来确保类型的使用符合你的预期。

   ```cpp
   template<typename T>
   class NonImplicit {
   public:
       explicit NonImplicit(T value) {}
   public:
       template<typename U>
       operator U() {
           static_assert(std::is_same<U, int>::value, "Conversion not allowed.");
           return 0;
       }
   };
   ```

7. **使用`enum`或`constexpr`变量**：
   - 定义一个`enum`或`constexpr`变量，使得转换需要显式地进行。

8. **使用C++11特性**：
   - 在C++11中，你可以使用`final`关键字来防止类的继承，从而间接防止了某些类型的隐式转换。

9. **使用模板**：
   - 通过模板可以创建一个只接受特定类型的类，从而避免隐式转换。

10. **使用`noexcept`**：
    - 在某些情况下，通过`noexcept`可以防止某些隐式转换，因为`noexcept`运算符在某些转换中是必需的。

选择哪种方法取决于你的具体需求和上下文。通常，`explicit`关键字是最简单和最直接的方法来防止单参数构造函数的隐式转换。其他方法可以用于更复杂的场景或特定的需求。

## 9.如果我想在类中同时使用explicit和noexcept关键字，应该怎么做？

在C++中，`explicit`关键字用于防止构造函数进行隐式类型转换，而`noexcept`关键字用于指定成员函数（包括构造函数、析构函数和赋值运算符）不会抛出异常。如果你想在同一个构造函数中同时使用`explicit`和`noexcept`，你可以这样做：

```cpp
class MyClass {
public:
    explicit MyClass(int value) noexcept : value_(value) {}
    // ...
private:
    int value_;
};
```

在这个例子中，构造函数`MyClass(int value)`被声明为`explicit`以防止隐式转换，并且被声明为`noexcept`以表明它不会抛出任何异常。

### 9.1.注意事项

1. **`explicit`关键字**：
   - `explicit`关键字只能用于单个参数的构造函数。如果构造函数有多个参数，即使它们都有默认值，也不能使用`explicit`。

2. **`noexcept`关键字**：
   - `noexcept`可以用于任何成员函数，包括构造函数、析构函数、赋值运算符和特殊成员函数（如移动构造函数和移动赋值运算符）。
   - 如果一个函数声明为`noexcept`，那么它必须保证不会抛出任何异常。如果函数调用了可能抛出异常的函数，那么`noexcept`的保证就被违反了。

3. **组合使用**：
   - 在某些情况下，将`explicit`和`noexcept`组合使用是有意义的。例如，你可能希望创建一个不会抛出异常且不允许隐式转换的构造函数。

4. **性能考虑**：
   - `noexcept`函数在某些编译器优化中可能会有更好的性能，因为编译器可以假设函数不会抛出异常，从而避免生成异常处理代码。

5. **异常安全性**：
   - 即使函数声明为`noexcept`，也应该确保代码的异常安全性。这意味着即使在异常发生的情况下，程序的状态也应该保持一致。

6. **兼容性**：
   - 在C++11及以后的版本中，`noexcept`是一个有效的声明，而在C++11之前的版本中，你应该使用`throw()`来指定函数不会抛出异常。

通过这种方式，你可以在类中同时使用`explicit`和`noexcept`关键字，以实现更安全、更高效的类型转换和异常处理。

## 10.能否给我一个使用explicit关键字的多参数构造函数的例子？

在C++中，`explicit`关键字只能用于单参数构造函数，以防止隐式类型转换。对于多参数构造函数，`explicit`关键字是不允许的。

### 10.1.为什么多参数构造函数不能使用`explicit`？

`explicit`关键字的目的是防止编译器对单参数构造函数进行隐式转换。当构造函数只有一个参数时，编译器可能会自动使用这个构造函数来创建对象，这可能会导致不期望的隐式类型转换。例如：

```cpp
class SmallInt {
public:
    explicit SmallInt(int value) : value_(value) {}
    // ...
private:
    int value_;
};

SmallInt si = 10; // 错误：因为构造函数是explicit的
```

### 10.2.多参数构造函数

对于多参数构造函数，由于参数的数量和类型，编译器通常不会进行隐式转换。因此，`explicit`关键字是多余的，也是不允许的。例如：

```cpp
class Point {
public:
    Point(int x, int y) : x_(x), y_(y) {}
    // ...
private:
    int x_, y_;
};

Point p1(10, 20); // 正确：显式调用
```

在这个例子中，由于`Point`构造函数需要两个参数，编译器不会尝试进行隐式转换。

### 10.3.示例

如果你想要一个类似`explicit`的效果，你可以使用`static_cast`来显式地进行转换：

```cpp
class Point {
public:
    Point(int x, int y) : x_(x), y_(y) {}

    static Point fromPolar(double radius, double angle) {
        int x = static_cast<int>(radius * cos(angle));
        int y = static_cast<int>(radius * sin(angle));
        return Point(x, y);
    }
    // ...
private:
    int x_, y_;
};

int main() {
    Point p1 = Point::fromPolar(10, M_PI / 4); // 需要显式调用
    return 0;
}
```

在这个例子中，`fromPolar`是一个静态成员函数，它接受极坐标参数并返回一个`Point`对象。由于它需要两个参数，编译器不会进行隐式转换，因此不需要`explicit`关键字。

### 10.4.结论

- `explicit`关键字只能用于单参数构造函数。
- 对于多参数构造函数，由于参数的数量和类型，编译器通常不会进行隐式转换，因此不需要`explicit`关键字。
- 如果你需要显式转换，可以使用`static_cast`或其他方法来实现。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
