#include <iostream>
#include <stdexcept>

// 函数声明
void mightGoWrong() {
    throw std::runtime_error("Something went wrong!");
}

int main() {
    try {
        mightGoWrong();
    } catch (const std::runtime_error &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}