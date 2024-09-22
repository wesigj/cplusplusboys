#include <iostream>
#include <fstream>
#include <string>
#include <exception>

int main() {
    try {
        const std::string filename = "example.txt";

        // 创建输出文件流对象，用于写入文件
        std::ofstream outFile(filename);

        if (!outFile.is_open()) {
            throw std::runtime_error("Failed to open " + filename + " for writing.");
        }

        outFile << "Hello, World!\n";
        outFile << "This is a simple C++ file operation example.\n";
        outFile.close();

        // 创建输入文件流对象，用于读取文件
        std::ifstream inFile(filename);

        if (!inFile.is_open()) {
            throw std::runtime_error("Failed to open " + filename + " for reading.");
        }

        std::string line;
        while (std::getline(inFile, line)) {
            std::cout << line << std::endl;
        }
        inFile.close();
    } catch (const std::exception &e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}