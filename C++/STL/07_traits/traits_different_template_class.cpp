#include <iostream>
#include <type_traits>

// 定义一个通用的 Traits 模板
template <typename T>
struct TypeTraits {
    // 默认实现，假设 T 不是特殊类型
    static void print(T t) {
        std::cout << "Generic type: " << t << std::endl;
    }
};

// 特化用于 int 类型的 Traits
template <>
struct TypeTraits<int> {
    static void print(int t) {
        std::cout << "Integer type: " << t << std::endl;
    }
};

// 特化用于 double 类型的 Traits
template <>
struct TypeTraits<double> {
    static void print(double t) {
        std::cout << "Double type: " << t << std::endl;
    }
};

// 特化用于 std::string 类型的 Traits
template <>
struct TypeTraits<std::string> {
    static void print(const std::string &t) {
        std::cout << "String type: " << t << std::endl;
    }
};