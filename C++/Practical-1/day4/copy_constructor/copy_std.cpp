#include <iostream>
#include <algorithm>
#include <vector>

class Point {
public:
    int x, y;

    Point() :
        x(0), y(0) {
        // 默认构造函数
    }

    // 拷贝构造函数
    Point(const Point &other) :
        x(other.x), y(other.y) {
        std::cout << "Copy constructor called" << std::endl;
    }
};

int main() {
    std::vector<Point> vec1;
    vec1.emplace_back(1, 2); // 使用emplace_back避免不必要的拷贝
    vec1.emplace_back(3, 4);

    // 创建一个新的向量，包含vec1中所有元素的副本
    std::vector<Point> vec2(vec1.begin(), vec1.end());
    return 0;
}