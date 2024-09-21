#include <iostream>

class Point {
public:
    int x, y;

    // 默认构造函数
    Point() :
        x(0), y(0) {
        std::cout << "Default constructor called. (" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    Point point1;
    return 0;
}