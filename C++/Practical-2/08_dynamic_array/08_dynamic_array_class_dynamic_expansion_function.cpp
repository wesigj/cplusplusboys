#include <iostream>
#include <algorithm> // for std::copy
#include <cstddef>   // for std::size_t

template <typename T>
class DynamicArray {
private:
    T          *data;     // 指向动态分配数组的指针
    std::size_t size;     // 当前数组中元素的数量
    std::size_t capacity; // 数组分配的总容量

    void resize(std::size_t newCapacity) {
        T *newData = new T[newCapacity];
        std::copy(data, data + size, newData);
        delete[] data;
        data     = newData;
        capacity = newCapacity;
    }

public:
    // 构造函数
    explicit DynamicArray(std::size_t initialCapacity = 10) :
        data(new T[initialCapacity]), size(0), capacity(initialCapacity) {
    }

    // 析构函数
    ~DynamicArray() {
        delete[] data;
    }

    // 禁止拷贝构造函数
    DynamicArray(const DynamicArray &) = delete;

    // 禁止拷贝赋值运算符
    DynamicArray &operator=(const DynamicArray &) = delete;

    // 移动构造函数
    DynamicArray(DynamicArray &&other) noexcept :
        data(other.data), size(other.size), capacity(other.capacity) {
        other.data     = nullptr;
        other.size     = 0;
        other.capacity = 0;
    }

    // 移动赋值运算符
    DynamicArray &operator=(DynamicArray &&other) noexcept {
        if (this != &other) {
            delete[] data;
            data           = other.data;
            size           = other.size;
            capacity       = other.capacity;
            other.data     = nullptr;
            other.size     = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // 添加元素
    void pushBack(const T &value) {
        if (size == capacity) {
            std::size_t newCapacity = capacity == 0 ? 1 : (capacity * 2);
            resize(newCapacity);
        }
        data[size++] = value;
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
    DynamicArray<int> arr;

    for (int i = 0; i < 15; ++i) { arr.pushBack(i); }

    for (std::size_t i = 0; i < arr.getSize(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}