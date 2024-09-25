class Shape {
public:
    virtual void draw() const { /* ... */
    }                           // 公有虚函数
    // ... 其他公有成员 ...
protected:
    // ... 保护成员 ...
};

class Circle : public Shape { // 公有继承
    double radius;

public:
    Circle(double r) : radius(r) { /* ... */
    }
    void draw() const override { /* ... */
    }                            // 覆盖基类的虚函数
    // ... 其他成员函数 ...
};

class Rectangle : public Shape { // 公有继承
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) { /* ... */
    }
    void draw() const override { /* ... */
    }                            // 覆盖基类的虚函数
    // ... 其他成员函数 ...
};