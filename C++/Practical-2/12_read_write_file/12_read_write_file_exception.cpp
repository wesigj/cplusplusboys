#include <fstream>
#include <iostream>
#include <string>

void writeToFile(const std::string &filename, const std::string &content) {
    std::ofstream outFile(filename);
    if (!outFile) {
        throw std::runtime_error("Unable to open file for writing: "
                                 + filename);
    }

    outFile << content;
    if (outFile.fail()) {
        outFile.close();
        throw std::runtime_error("Failed to write to file: " + filename);
    }

    outFile.close();
}

void readFromFile(const std::string &filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Unable to open file for reading: "
                                 + filename);
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (inFile.fail()) {
            inFile.close();
            throw std::runtime_error("Failed to read from file: " + filename);
        }
        std::cout << line << std::endl;
    }

    inFile.close();
}

int main() {
    std::string filename = "example.txt";
    std::string content  = "Hello, World!\n";

    try {
        writeToFile(filename, content);
        readFromFile(filename);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        // 这里可以进行额外的错误处理，如用户提示、日志记录等
    }

    return 0;
}