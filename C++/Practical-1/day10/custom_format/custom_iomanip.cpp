#include <iostream>
#include <iomanip>

int main() {
    int number = -42;
    std::cout << std::setw(10) << std::setfill('*') << std::showpos << number
              << std::endl;
    return 0;
}