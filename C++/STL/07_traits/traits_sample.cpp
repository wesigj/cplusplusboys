#include <iostream>
#include <type_traits>

// 定义数据类型
enum Type { TYPE_1, TYPE_2, TYPE_3 };

// 自定义类型
class Foo {
public:
    static constexpr Type type = TYPE_1;
};
class Bar {
public:
    static constexpr Type type = TYPE_2;
};

// Traits模板类
template <typename T>
struct type_traits {
    static constexpr Type type = TYPE_3; // 默认特征值为TYPE_3
};

// 特化Foo类型
template <>
struct type_traits<Foo> {
    static constexpr Type type = Foo::type;
};

// 特化Bar类型
template <>
struct type_traits<Bar> {
    static constexpr Type type = Bar::type;
};

// 特化内置数据类型int
template <>
struct type_traits<int> {
    static constexpr Type type = TYPE_3;
};

// 统一的编码函数
template <typename T>
void decode(const T &data) {
    if (type_traits<T>::type == TYPE_1) {
        std::cout << "Handling TYPE_1" << std::endl;
    } else if (type_traits<T>::type == TYPE_2) {
        std::cout << "Handling TYPE_2" << std::endl;
    } else {
        std::cout << "Default handling" << std::endl;
    }
}

int main() {
    Foo foo;
    Bar bar;
    int myInt = 0;

    decode(foo);   // Handling TYPE_1
    decode(bar);   // Handling TYPE_2
    decode(myInt); // Default handling

    return 0;
}