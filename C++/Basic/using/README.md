# C++面试基础系列-using

[TOC]

## Overview

## 1.using关键字

在 C++ 中，`using` 关键字有几种不同的用法，主要用于别名声明、类型导入和命名空间的成员导入。以下是 `using` 的几种常见用法：

### 1.1. 别名声明（Type Alias）

使用 `using` 为类型创建一个别名，简化复杂类型的书写。

```cpp
using int_ptr = std::shared_ptr<int>;
int_ptr p = std::make_shared<int>(10); // 使用别名创建智能指针
```

### 1.2. 模板别名

为模板类型创建一个别名，简化模板类型的书写。

```cpp
using IntVector = std::vector<int>;
IntVector v; // 使用别名创建向量
```

### 1.3. 类别名

为类或其指针、引用类型创建别名。

```cpp
class MyClass {
    // ...
};

using MyHandle = MyClass*; // 创建类指针的别名
MyHandle h = new MyClass();
```

### 1.4. 命名空间导入

使用 `using` 从命名空间中导入特定的名称，避免重复前缀。

```cpp
namespace NS {
    void foo() {}
}

using NS::foo; // 导入函数
foo(); // 直接调用
```

### 1.5. 命名空间别名

为命名空间创建别名，简化长命名空间的引用。

```cpp
namespace my_namespace = ::std::chrono;
my_namespace::seconds sec(5);
```

### 1.6. 导入构造函数

使用 `using` 语句导入基类的构造函数，使得派生类具有与基类相同的构造函数签名。

```cpp
class Base {
public:
    Base(int x) {}
};

class Derived : Base {
public:
    using Base::Base; // 导入 Base 类的构造函数
};

Derived d(10); // 直接使用 Base 的构造函数
```

### 1.7. 委托构造函数

C++11 允许在类内部使用 `using` 委托其他构造函数。

```cpp
class MyClass {
public:
    MyClass() {}
    MyClass(int x) : MyClass() {
        // ...
    }
};
```

### 1.8. 注意事项

- `using` 声明不应该与 `using` 指令混淆，后者是命名空间的另一种用法，用于使命名空间中的名称在当前作用域内可用。
- `using` 声明是作用域限定的，它只在声明它们的作用域内有效。
- 在模板中使用 `using` 可以简化模板类型的书写，特别是在模板别名中。

正确使用 `using` 可以提高代码的可读性和可维护性，但过度使用或不当使用可能会导致代码可读性降低。

在 C++ 中，`using` 声明（using declaration）和 `using` 指令（using directive）是两种不同的命名空间相关的关键字，它们各自有不同的用途和适用场景：

## 2.C++ 中的 using 声明和 using 指令有什么区别？

C++ 中的 using 声明和 using 指令有什么区别，它们各自在什么情况下使用？

### 2.1.using 声明 (using declaration)

`using` 声明用于从命名空间中导入特定的名称（如函数、变量、类型等），使其在当前作用域内可以直接使用而不需要命名空间前缀。

**语法：**

```cpp
using namespace::name;
```

**示例：**

```cpp
#include <vector>
using std::vector; // 导入 std 命名空间中的 vector

int main() {
    vector<int> v; // 直接使用 vector 而不需要 std:: 前缀
}
```

**使用场景：**

- 当你需要在当前作用域内多次使用某个命名空间中的特定名称时。
- 当你想要简化代码书写，避免重复书写长命名空间前缀时。

### 2.2.using 指令 (using directive)

`using` 指令用于将整个命名空间中的所有名称导入到当前作用域，使得所有名称都可以不加前缀地直接使用。

**语法：**

```cpp
using namespace ns;
```

**示例：**

```cpp
#include <iostream>
using namespace std; // 导入 std 命名空间中的所有内容

int main() {
    cout << "Hello, World!" << endl; // 直接使用 cout 和 endl 而不需要 std:: 前缀
}
```

**使用场景：**

