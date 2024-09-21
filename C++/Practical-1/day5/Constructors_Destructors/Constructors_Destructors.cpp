#include <iostream>

class Base {
public:
    Base() {
        std::cout << "Base constructor called" << std::endl;
    }
    virtual ~Base() {
        std::cout << "Base destructor called" << std::endl;
    }
};

class Derived : public Base {
public:
    Derived() {
        std::cout << "Derived constructor called" << std::endl;
    }
    ~Derived() {
        std::cout << "Derived destructor called" << std::endl;
    }
};

int main() {
    {
        Derived d; // 调用 Derived 的构造函数，然后调用 Base 的构造函数
    } // d 离开作用域，调用 Derived 的析构函数，然后调用 Base 的析构函数

    return 0;
}