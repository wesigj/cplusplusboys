#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T>
class PriorityQueue {
private:
    std::vector<T> elements;

    // 交换元素
    void swap(T &a, T &b) {
        T temp = a;
        a      = b;
        b      = temp;
    }

    // 上浮调整
    void siftUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (elements[index] < elements[parentIndex]) {
                swap(elements[index], elements[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    // 下沉调整
    void siftDown(int index) {
        int size = elements.size();
        int leftChildIndex, rightChildIndex, smallestIndex;

        while (true) {
            leftChildIndex  = 2 * index + 1;
            rightChildIndex = 2 * index + 2;
            smallestIndex   = index;

            if (leftChildIndex < size
                && elements[leftChildIndex] < elements[smallestIndex]) {
                smallestIndex = leftChildIndex;
            }
            if (rightChildIndex < size
                && elements[rightChildIndex] < elements[smallestIndex]) {
                smallestIndex = rightChildIndex;
            }
            if (smallestIndex != index) {
                swap(elements[index], elements[smallestIndex]);
                index = smallestIndex;
            } else {
                break;
            }
        }
    }

public:
    void push(const T &element) {
        elements.push_back(element);
        siftUp(elements.size() - 1);
    }

    void pop() {
        if (elements.empty()) {
            throw std::out_of_range("PriorityQueue<>::pop(): empty queue");
        }
        elements[0] = elements.back();
        elements.pop_back();
        siftDown(0);
    }

    T top() const {
        if (elements.empty()) {
            throw std::out_of_range("PriorityQueue<>::top(): empty queue");
        }
        return elements[0];
    }

    bool isEmpty() const {
        return elements.empty();
    }

    size_t getSize() const {
        return elements.size();
    }
};

int main() {
    PriorityQueue<int> pq;
    pq.push(10);
    pq.push(30);
    pq.push(20);

    std::cout << "Top element: " << pq.top() << std::endl; // 输出 10

    pq.pop();
    std::cout << "New top element: " << pq.top() << std::endl; // 输出 20

    return 0;
}