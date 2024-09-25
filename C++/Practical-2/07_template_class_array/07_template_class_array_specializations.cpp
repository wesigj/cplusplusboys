#include <iostream>

template <typename T>
class Array {
private:
    T     *data;
    size_t size;

public:
    // 构造函数
    Array(size_t size) : size(size), data(new T[size]) {
    }

    // 析构函数
    ~Array() {
        delete[] data;
    }

    // 获取元素
    T &operator[](size_t index) {
        return data[index];
    }

    // 获取元素（const版本）
    const T &operator[](size_t index) const {
        return data[index];
    }

    // 获取数组大小
    size_t getSize() const {
        return size;
    }

    // 其他通用操作...
};

// 特化版本
template <>
class Array<int> {
private:
    int   *data;
    size_t size;

public:
    // 构造函数
    Array(size_t size) : size(size), data(new int[size]) {
    }

    // 析构函数
    ~Array() {
        delete[] data;
    }

    // 获取元素
    int &operator[](size_t index) {
        return data[index];
    }

    // 获取元素（const版本）
    const int &operator[](size_t index) const {
        return data[index];
    }

    // 获取数组大小
    size_t getSize() const {
        return size;
    }

    // 特化操作：计算数组中所有元素的总和
    int sum() const {
        int total = 0;
        for (size_t i = 0; i < size; ++i) { total += data[i]; }
        return total;
    }
};

int main() {
    // 使用特化版本
    Array<int> intArray(5);
    for (size_t i = 0; i < intArray.getSize(); ++i) {
        intArray[i] = static_cast<int>(i);
    }

    std::cout << "Sum of elements: " << intArray.sum() << std::endl;

    // 使用通用版本
    Array<double> doubleArray(5);
    for (size_t i = 0; i < doubleArray.getSize(); ++i) {
        doubleArray[i] = static_cast<double>(i) * 1.5;
    }

    // doubleArray没有sum函数
    // std::cout << "Sum of elements: " << doubleArray.sum() << std::endl; //
    // 这将导致编译错误

    return 0;
}