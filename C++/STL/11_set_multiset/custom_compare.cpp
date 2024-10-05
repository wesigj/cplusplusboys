#include <set>
#include <iostream>

// 自定义比较函数
struct CustomCompare {
    bool operator()(int lhs, int rhs) const {
        return lhs > rhs; // 降序排列
    }
};

int main() {
    std::set<int, CustomCompare> mySet;

    // 插入元素
    mySet.insert(10);
    mySet.insert(5);
    mySet.insert(20);

    // 遍历set
    for (const int &value : mySet) { std::cout << value << " "; }
    // 输出: 20 10 5

    return 0;
}