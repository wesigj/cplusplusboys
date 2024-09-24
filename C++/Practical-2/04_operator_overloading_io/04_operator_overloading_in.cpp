#include <iostream>

class Point {
private:
    int x, y;

public:
    Point() : x(0), y(0) {
    }

    // 重载输入运算符
    friend std::istream &operator>>(std::istream &is, Point &p) {
        is >> p.x >> p.y;
        return is;
    }

    // 重载输出运算符
    friend std::ostream &operator<<(std::ostream &os, const Point &p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

int main() {
    Point p;
    std::cout << "Enter coordinates of the point (x y): ";
    std::cin >> p;
    std::cout << "You entered: " << p << std::endl;
    return 0;
}