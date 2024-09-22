#include <iostream>
#include <fstream>

class File {
private:
    std::fstream file;

public:
    File(const std::string &filename, std::ios_base::openmode mode) {
        file.open(filename, mode);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file");
        }
    }

    ~File() {
        if (file.is_open()) {
            file.close();
        }
    }

    // 禁止复制和赋值
    File(const File &)            = delete;
    File &operator=(const File &) = delete;

    // 支持移动语义
    File(File &&other) :
        file(std::move(other.file)) {
    }
    File &operator=(File &&other) {
        file = std::move(other.file);
        return *this;
    }
};

int main() {
    try {
        File f("example.txt", std::ios::in);
        // 使用文件
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
    // 文件在f的析构函数中自动关闭
    return 0;
}