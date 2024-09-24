#include <iostream>

// 函数模板声明
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

    double a = 5.5;
    double b = 10.5;
    std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
    swap(a, b);
    std::cout << "After swap: a = " << a << ", b = " << b << std::endl;

    return 0;
}