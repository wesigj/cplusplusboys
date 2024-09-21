#include <iostream>

class Base {
private:
    int  privateData = 30;
    void privateFunc() {
        std::cout << "Base private function." << std::endl;
    }

public:
    // 提供访问器方法
    int getPrivateData() const {
        return privateData;
    }
    void privateFuncPublic() {
        privateFunc();
    }
};

class Derived : public Base { // 改为公有继承
public:
    void derivedFunc() {
        privateFuncPublic();                        // 调用公共接口访问私有成员函数
        std::cout << getPrivateData() << std::endl; // 调用访问器方法
    }
};

int main() {
    Derived d;
    d.derivedFunc(); // 正确调用
    return 0;
}