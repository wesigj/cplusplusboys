#include <iostream>

class Base {
public:
    virtual void print() const {
        std::cout << "Base print function." << std::endl;
    }
    virtual ~Base() {
    } // 虚析构函数
};

class Derived : public Base {
public:
    void print() const override { // 使用override关键字
        std::cout << "Derived print function." << std::endl;
    }
};

int main() {
    Base *b = new Derived();
    b->print(); // 调用Derived的print函数
    delete b;   // 调用Derived的析构函数
    return 0;
}