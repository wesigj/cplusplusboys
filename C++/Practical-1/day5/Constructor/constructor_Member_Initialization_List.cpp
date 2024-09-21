#include <iostream>

class Point {
public:
    int x, y;

    // 使用成员初始化列表
    Point(int xValue, int yValue) :
        x(xValue), y(yValue) {
        std::cout << "Constructor called. (" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    Point point1(10, 20);
    return 0;
}