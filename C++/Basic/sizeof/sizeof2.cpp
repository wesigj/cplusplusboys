
#include <iostream>

int main()
{
    struct MyStruct
    {
        int a;
        char b;
        double c;
    };
    std::cout << sizeof(MyStruct);
    return 0;
}