#include <iostream>

class Person {
private:
    std::string name;

public:
    Person(const std::string &n) :
        name(n) {
    }

    // 声明友元函数
    friend std::ostream &operator<<(std::ostream &os, const Person &person);
};

// 重载<<操作符
std::ostream &operator<<(std::ostream &os, const Person &person) {
    os << "Name: " << person.name;
    return os;
}

int main() {
    Person person("Alice");
    std::cout << person << std::endl;
    return 0;
}