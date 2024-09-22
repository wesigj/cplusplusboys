#include <iostream>

template <typename T>
class MyClass {
private:
    T data;

public:
    MyClass(T value) :
        data(value) {
    }
    T getData() const {
        return data;
    }
    void setData(T value) {
        data = value;
    }
};

int main() {
    MyClass<int>         intObj(10);
    MyClass<std::string> stringObj("Hello, World!");

    std::cout << "intObj data: " << intObj.getData() << std::endl;
    std::cout << "stringObj data: " << stringObj.getData() << std::endl;

    intObj.setData(20);
    std::cout << "intObj data after update: " << intObj.getData() << std::endl;

    return 0;
}
