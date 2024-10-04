#include <iostream>
#include <string>
#include <type_traits>

// 通用类型转换 Traits
template <typename Target, typename Source>
struct Converter {
    static Target convert(const Source &source) {
        // 默认实现，使用 static_cast
        return static_cast<Target>(source);
    }
};

// 特化为 string 到 int 的转换
template <>
struct Converter<int, std::string> {
    static int convert(const std::string &source) {
        return std::stoi(source);
    }
};

// 特化为 int 到 string 的转换
template <>
struct Converter<std::string, int> {
    static std::string convert(int source) {
        return std::to_string(source);
    }
};

// 特化为 double 到 int 的转换
template <>
struct Converter<int, double> {
    static int convert(double source) {
        return static_cast<int>(source);
    }
};

// 特化为自定义类型之间的转换（示例）
struct Vector2D {
    double x, y;
};

Vector2D toVector2D(int x, int y) {
    return {x, y};
}

template <>
struct Converter<Vector2D, int> {
    static Vector2D convert(int source) {
        return toVector2D(source, source);
    }
};

// 使用示例
int main() {
    int         num    = Converter<int, std::string>::convert("123");
    std::string str    = Converter<std::string, int>::convert(45);
    int         newNum = Converter<int, double>::convert(98.6);
    Vector2D    vec    = Converter<Vector2D, int>::convert(10);

    std::cout << "num: " << num << std::endl;
    std::cout << "str: " << str << std::endl;
    std::cout << "newNum: " << newNum << std::endl;
    std::cout << "Vector2D: {" << vec.x << ", " << vec.y << "}" << std::endl;

    return 0;
}