#include <iostream>
// 普通模板
template <typename T>
void print(T value) {
    std::cout << value << std::endl;
}

// 特化模板
template <>
void print<int>(int value) {
    std::cout << "Integer: " << value << std::endl;
}

int main() {
    print(10);  // 调用特化版本
    print(5.5); // 调用普通模板
    return 0;
}