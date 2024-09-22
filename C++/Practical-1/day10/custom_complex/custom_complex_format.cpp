#include <iostream>
#include <iomanip>
#include <string>

// 自定义流操纵符，用于输出带边框并居中的字符串
std::ostream &bordered_and_centered(std::ostream &os, const std::string &str) {
    int length      = str.length();
    int total_width = 20; // 定义总宽度，确保足够长
    int padding     = (total_width - length) / 2;
    // 确保如果总宽度 - 长度是奇数，右侧的星号比左侧多一个
    int         extra_padding = (total_width - length) % 2;
    std::string padding_str =
        std::string(padding, '*') + (extra_padding ? "*" : "");
    os << "[" << padding_str << str << padding_str << "]";
    return os;
}

int main() {
    std::string text = "C++";
    std::cout << bordered_and_centered(std::cout, text) << std::endl;
    return 0;
}