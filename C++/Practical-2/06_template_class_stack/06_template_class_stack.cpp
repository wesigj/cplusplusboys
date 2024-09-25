#include <iostream>
#include <stdexcept> // for std::out_of_range

template <typename T>
class Stack {
private:
    // 使用动态数组来存储栈的元素
    T     *elements;
    size_t size;
    size_t capacity;

    // 动态数组扩容函数
    void resize() {
        capacity       = (capacity == 0) ? 1 : (capacity * 2);
        T *newElements = new T[capacity];
        for (size_t i = 0; i < size; ++i) { newElements[i] = elements[i]; }
        delete[] elements;
        elements = newElements;
    }

public:
    // 构造函数
    Stack() : size(0), capacity(0), elements(nullptr) {
    }

    // 析构函数
    ~Stack() {
        delete[] elements;
    }

    // 拷贝构造函数
    Stack(const Stack &other) : size(other.size), capacity(other.capacity) {
        elements = new T[capacity];
        for (size_t i = 0; i < size; ++i) { elements[i] = other.elements[i]; }
    }

    // 赋值运算符
    Stack &operator=(const Stack &other) {
        if (this != &other) {
            delete[] elements;
            size     = other.size;
            capacity = other.capacity;
            elements = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                elements[i] = other.elements[i];
            }
        }
        return *this;
    }

    // 检查栈是否为空
    bool isEmpty() const {
        return size == 0;
    }

    // 获取栈的大小
    size_t getSize() const {
        return size;
    }

    // 入栈操作
    void push(const T &element) {
        if (size == capacity) { resize(); }
        elements[size++] = element;
    }

    // 出栈操作
    void pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::pop(): empty stack");
        }
        elements[--size] = T();
    }

    // 获取栈顶元素
    T &top() {
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::top(): empty stack");
        }
        return elements[size - 1];
    }

    // 获取栈顶元素（const版本）
    const T &top() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::top(): empty stack");
        }
        return elements[size - 1];
    }
};

int main() {
    Stack<int> intStack;
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);

    std::cout << "Top element: " << intStack.top() << std::endl; // 输出 3

    intStack.pop();
    std::cout << "New top element: " << intStack.top() << std::endl; // 输出 2

    return 0;
}