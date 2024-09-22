#include <iostream>
#include <thread>
#include <exception>
#include <string>
#include <vector>

// 线程函数，可能会抛出异常
std::exception_ptr threadFunction(int id) {
    std::exception_ptr ptr = nullptr;
    try {
        // 模拟一些可能会抛出异常的操作
        if (id == 1) {
            throw std::runtime_error("Exception from thread with id 1");
        }
        std::cout << "Thread with id " << id << " is running..." << std::endl;
    } catch (...) {
        // 捕获所有异常并存储在exception_ptr中
        ptr = std::current_exception();
    }
    return ptr;
}

int main() {
    std::vector<std::thread>        threads;
    std::vector<std::exception_ptr> exceptions;

    try {
        // 创建两个线程
        for (int i = 1; i <= 2; ++i) {
            threads.emplace_back(threadFunction, i);
            exceptions.push_back(threadFunction(i)); // 执行线程函数并存储异常
        }

        // 等待线程完成并重新抛出异常
        for (auto &t : threads) {
            t.join();
        }
        for (auto &e : exceptions) {
            if (e) {
                std::rethrow_exception(e);
            }
        }
    } catch (const std::exception &e) {
        // 主线程中捕获异常
        std::cerr << "Exception in main thread: " << e.what() << std::endl;
    } catch (...) {
        // 捕获所有类型的异常
        std::cerr << "Unknown exception in main thread" << std::endl;
    }

    return 0;
}