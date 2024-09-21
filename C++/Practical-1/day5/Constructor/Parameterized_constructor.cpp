#include <iostream>

class Point {
public:
    int x, y;

    // 参数化构造函数
    Point(int xValue, int yValue) :
        x(xValue), y(yValue) {
        std::cout << "Constructor called. (" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    Point point1(10, 20);
    return 0;
}