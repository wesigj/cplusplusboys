#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl; // 输出并换行
    std::cout << "This message will not appear until we call flush."
              << std::flush; // 输出并刷新输出缓冲区
    return 0;
}