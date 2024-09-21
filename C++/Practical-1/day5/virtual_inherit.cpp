#include <iostream>

class A {
public:
    int data;
    A() {
        data = 10;
    }
    virtual void printData() {
        std::cout << "A: " << data << std::endl;
    }
};

// 虚继承 A
class B : virtual public A {
public:
    B() {
        std::cout << "B Constructor called" << std::endl;
    }
};

// 虚继承 A
class C : virtual public A {
public:
    C() {
        std::cout << "C Constructor called" << std::endl;
    }
};

// 继承 B 和 C
class D : public B, public C {
public:
    D() {
        std::cout << "D Constructor called" << std::endl;
    }
    void printData() {
        std::cout << "D: " << data << std::endl; // 直接访问 A 的成员
    }
};

int main() {
    D d;
    d.printData(); // 输出 A 的数据成员
    // d.B::printData(); // 错误：B 的 A 子对象是私有的
    // d.C::printData(); // 错误：C 的 A 子对象是私有的
    return 0;
}