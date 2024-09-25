#include <iostream>
#include <algorithm> // for std::copy
#include <cstddef>   // for std::size_t

template <typename T>
class DynamicArray {
private:
    T          *data; // 指向动态分配数组的指针
    std::size_t size; // 数组中元素的数量

public:
    // 构造函数
    explicit DynamicArray(std::size_t size) : data(new T[size]), size(size) {
    }

    // 析构函数
    ~DynamicArray() {
        delete[] data;
    }

    // 拷贝构造函数
    DynamicArray(const DynamicArray &other) :
        data(new T[other.size]), size(other.size) {
        std::copy(other.data, other.data + other.size, data);
    }

    // 移动构造函数
    DynamicArray(DynamicArray &&other) noexcept :
        data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    // 拷贝赋值运算符
    DynamicArray &operator=(const DynamicArray &other) {
        if (this != &other) {
            delete[] data;
            data = new T[other.size];
            size = other.size;
            std::copy(other.data, other.data + other.size, data);
        }
        return *this;
    }

    // 移动赋值运算符
    DynamicArray &operator=(DynamicArray &&other) noexcept {
        if (this != &other) {
            delete[] data;
            data       = other.data;
            size       = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // 获取数组的大小
    std::size_t getSize() const {
        return size;
    }

    // 获取指定索引的元素
    T &operator[](std::size_t index) {
        return data[index];
    }

    // 获取指定索引的元素（const版本）
    const T &operator[](std::size_t index) const {
        return data[index];
    }
};

int main() {
    DynamicArray<int> arr(5); // 创建一个大小为5的动态数组

    for (std::size_t i = 0; i < arr.getSize(); ++i) { arr[i] = i * i; }

    for (std::size_t i = 0; i < arr.getSize(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}