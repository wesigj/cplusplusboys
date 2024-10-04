#include <iostream>
#include <map>

int main() {
    std::map<std::string, int> mp = {
        {"apple", 1}, {"banana", 2}, {"cherry", 3}};

    // 使用迭代器遍历 map
    for (std::map<std::string, int>::iterator it = mp.begin(); it != mp.end();
         ++it) {
        std::cout << it->first << " : " << it->second
                  << std::endl; // 使用 -> 访问成员
    }

    // 使用 auto 关键字简化类型
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        std::cout << it->first << " : " << it->second << std::endl;
    }

    // 使用范围 for 循环 (C++11 及以上)
    for (const auto &pair : mp) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }

    return 0;
}