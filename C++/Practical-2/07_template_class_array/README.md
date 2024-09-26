# C++ Practical-2 day7 类模板特化之数组

[TOC]

## Overview

- C++不练习coding，就相当于空中楼阁，基础不扎实
- 光吃不干，等于没吃

---

## 1.类模板特化之数组

在C++中，类模板特化是为特定类型提供一个定制版本的模板类的过程。这在你需要对特定类型进行优化或者添加特定行为时非常有用。

假设我们有一个通用的数组类模板，我们想要为`int`类型提供一个特化版本，以添加一些特定于整数的操作，比如计算数组中所有元素的总和。

### 1.1.通用数组类模板

首先，我们定义一个通用的数组类模板：

```cpp
template <typename T>
class Array {
private:
    T* data;
    size_t size;

public:
    // 构造函数
    Array(size_t size) : size(size), data(new T[size]) {}

    // 析构函数
    ~Array() {
        delete[] data;
    }

    // 获取元素
    T& operator[](size_t index) {
        return data[index];
    }

    // 获取元素（const版本）
    const T& operator[](size_t index) const {
        return data[index];
    }

    // 获取数组大小
    size_t getSize() const {
        return size;
    }

    // 其他通用操作...
};
```

### 1.2.类模板特化

接下来，我们为`int`类型特化这个数组类模板：

```cpp
// 特化版本
template <>
class Array<int> {
private:
    int* data;
    size_t size;

public:
    // 构造函数
    Array(size_t size) : size(size), data(new int[size]) {}

    // 析构函数
    ~Array() {
        delete[] data;
    }

    // 获取元素
    int& operator[](size_t index) {
        return data[index];
    }

    // 获取元素（const版本）
    const int& operator[](size_t index) const {
        return data[index];
    }

    // 获取数组大小
    size_t getSize() const {
        return size;
    }

    // 特化操作：计算数组中所有元素的总和
    int sum() const {
        int total = 0;
        for (size_t i = 0; i < size; ++i) {
            total += data[i];
        }
        return total;
    }
};
```

在这个特化版本中，我们添加了一个`sum`成员函数，它遍历数组中的所有整数元素并计算它们的总和。

### 1.3.使用特化数组类

下面是如何使用这个特化的数组类：

```cpp
int main() {
    // 使用特化版本
    Array<int> intArray(5);
    for (size_t i = 0; i < intArray.getSize(); ++i) {
        intArray[i] = static_cast<int>(i);
    }

    std::cout << "Sum of elements: " << intArray.sum() << std::endl;

    // 使用通用版本
    Array<double> doubleArray(5);
    for (size_t i = 0; i < doubleArray.getSize(); ++i) {
        doubleArray[i] = static_cast<double>(i) * 1.5;
    }

    // doubleArray没有sum函数
    // std::cout << "Sum of elements: " << doubleArray.sum() << std::endl; // 这将导致编译错误

    return 0;
}
```

在这个例子中，`intArray`使用了特化的`Array<int>`类，因此它有`sum`函数。而`doubleArray`使用的是通用的`Array<double>`类，它没有`sum`函数。

### 1.4.注意事项

- 类模板特化应该在模板定义之后进行，以确保编译器能够识别特化版本。
- 特化版本和通用版本应该有相同的接口，以保持一致性。
- 特化可以针对不同的类型参数，甚至是模板参数的特定组合进行。

通过类模板特化，你可以为特定类型提供定制的行为，从而提高代码的灵活性和性能。

## 2.类模板特化在实际项目中有哪些常见的应用场景？

类模板特化在实际项目中的应用场景非常广泛，它允许开发者为特定类型或特定情况提供定制化的行为。以下是一些常见的应用场景：

1. **性能优化**：
   - 针对特定数据类型进行优化，比如为`int`或`double`类型提供专门的内存管理策略或算法实现。

2. **类型安全**：
   - 为特定的类型提供类型安全的接口，例如，为`std::string`和`char*`提供不同的处理方式。

3. **添加特定操作**：
   - 为特定类型添加额外的操作或成员函数，比如为`int`数组添加求和、求平均值等操作。

4. **处理特殊类型**：
   - 对于特殊的类型，如`void`指针或函数指针，提供特殊的处理方式。

