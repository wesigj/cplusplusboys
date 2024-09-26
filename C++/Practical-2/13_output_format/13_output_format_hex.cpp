#include <iostream>
#include <iomanip>

int main() {
    int    hexValue        = 255;
    double scientificValue = 1234.56;

    std::cout << "Hexadecimal: " << std::hex << hexValue << std::endl;
    std::cout << "Scientific notation: " << std::scientific << scientificValue
              << std::endl;

    return 0;
}