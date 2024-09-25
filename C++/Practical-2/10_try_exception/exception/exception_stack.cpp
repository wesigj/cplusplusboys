#include <iostream>
#include <stack>
#include <memory>
#include <stdexcept>

class Resource {
public:
    Resource() {
        std::cout << "Resource acquired\n";
    }
    ~Resource() {
        std::cout << "Resource released\n";
    }
};

void safeFunction(std::stack<std::unique_ptr<Resource>> &s) {
    try {
        // 模拟可能会抛出异常的操作
        throw std::runtime_error("Exception in safeFunction");
    } catch (...) {
        // 捕获所有异常
        std::cerr << "Exception caught in safeFunction\n";
        // 确保栈中的资源被正确释放
        s = std::stack<std::unique_ptr<Resource>>(); // 清空栈
        throw;                                       // 重新抛出异常
    }
}

int main() {
    std::stack<std::unique_ptr<Resource>> s;
    try {
        // 将资源推入栈中
        s.push(std::make_unique<Resource>());

        safeFunction(s);
    } catch (const std::exception &e) {
        // 主线程中捕获异常
        std::cerr << "Exception in main thread: " << e.what() << std::endl;
    } catch (...) {
        // 捕获所有类型的异常
        std::cerr << "Unknown exception in main thread" << std::endl;
    }

    // 栈中的资源将自动被释放
    return 0;
}