#include <iostream>
#include <fstream>

int main() {
    std::ofstream outFile("example.txt");
    if (outFile.fail()) {
        std::cerr << "Failed to open file for writing." << std::endl;
    } else {
        outFile << "Hello, World!" << std::endl;
        if (outFile.fail()) {
            std::cerr << "Failed to write to file." << std::endl;
        }
    }
    outFile.close();

    /********************************************************* */
    std::ifstream inFile("example.txt");
    if (inFile.bad()) {
        std::cerr << "Failed to open file for reading." << std::endl;
    } else {
        std::string line;
        while (std::getline(inFile, line)) {
            if (inFile.bad()) {
                std::cerr << "Failed to read from file." << std::endl;
                break;
            }
            std::cout << line << std::endl;
        }
    }
    inFile.close();

    /********************************************************* */
    std::ofstream outFile("example.txt", std::ios::app);
    outFile << "Appending text." << std::endl;
    if (!outFile) { // 等同于检查 fail() 或 bad()
        std::cerr << "Write operation failed." << std::endl;
    }
    outFile.close();
}