# C++面试基础系列-sizeof

[TOC]

## Overview

- sizeof，可用于分析数据结构的内存分配，字节对齐
  - 类
  - 结构体
  - 基础类型int，char等
  - 数组
  - 模板
- sizeof与类，
  - 空类的大小为1字节
  - 虚函数本身、成员函数（包括静态与非静态）和静态数据成员都是不占用类对象的存储空间
  - 对于包含虚函数的类，不管有多少个虚函数，只有一个虚指针,vptr的大小
  - 普通继承，派生类继承了所有基类的函数与成员，要按照字节对齐来计算大小
  - 虚函数继承，不管是单继承还是多继承，都是继承了基类的vptr。(32位操作系统4字节，64位操作系统 8字节)！
  - 虚继承,继承基类的vptr。

## 1.sizeof基本用法

在 C++ 中，`sizeof` 运算符用于确定变量或类型在内存中的大小，以字节为单位。`sizeof` 是编译时运算符，它的**值在编译时就已经确定，并被用作一个常量表达式。**

以下是 `sizeof` 的一些用法示例：

### 1.1.基本类型

```cpp
int i = 10;
std::cout << sizeof(i);  // 输出 'i' 的大小，通常是 4 字节（取决于平台）
```

### 1.2.指针类型

```cpp
int *p = &i;
std::cout << sizeof(p);  // 输出指针 'p' 的大小，通常是 sizeof(void*)（取决于平台）
```

### 1.3.数组类型

```cpp
int arr[10];
std::cout << sizeof(arr);  // 输出整个数组 'arr' 的大小，10 * sizeof(int)
```

### 1.1.结构体和类

```cpp
struct MyStruct {
    int a;
    char b;
    double c;
};

std::cout << sizeof(MyStruct);  // 输出 'MyStruct' 的总大小 4 + 1 + （3）+8 =16
```

### 1.4.引用类型

```cpp
int &ref = i;
std::cout << sizeof(ref);  // 输出引用 'ref' 的大小，通常等于 int 的大小
```

### 1.5.动态内存分配

```cpp
int *dynamicArray = new int[10];
std::cout << sizeof(dynamicArray);  // 输出指针的大小，不是数组的大小
delete[] dynamicArray;  // 记得释放内存
```

### 1.6.sizeof... (C++11 可变参数模板)

C++11 引入了 `sizeof...` 运算符，用于在模板中获取参数包中的参数数量。

```cpp
template<typename... Args>
std::size_t countArgs() {
    return sizeof...(Args);
}
```

### 1.7.注意事项

- `sizeof` 一个类型或变量是编译时计算的，不占用运行时间。
- `sizeof` 一个指针总是返回相同大小，因为指针的大小与它指向的对象的大小无关。
- `sizeof` 一个数组返回的是整个数组的大小，不是数组指针的大小。
- `sizeof` 可以用于静态数组，但对于动态数组，它返回的是指针的大小，而不是分配的内存块的大小。
- `sizeof` 可以用于基本数据类型、指针、数组、结构体、类、枚举和引用。

`sizeof` 是 C++ 中一个非常有用的工具，可以帮助你了解不同类型和变量在内存中占用的空间大小。

在 C++ 中，`sizeof` 运算符可以用来确定类型或对象在内存中的大小，这有助于优化内存分配。以下是一些使用 `sizeof` 来优化内存分配的方法：

## 2.在 C++ 中，如何使用 sizeof 运算符来优化内存分配？

在 C++ 中，`sizeof` 运算符可以用来优化内存分配，主要通过确保为对象分配的内存既足够又不过度。以下是一些具体的策略：

在 C++ 中，可以使用 `sizeof` 运算符来优化内存分配，以下是一些方法：

### 2.1.确定数组大小

1. 静态数组：在定义静态数组时，可以使用 `sizeof` 来确保数组的大小与特定类型的对象相匹配，避免浪费内存或出现缓冲区溢出。例如：

   ```cpp
   int arr[sizeof(int) * 10]; // 创建一个足够容纳 10 个整数的数组
   ```

   这样可以确保数组的大小是根据整数的实际大小计算出来的，而不是使用一个固定的数字，提高了代码的可维护性和灵活性。

2. 动态分配数组：在使用 `new` 运算符动态分配数组时，可以结合 `sizeof` 来确定数组的大小。例如：

   ```cpp
   int* dynamicArray = new int[sizeof(int) * n]; // n 是一个变量，表示所需的整数数量
   ```

   这种方法可以根据实际需求动态地分配内存，避免分配过多或过少的内存。

