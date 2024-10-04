#include <array>

template <class T, size_t N>
class array {
public:
    // 类型定义
    typedef T                 value_type;
    typedef value_type       &reference;
    typedef const value_type &const_reference;
    typedef value_type       *pointer;
    typedef const value_type *const_pointer;
    typedef size_t            size_type;
    typedef std::ptrdiff_t    difference_type;

    // 成员函数
    reference       operator[](size_type i);
    const_reference operator[](size_type i) const;
    reference       at(size_type i);
    const_reference at(size_type i) const;
    pointer         data();
    const_pointer   data() const;
    void            fill(const T &value);
    void            swap(array &other);
    size_type       size() const;
    size_type       max_size() const;
    bool            empty() const;

    // 迭代器
    iterator               begin() noexcept;
    const_iterator         begin() const noexcept;
    iterator               end() noexcept;
    const_iterator         end() const noexcept;
    reverse_iterator       rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    reverse_iterator       rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_iterator         cbegin() const noexcept;
    const_iterator         cend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;
};

int main() {
    std::array<int, 0> array;

    std::array<int, 5> arr = {1, 2, 3, 4, 5};

    return 0;
}