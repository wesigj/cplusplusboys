#include <iostream>

enum Color : unsigned int {
    Red = 10,
    Green,
    Blue
};

int main() {
    std::cout << "Red is: " << Red << std::endl;     // 输出: Red is: 10
    std::cout << "Green is: " << Green << std::endl; // 输出: Green is: 11
    std::cout << "Blue is: " << Blue << std::endl;   // 输出: Blue is: 12
    return 0;
}