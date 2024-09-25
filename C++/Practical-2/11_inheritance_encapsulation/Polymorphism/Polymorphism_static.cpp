#include <iostream>

void print(int i) {
    std::cout << "Printing int: " << i << std::endl;
}

void print(double f) {
    std::cout << "Printing float: " << f << std::endl;
}

int main() {
    print(5);   // 调用 print(int)
    print(5.0); // 调用 print(double)
    return 0;
}