### 2.2.结构体和类的内存布局

1. 了解内存占用：通过 `sizeof` 运算符可以了解结构体或类对象在内存中的占用大小。这对于优化内存布局和避免不必要的内存浪费非常有用。例如：

   ```cpp
   struct MyStruct {
       int a;
       double b;
       char c;
   };
   std::cout << "Size of MyStruct: " << sizeof(MyStruct) << std::endl;
   ```

   通过查看结构体的大小，可以确定其中各个成员变量的排列方式以及可能存在的内存对齐问题。如果发现结构体的大小超出了预期，可以考虑重新排列成员变量的顺序或者使用位域等技术来优化内存布局。

2. 内存对齐考虑：`sizeof` 运算符返回的值可能会受到内存对齐的影响。在某些平台上，编译器会对结构体和类的成员变量进行内存对齐，以提高访问效率。了解内存对齐规则可以帮助你更好地利用内存，并避免因对齐问题导致的内存浪费。例如：

   ```cpp
   struct MyAlignedStruct {
       char a;
       int b;
       short c;
   };
   std::cout << "Size of MyAlignedStruct: " << sizeof(MyAlignedStruct) << std::endl;
   ```

   在这个例子中，由于内存对齐的原因，结构体的大小可能会大于各个成员变量大小之和。可以通过调整成员变量的顺序或者使用特定的编译指令来控制内存对齐，以达到优化内存分配的目的。

### 2.3.模板参数推导

1. 容器类模板：在编写容器类模板时，可以使用 `sizeof` 运算符来推导模板参数的大小，从而实现更灵活的内存分配策略。例如：

   ```cpp
   template<typename T>
   class MyContainer {
   public:
       MyContainer(size_t size) : data(new T[size * sizeof(T)]) {}
       ~MyContainer() { delete[] data; }
   private:
       T* data;
   };
   ```

   在这个容器类模板中，构造函数根据传入的大小参数和 `sizeof(T)` 来动态分配内存，确保容器能够容纳正确数量的对象。这种方法可以适应不同类型的对象，提高了代码的通用性。

2. 函数模板参数推导：在函数模板中，也可以使用 `sizeof` 来推导参数的大小，从而实现更高效的内存操作。例如：

   ```cpp
   template<typename T>
   void copyArray(T* destination, T* source, size_t size) {
       for (size_t i = 0; i < size; ++i) {
           new (destination + i) T(source[i]);
       }
   }
   ```

   在这个函数模板中，通过 `sizeof(T)` 可以确定每个元素的大小，从而正确地进行内存复制操作。这种方法可以适用于不同类型的数组，提高了代码的复用性。

### 2.4.避免内存泄漏和重复分配

1. 动态内存管理：在使用动态内存分配时，要注意避免内存泄漏和重复分配。可以使用智能指针（如 `std::unique_ptr` 和 `std::shared_ptr`）来自动管理内存，或者在手动管理内存时，确保在合适的时机释放内存。例如：

   ```cpp
   void processData() {
       int* data = new int[sizeof(int) * 10];
       // 使用数据
       delete[] data;
   }
   ```

   在这个例子中，手动分配了一块内存，然后在使用完后及时释放。如果忘记释放内存，就会导致内存泄漏。可以考虑使用智能指针来自动管理内存，避免这种错误。

2. 避免重复分配：在一些情况下，可能会多次分配和释放内存，这会导致性能下降。可以通过合理的设计和使用 `sizeof` 来避免重复分配内存。例如：

   ```cpp
   class MyDataProcessor {
   public:
       MyDataProcessor(size_t size) : data(new int[size * sizeof(int)]) {}
       ~MyDataProcessor() { delete[] data; }
       void processData() {
           // 使用数据
       }
   private:
       int* data;
   };
   ```

   在这个例子中，在类的构造函数中一次性分配了足够的内存，然后在整个对象的生命周期内使用。避免了在每次处理数据时都进行内存分配和释放，提高了性能。

总之，在 C++ 中，`sizeof` 运算符是一个非常有用的工具，可以帮助你优化内存分配，提高程序的性能和可维护性。但是，要注意正确使用 `sizeof`，并结合其他内存管理技术，以确保程序的正确性和稳定性。

## 3.sizeof详细用例

在 C++ 中，`sizeof` 运算符提供了类型或对象所占内存的大小（以字节为单位），这可以在多种情况下帮助优化内存分配：

