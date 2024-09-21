#include <iostream>
#include <cmath> // 用于sqrt函数

// 定义一个结构体，用于表示点，并包含构造函数
struct Point {
    int x, y;

    // 构造函数
    Point(int x, int y) :
        x(x), y(y) {
    }

    // 方法：计算点到原点的距离
    double distanceToOrigin() const {
        return sqrt(x * x + y * y);
    }
};

int main() {
    Point p(3, 4);

    std::cout << "Point: (" << p.x << ", " << p.y << ")" << std::endl;
    std::cout << "Distance to origin: " << p.distanceToOrigin() << std::endl;

    return 0;
}