#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> ageMap;

    // 插入元素
    ageMap["Alice"] = 30;
    ageMap["Bob"]   = 25;
    ageMap["Carol"] = 35;

    // 访问元素
    std::cout << "Alice's age: " << ageMap["Alice"] << std::endl;

    // 查找元素
    auto it = ageMap.find("Bob");
    if (it != ageMap.end()) {
        std::cout << "Bob's age: " << it->second << std::endl;
    }

    // 删除元素
    ageMap.erase("Carol");

    // 遍历 map
    for (const auto &pair : ageMap) {
        std::cout << pair.first << " is " << pair.second << " years old." << std::endl;
    }

    return 0;
}