#include <iostream>

struct Base
{
    int a;

    virtual void print()
    {
        std::cout << "print" << std::endl;
    }
};

struct Derived : public Base
{
public:
    int v2;
    void print()
    {
        printf("%s\n", "Derived");
    };
};

int main()
{
    Derived *b = new Derived();
    b->print();
    return 0;
}