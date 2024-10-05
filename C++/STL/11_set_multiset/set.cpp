#include <set>
#include <iostream>

int main() {
    std::set<int> mySet;

    // 插入元素
    mySet.insert(10);
    mySet.insert(5);
    mySet.insert(20);

    // 尝试插入重复元素
    mySet.insert(10); // 不会插入

    // 遍历set
    for (const int &value : mySet) { std::cout << value << " "; }
    // 输出: 5 10 20

    return 0;
}