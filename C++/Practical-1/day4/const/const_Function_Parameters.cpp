#include <iostream>
#include <string>

void printMessage(const std::string &message) {
    std::cout << message << std::endl;
    // message = "Hello"; // 错误：不能修改const引用
}

int main() {
    printMessage("Hello, World!");
    return 0;
}