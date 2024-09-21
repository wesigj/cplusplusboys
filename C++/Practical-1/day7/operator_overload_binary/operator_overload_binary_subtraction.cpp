#include <iostream>

class Vector {
public:
    double x, y;

    Vector(double px, double py) :
        x(px), y(py) {
    }

    // 重载减法运算符（成员函数）
    Vector operator-(const Vector &rhs) const {
        return Vector(x - rhs.x, y - rhs.y);
    }
};

int main() {
    Vector v1(5.0, 3.0);
    Vector v2(1.0, 2.0);
    Vector v3 = v1 - v2; // 使用重载的减法运算符
    std::cout << "v3: (" << v3.x << ", " << v3.y << ")" << std::endl;
    return 0;
}