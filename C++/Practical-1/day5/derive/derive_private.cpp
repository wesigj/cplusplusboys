#include <iostream>

// 基类
class Base {
public:
    void baseFunction() const {
        std::cout << "Base function.\n";
    }
};

// 派生类
class Derived : private Base {
public:
    void derivedFunction() const {
        baseFunction(); // 派生类可以访问基类的私有成员
    }
};

int main() {
    Derived d;
    // d.baseFunction(); // 错误：基类的私有成员在派生类外部不可访问
    d.derivedFunction(); // 调用派生类的函数

    return 0;
}