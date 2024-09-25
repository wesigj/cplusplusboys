#include <iostream>
#include <exception>
#include <string>

// 自定义异常类
class MyException : public std::exception {
private:
    std::string message;

public:
    MyException(const std::string &msg) :
        message(msg) {
    }

    // 重写 what() 方法
    const char *what() const noexcept override {
        return message.c_str();
    }
};

// 一个可能抛出异常的函数
void mightGoWrong(int value) {
    if (value < 0) {
        throw MyException("Negative value is not allowed");
    }
}

int main() {
    try {
        mightGoWrong(-1);
    } catch (const MyException &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Caught standard exception: " << e.what() << std::endl;
    }
    return 0;
}