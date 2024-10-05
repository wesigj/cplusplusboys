#include <map>
#include <iostream>

int main() {
    std::map<int, std::string> myMap;

    // 插入键值对
    myMap.insert({1, "Kimi"});
    myMap.insert({2, "Moonshot AI"});

    // 查找键值对
    if (myMap.find(1) != myMap.end()) {
        std::cout << "Found: " << myMap[1] << std::endl;
    }

    // 遍历map
    for (const auto &pair : myMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}