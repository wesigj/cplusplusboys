#include <iostream>
#include <list>

int main() {
    std::list<int> lst = {1, 2, 3, 4, 5};

    // 插入元素
    lst.push_front(0);
    lst.push_back(6);

    // 遍历列表
    for (int num : lst) { std::cout << num << " "; }
    std::cout << std::endl;

    // 删除元素
    lst.remove(3);

    // 再次遍历列表
    for (int num : lst) { std::cout << num << " "; }
    std::cout << std::endl;

    return 0;
}