#include <iostream>
#include <queue>
#include <stack>

int main() {
    // 使用 std::queue
    std::queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    std::cout << "Queue: ";
    while (!q.empty()) {
        std::cout << q.front() << " "; // 1 2 3
        q.pop();
    }
    std::cout << std::endl;

    // 使用 std::stack
    std::stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    std::cout << "Stack: ";
    while (!s.empty()) {
        std::cout << s.top() << " "; // 3 2 1
        s.pop();
    }
    std::cout << std::endl;

    return 0;
}