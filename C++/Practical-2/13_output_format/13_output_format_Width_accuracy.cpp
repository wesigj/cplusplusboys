#include <iostream>
#include <iomanip>

int main() {
    double price = 19.99;

    std::cout << "Default output: " << price << std::endl;
    std::cout << "Formatted output: " << std::fixed << std::setprecision(2)
              << price << std::endl;
    std::cout << "Right-justified: " << std::setw(10) << std::setfill('*')
              << "Right" << std::endl;

    return 0;
}