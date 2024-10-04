#include <list>
#include <memory>

template <typename T>
class MyAllocator : public std::allocator<T> {
public:
    using typename std::allocator<T>::size_type;
    using typename std::allocator<T>::pointer;

    template <class U>
    struct rebind {
        typedef MyAllocator<U> other;
    };

    pointer allocate(size_type n, const void *hint = 0) {
        // 实现自定义的内存分配逻辑
        return static_cast<pointer>(malloc(n * sizeof(T)));
    }

    void deallocate(pointer p, size_type n) {
        // 实现自定义的内存释放逻辑
        free(p);
    }
};

int main() {
    std::list<int, MyAllocator<int>> my_list;
    my_list.push_back(1);
    my_list.push_back(2);
    my_list.push_back(3);

    return 0;
}