#include <set>
#include <iostream>

int main() {
    std::multiset<int> myMultiSet;

    // 插入元素
    myMultiSet.insert(10);
    myMultiSet.insert(5);
    myMultiSet.insert(10); // 允许插入重复元素

    // 遍历multiset
    for (const int &value : myMultiSet) { std::cout << value << " "; }
    // 输出: 5 10 10

    return 0;
}