#include <iostream>
#include <iomanip>

double calculatePi(int terms) {
    double sum = 0.0;
    for (int i = 0; i < terms; i++) {
        // 交替加减1/(2n-1)
        if (i % 2 == 0)
            sum += 1.0 / (2 * i + 1);
        else
            sum -= 1.0 / (2 * i + 1);
    }
    return 4 * sum;
}

int main() {
    int terms;
    std::cout << "Enter the number of terms to approximate Pi: ";
    std::cin >> terms;

    double pi = calculatePi(terms);
    std::cout << "Calculated Pi: " << std::setprecision(15) << pi << std::endl;

    return 0;
}
