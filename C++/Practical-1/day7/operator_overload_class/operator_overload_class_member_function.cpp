class MyClass {
public:
    // 成员函数形式的运算符重载
    MyClass operator+(const MyClass &rhs) const {
        MyClass result(*this); // 复制当前对象
        result += rhs;         // 调用赋值运算符
        return result;
    }

    // 赋值运算符
    MyClass &operator+=(const MyClass &rhs) {
        // 实现加法并更新当前对象
        return *this;
    }
};