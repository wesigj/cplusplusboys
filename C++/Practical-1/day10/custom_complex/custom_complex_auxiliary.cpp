#include <iostream>
#include <string>

// 自定义流操纵符，用于输出带边框的字符串
std::ostream &bordered(std::ostream &os, const std::string &str) {
    os << "[" << str << "]";
    return os;
}