#include <iostream>

class Point {
public:
    int x, y;

    Point(int px, int py) :
        x(px), y(py) {
    }

    // 重载加法运算符（成员函数）
    Point operator+(const Point &rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
};

int main() {
    Point p1(1, 2);
    Point p2(3, 4);
    Point p3 = p1 + p2; // 使用重载的加法运算符
    std::cout << "p3: (" << p3.x << ", " << p3.y << ")" << std::endl;
    return 0;
}