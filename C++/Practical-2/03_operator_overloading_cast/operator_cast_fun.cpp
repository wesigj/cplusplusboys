class Distance {
private:
    double meters;

public:
    Distance(double m) : meters(m) {
    }

    // 方法一：转换构造函数
    // Distance(const double &m) : meters(m) {
    // }

    // 方法二：重载类型转换运算符为double
    operator double() const {
        return meters;
    }
    // 方法一，方法二会冲突，注释其中一个即可
};

int main() {
    Distance d(10.5);
    double   length = d;    // 自动调用operator double()
    Distance d2     = 20.0; // 自动调用转换构造函数
    return 0;
}