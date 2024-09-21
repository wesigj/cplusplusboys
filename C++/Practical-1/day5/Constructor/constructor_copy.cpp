#include <iostream>

class Point {
public:
    int x, y;

    // 参数化构造函数
    Point(int xValue, int yValue) :
        x(xValue), y(yValue) {
    }

    // 拷贝构造函数
    Point(const Point &other) :
        x(other.x), y(other.y) {
        std::cout << "Copy constructor called. (" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    Point point1(10, 20);
    Point point2 = point1; // 调用拷贝构造函数
    return 0;
}