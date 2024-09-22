#include <iostream>
#include <vector>
#include <stdexcept> // For std::out_of_range
#include <iterator>  // For std::begin, std::end

// 栈的模板类定义
template <typename T>
class Stack {
private:
    std::vector<T> elements; // 使用标准库中的vector来存储栈元素

public:
    // 默认构造函数
    Stack() = default;

    // 构造函数，接受一个初始化列表
    Stack(std::initializer_list<T> init) :
        elements(init) {
    }

    // 将元素压入栈顶
    void push(const T &element) {
        elements.push_back(element);
    }

    // 移除栈顶元素
    void pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::pop(): empty stack");
        }
        elements.pop_back();
    }

    // 获取栈顶元素
    T top() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::top(): empty stack");
        }
        return elements.back();
    }

    // 检查栈是否为空
    bool isEmpty() const {
        return elements.empty();
    }

    // 获取栈的大小
    size_t size() const {
        return elements.size();
    }

    // 获取栈的容量
    size_t capacity() const {
        return elements.capacity();
    }

    // 清空栈
    void clear() {
        elements.clear();
    }

    // 交换两个栈的内容
    void swap(Stack &other) {
        elements.swap(other.elements);
    }

    // 迭代器支持
    using iterator       = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

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
    Stack<int> intStack;
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);

    std::cout << "Top of stack: " << intStack.top() << std::endl; // 应该输出 3

    intStack.pop();
    std::cout << "New top of stack: " << intStack.top() << std::endl; // 应该输出 2

    std::cout << "Stack size: " << intStack.size() << std::endl; // 应该输出 2

    // 使用迭代器遍历栈
    std::cout << "Stack contents: ";
    for (const auto &value : intStack) {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    // 清空栈
    intStack.clear();
    std::cout << "Stack size after clear: " << intStack.size() << std::endl; // 应该输出 0

    return 0;
}