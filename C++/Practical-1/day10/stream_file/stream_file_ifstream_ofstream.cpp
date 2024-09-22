#include <iostream>
#include <fstream>
#include <string>

int main() {
    // 定义文件名
    const std::string filename = "example.txt";

    // 创建输出文件流对象，用于写入文件
    std::ofstream outFile(filename);

    // 检查文件是否成功打开
    if (!outFile.is_open()) {
        std::cerr << "Failed to open " << filename << " for writing." << std::endl;
        return 1;
    }

    // 写入内容到文件
    outFile << "Hello, World!\n";
    outFile << "This is a simple C++ file operation example.\n";

    // 关闭文件
    outFile.close();

    // 创建输入文件流对象，用于读取文件
    std::ifstream inFile(filename);

    // 检查文件是否成功打开
    if (!inFile.is_open()) {
        std::cerr << "Failed to open " << filename << " for reading." << std::endl;
        return 1;
    }

    // 读取文件内容
    std::string line;
    while (std::getline(inFile, line)) {
        std::cout << line << std::endl;
    }

    // 关闭文件
    inFile.close();

    return 0;
}