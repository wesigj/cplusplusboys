#include <iostream>

class Point {
private:
    int x, y;

public:
    Point(int x, int y) : x(x), y(y) {
    }

    // 重载输出运算符
    friend std::ostream &operator<<(std::ostream &os, const Point &p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

int main() {
    Point p(10, 20);
    std::cout << p << std::endl;
    return 0;
}