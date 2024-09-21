class MyClass {
public:
    // 友元函数声明
    friend MyClass operator+(const MyClass &lhs, const MyClass &rhs);

    // 其他成员函数和数据
};

// 友元函数定义
MyClass operator+(const MyClass &lhs, const MyClass &rhs) {
    MyClass result(lhs);   // 复制左侧操作数
    result = result + rhs; // 调用赋值运算符
    return result;
}