5. **简化接口**：
   - 为常用的类型提供简化的接口，比如为`std::vector`或`std::list`提供定制的迭代器。

6. **兼容性处理**：
   - 为不同的编译器或平台提供不同的实现，以确保代码的兼容性。

7. **实现策略模式**：
   - 在模板类中使用特化来实现策略模式，根据不同的策略类型提供不同的行为。

8. **处理遗留代码**：
   - 为遗留代码中的特定类型提供特化，以便在不修改原有代码的基础上进行扩展。

9. **实现多态**：
   - 为基类和派生类提供不同的实现，利用特化实现多态性。

10. **实现模板元编程**：
    - 在模板元编程中，特化用于实现复杂的编译时计算和决策。

11. **错误处理**：
    - 为特定类型提供错误处理机制，比如为数值类型和字符串类型提供不同的异常处理策略。

12. **资源管理**：
    - 为资源密集型类型（如文件句柄、网络连接）提供定制的资源管理策略。

13. **算法实现**：
    - 为特定类型提供定制的算法实现，比如为`float`和`double`提供不同的数值处理算法。

14. **国际化和本地化**：
    - 为不同的语言和地区提供定制化的字符串处理和格式化。

15. **图形和游戏开发**：
    - 为图形库中的特定类型（如颜色、顶点）提供特化，以优化渲染性能。

16. **数据库访问**：
    - 为不同类型的数据库字段（如整数、字符串、日期）提供定制化的访问和处理方式。

17. **网络通信**：
    - 为不同的数据类型（如TCP连接、UDP数据包）提供定制化的网络通信协议处理。

通过类模板特化，开发者可以充分利用C++的类型系统和模板机制，为不同的应用场景提供灵活和高效的解决方案。

## 3.如何为类模板特化添加多态性？

在C++中，为类模板特化添加多态性主要涉及到使用虚函数和基类指针。多态性允许你通过基类指针或引用来调用派生类的方法，这在模板特化中同样适用。

### 3.1.步骤1: 定义基类模板

首先，定义一个包含虚函数的基类模板，这个基类模板将被用于后续的特化。

```cpp
template <typename T>
class Base {
public:
    virtual void display() const = 0;  // 纯虚函数
    virtual ~Base() {}  // 虚析构函数以确保派生类对象的正确清理
};
```

### 3.2.步骤2: 定义派生类模板

定义一个派生类模板，继承自基类模板，并实现基类中的虚函数。

```cpp
template <typename T>
class Derived : public Base<T> {
public:
    void display() const override {
        std::cout << "Displaying Derived class with type: " << typeid(T).name() << std::endl;
    }
};
```

### 3.3.步骤3: 特化基类模板

为特定类型特化基类模板。在这个特化版本中，你可以添加特定于该类型的功能。

```cpp
// 特化基类模板
template <>
class Base<int> {
public:
    virtual void display() const = 0;
    virtual ~Base() {}
};

// 特化派生类模板
class IntSpecificClass : public Base<int> {
public:
    void display() const override {
        std::cout << "Int specific display" << std::endl;
    }
};
```

### 3.4.步骤4: 使用多态

创建基类指针，指向派生类对象，并通过基类指针调用虚函数来展示多态性。

```cpp
int main() {
    Base<int>* b = new IntSpecificClass();
    b->display();  // 输出 "Int specific display"
    delete b;

    Base<double>* d = new Derived<double>();
    d->display();  // 输出 "Displaying Derived class with type: double"
    delete d;

    return 0;
}
```

### 3.5.说明

1. **基类模板**定义了一个接口，包含一个纯虚函数`display`，这使得它成为一个抽象类。
2. **派生类模板**实现了基类模板的接口。
3. **特化基类模板**为特定类型（如`int`）提供了定制的实现。
4. **特化派生类**实现了特化基类的接口。
5. **多态性**通过基类指针调用虚函数实现，允许在运行时确定调用哪个函数版本。

### 3.6.注意事项

- **虚析构函数**：确保在删除基类指针时正确调用派生类的析构函数。
- **类型安全**：特化时需要确保类型匹配正确，避免类型错误。
- **内存管理**：使用动态分配时，确保适当地释放内存。

通过这种方式，你可以在模板类中实现多态性，使得代码更加灵活和可扩展。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
