#include <iostream>
#include <vector>
#include <algorithm> // For std::copy

// 辅助函数，用于合并两个已排序的子数组
template <typename T>
void merge(T *begin, T *mid, T *end, T *temp) {
    int i = 0, j = 0, k = 0;
    while (begin + i < mid && mid + j < end) {
        if (*(begin + i) <= *(mid + j)) {
            temp[k++] = *(begin + i++);
        } else {
            temp[k++] = *(mid + j++);
        }
    }
    while (begin + i < mid) {
        temp[k++] = *(begin + i++);
    }
    while (mid + j < end) {
        temp[k++] = *(mid + j++);
    }
    std::copy(temp, temp + k, begin);
}

// 归并排序的递归函数
template <typename T>
void mergeSort(T *begin, T *end, T *temp) {
    if (end - begin <= 1) {
        return;
    }
    T *mid = begin + (end - begin) / 2;
    mergeSort(begin, mid, temp);
    mergeSort(mid, end, temp);
    merge(begin, mid, end, temp);
}

// 归并排序的模板类
template <typename T>
class MergeSorter {
public:
    void sort(T *array, int size) {
        T *temp = new T[size];
        mergeSort(array, array + size, temp);
        delete[] temp;
    }
};

int main() {
    std::vector<int> vec = {5, 3, 8, 4, 2, 3, 1};
    MergeSorter<int> sorter;
    sorter.sort(vec.data(), vec.size());
    std::cout << "Sorted vector: ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    MergeSorter<std::string> string_sorter;

    std::vector<std::string> vecStr = {"z", "a", "k", "m", "a", "z"};
    string_sorter.sort(vecStr.data(), vecStr.size());
    std::cout << "Sorted vector: ";
    for (const auto &str : vecStr) {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    return 0;
}
