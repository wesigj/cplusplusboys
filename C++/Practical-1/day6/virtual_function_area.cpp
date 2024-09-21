#include <iostream>

// 基类：形状
class Shape {
public:
    virtual double area() const = 0; // 纯虚函数
    virtual ~Shape() {
    } // 虚析构函数
};

// 派生类：圆形
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) :
        radius(r) {
    }

    double area() const override {
        return 3.14159 * radius * radius;
    }
};

// 派生类：矩形
class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) :
        width(w), height(h) {
    }

    double area() const override {
        return width * height;
    }
};

int main() {
    const double pi = 3.14159;
    Shape       *shape;

    Circle circle(5); // 半径为5的圆
    shape = &circle;
    std::cout << "Circle area: " << shape->area() << std::endl; // 输出圆形的面积

    Rectangle rectangle(4, 6); // 宽4高6的矩形
    shape = &rectangle;
    std::cout << "Rectangle area: " << shape->area() << std::endl; // 输出矩形的面积

    return 0;
}