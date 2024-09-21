#include <iostream>

// 定义一个结构体，用于表示点
struct Point {
    int x;
    int y;
};

int main() {
    // 创建一个点
    Point p;
    p.x = 10;
    p.y = 20;

    // 输出点的坐标
    std::cout << "Point: (" << p.x << ", " << p.y << ")" << std::endl;

    // 创建另一个点
    Point q = {5, 15}; // 列表初始化

    // 修改并输出点的坐标
    std::cout << "Point: (" << q.x << ", " << q.y << ")" << std::endl;

    return 0;
}