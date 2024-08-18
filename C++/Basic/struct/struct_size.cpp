#include <iostream>
struct A
{
    int a;
    char b;
    double c;
};
int main()
{
    std::cout << "A size is" << sizeof(A) << std::endl;
}