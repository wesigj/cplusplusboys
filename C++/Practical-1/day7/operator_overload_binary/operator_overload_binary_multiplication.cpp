#include <iostream>

class Matrix {
public:
    double m[2][2];

    Matrix(double m11, double m12, double m21, double m22) {
        m[0][0] = m11;
        m[0][1] = m12;
        m[1][0] = m21;
        m[1][1] = m22;
    }

    // 重载乘法运算符（成员函数，与标量）
    Matrix operator*(double scalar) const {
        return Matrix(m[0][0] * scalar, m[0][1] * scalar,
                      m[1][0] * scalar, m[1][1] * scalar);
    }
};

int main() {
    Matrix mat(1.0, 2.0, 3.0, 4.0);
    Matrix result = mat * 2.0; // 使用重载的乘法运算符
    std::cout << "Matrix after multiplication: "
              << result.m[0][0] << ", " << result.m[0][1] << "; "
              << result.m[1][0] << ", " << result.m[1][1] << std::endl;
    return 0;
}