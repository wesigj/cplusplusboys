#include <iostream>

// 普通模板定义
template <typename T>
void print(T value) {
    std::cout << "Generic template: " << value << std::endl;
}

// 函数模板特化，针对 int 类型
template <>
void print<int>(int value) {
    std::cout << "Specialized for int: " << value << std::endl;
}

// 函数模板特化，针对 const char* 类型
template <>
void print<const char *>(const char *value) {
    std::cout << "Specialized for const char*: " << value << std::endl;
}

// 函数模板特化，针对 char* 类型
template <>
void print<char *>(char *value) {
    std::cout << "Specialized for char*: " << value << std::endl;
}

int main() {
    print(3.14);    // 输出: Generic template: 3.14
    print(42);      // 输出: Specialized for int: 42
    print("Hello"); // 输出: Specialized for const char*: Hello

    char greeting[] = "Hi";
    print(greeting); // 输出: Specialized for char*: Hi

    return 0;
}