#include <iostream>
#include <stdexcept> // for std::out_of_range

template <typename T>
class Stack {
private:
    T     *elements;
    size_t size;
    size_t capacity;

    void resize() {
        capacity       = (capacity == 0) ? 1 : (capacity * 2);
        T *newElements = new T[capacity];
        for (size_t i = 0; i < size; ++i) { newElements[i] = elements[i]; }
        delete[] elements;
        elements = newElements;
    }

public:
    Stack() : size(0), capacity(0), elements(nullptr) {
    }
    ~Stack() {
        delete[] elements;
    }
    Stack(const Stack &other) : size(other.size), capacity(other.capacity) {
        elements = new T[capacity];
        for (size_t i = 0; i < size; ++i) { elements[i] = other.elements[i]; }
    }
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

    bool isEmpty() const {
        return size == 0;
    }

    size_t getSize() const {
        return size;
    }

    void push(const T &element) {
        if (size == capacity) { resize(); }
        elements[size++] = element;
    }

    void pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::pop(): empty stack");
        }
        elements[--size] = T();
    }

    T &top() {
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::top(): empty stack");
        }
        return elements[size - 1];
    }

    const T &top() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::top(): empty stack");
        }
        return elements[size - 1];
    }

    // 迭代器接口
    class Iterator {
    private:
        const Stack *stack;
        size_t       index;

    public:
        Iterator(const Stack *s, size_t idx) : stack(s), index(idx) {
        }

        T &operator*() const {
            return stack->elements[index];
        }

        T *operator->() const {
            return &stack->elements[index];
        }

        Iterator &operator++() {
            if (index > 0) index--;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator &other) const {
            return index == other.index && stack == other.stack;
        }

        bool operator!=(const Iterator &other) const {
            return !(*this == other);
        }
    };

    Iterator begin() const {
        return Iterator(this, size - 1);
    }

    Iterator end() const {
        return Iterator(this, -1);
    }
};

int main() {
    Stack<int> intStack;
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);

    std::cout << "Stack elements: ";
    for (Stack<int>::Iterator it = intStack.begin(); it != intStack.end();
         ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}