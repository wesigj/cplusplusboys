#include <iostream>

// 自定义流操纵符，用于输出带边框的值
struct bordered {
    const std::string value;

    bordered(const std::string &value) : value(value) {
    }

    friend std::ostream &operator<<(std::ostream &os, const bordered &obj) {
        os << "【" << obj.value << "】";
        return os;
    }
};

int main() {
    std::cout << bordered("Hello, World!") << std::endl; // 使用自定义流操纵符
    return 0;
}