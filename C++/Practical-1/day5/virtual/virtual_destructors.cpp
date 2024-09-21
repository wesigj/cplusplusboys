#include <iostream>

class Base {
public:
    virtual ~Base() {
        std::cout << "Base destructor called." << std::endl;
    }
};

class Derived : public Base {
public:
    ~Derived() {
        std::cout << "Derived destructor called." << std::endl;
    }
};

int main() {
    Base *b = new Derived();
    delete b; // 调用Derived的析构函数，然后调用Base的析构函数
    return 0;
}