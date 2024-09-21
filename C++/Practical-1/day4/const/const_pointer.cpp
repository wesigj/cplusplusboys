#include <iostream>

int main() {
    const int  value = 42;
    const int *ptr   = &value; // 指针ptr可以改变指向，但通过ptr不能修改value的值
    // *ptr = 100; // 错误：尝试修改const变量

    const int *constPtr = &value; // constPtr是一个指向const值的const指针，既不能改变指向，也不能通过constPtr修改值
    // *constPtr = 100; // 错误：尝试修改const变量
    // constPtr = &value; // 错误：尝试改变const指针的指向

    int        anotherValue = 24;
    int *const constPtr2    = &anotherValue; // constPtr2是一个指向int的const指针，不能改变指向，但可以通过constPtr2修改值
    constPtr2               = &value;        // 错误：尝试改变const指针的指向

    return 0;
}