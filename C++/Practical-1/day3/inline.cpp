#include <iostream>
inline double CalArea(double radius);

int main(int argc, char *argv[]) {
    double r(3.0);
    double area;
    area = CalArea(r);
    std::cout << area << std::endl;
    return 0;
}
inline double CalArea(double radius) {
    return 3.14 * radius * radius;
}