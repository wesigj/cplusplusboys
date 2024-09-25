class Base {
public:
    virtual void function() {
        // 基类的实现
    }
};

class Derived : public Base {
public:
    void function() override {
        // 派生类的实现
    }
};

class Derived : public Base {
public:
    void function() override {
        // 派生类的实现
    }
};

int main() {
    Base *b = new Derived();
    b->function(); // 调用 Derived::function()
    delete b;
}