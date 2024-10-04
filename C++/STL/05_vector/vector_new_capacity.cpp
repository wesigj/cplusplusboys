#include <vector>
#include <iostream>

int main() {
    std::vector<int> vec;

    // 添加元素
    for (int i = 0; i < 10; ++i) { vec.push_back(i); }

    // 显示当前容量
    std::cout << "Capacity: " << vec.capacity() << std::endl;

    // 添加更多元素以触发扩容
    for (int i = 10; i < 20; ++i) { vec.push_back(i); }

    // 显示扩容后的容量
    std::cout << "New Capacity: " << vec.capacity() << std::endl;

    return 0;
}