#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

bool insertText(const std::string &filename, const std::string &insertText, int position) {
    std::ifstream inFile(filename, std::ios::in | std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open " << filename << " for reading." << std::endl;
        return false;
    }

    // 读取文件内容到字符串
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string fileContent = buffer.str();
    inFile.close();

    // 检查插入位置是否有效
    if (position < 0 || position > static_cast<int>(fileContent.size())) {
        std::cerr << "Invalid position for insertion." << std::endl;
        return false;
    }

    // 在特定位置插入文本
    std::string modifiedContent = fileContent.substr(0, position) + insertText + fileContent.substr(position);

    // 将修改后的内容写回文件
    std::ofstream outFile(filename, std::ios::out | std::ios::trunc | std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open " << filename << " for writing." << std::endl;
        return false;
    }
    outFile.write(modifiedContent.c_str(), modifiedContent.size());
    outFile.close();

    return true;
}

int main() {
    const std::string filename        = "example.txt";
    const std::string insertText_temp = "Inserted Text: ";
    int               position        = 10; // 插入位置

    if (insertText(filename, insertText_temp, position)) {
        std::cout << "Text inserted successfully." << std::endl;
    } else {
        std::cout << "Failed to insert text." << std::endl;
    }

    return 0;
}