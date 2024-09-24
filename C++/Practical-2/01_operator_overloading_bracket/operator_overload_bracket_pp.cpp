#include <iostream>

class Counter {
private:
    int count;

public:
    // 构造函数
    Counter() : count(0) {
    }

    // 重载()运算符
    int operator()() {
        return ++count;
    }
};

int main() {
    Counter myCounter;
    std::cout << myCounter() << std::endl; // 输出 1
    std::cout << myCounter() << std::endl; // 输出 2
    std::cout << myCounter() << std::endl; // 输出 3
    return 0;
}