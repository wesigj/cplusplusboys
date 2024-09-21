#include <iostream>

class Base {
public:
    Base() {
        std::cout << "Base constructor called" << std::endl;
    }
};

class Derived : public Base {
public:
    int a;
    int b;

    Derived(int x, int y) :
        a(x), b(y) {
        std::cout << "Derived constructor called" << std::endl;
    }
};

int main() {
    Derived obj(10, 20);
    return 0;
}