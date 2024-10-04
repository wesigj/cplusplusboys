#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 4, 5};
    auto             it  = std::find(vec.begin(), vec.end(), 3);

    // 在迭代器指向的位置之前插入元素
    if (it != vec.end()) {
        vec.insert(it, 3);
    } else {
        // 如果没找到要插入的位置，将元素插入到末尾
        vec.push_back(3);
    }

    for (int num : vec) { std::cout << num << " "; }
    std::cout << std::endl;

    return 0;
}