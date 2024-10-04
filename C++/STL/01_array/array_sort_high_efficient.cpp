#include <iostream>
#include <array>
#include <algorithm>

int main() {
    // 定义并初始化 std::array
    std::array<int, 5> arr = {5, 3, 9, 1, 6};

    // 使用默认排序规则进行排序
    std::sort(arr.begin(), arr.end());

    // 打印排序后的结果
    for (int num : arr) { std::cout << num << " "; }
    std::cout << std::endl;

    // 使用自定义排序规则（例如：降序排序）
    std::sort(arr.begin(), arr.end(), std::greater<int>());

    // 打印自定义排序后的结果
    for (int num : arr) { std::cout << num << " "; }
    std::cout << std::endl;

    return 0;
}
