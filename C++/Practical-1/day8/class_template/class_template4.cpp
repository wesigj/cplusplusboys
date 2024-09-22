#include <iostream>

// 原始模板
template <typename T>
class MyClass {
public:
    void print() {
        std::cout << "Generic template" << std::endl;
    }
};

// 特化模板
template <>
class MyClass<int> {
public:
    void print() {
        std::cout << "Specialized for int" << std::endl;
    }
};

int main() {
    MyClass<int>    intObj;
    MyClass<double> doubleObj;

    intObj.print();    // 输出: Specialized for int
    doubleObj.print(); // 输出: Generic template

    return 0;
}