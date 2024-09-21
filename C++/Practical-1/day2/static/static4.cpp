#include <iostream>

class MyClass {
public:
    static void staticMemberFunction() {
        std::cout << "This is a static member function." << std::endl;
    }
};

int main() {
    MyClass::staticMemberFunction();
    return 0;
}