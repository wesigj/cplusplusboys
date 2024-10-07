#include <atomic>
#include <iostream>

template <typename T>
class LockFreeQueue {
private:
    struct Node {
        T                   data;
        std::atomic<Node *> next;
        Node(T const &data) : data(data), next(nullptr) {
        }
    };

    std::atomic<Node *> head;
    std::atomic<Node *> tail;

public:
    LockFreeQueue() :
        head(new Node(T())), tail(head.load(std::memory_order_relaxed)) {
    }

    ~LockFreeQueue() {
        while (Node *const old_head = head.load(std::memory_order_relaxed)) {
            head.store(old_head->next, std::memory_order_relaxed);
            delete old_head;
        }
    }

    LockFreeQueue(const LockFreeQueue &other)            = delete;
    LockFreeQueue &operator=(const LockFreeQueue &other) = delete;

    void enqueue(T const &data) {
        Node *new_node = new Node(data);
        Node *old_tail = tail.load();
        while (!tail.compare_exchange_weak(old_tail, new_node)) {
            old_tail = tail.load();
        }
        old_tail->next.store(new_node, std::memory_order_release);
    }

    bool dequeue(T &result) {
        Node *old_head = head.load(std::memory_order_relaxed);
        while (old_head
               && !head.compare_exchange_weak(old_head, old_head->next)) {
            old_head = head.load(std::memory_order_relaxed);
        }
        if (old_head == nullptr) { return false; }
        result           = old_head->data;
        Node *const next = old_head->next.load(std::memory_order_relaxed);
        delete old_head;
        tail.store(next, std::memory_order_relaxed);
        return true;
    }
};

int main() {
    LockFreeQueue<int> queue;
    queue.enqueue(42);

    int value;
    if (queue.dequeue(value)) {
        std::cout << "Dequeued: " << value << std::endl;
    } else {
        std::cout << "Queue was empty" << std::endl;
    }

    return 0;
}