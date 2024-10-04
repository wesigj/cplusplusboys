#include <iostream>
#include <array>
#include <algorithm>

struct CustomCompare {
    bool operator()(int lhs, int rhs) const {
        // 自定义排序逻辑，例如：根据绝对值排序
        return std::abs(lhs) < std::abs(rhs);
    }
};

int main() {
    std::array<int, 5> arr = {-5, 3, -9, 1, 6};

    // 使用自定义比较函数进行排序
    std::sort(arr.begin(), arr.end(), CustomCompare());

    // 打印排序后的结果
    for (int num : arr) { std::cout << num << " "; }
    std::cout << std::endl;

    return 0;
}