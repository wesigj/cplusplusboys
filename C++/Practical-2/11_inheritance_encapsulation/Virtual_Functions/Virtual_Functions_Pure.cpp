class Base {
public:
    virtual void pureFunction() = 0;
};

// class Base {
// public:
//     virtual void interfaceFunction() = 0;
//     virtual void defaultFunction() {
//         // 默认实现
//     }
// };
class Derived : public Base {
public:
    void pureFunction() override {
        // 实现纯虚函数
    }
};
