#include <iostream>

class MyClass {
public:
    // 普通构造函数
    MyClass(int x) : value(x) {
        // 执行一些初始化工作
    }

    // 委托构造函数
    MyClass() : MyClass(0) {
        // 可以在这里添加一些仅适用于这个构造函数的初始化工作
    }

    // 另一个委托构造函数
    MyClass(int x, std::string str) : MyClass(x) {
        // 委托给另一个构造函数
        this->str = std::move(str);
    }

private:
    int         value;
    std::string str;
};
