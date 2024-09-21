#include <iostream>

class Boolean {
private:
    bool value;

public:
    Boolean(bool val) :
        value(val) {
    }

    // 重载一元逻辑非运算符
    bool operator!() const {
        return !value;
    }
};

int main() {
    Boolean trueBool(true);
    Boolean falseBool(false);

    std::cout << "TrueBool: " << (!trueBool ? "False" : "True") << std::endl;
    std::cout << "FalseBool: " << (!falseBool ? "False" : "True") << std::endl;

    return 0;
}