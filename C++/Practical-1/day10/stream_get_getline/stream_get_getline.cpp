#include <iostream>
#include <string>

int main() {
    std::string line;

    // 使用getline读取一行
    std::cout << "Enter a line: ";
    getline(std::cin, line);
    std::cout << "You entered: " << line << std::endl;

    // 使用get读取字符数组
    char buffer[100];
    std::cout << "Enter a word: ";
    std::cin.get(buffer, 100);
    std::cout << "You entered: " << buffer << std::endl;

    return 0;
}