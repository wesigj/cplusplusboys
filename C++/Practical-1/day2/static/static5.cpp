#include <iostream>
#include <string>

template <typename T>
class MyClass {
public:
    static std::string staticMember;
};

template <typename T>
std::string MyClass<T>::staticMember = "Hello, World!";

int main() {
    std::cout << "MyClass<int>::staticMember: " << MyClass<int>::staticMember << std::endl;
    std::cout << "MyClass<double>::staticMember: " << MyClass<double>::staticMember << std::endl;
    return 0;
}