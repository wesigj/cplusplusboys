#include <filesystem>
namespace fs = std::filesystem;

int main() {
    fs::path filePath = "example.txt";
    fs::create_directory("example_dir");       // 创建目录
    fs::copy("source.txt", "destination.txt"); // 复制文件
    fs::remove("example.txt");                 // 删除文件
}
