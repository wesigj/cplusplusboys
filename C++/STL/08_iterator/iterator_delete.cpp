#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 删除元素 3
    auto it = std::find(vec.begin(), vec.end(), 3);
    if (it != vec.end()) { vec.erase(it); }

    for (int num : vec) { std::cout << num << " "; }
    std::cout << std::endl;

    // 删除区间 [2, 4)
    vec.erase(vec.begin() + 1, vec.begin() + 3);

    for (int num : vec) { std::cout << num << " "; }
    std::cout << std::endl;

    return 0;
}