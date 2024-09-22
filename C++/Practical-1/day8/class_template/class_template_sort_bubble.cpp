#include <iostream>
#include <vector>
#include <functional> // For std::less

// 模板函数，用于交换元素
template <typename T>
void swap(T &a, T &b) {
    T temp = a;
    a      = b;
    b      = temp;
}

// 模板函数，实现冒泡排序
template <typename T, typename Compare = std::less<>>
void bubbleSort(T &arr, Compare comp = Compare()) {
    bool swapped = true;
    int  n       = arr.size();
    while (swapped) {
        swapped = false;
        for (int i = 1; i < n; ++i) {
            if (comp(arr[i - 1], arr[i])) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        --n; // 最大元素已经排在正确的位置
    }
}

int main() {
    std::vector<int> vec = {5, 3, 8, 4, 2};
    bubbleSort(vec);
    std::cout << "Sorted vector: ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::vector<std::string> vecStr = {"z", "a", "k", "m"};
    bubbleSort(vecStr, std::greater<>());
    std::cout << "Sorted vector: ";
    for (const auto &str : vecStr) {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    return 0;
}