#include <iostream>

class Pointer {
private:
    int *ptr;

public:
    Pointer(int *p) :
        ptr(p) {
    }

    // 重载一元取地址运算符
    operator int *() const {
        return ptr;
    }
};

int main() {
    int     data = 42;
    Pointer ptr(&data);
    int    *pdata = ptr; // 使用重载的取地址运算符
    std::cout << "Value: " << *pdata << std::endl;

    return 0;
}