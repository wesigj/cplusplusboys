# C++11 24-删除的函数 delete functions

- [C++11 24-删除的函数 delete functions](#c11-24-删除的函数-delete-functions)
  - [Overview](#overview)
  - [1.删除的函数 delete functions](#1删除的函数-delete-functions)
  - [关于作者](#关于作者)

## Overview

---

## 1.删除的函数 delete functions

在 C++中，可以使用以下几种方式来“删除”函数：

1. 使用 `delete` 关键字：
   - 如前面提到的，可以将特定的函数（如拷贝构造函数、赋值运算符等）标记为 `delete`，以禁止它们被调用。
   - 例如：

   ```cpp
   class MyClass {
   public:
       MyClass() = default;
       // 禁用拷贝构造函数
       MyClass(const MyClass&) = delete;
       // 禁用赋值运算符
       MyClass& operator=(const MyClass&) = delete;
   };
   ```

2. 覆盖并实现为空：
   - 对于虚函数，可以在派生类中覆盖并实现为空函数体，从而在特定情况下“删除”该函数的功能。
   - 例如：

   ```cpp
   class Base {
   public:
       virtual void foo() {
           std::cout << "Base::foo()\n";
       }
   };

   class Derived : public Base {
   public:
       void foo() override {} // 实现为空，相当于“删除”该函数在派生类中的功能
   };
   ```

3. 隐藏函数：
   - 在派生类中定义与基类同名但参数不同的函数，可以隐藏基类中的函数，从某种程度上也可以看作是“删除”了基类中的那个函数版本。
   - 例如：

   ```cpp
   class Base {
   public:
       void bar(int x) {
           std::cout << "Base::bar(int)\n";
       }
   };

   class Derived : public Base {
   public:
       void bar(double y) {
           std::cout << "Derived::bar(double)\n";
       }
   };
   ```

4. 通过访问限定符：
   - 将函数放在 `private` 或 `protected` 区域内，可以限制其被外部访问，在一定程度上起到类似“删除”的效果（外部无法调用）。
   - 例如：

   ```cpp
   class MyClass {
   private:
       void secretFunction() {
           std::cout << "This is a secret function.\n";
       }
   };
   ```

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
