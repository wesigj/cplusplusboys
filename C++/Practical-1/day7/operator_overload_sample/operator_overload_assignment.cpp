#include <iostream>
#include <string>

class Person {
public:
    std::string name;
    int         age;

    Person(const std::string &n, int a) :
        name(n), age(a) {
    }

    // 重载赋值运算符
    Person &operator=(const Person &rhs) {
        if (this != &rhs) {
            name = rhs.name;
            age  = rhs.age;
        }
        return *this;
    }
};

int main() {
    Person p1("Alice", 30);
    Person p2 = p1;
    std::cout << "p2: " << p2.name << ", " << p2.age << std::endl;
    return 0;
}