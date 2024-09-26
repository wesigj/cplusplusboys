#include <iostream>
#include <iomanip>

int main() {
    int         year        = 2024;
    double      temperature = 23.6;
    std::string location    = "Shanghai";

    std::cout << "It is " << temperature << " degrees in " << location
              << " this year " << year << "." << std::endl;

    // 使用 setw 和 setfill 进行格式化
    std::cout << std::setw(5) << std::setfill('0') << year << std::endl;
    std::cout << std::fixed << std::setprecision(2) << temperature << std::endl;

    return 0;
}