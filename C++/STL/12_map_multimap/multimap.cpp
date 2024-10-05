#include <map>
#include <iostream>

int main() {
    std::multimap<int, std::string> myMultiMap;

    // 插入键值对
    myMultiMap.insert({1, "Kimi"});
    myMultiMap.insert({2, "Moonshot AI"});
    myMultiMap.insert({1, "Another value"}); // 允许重复的键

    // 查找键值对
    auto range = myMultiMap.equal_range(1);
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    // 遍历multimap
    for (const auto &pair : myMultiMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}