#include <iostream>
#include <string>

const std::string getCurrentTime() {
    // 假设这是一个获取当前时间的函数
    return "14:00";
}

int main() {
    std::string time = getCurrentTime();
    // time = getCurrentTime(); // 错误：不能修改const返回值
    std::cout << "Current time: " << time << std::endl;
    return 0;
}