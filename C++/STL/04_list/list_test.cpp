#include <iostream>
#include <list>

int main() {
    std::list<int> lst = {1, 2, 3, 4, 5, 3, 2};
    for (auto it : lst) { std::cout << it; }
    std::cout << std::endl;

    lst.remove(3); // 移除所有值为3的元素
    for (auto it : lst) { std::cout << it; }

    std::cout << std::endl;

    return 0;
}