# C++11 20-扩展的 `sizeof` Extended sizeof

- [C++11 20-扩展的 `sizeof` Extended sizeof](#c11-20-扩展的-sizeof-extended-sizeof)
  - [Overview](#overview)
  - [1.扩展的 `sizeof` Extended sizeof](#1扩展的-sizeof-extended-sizeof)
  - [2.C++11 中的 `sizeof` 运算符在实际编程中有哪些常见的应用场景？](#2c11-中的-sizeof-运算符在实际编程中有哪些常见的应用场景)
  - [3.在 C++11 中，除了 `sizeof` 运算符，还有哪些其他方式可以获取类型的大小信息？](#3在-c11-中除了-sizeof-运算符还有哪些其他方式可以获取类型的大小信息)
  - [4.如何使用~sizeof运算符来优化C++程序的性能？](#4如何使用sizeof运算符来优化c程序的性能)
  - [5.在使用sizeof运算符时，有哪些常见的错误或陷阱需要避免？](#5在使用sizeof运算符时有哪些常见的错误或陷阱需要避免)
  - [关于作者](#关于作者)

## Overview

---

## 1.扩展的 `sizeof` Extended sizeof

在 C++11 之前，`sizeof` 运算符主要用于获取变量或类型在内存中所占的字节数。C++11 扩展了 `sizeof` 的用法，允许在编译时对表达式进行操作，增加了它的灵活性和表达能力。以下是 C++11 扩展的 `sizeof` 用法：

1. **对表达式使用 `sizeof`**：
   C++11 允许你在 `sizeof` 中使用表达式，而不仅仅是类型或变量。编译器会计算该表达式的返回类型所占用的字节数。

   ```cpp
   int a[10];
   std::cout << sizeof(a) / sizeof(*a); // 输出数组的元素个数：10
   ```

2. **对函数返回类型使用 `sizeof`**：
   可以对函数的返回类型使用 `sizeof`，编译器会计算返回值类型所占用的字节数。

   ```cpp
   int foo() {
       return 42;
   }
   std::cout << sizeof(foo()); // 输出函数返回类型的大小：4
   ```

3. **对成员函数使用 `sizeof`**：
   可以对类的成员函数使用 `sizeof`，编译器会计算成员函数指针的大小。

   ```cpp
   struct S {
       void bar();
   };
   std::cout << sizeof(&S::bar); // 输出成员函数指针的大小
   ```

4. **对成员变量使用 `sizeof`**：
   可以对类的成员变量使用 `sizeof`，编译器会计算成员变量的大小。

   ```cpp
   struct S {
       int a;
   };
   std::cout << sizeof(S::a); // 输出成员变量的大小：4
   ```

5. **对模板实例使用 `sizeof`**：
   可以对模板实例使用 `sizeof`，编译器会计算模板实例类型所占用的字节数。

   ```cpp
   template <typename T>
   struct Wrapper {
       T value;
   };
   std::cout << sizeof(Wrapper<int>); // 输出模板实例类型的大小
   ```

6. **对类型别名使用 `sizeof`**：
   可以对类型别名使用 `sizeof`，编译器会计算别名所指向类型的大小。

   ```cpp
   typedef int MyInt;
   std::cout << sizeof(MyInt); // 输出类型别名的大小：4
   ```

7. **对 decltype 使用 `sizeof`**：
   `decltype` 关键字用于推断表达式的类型，可以与 `sizeof` 结合使用。

   ```cpp
   int x = 10;
   std::cout << sizeof(decltype(x)(2 * x)); // 输出表达式的返回类型的大小：4
   ```

8. **对条件表达式使用 `sizeof`**：
   可以对条件表达式使用 `sizeof`，编译器会计算条件表达式结果的类型所占用的字节数。

   ```cpp
   int a = 4;
   std::cout << sizeof(a ? 1.0 : "Hello"); // 输出条件表达式结果类型的大小：8
   ```

C++11 扩展的 `sizeof` 提供了更多的灵活性，允许开发者在编译时获取更多类型信息，从而编写更高效和灵活的代码。

## 2.C++11 中的 `sizeof` 运算符在实际编程中有哪些常见的应用场景？

在 C++11 中，`sizeof` 运算符可以帮助开发者在编译时获取类型的内存布局信息。以下是一些常见的应用场景：

1. **数组大小计算**：
   确定数组中元素的数量，这在处理固定大小的数组时非常有用。

   ```cpp
   int array[10];
   size_t num_elements = sizeof(array) / sizeof(array[0]);
   ```

2. **内存分配**：
   在动态内存分配时，计算需要分配的字节数。

   ```cpp
   int* ptr = new int[sizeof(int) * 10];
   ```

3. **类型安全性检查**：
   确保类型的大小符合预期，这在处理底层数据结构或硬件接口时尤为重要。

   ```cpp
   static_assert(sizeof(int) == 4, "Expected int to be 4 bytes");
   ```

4. **数据对齐**：
   确保数据符合特定的对齐要求，这可以提升性能。

   ```cpp
   struct alignas(16) MyStruct {
       double a, b, c, d;
   };
   ```

5. **泛型编程**：
   在模板元编程中，使用 `sizeof` 来确定模板参数的类型大小。

   ```cpp
   template <typename T>
   void function() {
       std::cout << "Size of T: " << sizeof(T) << std::endl;
   }
   ```

6. **编译时决策**：
   使用 `sizeof` 结合 `if constexpr` 或 `static_assert` 进行编译时的决策。

   ```cpp
   template <typename T>
   void process() {
       if constexpr (sizeof(T) == 1) {
           // Handle single-byte types
       } else {
           // Handle other types
       }
   }
   ```

7. **避免缓冲区溢出**：
   确保不会写入超过变量分配大小的数据。

   ```cpp
   void safeMemcpy(void* dest, const void* src, size_t count) {
       size_t dest_size = sizeof(*static_cast<decltype(*dest)*>(dest));
       size_t src_size = sizeof(*static_cast<const decltype(*src)*>(src));
       std::copy(src, src + std::min(count, dest_size, src_size), dest);
   }
   ```

8. **实现容器类**：
   在自定义容器类中，使用 `sizeof` 来计算存储元素所需的空间。

   ```cpp
   template <typename T, size_t N>
   class Array {
       T data[N];
   public:
       T* begin() { return data; }
       T* end() { return data + N; }
       size_t size() { return sizeof(data) / sizeof(T); }
   };
   ```

9. **优化数据结构**：
   根据类型大小优化数据结构，比如选择适当的数据类型以减少内存占用。

10. **网络通信**：
    在网络编程中，确定发送和接收缓冲区的大小。

11. **资源打包**：
    在需要将多个数据项打包到一个单一的内存块时，计算总大小。

12. **内存对齐和填充**：
    分析结构体的内存布局，确定是否有填充（padding）存在。

使用 `sizeof` 可以帮助开发者编写更高效、更安全的代码，尤其是在性能敏感或资源受限的应用中。

## 3.在 C++11 中，除了 `sizeof` 运算符，还有哪些其他方式可以获取类型的大小信息？

在 C++11 中，除了使用 `sizeof` 运算符，你还可以使用以下方法获取类型的尺寸信息：

1. **type traits**：
   C++11 引入了类型特征（type traits）机制，它是一种模板编程技术，可以用来查询和操作类型信息。`std::integral_constant` 是一个用于类型特征的模板类。

   ```cpp
   #include <type_traits>

   std::integral_constant<size_t, sizeof(int)>::value  // 获取 int 的大小
   ```

   更常见的是使用 `std::is_same` 来获取类型尺寸：

   ```cpp
   std::is_same<int, int>::value  // true
   ```

2. **decltype 关键字**：
   使用 `decltype` 关键字结合 `sizeof` 来获取某个表达式的类型大小。

   ```cpp
   int value = 5;
   decltype(value) var;
   std::cout << sizeof(var);  // 输出变量 var 的大小
   ```

3. **模板特化**：
   通过模板特化，可以为不同的类型提供不同的实现，从而获取类型的尺寸信息。

   ```cpp
   template <typename T>
   struct SizeOf;

   template <>
   struct SizeOf<int> {
       static const size_t value = sizeof(int);
   };

   SizeOf<int>::value  // 获取 int 的大小
   ```

4. **编译器特定扩展**：
   某些编译器提供了它们自己的扩展来获取类型的尺寸信息。

   ```cpp
   __alignof(int)  // 获取 int 的对齐要求（一些编译器支持）
   ```

5. **C++11标准库函数**：
   使用 `std::numeric_limits` 可以获取某些类型相关的信息，尽管它不直接提供类型大小，但提供了其他有用的信息。

   ```cpp
   std::numeric_limits<int>::digits  // 获取 int 类型的位数
   ```

6. **CTAD（类模板参数推导）**：
   C++17 引入了类模板参数推导（CTAD），它允许编译器自动推导模板类型参数。虽然这不是用来获取类型大小的，但它是 C++11 之后的一个特性，可以与类型特征结合使用。

7. **编译器文档**：
   查阅特定编译器的文档，了解是否有特定的机制或扩展来获取类型的尺寸信息。

需要注意的是，`sizeof` 运算符是唯一可以在编译时获取类型大小的方式，而类型特征和模板特化通常用于更复杂的查询和操作。在大多数情况下，`sizeof` 运算符是获取类型大小信息的首选方法。

## 4.如何使用~sizeof运算符来优化C++程序的性能？

在 C++11 中，`sizeof` 运算符是一个编译时工具，用于确定类型或变量在内存中占用的字节数。以下是一些使用 `sizeof` 来优化程序性能的常见方法：

1. **动态内存分配**：
   使用 `sizeof` 来确定动态数组或其他数据结构的大小，可以确保分配的内存足够存储所有元素，避免内存溢出。

   ```cpp
   int* array = new int[sizeof(int) * 100];
   ```

2. **数组大小计算**：
   `sizeof` 可以用来计算静态数组的总大小和元素数量，这对于处理数组操作非常有用。

   ```cpp
   int array[100];
   size_t num_elements = sizeof(array) / sizeof(array[0]);
   ```

3. **结构体内存布局**：
   通过 `sizeof` 可以了解结构体的内存布局，包括成员对齐和填充字节。这有助于优化结构体的设计，减少内存浪费。

   ```cpp
   struct MyStruct {
       char a;
       int b;
   };
   std::cout << "Size of MyStruct: " << sizeof(MyStruct) << std::endl;
   ```

4. **指针大小**：
   `sizeof` 可以用来获取指针的大小，这在处理指针数组或指针动态分配时很有用。

   ```cpp
   int* ptr;
   std::cout << "Size of pointer: " << sizeof(ptr) << std::endl;
   ```

5. **类型安全性检查**：
   使用 `sizeof` 来确保类型的大小符合预期，这在处理底层数据结构或硬件接口时尤为重要。

   ```cpp
   static_assert(sizeof(int) == 4, "Expected int to be 4 bytes");
   ```

6. **优化数据结构**：
   根据 `sizeof` 的结果调整数据结构，以减少内存对齐带来的浪费。

   ```cpp
   struct OptimizedStruct {
       char a;
       int b;
       char c;
   };
   ```

7. **编译时决策**：
   使用 `sizeof` 结合 `if constexpr` 或 `static_assert` 进行编译时的决策。

   ```cpp
   template <typename T>
   void process() {
       if constexpr (sizeof(T) == sizeof(int)) {
           // Handle int type
       }
   }
   ```

8. **避免缓冲区溢出**：
   确保不会写入超过变量分配大小的数据。

   ```cpp
   void safeMemcpy(void* dest, const void* src, size_t count) {
       size_t dest_size = sizeof(*static_cast<decltype(*dest)*>(dest));
       std::copy(src, src + std::min(count, dest_size), dest);
   }
   ```

9. **实现容器类**：
   在自定义容器类中，使用 `sizeof` 来计算存储元素所需的空间。

   ```cpp
   template <typename T, size_t N>
   class Array {
       T data[N];
   public:
       size_t size() { return sizeof(data) / sizeof(T); }
   };
   ```

10. **性能考量与优化技巧**：
    使用 `sizeof` 可以帮助开发者理解内存布局，优化内存使用。

通过这些方法，`sizeof` 运算符可以帮助开发者编写更高效、更安全的代码，尤其是在性能敏感或资源受限的应用中。

## 5.在使用sizeof运算符时，有哪些常见的错误或陷阱需要避免？

在使用 `sizeof` 运算符时，以下是一些常见的错误或陷阱，以及如何避免它们：

1. **对非POD类型使用 `sizeof` 来计算成员变量数量**：
   对于包含虚函数或成员指针的类类型，`sizeof` 返回的是对象在内存中的大小，可能包含虚函数表指针、对齐填充等，不能用来计算静态数组的实际元素数量。

   **避免方法**：确保使用 `sizeof` 计算简单数据类型的数组大小，对于复杂类型，手动计算或使用标准容器。

2. **对空数组使用 `sizeof`**：
   对于声明为 `type[]` 的空数组，`sizeof` 返回的是指针大小，而非数组的总大小。

   ```cpp
   int array[]; // 空数组
   std::cout << sizeof(array); // 返回的是指针大小，不是数组大小
   ```

   **避免方法**：提供数组的大小或使用动态分配的数组。

3. **对包含空成员的 struct 使用 `sizeof`**：
   包含空结构体成员的 `struct` 可能导致意想不到的行为，因为空成员可能不占用任何空间。

   ```cpp
   struct Empty {};
   struct S {
       int a;
       Empty b;
       int c;
   };
   std::cout << sizeof(S); // 实际大小可能小于预期
   ```

   **避免方法**：设计结构体时避免使用空成员，或使用标准库容器。

4. **对大小可变的类型使用 `sizeof`**：
   对于大小可变的类型，如 `std::string` 或动态分配的容器，`sizeof` 返回的是对象本身的大小，而非其管理的数据的大小。

   ```cpp
   std::string str;
   std::cout << sizeof(str); // 返回的是 string 对象的大小，而非其容量
   ```

   **避免方法**：使用 `capacity()` 或 `size()` 方法获取动态数据的实际大小。

5. **对引用类型使用 `sizeof`**：
   对引用使用 `sizeof` 返回的是引用本身的大小，而非引用所指向的对象的大小。

   ```cpp
   int a = 5;
   std::cout << sizeof(a); // 返回的是 int 的大小
   std::cout << sizeof(&a); // 返回的是指针的大小
   std::cout << sizeof(int&); // 返回的是引用的大小
   ```

   **避免方法**：直接对变量使用 `sizeof`，而非变量的引用或指针。

6. **对类型参数使用 `sizeof` 在模板中**：
   在模板编程中，对类型参数使用 `sizeof` 可能不会得到预期的结果，因为模板实例化时的具体类型可能未知。

   ```cpp
   template <typename T>
   void printSize() {
       std::cout << sizeof(T); // 在模板实例化之前，T 的具体大小是未知的
   }
   ```

   **避免方法**：在模板实例化后使用 `sizeof`，或使用类型特征。

7. **假设 `sizeof` 返回值是可预测的**：
   不同的编译器和平台可能会有不同的内存对齐和填充策略，因此 `sizeof` 的返回值可能因环境而异。

   **避免方法**：不要依赖于特定的 `sizeof` 返回值，除非对特定的平台和编译器有明确的了解。

8. **对联合(union)使用 `sizeof`**：
   `sizeof` 运算符对联合成员使用时，返回的是整个联合的大小，而不是选定成员的大小。

   ```cpp
   union Data {
       int i;
       double d;
   };
   std::cout << sizeof(Data); // 返回的是联合可以容纳的最大成员的大小
   ```

   **避免方法**：了解联合的特性，并根据需要设计数据结构。

通过了解这些陷阱，并采取适当的预防措施，你可以避免在使用 `sizeof` 时遇到问题。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
