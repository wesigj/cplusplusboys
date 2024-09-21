#include <iostream>

class Base {
private:
    int  privateData = 30;
    void privateFunc() {
        std::cout << "Base private function." << std::endl;
    }
};

class Derived : private Base {
public:
    void derivedFunc() {
        privateFunc();                         // 可以访问基类的私有成员
        std::cout << privateData << std::endl; // 可以访问基类的私有成员
    }
};

int main() {
    Derived d;
    // d.privateFunc(); // 错误：基类的私有成员在派生类外部不可访问
    // std::cout << d.privateData << std::endl; // 错误：基类的私有成员在派生类外部不可访问
    d.derivedFunc();
    return 0;
}