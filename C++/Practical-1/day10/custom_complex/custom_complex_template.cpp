#include <iostream>
#include <iomanip>

// 前向声明，以便在下面的 operator<< 中使用 Centered
template <typename T>
class Centered;

// 重载 operator<<
template <typename T>
std::ostream &operator<<(std::ostream &os, const Centered<T> &obj) {
    os << std::setw(20) << std::setfill('*') << std::internal << obj.value;
    return os;
}

// 自定义流操纵符模板，用于输出居中的值
template <typename T>
class Centered {
public:
    T value;

    Centered(const T &val) : value(val) {
    }
};

// 创建一个辅助函数来简化流操纵符的调用
template <typename T>
Centered<T> centered(const T &value) {
    return Centered<T>(value);
}

int main() {
    int number = 42;
    std::cout << centered(number) << std::endl;
    double pi = 3.14159;
    std::cout << centered(pi) << std::endl;
    return 0;
}