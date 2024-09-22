#include <iostream>
#include <iomanip>

int main() {
    double      pi     = 3.14159;
    std::string name   = "Kimi";
    int         number = 42;

    std::cout << "Formatted Output:\n";
    std::cout << std::setw(10) << std::setfill('*') << "Name: " << name
              << std::endl;
    std::cout << std::setw(10) << std::setfill('*') << "Num: " << number
              << std::endl;
    std::cout << std::setw(15) << std::setfill(' ') << std::left
              << "Pi value: " << pi << std::endl;
    std::cout << std::fixed << std::setprecision(3)
              << "Pi value (fixed): " << pi << std::endl;
    std::cout << std::scientific << "Pi value (scientific): " << pi
              << std::endl;
    std::cout << std::hexfloat << "Pi value (hex): " << pi << std::endl;

    return 0;
}