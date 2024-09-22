#include <iostream>

// 模板函数，用于获取两个值中的最大值
template <typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    int i = 5;
    int j = 10;
    std::cout << "Max of " << i << " and " << j << " is " << max(i, j) << std::endl;

    double f = 5.5;
    double g = 10.7;
    std::cout << "Max of " << f << " and " << g << " is " << max(f, g) << std::endl;

    return 0;
}

// #include <iostream>
// #include <algorithm> // 包含std::max

// int main() {
//     int i = 5;
//     int j = 10;
//     std::cout << "Max of " << i << " and " << j << " is " << std::max(i, j) << std::endl;

//     double f = 5.5;
//     double g = 10.7;
//     std::cout << "Max of " << f << " and " << g << " is " << std::max(f, g) << std::endl;

//     return 0;
// }