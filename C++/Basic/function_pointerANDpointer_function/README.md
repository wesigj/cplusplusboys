# C++面试基础系列-函数指针与指针函数

[toc]

## Overview

## 1.function_pointer函数指针

- function_pointer函数指针也是一个指针，
  - 只不过函数指针可以指向函数，可以通过该指针调用函数
  - 联想到重载，多态，模板，只不过函数指针需要重新调整指针指向的函数类型

## 2.pointer_function指针函数

- 指针函数实际上只是函数返回值返回一个指针

## 3.面试中，最喜欢的是函数指针和指针函数的区别

函数指针和指针函数是两个不同的概念，主要区别如下：

### 3.1.定义

1. 指针函数：
   - 本质是一个函数，其返回值是一个指针。
   - 例如：`int* fun() { /* 函数体 */ }`，这里的函数 `fun`就是一个指针函数，它返回一个指向整数的指针。
2. 函数指针：
   - 是指向函数的指针变量。
   - 例如：`int (*pf)();`，这里 `pf`是一个函数指针，它指向一个返回值为整数的函数。

### 3.2.用法

1. 指针函数的用法：

   - 先调用指针函数，得到一个指针结果，然后通过这个指针访问其所指向的内存空间中的数据。
   - 例如：
   - 看出下面代码的错误了吗？

     ```c
     int* fun() {
         int a = 10;
         return &a;
     }
     int main() {
         int* ptr = fun();
         printf("%d\n", *ptr);//error
         return 0;
     }
     ```

   - **ERROR:a是一个局部变量，调用指向a的指针，会出现内存泄漏，应避免这种用法。**
2. 函数指针的用法：

   - 可以将函数指针作为参数传递给其他函数，实现回调函数的功能。
   - 例如：

     ```c
     void callback(int (*func)(int), int arg) {
         int result = func(arg);
         printf("Result: %d\n", result);
     }
     int square(int num) {
         return num * num;
     }
     int main() {
         callback(square, 5);
         return 0;
     }
     ```

### 3.3.存储方式

1. 指针函数：在内存中与普通函数一样，有特定的代码段存储函数体，执行时将在该代码段中运行。返回的指针则存储在相应的内存地址中。
2. 函数指针：本身作为一个变量存储在内存中，它的值是所指向函数的入口地址。

## 4.函数指针用法

函数指针是C++中一种重要的特性，它允许将函数作为值来处理。以下是函数指针的一些常见用法：

1. **动态函数调用**：
   使用函数指针可以在运行时决定调用哪个函数。这在实现回调机制、策略模式或事件处理系统时非常有用。

   ```cpp
   void function1() { std::cout << "Function 1" << std::endl; }
   void function2() { std::cout << "Function 2" << std::endl; }
   void (*functionPtr)() = function1; // 函数指针指向function1
   functionPtr(); // 调用function1
   functionPtr = function2; // 现在指向function2
   functionPtr(); // 调用function2
   ```

2. **实现回调函数**：
   函数指针经常用于回调函数，即作为参数传递给另一个函数，然后在该函数内部调用。

   ```cpp
   void callback(void (*func)()) {
       func();
   }
   void myFunction() {
       std::cout << "Hello from myFunction" << std::endl;
   }
   int main() {
       callback(myFunction);
   }
   ```

3. **作为数据成员**：
   在类中使用函数指针作为数据成员，允许对象根据行为的不同来调用不同的函数。

   ```cpp
   class Event {
   public:
       void (*handler)(); // 函数指针作为数据成员
   };
   Event event;
   event.handler = myFunction;
   event.handler(); // 调用myFunction
   ```

4. **数组和向量**：
   函数指针可以存储在数组或向量中，用于管理一组函数。

   ```cpp
   void (*functions[])() = {function1, function2};
   for (auto func : functions) {
       func();
   }
   ```

5. **函数指针类型转换**：
   在某些情况下，可能需要将一个函数指针转换为另一个类型的指针，或者反之。

   ```cpp
   typedef void (*FuncType)();
   int (*intFunc)(int) = static_cast<int (*)(int)>(function1); // 类型转换
   ```

