#include <iostream>
#include <iomanip>

// 自定义流操纵符结构，用于输出带边框并右对齐的浮点数
struct BorderedRightAligned {
    double value;

    BorderedRightAligned(double val) : value(val) {
    }
};

// 重载 operator<<
std::ostream &operator<<(std::ostream &os, const BorderedRightAligned &obj) {
    os << std::fixed << std::setprecision(2);
    os << "[" << std::right << std::setw(10) << obj.value << "]";
    return os;
}

// 创建一个辅助函数，用于创建 BorderedRightAligned 对象
inline BorderedRightAligned bordered_right_aligned(double value) {
    return BorderedRightAligned(value);
}

int main() {
    double pi = 3.14159;
    std::cout << bordered_right_aligned(pi) << std::endl; // 正确的调用
    return 0;
}