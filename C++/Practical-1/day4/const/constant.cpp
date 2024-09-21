#include <iostream>

int main() {
    const int hours = 24; // 定义一个常量
    std::cout << "Number of hours in a day: " << hours << std::endl;
    // hours = 25; // 错误：不能修改常量
    return 0;
}