#include <stack>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeStack {
private:
    std::stack<T>           stack;
    mutable std::mutex      mutex;
    std::condition_variable cond_var;

public:
    void push(const T &value) {
        std::lock_guard<std::mutex> lock(mutex);
        stack.push(value);
    }

    void pop() {
        std::lock_guard<std::mutex> lock(mutex);
        if (!stack.empty()) { stack.pop(); }
    }

    T top() {
        std::lock_guard<std::mutex> lock(mutex);
        if (!stack.empty()) { return stack.top(); }
        throw std::runtime_error("Stack is empty");
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mutex);
        return stack.empty();
    }
};