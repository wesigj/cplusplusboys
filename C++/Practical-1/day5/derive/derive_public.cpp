#include <iostream>

// 基类
class Base {
public:
    Base() {
        std::cout << "Base constructor called.\n";
    }
    virtual void print() const {
        std::cout << "Base print function.\n";
    }
};

// 派生类
class Derived : public Base {
public:
    Derived() {
        std::cout << "Derived constructor called.\n";
    }
    void print() const override {
        std::cout << "Derived print function.\n";
    }
};

int main() {
    Derived d;
    d.print(); // 调用派生类的print函数

    Base *b = &d;
    b->print(); // 调用派生类的print函数，因为print函数是虚函数

    return 0;
}