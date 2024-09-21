#include <iostream>

class Base {
protected:
    int  protectedData = 20;
    void protectedFunc() {
        std::cout << "Base protected function." << std::endl;
    }
};

class Derived : protected Base {
public:
    void derivedFunc() {
        protectedFunc();                         // 可以访问基类的保护成员
        std::cout << protectedData << std::endl; // 可以访问基类的保护成员
    }
};

int main() {
    Derived d;
    // d.protectedFunc(); // 错误：基类的保护成员在派生类外部不可访问
    // std::cout << d.protectedData << std::endl; // 错误：基类的保护成员在派生类外部不可访问
    d.derivedFunc();
    return 0;
}