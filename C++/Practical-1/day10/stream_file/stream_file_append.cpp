#include <iostream>
#include <fstream>
#include <string>

int main() {
    // 定义文件名
    const std::string filename = "example.txt";

    // 创建输出文件流对象，以追加模式打开文件
    std::ofstream outFile(filename, std::ios::app);

    // 检查文件是否成功打开
    if (!outFile.is_open()) {
        std::cerr << "Failed to open " << filename << " for appending." << std::endl;
        return 1;
    }

    // 写入内容到文件末尾
    outFile << "This line will be appended to the end of the file.\n";

    // 关闭文件
    outFile.close();

    return 0;
}