#include <iostream>

class Number {
public:
    int value;

    Number(int val) :
        value(val) {
    }

    // 重载一元加运算符
    Number operator+() const {
        return *this; // 返回当前对象的一个副本
    }

    // 重载一元减运算符
    Number operator-() const {
        return Number(-value); // 返回当前对象的相反数
    }
};

int main() {
    Number num(10);
    Number pos = +num; // 调用一元加运算符
    Number neg = -num; // 调用一元减运算符

    std::cout << "Positive: " << pos.value << std::endl;
    std::cout << "Negative: " << neg.value << std::endl;

    return 0;
}