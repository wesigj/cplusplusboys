#include <array>
#include <algorithm>
#include <iostream>

int main() {
    std::array<int, 4> arr = {1, 2, 3, 4};

    // 使用STL算法排序
    std::sort(arr.begin(), arr.end());

    // 打印数组内容
    for (int i : arr) { std::cout << i << ' '; }
    std::cout << '\n';

    return 0;
}