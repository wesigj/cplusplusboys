# C++面试基础系列-指针和引用

[toc]

## Overview

## 1.指针和引用含义

在C++中，"pointer reference"这个术语可能引起一些混淆，因为"reference"（引用）和"pointer"（指针）是两种不同的概念，但它们可以一起使用。以下是对这两种概念的解释和它们如何一起使用的示例：

### 1.1.指针（Pointer）

指针是一个变量，它存储了另一个变量的内存地址。指针允许你间接访问内存地址上存储的值。

```cpp
int value = 10;
int* pointer = &value; // 'pointer'是指向'value'的指针
```

### 1.2.引用（Reference）

引用是一个别名，为一个已存在的变量提供了另一个名字。一旦引用被初始化，它就不能重新绑定到另一个变量。

```cpp
int value = 10;
int& reference = value; // 'reference'是'value'的引用
```

### 1.3.指针和引用一起使用

你可以有一个指针到引用，这通常在函数参数中看到，以便传递一个对对象的引用而不是对象本身，同时还能保持指针的语义。

```cpp
void increment(int& ref) {
    ref += 1;
}

void process(int* ptr) {
    increment(*ptr); // 通过指针传递引用
}
```

在这个例子中，`increment` 函数接受一个引用作为参数。在 `process` 函数中，我们有一个指向 `value` 的指针 `ptr`。我们通过 `*ptr`（解引用指针以获取它所指向的值）来调用 `increment`，这样 `increment` 就可以修改 `value` 的原始值。

### 1.4.指针引用（Pointer to Reference）

虽然不常见，但你可以有一个指向引用的指针。这通常在复杂的数据结构或模板元编程中看到。

```cpp
int value = 10;
int& ref = value;
int*& refRef = ref; // 'refRef'是指向引用的引用，也指向'value'
```

在这个例子中，`refRef` 是一个引用到引用的指针。它首先声明为 `ref` 的引用，然后可以被当作一个指向 `value` 的指针使用。

### 1.5.注意事项

- 引用必须在声明时被初始化，并且不能是`nullptr`。
- 指针可以是`nullptr`，表示它不指向任何地址。
- 引用的引用（或指向引用的指针）在大多数情况下是不推荐的，因为它可能导致代码难以理解和维护。

在实际编程中，通常建议使用常规的引用或指针，因为它们已经能够满足大多数需求，而且更易于理解和使用。

## 2.指针和引用的区别

指针（Pointer）和引用（Reference）在C++中是两种不同的概念，它们在使用和行为上有着明显的区别：

1. **定义方式**：
   - 指针是一个变量，它存储了另一个变量的内存地址。
  
     ```cpp
     int a = 10;
     int* p = &a; // p是指向a的指针
     ```

   - 引用是某个已存在变量的别名。
  
     ```cpp
     int a = 10;
     int& r = a; // r是a的引用
     ```

2. **初始化**：
   - 指针可以在任何时候被初始化或重新指向另一个地址。
   - 引用必须在声明时立即初始化，且一旦初始化后，就不能再指向另一个变量。

3. **可修改性**：
   - 指针可以在任何时间指向`nullptr`或被重新赋值为其他地址。
   - 引用不能是`nullptr`，且一旦引用绑定到一个对象，就不能被修改为引用其他对象。

4. **语法使用**：
   - 通过指针访问其指向的值需要使用解引用操作符`*`。
   - 引用使用起来就像使用原始变量一样，没有特别的语法需求。

5. **内存分配**：
   - 指针可能涉及到动态内存分配（使用`new`和`delete`）。
   - 引用不涉及动态内存分配，它们只是现有变量的别名。

6. **类型转换**：
   - 指针可以进行类型转换，如从`void*`转换为具体类型指针。
   - 引用通常不进行类型转换，它们在声明时类型就固定了。

7. **数组和函数参数**：
   - 指针可以用于数组和作为函数参数，以实现更复杂的数据操作。
   - 引用通常用于函数参数，以提供对实际参数的直接修改能力，避免复制开销。

8. **内存占用**：
   - 指针变量本身占用内存，它们存储的是另一个变量的地址。
   - 引用不占用额外内存，它们不存储地址，只是现有变量的一个别名。

9. **安全性**：
   - 指针可能更容易出错，如野指针、内存泄漏等。
   - 引用由于其绑定的特性，使用起来更安全，不容易出现错误。

10. **与`const`结合使用**：
    - 可以有指向`const`的指针（指向常量的指针），这意味着不能通过这个指针修改其指向的值。
    - 引用可以是`const`的，表示不能通过引用修改原始变量的值。

在实际编程中，选择使用指针还是引用通常取决于具体的应用场景和需求。引用通常用于简化代码和提高可读性，而指针则提供了更多的灵活性和控制能力。

## 3.指针和引用使用方法

以下是一个简单的C++代码示例，展示了指针和引用的使用：

```cpp
#include <iostream>

void usePointer(int* ptr) {
    if (ptr != nullptr) {
        std::cout << "Using pointer: " << *ptr << std::endl;
        *ptr = 20; // 修改指针指向的值
    }
}

void useReference(int& ref) {
    std::cout << "Using reference: " << ref << std::endl;
    ref = 30; // 修改引用绑定的值
}

int main() {
    int value = 10;

    // 使用指针
    std::cout << "Original value: " << value << std::endl;
    usePointer(&value);
    std::cout << "Value after pointer function: " << value << std::endl;
    std::cout << std::endl;

    // 使用引用
    std::cout << "Original value: " << value << std::endl;
    useReference(value);
    std::cout << "Value after reference function: " << value << std::endl;

    return 0;
}
```

在这个示例中：

- `usePointer` 函数接受一个`int*`类型的参数，即指向`int`的指针。在函数内部，我们首先检查指针是否不为`nullptr`，然后通过解引用操作符`*`来访问和修改指针指向的值。

- `useReference` 函数接受一个`int&`类型的参数，即`int`的引用。在函数内部，我们直接使用引用来访问和修改它绑定的原始变量的值。

- 在`main`函数中，我们声明了一个`int`类型的变量`value`并初始化为10。然后分别使用指针和引用的方式调用函数，并观察变量值的变化。

这个示例展示了指针和引用在函数参数传递中的使用，以及它们如何影响原始变量的值。请注意，引用在函数内部被当作原始变量的别名来使用，而指针则需要通过解引用来访问其指向的值。

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/img/wechat.jpg width=60% />
