#include <iostream>

class Point {
public:
    int x, y;

    Point() :
        x(0), y(0) {
    }

    // 拷贝构造函数
    Point(const Point &other) :
        x(other.x), y(other.y) {
        std::cout << "Copy constructor called" << std::endl;
    }
};

int main() {
    Point p1;
    Point p2 = p1; // 调用拷贝构造函数
    return 0;
}