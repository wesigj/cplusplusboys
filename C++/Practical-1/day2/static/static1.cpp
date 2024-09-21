#include <iostream>

void function() {
    static int local_static_var = 1;
    local_static_var++;
    std::cout << local_static_var << std::endl;
}

int main() {
    function();
    function();
    function();
    return 0;
}