### 3.1.动态数组分配

   使用 `sizeof` 确定数组元素类型的大小，然后根据需要的元素数量动态分配数组。

   ```cpp
   int n = 10;
   int* arr = new int[n];
   // 使用 arr
   delete[] arr;
   ```

### 3.2.避免过度分配

   对于结构体或类，使用 `sizeof` 来确保为实例分配的内存正好满足需求。

   ```cpp
   struct MyStruct {
       int a;
       char b;
   };
   
   size_t size = sizeof(MyStruct);
   MyStruct* s = static_cast<MyStruct*>(operator new(size));
   // 使用 s
   operator delete(s);
   ```

### 3.3.使用 `sizeof` 与 `new` 表达式

   在分配未知大小的对象时，可以使用 `sizeof` 来确保分配正确的大小。

   ```cpp
   char* data = new char[sizeof(MyStruct)];
   // 使用 data 作为 MyStruct 类型的内存
   MyStruct* s = reinterpret_cast<MyStruct*>(data);
   // 使用 s
   delete[] data;
   ```

### 3.4.动态内存分配的类型安全封装

   创建模板函数或类来封装内存分配逻辑，使用 `sizeof` 确保类型安全。

   ```cpp
   template<typename T>
   T* allocateArray(size_t count) {
       return new T[count];
   }

   int* intArray = allocateArray<int>(100);
   // 使用 intArray
   delete[] intArray;
   ```

### 3.5.优化容器类

   如果你实现了自定义容器类，使用 `sizeof` 来确定存储元素所需的内存，可以避免使用额外的内存分配器。

   ```cpp
   template<typename T, size_t N>
   class Stack {
   private:
       T buffer[N];
       // ...
   };
   ```

### 3.6.内存对齐

   使用 `sizeof` 来确保对象按照特定的对齐要求分配内存，这有助于提高访问效率。

   ```cpp
   struct AlignedStruct {
       char a;
       double b;
   };

   size_t alignment = alignof(AlignedStruct);
   size_t size = sizeof(AlignedStruct);
   void* memory = operator new(size);
   AlignedStruct* alignedStruct = reinterpret_cast<AlignedStruct*>(
       reinterpret_cast<std::uintptr_t>(memory) + alignment -
       reinterpret_cast<std::uintptr_t>(memory) % alignment
   );
   // 使用 alignedStruct
   operator delete(memory);
   ```

### 3.7.避免内存泄漏

   使用 `sizeof` 来跟踪分配的内存大小，确保正确释放内存。

### 3.8.利用编译时常量

   由于 `sizeof` 是编译时常量，可以在编译时计算所需内存大小，从而避免运行时计算的开销。

### 3.9.使用 `std::size`

   对于标准库容器，使用 `std::size` 成员函数来获取容器中元素的数量，然后结合 `sizeof` 来分配所需内存。

   ```cpp
   std::vector<int> vec;
   // ...
   size_t numElements = vec.size();
   int* array = new int[numElements];
   // 使用 array
   delete[] array;
   ```

### 3.10.C++11 标准库特性

利用 C++11 的 `std::array` 或 `std::unique_ptr` 等特性，它们内部使用 `sizeof` 来管理内存，提供自动内存管理。

通过这些方法，`sizeof` 运算符可以帮助你更精确地控制内存的使用，从而提高程序的性能和效率。然而，也要注意，过度优化可能会导致代码复杂性增加，因此应当在真正需要优化的地方使用这些技术。


在 C++ 中，`sizeof` 运算符提供了一种在编译时获取类型或对象所占内存大小的方式。当涉及到类时，`sizeof` 的行为可以更加复杂，因为类可能包含成员变量、继承、内存对齐要求等。以下是一些更详细的点，解释了 `sizeof` 与类在 C++ 中的使用：

## 4.sizeof与类

### 4.1.成员变量和类大小

类的大小由其所有非静态成员变量的大小决定。继承的成员也会被计算在内。

```cpp
class MyClass {
    int a; // 4 字节（大多数系统上）
    char b; // 1 字节
    double c; // 8 字节
};

std::cout << "Size of MyClass: " << sizeof(MyClass) << " bytes";
// 输出通常是 13 字节，但可能会因为内存对齐而更大，比如16字节。
```

### 4.2.内存对齐

编译器可能会在类成员之间或类末尾添加填充（padding），以确保数据按照特定的对齐边界存储。这可能会增加类的总大小。

