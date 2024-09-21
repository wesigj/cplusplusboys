#include <iostream>
#include <string>

class StringFactory {
public:
    // 重载函数调用运算符
    std::string operator()(const std::string &str) const {
        return str;
    }
};

int main() {
    StringFactory factory;

    std::string result = factory("Hello, Factory!");

    std::cout << result << std::endl; // 输出: Hello, Factory!

    return 0;
}