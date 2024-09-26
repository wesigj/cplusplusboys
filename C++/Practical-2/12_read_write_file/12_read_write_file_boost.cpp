#include <boost/filesystem.hpp>

int main() {
    boost::filesystem::path filePath = "example.txt";
    boost::filesystem::create_directory("example_dir");
    boost::filesystem::copy_file("source.txt", "destination.txt");
    boost::filesystem::remove("example.txt");
}
