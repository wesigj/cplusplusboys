#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>

// 二分搜索的模板函数
template <typename RandomAccessIterator, typename T>
typename std::enable_if_t<
    std::is_base_of<std::random_access_iterator_tag,
                    typename std::iterator_traits<
                        RandomAccessIterator>::iterator_category>::value,
    RandomAccessIterator>
binary_search_my(RandomAccessIterator first, RandomAccessIterator last,
                 const T &value) {
    // 当前搜索区间的长度
    auto len = std::distance(first, last);

    // 如果区间为空，返回末尾迭代器
    if (len == 0) { return last; }

    while (len > 0) {
        // 计算当前搜索区间的中间位置
        auto half = len / 2;
        auto mid  = first + half;

        if (*mid < value) {
            // 如果中间的元素小于 value，忽略左半边
            first = mid + 1;
            len -= half + 1;
        } else if (*mid > value) {
            // 如果中间的元素大于 value，忽略右半边
            len = half;
        } else {
            // 如果中间的元素等于 value，返回当前迭代器
            return mid;
        }
    }

    // 如果没有找到，返回末尾迭代器
    return last;
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // 搜索 5
    auto it = binary_search_my(vec.begin(), vec.end(), 5);
    if (it != vec.end()) {
        std::cout << "Element 5 found at position: "
                  << std::distance(vec.begin(), it) << std::endl;
    } else {
        std::cout << "Element 5 not found." << std::endl;
    }

    // 搜索 10
    it = binary_search_my(vec.begin(), vec.end(), 10);
    if (it != vec.end()) {
        std::cout << "Element 10 found at position: "
                  << std::distance(vec.begin(), it) << std::endl;
    } else {
        std::cout << "Element 10 not found." << std::endl;
    }

    return 0;
}