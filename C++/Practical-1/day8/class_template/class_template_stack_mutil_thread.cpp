#include <iostream>
#include <vector>
#include <mutex>
#include <stdexcept>

template <typename T>
class ThreadSafeStack {
private:
    std::vector<T>     data;
    mutable std::mutex mutex;

public:
    ThreadSafeStack() = default;

    // 将元素压入栈顶
    void push(const T &element) {
        std::lock_guard<std::mutex> lock(mutex);
        data.push_back(element);
    }

    // 移除栈顶元素
    void pop() {
        std::lock_guard<std::mutex> lock(mutex);
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::pop(): empty stack");
        }
        data.pop_back();
    }

    // 获取栈顶元素
    T top() const {
        std::lock_guard<std::mutex> lock(mutex);
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::top(): empty stack");
        }
        return data.back();
    }

    // 检查栈是否为空
    bool isEmpty() const {
        std::lock_guard<std::mutex> lock(mutex);
        return data.empty();
    }

    // 获取栈的大小
    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex);
        return data.size();
    }
};

int main() {
    ThreadSafeStack<int> intStack;

    // 启动多个线程来操作栈
    // ...

    return 0;
}