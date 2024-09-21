#include <iostream>
#include <cstdlib> // 包含rand()和srand()
#include <ctime>   // 包含time()
#include <map>

int main() {
    const int          rolls     = 100000; // 掷骰子的次数
    const int          diceCount = 2;      // 骰子的数量
    std::map<int, int> frequency;          // 用于存储点数之和的频率

    // 初始化随机数生成器
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < rolls; ++i) {
        int sum = 0;
        for (int j = 0; j < diceCount; ++j) {
            sum += rand() % 6 + 1; // 每个骰子的点数
        }
        ++frequency[sum]; // 更新频率
    }

    std::cout << "Sum Frequency after " << rolls << " rolls:" << std::endl;
    for (const auto &kv : frequency) {
        std::cout << "Sum " << kv.first << " appears " << kv.second << " times." << std::endl;
    }

    return 0;
}