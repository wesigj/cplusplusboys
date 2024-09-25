#include <iostream>

template <typename T>
class Base {
public:
    virtual void display() const = 0; // 纯虚函数
    virtual ~Base() {
    } // 虚析构函数以确保派生类对象的正确清理
};

template <typename T>
class Derived : public Base<T> {
public:
    void display() const override {
        std::cout << "Displaying Derived class with type: " << typeid(T).name()
                  << std::endl;
    }
};

// 特化基类模板
template <>
class Base<int> {
public:
    virtual void display() const = 0;
    virtual ~Base() {
    }
};

// 特化派生类模板
class IntSpecificClass : public Base<int> {
public:
    void display() const override {
        std::cout << "Int specific display" << std::endl;
    }
};

int main() {
    Base<int> *b = new IntSpecificClass();
    b->display(); // 输出 "Int specific display"
    delete b;

    Base<double> *d = new Derived<double>();
    d->display(); // 输出 "Displaying Derived class with type: double"
    delete d;

    return 0;
}