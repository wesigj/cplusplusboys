#include <type_traits>
#include <iostream>

struct MyType {};

int main() {
    std::cout << std::is_integral<int>::value << std::endl; // 输出 1 (true)
    std::cout << std::is_floating_point<double>::value
              << std::endl;                                  // 输出 1 (true)
    std::cout << std::is_pointer<int *>::value << std::endl; // 输出 1 (true)
    std::cout << std::is_same<int, int>::value << std::endl; // 输出 1 (true)
    std::cout << std::is_same<MyType, int>::value
              << std::endl; // 输出 0 (false)

    return 0;
}