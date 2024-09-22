#include <iostream>
#include <format>

// #include <format>
// -std=c++20
int main() {
    int    number = 42;
    double pi     = 3.14159;

    std::cout << std::format("Number: {:0>10}\n", number);
    std::cout << std::format("Pi: {:.2f}\n", pi);
    return 0;
}