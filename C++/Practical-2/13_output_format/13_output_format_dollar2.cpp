#include <iostream>
#include <format>
#include <locale>

int main() {
    std::locale::global(std::locale("en_US.UTF-8"));

    double amount = 1234.56;

    // 使用 std::format 输出货币格式
    // 头文件添加 #include <format>
    // 编译选项添加：-std=C++20
    std::cout << std::format("{:$L}", amount) << std::endl;

    return 0;
}