```cpp
class AlignExample {
    char a;
    double b; // 可能需要 8 字节对齐
};

std::cout << "Size of AlignExample: " << sizeof(AlignExample);
// 输出可能大于 9 字节，因为可能会在 'a' 和 'b' 之间添加填充。
```

### 4.3.继承和大小

派生类的 `sizeof` 包括了所有基类的成员，以及它自己的成员。

```cpp
class Base {
    int x;
};

class Derived : public Base {
    double y;
};

std::cout << "Size of Derived: " << sizeof(Derived);
// 输出将包括 Base 中的 'x' 和 Derived 中的 'y' 的大小。
```

### 4.4.静态成员和大小

静态成员不属于任何类实例，因此它们不计入 `sizeof` 类的结果。

```cpp
class MyClass {
public:
    static int staticVar;
};

std::cout << "Size of MyClass with static member: " << sizeof(MyClass);
// 输出通常为 1，因为静态成员不计入大小。
```

### 4.5.空类和大小

空类的大小通常至少为 1 字节，以确保在内存中可以区分不同的实例。

```cpp
class Empty {};

std::cout << "Size of Empty class: " << sizeof(Empty);
// 输出通常为 1。
```

### 4.6.位域

位域是一种特殊的成员，它占用一个固定数量的位，但不一定增加类的大小。

```cpp
class BitFields {
    char a : 1; // 占用 1 位
    int b : 7; // 占用 7 位，可能占用额外的存储单元
};

std::cout << "Size of BitFields: " << sizeof(BitFields);
// 输出可能小于 5 字节，因为位域可能共享存储单元。
```

### 4.7.模板类和大小

模板类的大小取决于实例化时使用的类型。

```cpp
template <typename T>
class TemplateClass {
    T value;
};

std::cout << "Size of TemplateClass<int>: " << sizeof(TemplateClass<int>);
// 输出将取决于 'int' 的大小。
```

### 4.8.匿名类和大小

匿名类的大小由其成员决定，但它们通常用于定义不命名的类型。

```cpp
int main() {
    auto lambda = []() {};
    std::cout << "Size of anonymous lambda: " << sizeof(lambda);
    // 输出取决于捕获的变量和编译器实现。
}
```

### 4.9.`sizeof` 与指针

`sizeof` 一个类的指针总是等于指针的大小，而不是类实例的大小。

```cpp
MyClass* ptr = nullptr;
std::cout << "Size of pointer to MyClass: " << sizeof(ptr);
// 输出是指针的大小，通常为 4 或 8 字节。
```

理解 `sizeof` 在类中的应用可以帮助你更好地管理内存和优化性能。然而，依赖于 `sizeof` 进行编程应该谨慎，因为内存布局可能因编译器和平台而异。

在 C++中，`sizeof`运算符在涉及类时有以下一些重要特点和用途：

### 4.10.继承与多态对`sizeof`的影响

1. 单继承：
   - 当一个类从另一个类继承时，派生类对象的大小包括基类部分的大小和派生类自身成员变量的大小。
   - 例如：
  
     ```cpp
     class Base {
     public:
         int baseData;
     };
     class Derived : public Base {
     public:
         char derivedData;
     };
     ```

   - `sizeof(Derived)`的结果将大于等于`sizeof(Base)+sizeof(char)`，具体大小取决于内存对齐要求。

2. 多继承：
   - 在多继承的情况下，派生类对象的大小是各个基类部分大小之和，再加上派生类自身成员变量的大小以及可能的内存对齐所需的额外空间。
   - 例如：
  
     ```cpp
     class Base1 {
     public:
         int data1;
     };
     class Base2 {
     public:
         double data2;
     };
     class DerivedMulti : public Base1, public Base2 {
     public:
         char data3;
     };
     ```

   - `sizeof(DerivedMulti)`的结果将取决于`Base1`、`Base2`和`DerivedMulti`各自的大小以及内存对齐要求。

3. 虚函数与虚继承：
   - 如果一个类包含虚函数，编译器通常会为该类对象添加一个指向虚函数表的指针，这会增加类对象的大小。
   - 例如：
  
     ```cpp
     class WithVirtual {
     public:
         virtual void doVirtual() {}
         int normalData;
     };
     ```

   - `sizeof(WithVirtual)`将大于`sizeof(int)`，因为需要额外的空间来存储虚函数表指针。
   - 如果一个类使用虚继承，也会增加类对象的大小，以存储额外的信息来解决多继承中的二义性问题。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
