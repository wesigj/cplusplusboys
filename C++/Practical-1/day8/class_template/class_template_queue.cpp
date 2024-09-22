#include <iostream>
#include <deque>
#include <stdexcept>
#include <iterator>

// 队列的模板类定义
template <typename T>
class Queue {
private:
    std::deque<T> elements; // 使用标准库中的deque来存储队列元素

public:
    // 默认构造函数
    Queue() = default;

    // 构造函数，接受一个初始化列表
    Queue(std::initializer_list<T> init) :
        elements(init) {
    }

    // 将元素添加到队列尾部
    void enqueue(const T &element) {
        elements.push_back(element);
    }

    // 移除队列头部的元素
    void dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("Queue<>::dequeue(): empty queue");
        }
        elements.pop_front();
    }

    // 获取队列头部的元素
    T front() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue<>::front(): empty queue");
        }
        return elements.front();
    }

    // 获取队列尾部的元素
    T back() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue<>::back(): empty queue");
        }
        return elements.back();
    }

    // 检查队列是否为空
    bool isEmpty() const {
        return elements.empty();
    }

    // 获取队列的大小
    size_t size() const {
        return elements.size();
    }

    // 清空队列
    void clear() {
        elements.clear();
    }

    // 交换两个队列的内容
    void swap(Queue &other) {
        elements.swap(other.elements);
    }

    // 迭代器支持
    using iterator       = typename std::deque<T>::iterator;
    using const_iterator = typename std::deque<T>::const_iterator;

    iterator begin() {
        return elements.begin();
    }

    const_iterator begin() const {
        return elements.begin();
    }

    iterator end() {
        return elements.end();
    }

    const_iterator end() const {
        return elements.end();
    }
};

int main() {
    Queue<int> intQueue;

    intQueue.enqueue(1);
    intQueue.enqueue(2);
    intQueue.enqueue(3);

    std::cout << "Queue front: " << intQueue.front() << std::endl; // 应该输出 1
    std::cout << "Queue back: " << intQueue.back() << std::endl;   // 应该输出 3

    intQueue.dequeue();
    std::cout << "New queue front after one dequeue: " << intQueue.front() << std::endl; // 应该输出 2

    std::cout << "Queue size: " << intQueue.size() << std::endl; // 应该输出 2

    // 使用迭代器遍历队列
    std::cout << "Queue contents: ";
    for (const auto &value : intQueue) {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    // 清空队列
    intQueue.clear();
    std::cout << "Queue size after clear: " << intQueue.size() << std::endl; // 应该输出 0

    return 0;
}