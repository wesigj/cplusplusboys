#include <iostream>
#include <deque>

int main() {
    std::deque<int> d;

    // 在deque的末尾添加元素
    d.push_back(10);
    d.push_back(20);
    d.push_back(30);

    // 在deque的开头添加元素
    d.push_front(5);
    d.push_front(3);

    // 打印deque中的元素
    std::cout << "Deque contains: ";
    for (int num : d) { std::cout << num << " "; }
    std::cout << std::endl;

    // 删除deque开头的元素
    d.pop_front();

    // 再次打印deque中的元素
    std::cout << "Deque contains after pop_front: ";
    for (int num : d) { std::cout << num << " "; }
    std::cout << std::endl;

    return 0;
}