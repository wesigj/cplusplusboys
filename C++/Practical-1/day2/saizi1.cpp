#include <iostream>
#include <cstdlib> // 包含rand()和srand()
#include <ctime>   // 包含time()

int main() {
    // 初始化随机数生成器
    srand(static_cast<unsigned int>(time(0)));

    // 生成一个1到6的随机数
    int dice = rand() % 6 + 1;

    std::cout << "You rolled a dice and got: " << dice << std::endl;

    return 0;
}