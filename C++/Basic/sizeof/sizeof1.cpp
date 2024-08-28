
#include <iostream>

class A
{
public:
    char a;
    int b;
};

/**
 * @brief 此时B按照顺序：
 * char 1
 * NULL 3
 * int  4
 * short 2
 * NULL 2
 * long 4
 * =16
 */
class B : A
{
public:
    short a;
    long b;
};
/**
 * 把A的成员拆开看，char为1，int为4，所以是1+（3）+4+1+（3）=12，（）为字节补齐
 */
class C
{
    A a;
    char c;
};

class A1
{
    virtual void fun() {}
};
class C1 : public A1
{
};

int main()
{
    std::cout << sizeof(A) << std::endl; // 8
    std::cout << sizeof(B) << std::endl; // 16
    std::cout << sizeof(C) << std::endl; // 12

    /**
     * @brief 对于虚单函数继承，派生类也继承了基类的vptr，所以是8字节
     */
    std::cout << sizeof(C1) << std::endl; // 8
    return 0;
}