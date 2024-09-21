#include <iostream>
#include <memory>

// 抽象类
class Shape {
public:
    // 纯虚函数
    virtual void draw() const = 0;

    // 虚析构函数
    virtual ~Shape() {
    }
};

// 派生类
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a circle." << std::endl;
    }
};

// 另一个派生类
class Rectangle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a rectangle." << std::endl;
    }
};

int main() {
    // 使用基类指针指向派生类对象
    std::unique_ptr<Shape> shape1(new Circle());
    std::unique_ptr<Shape> shape2(new Rectangle());

    shape1->draw(); // 调用Circle的draw函数
    shape2->draw(); // 调用Rectangle的draw函数

    return 0;
}