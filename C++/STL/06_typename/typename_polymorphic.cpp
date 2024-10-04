#include <iostream>
#include <memory>
#include <vector>
#include <typeinfo>

// 基础类接口
template <typename T>
class Interface {
public:
    virtual ~Interface()         = default;
    virtual void performAction() = 0; // 纯虚函数
};

// 具体实现类A
template <typename T>
class ImplementationA : public Interface<T> {
public:
    void performAction() override {
        std::cout << "Implementation A with type: " << typeid(T).name()
                  << std::endl;
    }
};

// 具体实现类B
template <typename T>
class ImplementationB : public Interface<T> {
public:
    void performAction() override {
        std::cout << "Implementation B with type: " << typeid(T).name()
                  << std::endl;
    }
};

// 函数模板，接受任何实现了 Interface 的类型
template <typename Implementation>
void execute(Implementation &impl) {
    impl.performAction();
}

int main() {
    // 使用模板类创建对象
    ImplementationA<int>    implA;
    ImplementationB<double> implB;

    // 将具体实现对象传递给函数模板
    execute(implA);
    execute(implB);

    // 存储不同类型的实现到向量
    std::vector<std::unique_ptr<Interface<int>>> implementations;
    implementations.push_back(std::make_unique<ImplementationA<int>>());
    implementations.push_back(std::make_unique<ImplementationB<int>>());

    // 多态调用
    for (auto &impl : implementations) { impl->performAction(); }

    return 0;
}