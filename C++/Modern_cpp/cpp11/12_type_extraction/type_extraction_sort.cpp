#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>   // std::sort
#include <type_traits> // std::is_arithmetic

template <typename T>
void sortContainer(T &container) {
    // 使用类型特征来判断容器中的数据类型
    if constexpr (std::is_arithmetic_v<typename T::value_type>) {
        // 如果容器中的数据类型是算术类型，使用标准库的 sort 函数
        std::sort(container.begin(), container.end());
    } else {
        // 对于非算术类型，使用自定义的排序规则
        std::sort(container.begin(), container.end(),
                  [](const typename T::value_type &a,
                     const typename T::value_type &b) { return a < b; });
    }
}

int main() {
    // 整数类型的 vector
    std::vector<int> intVec = {5, 3, 9, 1, 6};
    sortContainer(intVec);
    for (int num : intVec) { std::cout << num << " "; }
    std::cout << std::endl;

    // 字符串类型的 vector
    std::vector<std::string> stringVec = {"banana", "apple", "cherry"};
    sortContainer(stringVec);
    for (const auto &str : stringVec) { std::cout << str << " "; }
    std::cout << std::endl;

    return 0;
}