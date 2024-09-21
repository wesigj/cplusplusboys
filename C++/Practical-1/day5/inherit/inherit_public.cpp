#include <iostream>

class Base {
public:
    int  publicData = 10;
    void publicFunc() {
        std::cout << "Base public function." << std::endl;
    }
};

class Derived : public Base {
public:
    void derivedFunc() {
        publicFunc();                         // 可以访问基类的公有成员
        std::cout << publicData << std::endl; // 可以访问基类的公有成员
    }
};

int main() {
    Derived d;
    d.publicFunc();                         // 可以访问派生类的公有继承成员
    std::cout << d.publicData << std::endl; // 可以访问派生类的公有继承成员
    d.derivedFunc();
    return 0;
}