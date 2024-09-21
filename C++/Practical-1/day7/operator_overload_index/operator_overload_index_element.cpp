#include <iostream>
#include <vector>
#include <stdexcept> // 用于标准异常

class IntArray {
private:
    std::vector<int> data;

public:
    // 带参数的下标运算符，用于修改元素
    int &operator[](size_t index) {
        // 简单的边界检查
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // 带参数的下标运算符，用于读取元素
    const int &operator[](size_t index) const {
        // 简单的边界检查
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // 添加元素的方法
    void push_back(int value) {
        data.push_back(value);
    }
};

int main() {
    IntArray arr;
    arr.push_back(10);
    arr.push_back(20);

    std::cout << "Element at index 0: " << arr[0] << std::endl; // 读取元素
    std::cout << "Element at index 1: " << arr[1] << std::endl;

    // 修改元素
    arr[0] = 30;

    std::cout << "Element at index 0 after modification: " << arr[0] << std::endl;

    return 0;
}