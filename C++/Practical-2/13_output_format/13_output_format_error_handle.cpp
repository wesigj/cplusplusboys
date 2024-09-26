#include <iostream>
#include <fstream>
#include <stdexcept>

int main() {
    std::ofstream outFile("example.txt");

    if (!outFile) {
        throw std::runtime_error("Unable to open file for writing.");
    }

    outFile << "Hello, File!" << std::endl;

    if (outFile.fail()) {
        throw std::runtime_error("Failed to write to file.");
    }

    outFile.close();

    return 0;
}