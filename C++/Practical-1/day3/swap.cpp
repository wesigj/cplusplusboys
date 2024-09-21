#include <iostream>

// 自定义swap函数
template <typename T>
void swap(T &a, T &b) {
    T temp = a;
    a      = b;
    b      = temp;
}

int main() {
    int x = 10;
    int y = 20;

    std::cout << "Before swap: x = " << x << ", y = " << y << std::endl;

    swap(x, y);

    std::cout << "After swap: x = " << x << ", y = " << y << std::endl;

    return 0;
}