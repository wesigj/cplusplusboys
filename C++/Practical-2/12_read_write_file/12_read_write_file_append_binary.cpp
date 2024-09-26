#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void appendToFile(const std::string &filename, const std::string &content) {
    std::ofstream outFile(filename, std::ios::app); // 以追加模式打开文件
    if (!outFile) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }

    outFile << content; // 追加内容到文件
    outFile.close();    // 关闭文件
}
void writeBinaryFile(const std::string       &filename,
                     const std::vector<char> &data) {
    std::ofstream outFile(filename, std::ios::binary); // 以二进制模式打开文件
    if (!outFile) {
        std::cerr << "Unable to create binary file " << filename << std::endl;
        return;
    }

    outFile.write(data.data(), data.size()); // 写入二进制数据
    outFile.close();                         // 关闭文件
}

void readBinaryFile(const std::string &filename, std::vector<char> &buffer) {
    std::ifstream inFile(filename, std::ios::binary); // 以二进制模式打开文件
    if (!inFile) {
        std::cerr << "Unable to open binary file " << filename << std::endl;
        return;
    }

    inFile.seekg(0, std::ios::end);   // 移动到文件末尾
    size_t fileSize = inFile.tellg(); // 获取文件大小
    inFile.seekg(0, std::ios::beg);   // 回到文件开头

    buffer.resize(fileSize);              // 调整缓冲区大小
    inFile.read(buffer.data(), fileSize); // 读取文件内容到缓冲区
    inFile.close();                       // 关闭文件
}

int main() {
    std::string filename    = "example.txt";
    std::string textContent = "This is additional text.\n";

    // 追加文本内容
    appendToFile(filename, textContent);

    // 二进制写入
    std::vector<char> binaryData = {0x00, 0x01, 0x02, 0x03, 0x04};
    writeBinaryFile("binaryData.bin", binaryData);

    // 二进制读取
    std::vector<char> readData;
    readBinaryFile("binaryData.bin", readData);

    // 显示读取的二进制数据
    for (char c : readData) { std::cout << std::hex << (int)c << " "; }
    std::cout << std::endl;

    return 0;
}