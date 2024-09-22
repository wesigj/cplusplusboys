#include <iostream>
#include <iomanip>
#include <string>

class Point {
public:
    double x, y;
    Point(double x, double y) : x(x), y(y) {
    }
};

// 为Point类定义流操纵符
std::ostream &operator<<(std::ostream &os, const Point &p) {
    os << "(" << std::fixed << std::setprecision(2) << p.x << ", " << p.y
       << ")";
    return os;
}

int main() {
    Point p(3.14159, 2.71828);
    std::cout << "Point: " << p << std::endl;
    return 0;
}