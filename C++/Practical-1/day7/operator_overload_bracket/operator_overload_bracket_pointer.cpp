#include <iostream>
#include <functional>

class FunctionWrapper {
public:
    // 存储一个可调用对象
    std::function<void()> func;

    // 构造函数
    FunctionWrapper(std::function<void()> f) :
        func(f) {
    }

    // 重载函数调用运算符
    void operator()() {
        func();
    }
};

int main() {
    // 创建一个lambda表达式
    auto lambda = []() { std::cout << "Hello, World!" << std::endl; };

    // 创建FunctionWrapper对象
    FunctionWrapper wrapper(lambda);

    // 使用重载的()运算符调用
    wrapper(); // 输出: Hello, World!

    return 0;
}