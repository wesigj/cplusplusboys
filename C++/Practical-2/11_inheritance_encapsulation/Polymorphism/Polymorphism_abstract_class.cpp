#include <iostream>

class Shape {
public:
    virtual void draw() const = 0; // 纯虚函数
    virtual ~Shape() {
    }
};

class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a circle" << std::endl;
    }
};

class Rectangle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a rectangle" << std::endl;
    }
};

int main() {
    Shape *shape1 = new Circle();
    shape1->draw(); // 输出 "Drawing a circle"

    Shape *shape2 = new Rectangle();
    shape2->draw(); // 输出 "Drawing a rectangle"

    delete shape1;
    delete shape2;
    return 0;
}