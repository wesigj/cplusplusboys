#include <iostream>
#include <cmath> // 用于abs函数

double power(double x, int n) {
    if (n == 0) {
        return 1; // 任何数的0次方都是1
    }
    if (n < 0) {
        return 1 / power(x, -n); // 负指数转换为正指数的倒数
    }
    double half = power(x, n / 2);
    if (n % 2 == 0) {
        return half * half;
    } else {
        return half * half * x;
    }
}

int main() {
    double x;
    int    n;
    std::cout << "Enter base (x): ";
    std::cin >> x;
    std::cout << "Enter exponent (n): ";
    std::cin >> n;

    double result = power(x, n);
    std::cout << x << " raised to the power " << n << " is " << result << std::endl;

    return 0;
}