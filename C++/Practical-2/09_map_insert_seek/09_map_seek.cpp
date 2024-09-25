#include <map>
#include <iostream>

int main() {
    std::map<int, std::string> dictionary = {
        {1, "one"}, {2, "two"}, {3, "three"}};

    // 查找元素
    int key = 2;
    if (dictionary.find(key) != dictionary.end()) {
        std::cout << "Found: " << dictionary[key] << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }
}