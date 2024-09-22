#include <iostream>
#include <iomanip>
#include <sstream>

int main() {
    std::stringstream ss;
    int               number = 42;
    double            pi     = 3.14159;

    ss << std::left << std::setw(20) << "Number: " << std::setw(10) << number
       << std::endl;
    ss << std::left << std::setw(20) << "Pi: " << std::fixed
       << std::setprecision(2) << pi << std::endl;

    std::cout << ss.str() << std::endl;
    return 0;
}