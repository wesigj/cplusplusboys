#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 使用迭代器遍历 vector
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " "; // 访问迭代器指向的元素
    }
    std::cout << std::endl;

    // 使用 auto 关键字简化类型
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 使用范围 for 循环 (C++11 及以上)
    for (auto &value : vec) { std::cout << value << " "; }
    std::cout << std::endl;

    return 0;
}