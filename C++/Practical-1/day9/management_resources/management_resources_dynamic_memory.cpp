#include <iostream>

class AutoPtr {
private:
    int *ptr;

public:
    AutoPtr() :
        ptr(nullptr) {
    }
    explicit AutoPtr(int *p) :
        ptr(p) {
    }
    ~AutoPtr() {
        delete[] ptr;
    }

    // 禁止复制和赋值
    AutoPtr(const AutoPtr &)            = delete;
    AutoPtr &operator=(const AutoPtr &) = delete;

    // 支持移动语义
    AutoPtr(AutoPtr &&other) :
        ptr(other.ptr) {
        other.ptr = nullptr;
    }
    AutoPtr &operator=(AutoPtr &&other) {
        if (this != &other) {
            delete[] ptr;
            ptr       = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    int *get() const {
        return ptr;
    }
};

int main() {
    AutoPtr ap(new int[10]); // 分配数组
    // 不需要手动释放，析构函数会自动处理
    return 0;
}