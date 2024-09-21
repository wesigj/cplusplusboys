#include <iostream>

static int global_static_var = 10;

int main() {
    std::cout << "global_static_var: " << global_static_var << std::endl;
    global_static_var++;
    std::cout << "global_static_var: " << global_static_var << std::endl;
    return 0;
}