#include <iostream>
#include <list>

int main() {
    std::list<int> lst = {1, 2, 3, 4, 5};

    // 使用迭代器遍历 list
    for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 使用 auto 关键字简化类型
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 使用范围 for 循环 (C++11 及以上)
    for (auto &value : lst) { std::cout << value << " "; }
    std::cout << std::endl;

    return 0;
}