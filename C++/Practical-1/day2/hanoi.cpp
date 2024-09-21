#include <iostream>

// 递归函数，用于移动盘子
void hanoi(int n, char from_rod, char to_rod, char aux_rod) {
    if (n == 1) {
        std::cout << "Move disk 1 from rod " << from_rod << " to rod " << to_rod << std::endl;
        return;
    }
    hanoi(n - 1, from_rod, aux_rod, to_rod);
    std::cout << "Move disk " << n << " from rod " << from_rod << " to rod " << to_rod << std::endl;
    hanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main() {
    int n; // 盘子的数目

    std::cout << "Enter number of disks: ";
    std::cin >> n; // 用户输入盘子的数量

    // 调用递归函数开始解决汉诺塔问题
    hanoi(n, 'A', 'C', 'B'); // A为起始柱子，C为目标柱子，B为辅助柱子
    return 0;
}