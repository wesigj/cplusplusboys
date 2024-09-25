#include <iostream>

class Shape {
public:
    // 纯虚函数，用于绘制图形
    virtual void draw() const = 0;

    // 虚函数，用于计算图形的面积
    virtual double area() const {
        return 0.0; // 默认实现，对于不关心面积的图形可以返回0
    }

    // 虚析构函数，确保派生类的析构函数被正确调用
    virtual ~Shape() {
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {
    }

    void draw() const override {
        std::cout << "Drawing a circle with radius: " << radius << std::endl;
    }

    double area() const override {
        return 3.14159 * radius * radius;
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {
    }

    void draw() const override {
        std::cout << "Drawing a rectangle with width: " << width
                  << " and height: " << height << std::endl;
    }

    double area() const override {
        return width * height;
    }
};

class Triangle : public Shape {
private:
    double base;
    double height;

public:
    Triangle(double b, double h) : base(b), height(h) {
    }

    void draw() const override {
        std::cout << "Drawing a triangle with base: " << base
                  << " and height: " << height << std::endl;
    }

    double area() const override {
        return 0.5 * base * height;
    }
};

int main() {
    // 创建一个 Shape 类型的指针数组
    const int numShapes = 3;
    Shape    *shapes[numShapes];
    shapes[0] = new Circle(5.0);
    shapes[1] = new Rectangle(4.0, 5.0);
    shapes[2] = new Triangle(3.0, 4.0);

    // 绘制所有图形
    for (int i = 0; i < numShapes; ++i) {
        shapes[i]->draw();
        std::cout << "Area: " << shapes[i]->area() << std::endl;
    }

    // 清理资源
    for (int i = 0; i < numShapes; ++i) { delete shapes[i]; }

    return 0;
}