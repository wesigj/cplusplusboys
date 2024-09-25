#include <iostream>
#include <thread>
#include <exception>
#include <string>

// 线程函数，可能会抛出异常
void threadFunction(int id) {
    try {
        // 模拟一些可能会抛出异常的操作
        if (id == 1) {
            throw std::runtime_error("Exception from thread with id 1");
        }
        std::cout << "Thread with id " << id << " is running..." << std::endl;
    } catch (const std::exception &e) {
        // 在线程内部捕获和处理异常
        std::cerr << "Exception caught in thread with id " << id << ": " << e.what() << std::endl;
    } catch (...) {
        // 捕获所有类型的异常
        std::cerr << "Unknown exception caught in thread with id " << id << std::endl;
    }
}

int main() {
    try {
        // 创建两个线程
        std::thread t1(threadFunction, 1);
        std::thread t2(threadFunction, 2);

        // 等待线程完成
        t1.join();
        t2.join();

    } catch (const std::exception &e) {
        // 主线程中捕获异常
        std::cerr << "Exception in main thread: " << e.what() << std::endl;
    } catch (...) {
        // 捕获所有类型的异常
        std::cerr << "Unknown exception in main thread" << std::endl;
    }

    return 0;
}