6. **实现多态**：
   函数指针可以用来实现类似多态的行为，尤其是在使用函数作为类的成员或参数时。

   ```cpp
   class Base {
   public:
       virtual void execute() = 0;
   };
   class Derived : public Base {
   public:
       void execute() override {
           std::cout << "Execute in Derived" << std::endl;
       }
   };
   Base* basePtr = new Derived();
   (*basePtr).execute(); // 多态调用
   delete basePtr;
   ```

7. **用于排序和搜索算法**：
   在标准库算法中，如 `std::sort`或 `std::find_if`，可以传递函数指针或函数对象来指定自定义的比较或谓词函数。

   ```cpp
   int array[] = {5, 3, 2, 4, 1};
   std::sort(std::begin(array), std::end(array),
            [](int a, int b) { return a > b; }); // lambda表达式作为函数指针使用
   ```

8. **信号处理**：
   在Unix和类Unix系统中，`signal`函数允许为各种信号注册信号处理函数，这通常通过函数指针完成。

   ```cpp
   void signalHandler(int signal) {
       std::cout << "Signal received" << std::endl;
   }
   // 注册信号处理函数
   signal(SIGINT, signalHandler);
   ```

9. **函数指针的指针**：
   可以创建函数指针的数组或指针，这在实现函数表或多级回调时很有用。

   ```cpp
   void (*functionTable[])() = {function1, function2};
   void (**functionTablePtr)() = functionTable;
   (*functionTablePtr)[0](); // 调用function1
   ```

10. **与C ABI兼容**：
    由于C++兼容C的ABI（应用程序二进制接口），函数指针在C和C++之间可以互用，这在编写跨语言的库或接口时非常有用。

函数指针是C++中实现多态、回调和高阶函数（即接受或返回函数的函数）的关键工具。然而，过度使用函数指针可能会使代码难以理解和维护，因此应谨慎使用，并考虑使用更现代的C++特性，如函数对象、lambda表达式和std::function。

## 5.指针函数

指针函数是一种返回指针类型的函数。以下是指针函数的一些用法：

### 5.1.动态内存分配

在 C 和 C++中，可以使用指针函数来动态分配内存并返回指向该内存的指针。例如：

```c++
int* allocateArray(int size) {
    int* arr = new int[size];
    return arr;
}
```

在这个例子中，`allocateArray`函数接受一个整数参数`size`，用于指定要分配的数组大小。函数内部使用`new`关键字动态分配一个整数数组，并返回指向该数组的指针。使用时可以这样调用：

```c++
int main() {
    int* myArray = allocateArray(10);
    // 使用 myArray
    delete[] myArray;
    return 0;
}
```

### 5.2.返回复杂数据结构的指针

当需要从函数中返回一个复杂的数据结构时，可以使用指针函数。例如，假设有一个结构体表示学生信息：

```c++
struct Student {
    std::string name;
    int age;
};

Student* createStudent(std::string name, int age) {
    Student* s = new Student;
    s->name = name;
    s->age = age;
    return s;
}
```

使用方式如下：

```c++
int main() {
    Student* student = createStudent("Tom", 18);
    // 使用 student
    delete student;
    return 0;
}
```

### 5.3.作为函数参数传递

指针函数的返回值可以作为其他函数的参数进行传递。例如：

```c++
void processArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;
    }
}

int* generateArray(int size) {
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
    return arr;
}
```

可以这样调用：

```c++
int main() {
    int* myArray = generateArray(5);
    processArray(myArray, 5);
    // 使用 myArray
    delete[] myArray;
    return 0;
}
```

在这个例子中，`generateArray`函数生成一个整数数组，然后将其作为参数传递给`processArray`函数进行处理。

---

## 关于作者

- 本文作者:WeSiGJ
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 微信公众号:WeSiGJ

<img src=/./img/wechat.jpg width=60% />
