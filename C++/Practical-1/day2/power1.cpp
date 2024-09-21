#include <iostream>
#include <cmath> // 用于abs函数

double power(double x, int n) {
    double result   = 1;
    bool   negative = n < 0;
    n               = abs(n);

    for (int i = 0; i < n; i++) {
        result *= x;
    }

    return negative ? 1 / result : result;
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