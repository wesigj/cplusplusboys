#include <map>
#include <iostream>

// 自定义比较函数
struct CustomCompare {
    bool operator()(const int &lhs, const int &rhs) const {
        return lhs > rhs; // 降序排列
    }
};

int main() {
    std::map<int, std::string, CustomCompare> myMap;

    // 插入键值对
    myMap.insert({1, "Kimi"});
    myMap.insert({2, "Moonshot AI"});

    // 遍历map
    for (const auto &pair : myMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}