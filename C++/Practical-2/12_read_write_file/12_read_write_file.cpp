#include <fstream>
#include <string>
#include <iostream>

void writeToFile(const std::string &filename, const std::string &content) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Unable to create file " << filename << std::endl;
        return;
    }

    outFile << content;
    outFile.close();
}

void readFromFile(const std::string &filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) { std::cout << line << std::endl; }

    inFile.close();
}

int main() {
    std::string filename = "example.txt";
    std::string content  = "Hello, World!\nThis is a test file.\n";

    writeToFile(filename, content);
    readFromFile(filename);

    return 0;
}