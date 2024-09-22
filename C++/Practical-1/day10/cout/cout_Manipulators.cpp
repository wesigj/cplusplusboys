#include <iostream>
#include <iomanip>

int main() {
    double pi = 3.14159;

    std::cout << "Default precision: " << pi << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Fixed precision: " << pi << std::endl;
    std::cout << std::setw(10) << "Width: " << std::left << "Left aligned." << std::endl;
    return 0;
}