#include <iostream>

// 基类
class Base {
protected:
    int baseValue = 10;
};

// 派生类
class Derived : protected Base {
public:
    int getBaseValue() const {
        return baseValue;
    }
};

int main() {
    Derived d;
    std::cout << d.getBaseValue() << std::endl; // 访问基类的保护成员

    return 0;
}