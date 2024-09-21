#include <iostream>

class MyClass {
public:
    static int staticMember;
};

int MyClass::staticMember = 0;

int main() {
    MyClass::staticMember = 100;
    std::cout << "MyClass::staticMember: " << MyClass::staticMember << std::endl;
    return 0;
}