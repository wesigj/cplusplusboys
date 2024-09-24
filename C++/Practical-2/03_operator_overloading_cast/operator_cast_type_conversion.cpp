class Distance {
private:
    double meters;

public:
    Distance(double m) : meters(m) {
    }

    // 重载类型转换运算符为double
    operator double() const {
        return meters;
    }
};

int main() {
    Distance d(10.5);
    double   length = d; // 自动调用operator double()
    return 0;
}