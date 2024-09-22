#include <iostream>
#include <sstream>
#include <iomanip>

int main() {
    std::stringstream ss;
    int               number = 42;
    double            pi     = 3.14159;

    ss << "Number: " << std::setw(10) << std::setfill('0') << number
       << std::endl;
    ss << "Pi: " << std::fixed << std::setprecision(2) << pi << std::endl;

    std::cout << ss.str() << std::endl;
    return 0;
}