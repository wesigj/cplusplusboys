#include <iostream>

class Counter {
private:
    int count;

public:
    Counter() :
        count(0) {
    }

    // 重载前置递增运算符
    Counter &operator++() {
        ++count;
        return *this;
    }

    // 重载后置递增运算符
    Counter operator++(int) {
        Counter temp = *this;
        ++(*this);
        return temp;
    }

    void display() const {
        std::cout << count << std::endl;
    }
};

int main() {
    Counter c;
    std::cout << "Before increment: ";
    c.display();

    ++c;
    std::cout << "After prefix increment: ";
    c.display();

    c++;
    std::cout << "After postfix increment: ";
    c.display();
    return 0;
}