#include <iostream>

// 普通模板定义
template <typename T>
class MyClass {
public:
    void display() {
        std::cout << "Generic template" << std::endl;
    }
};

// 类模板特化
template <>
class MyClass<int> {
public:
    void display() {
        std::cout << "Specialized for int" << std::endl;
    }
};

// 类模板部分特化
template <typename T>
class MyClass<T *> {
public:
    void display() {
        std::cout << "Specialized for pointer" << std::endl;
    }
};

int main() {
    MyClass<double> myClassDouble;
    myClassDouble.display(); // 输出: Generic template

    MyClass<int> myClassInt;
    myClassInt.display(); // 输出: Specialized for int

    MyClass<char *> myClassCharPtr;
    myClassCharPtr.display(); // 输出: Specialized for pointer

    return 0;
}