- 当你需要在当前作用域内使用某个命名空间中的多个名称时。
- 当你确信当前作用域内不会发生名称冲突时。

### 2.3.区别

1. **作用范围**：`using` 声明只导入特定的名称，而 `using` 指令导入整个命名空间的所有名称。
2. **名称冲突**：使用 `using` 声明时，不容易造成名称冲突，因为只有特定的名称被导入；而 `using` 指令可能会引起名称冲突，因为它导入了所有名称。
3. **代码清晰度**：`using` 声明可以提高代码的清晰度，因为它明确了名称的来源；而 `using` 指令可能会降低代码的清晰度，因为它隐藏了名称的来源。
4. **使用限制**：`using` 指令不能用于类的作用域内，而 `using` 声明可以。

### 2.4.最佳实践

- 尽量避免在大型代码库或头文件中使用 `using` 指令，因为它可能导致名称冲突和降低代码的可读性。
- 优先使用 `using` 声明来导入所需的特定名称，这样可以提高代码的可维护性和可读性。
- 在确实需要使用 `using` 指令时，最好将其限制在较小的作用域内，如函数或代码块内部。

理解 `using` 声明和 `using` 指令的区别，以及它们各自的适用场景，有助于编写更清晰、更安全的 C++ 代码。

## 3.using示例

以下是一个简单的 C++ 代码示例，展示了 `using` 声明和 `using` 指令的使用及其区别：

```cpp
#include <iostream>
#include <vector>
#include <string>

// 使用 using 指令导入整个 std 命名空间
using namespace std;

// main 函数
int main() {
    // 可以直接使用命名空间 std 中的类型和函数，无需前缀
    cout << "Hello, World!" << endl;
    vector<int> numbers = {1, 2, 3, 4, 5};
    
    // 使用 using 声明导入特定函数
    using string::npos; // 从 string 类中导入 npos 成员

    // 使用导入的 npos
    string s = "Hello, using declaration!";
    string::size_type pos = s.find("using");
    cout << "Position of 'using': " << pos << endl; // 输出找到的字符串位置
    cout << "Position of 'example' (not found): " << s.find("example", 0) << endl; // 使用 npos 作为未找到的默认值

    // 尝试使用 std::vector 的 size() 成员函数
    cout << "Size of vector: " << numbers.size() << endl; // 正确使用

    // 如果注释掉 using namespace std; 则需要使用 std:: 前缀来调用
    // cout << "Size of vector (with prefix): " << std::vector<int>::size() << endl;

    return 0;
}
```

在这个示例中：

- 我们首先使用 `using namespace std;` 导入了整个 `std` 命名空间，这允许我们在 `main` 函数中直接使用 `std` 命名空间中的所有名称，如 `cout`、`endl` 和 `vector`。

- 接着，我们使用 `using string::npos;` 声明导入了 `std::string` 类的 `npos` 成员。这是一种 `using` 声明，它只导入了 `string` 类中的 `npos` 常量，而不是整个 `string` 类或 `std` 命名空间。这样，我们就可以在不使用 `std::` 前缀的情况下直接使用 `npos`。

- 示例中展示了使用 `npos` 来查询字符串中未找到的子字符串的默认行为。

- 我们可以直接使用 `vector` 的 `size()` 成员函数，因为我们已经通过 `using namespace std;` 导入了 `std` 命名空间。如果你注释掉 `using namespace std;`，则需要使用 `std::` 前缀来访问 `size()`，如示例中注释的部分所示。

这个示例展示了 `using` 声明和 `using` 指令如何影响作用域内名称的使用，以及如何通过它们来简化代码书写。使用 `using` 声明可以避免命名空间的冲突，而 `using` 指令则提供了一种快速访问命名空间中所有名称的方法，但可能会引起名称冲突。


---

## 关于作者

- 本文作者:WeSiGJ
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 微信公众号:WeSiGJ

<img src=/./img/wechat.jpg width=60% />
