#include <iostream>
#include <vector>
#include <functional>
#include <typeinfo> // 需要包含这个头文件来使用 typeid

void exampleFunction(int &i)
{
    std::cout << "Type of i: " << typeid(i).name() << std::endl;
    // 注意：这里不需要使用 decltype，因为 i 已经是 int& 类型
}

int main()
{
    int a = 10;
    double b = 3.14;

    std::cout << "Type of a: " << typeid(a).name() << std::endl;
    // decltype(a) 是不必要的，因为 a 已经是一个 int 类型的变量

    auto x = a; // 使用 auto 推导 x 的类型为 int
    std::cout << "Type of x: " << typeid(x).name() << std::endl;

    // 移除 exampleFunction 的调用，因为它没有返回值
    // auto y = exampleFunction(a); // 这行是错误的

    // 代码中 auto y = exampleFunction(a); 这一行存在问题，因为 exampleFunction 函数没有返回值，所以尝试将一个没有返回值的函数调用赋值给变量 y 是不正确的。auto 关键字在这里会推导出 void 类型，因为 exampleFunction 的返回类型是 void。

    // decltype 推导 lambda 表达式的类型
    auto lambda = [](int i)
    { return i * 2; };
    std::cout << "Type of lambda: " << typeid(lambda).name() << std::endl;

    return 0;
}