#include <iostream>
#include <iterator>
#include <cstddef>

// 自定义容器
class Array {
    int   *data_;
    size_t size_;

public:
    Array(size_t size) : data_(new int[size]), size_(size) {
    }
    ~Array() {
        delete[] data_;
    }

    // 元素访问
    int &operator[](size_t index) {
        return data_[index];
    }
    const int &operator[](size_t index) const {
        return data_[index];
    }

    // 迭代器支持
    class iterator {
        int *ptr_;

    public:
        iterator(int *ptr) : ptr_(ptr) {
        }
        iterator &operator++() {
            ++ptr_;
            return *this;
        }
        int &operator*() const {
            return *ptr_;
        }
        bool operator==(const iterator &other) const {
            return ptr_ == other.ptr_;
        }
        bool operator!=(const iterator &other) const {
            return ptr_ != other.ptr_;
        }

        // 用于 std::iterator_traits
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = int;
        using difference_type   = std::ptrdiff_t;
        using pointer           = int *;
        using reference         = int &;
    };

    iterator begin() const {
        return iterator(data_);
    }
    iterator end() const {
        return iterator(data_ + size_);
    }
};

int main() {
    Array arr(5);

    // 使用自定义迭代器
    for (Array::iterator it = arr.begin(); it != arr.end(); ++it) {
        *it = 1; // 设置所有元素为 1
    }

    // 验证结果
    for (Array::iterator it = arr.begin(); it != arr.end(); ++it) {
        std::cout << *it << " "; // 应该输出 "1 1 1 1 1"
    }
    std::cout << std::endl;

    return 0;
}