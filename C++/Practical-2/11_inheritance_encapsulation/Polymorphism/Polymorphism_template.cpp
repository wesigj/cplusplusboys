#include <iostream>

template <typename T>
void print(T value) {
    std::cout << "Print: " << value << std::endl;
}

int main() {
    print(5);       // 调用 print<int>(5)
    print(5.0);     // 调用 print<double>(5.0)
    print("Hello"); // 调用 print<std::string>("Hello")
    return 0;
}