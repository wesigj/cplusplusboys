#include <iostream>
#include <cstring>
// 定义一个名为Data的union
union Data {
    int    i;
    double f;
    char   str[20];
    struct {
        int x;
        int y;
        int z;
    } u;
    int k;
};

int main() {
    Data data;

    // 存储整数值
    data.i = 10;
    std::cout << "data.i: " << data.i << std::endl; // 输出: data.i: 10

    // 存储浮点数值
    data.f = 220.5;
    std::cout << "data.f: " << data.f << std::endl; // 输出: data.f: 220.5

    // 存储字符串
    strcpy(data.str, "C++ Union");
    std::cout << "data.str: " << data.str << std::endl; // 输出: data.str: C++ Union

    data.u.x = 1;
    data.u.y = 2;
    data.u.z = 3;
    data.k   = 4; // 覆盖掉第一个int空间值
    printf("%d %d %d %d\n", data.u.x, data.u.y, data.u.z, data.k);
    return 0;
}