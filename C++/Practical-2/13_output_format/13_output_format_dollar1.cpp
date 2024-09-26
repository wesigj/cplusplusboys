#include <iostream>
#include <locale>

int main() {
    // 设置地区为美国，这通常会使用美元符号
    std::locale::global(std::locale("en_US.UTF-8"));

    double amount = 1234.56;

    // 使用 std::cout 输出货币格式
    std::cout << std::showbase << "Amount: $" << amount << std::endl;

    // 如果你想要更精确地控制货币的显示格式，可以使用 std::moneypunct
    std::cout << "Amount with currency symbol: "
              << std::moneypunct<std::string::value_type, false>::char_type('¤')
              << amount << std::endl;

    return 0;
}