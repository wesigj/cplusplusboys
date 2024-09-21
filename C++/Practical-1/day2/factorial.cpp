#include <iostream>

// 递归函数，用于计算阶乘
unsigned long long factorial(int n) {
    if (n == 0) { // 递归终止条件
        return 1;
    }
    return n * factorial(n - 1); // 递归调用
}

int main() {
    int number;
    std::cout << "Enter a positive integer: ";
    std::cin >> number;

    // 检查输入是否为正整数
    if (number < 0) {
        std::cout << "Factorial is not defined for negative numbers." << std::endl;
    } else {
        unsigned long long result = factorial(number);
        std::cout << "Factorial of " << number << " = " << result << std::endl;
    }

    return 0;
}