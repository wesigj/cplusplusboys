#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <list>

// 模板类，用于实现排序算法
template <typename T>
class Sorter {
public:
    // 模板函数，执行排序
    void sort(T &collection) {
        std::sort(std::begin(collection), std::end(collection));
    }
};

// 模板函数，打印容器元素
template <typename T>
void print(const T &collection) {
    for (const auto &item : collection) { std::cout << item << " "; }
    std::cout << std::endl;
}

int main() {
    // 示例：使用 std::vector<int>
    std::vector<int>         vec = {4, 1, 3, 5, 2};
    Sorter<std::vector<int>> intSorter;
    intSorter.sort(vec);
    print(vec); // 输出: 1 2 3 4 5

    // 示例：使用 std::vector<double>
    std::vector<double>         vecDouble = {4.5, 1.2, 3.7, 5.1, 2.3};
    Sorter<std::vector<double>> doubleSorter;
    doubleSorter.sort(vecDouble);
    print(vecDouble); // 输出: 1.2 2.3 3.7 4.5 5.1

    // 示例：使用 std::list<int>
    std::list<int>         lst = {4, 1, 3, 5, 2};
    Sorter<std::list<int>> listSorter;
    listSorter.sort(lst);
    print(lst.begin(), lst.end()); // 输出: 1 2 3 4 5

    return 0;
}

// 提供 print 特化版本，用于 std::list
template <typename T>
void print(const T &collection, const T &end) {
    for (auto it = collection; it != end; ++it) { std::cout << *it << " "; }
    std::cout << std::endl;
}