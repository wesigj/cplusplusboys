#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

std::queue<int>         q;   // 共享队列
std::mutex              mtx; // 互斥锁
std::condition_variable cv;  // 条件变量

// 生产者函数
void producer(int id) {
    for (int i = 0; i < 5; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        std::cout << "Producer " << id << " produced " << i << std::endl;
        q.push(i);
        lock.unlock();
        cv.notify_one(); // 通知一个等待的消费者
    }
}

// 消费者函数
void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !q.empty(); }); // 等待直到队列非空
        int val = q.front();
        q.pop();
        std::cout << "Consumer " << id << " consumed " << val << std::endl;
        lock.unlock();
        // 如果消费了某个值后结束（例如-1），则退出循环
        if (val == -1) break;
    }
}

int main() {
    std::thread producers[2];
    std::thread consumers[2];

    // 创建生产者线程
    for (int i = 0; i < 2; ++i) { producers[i] = std::thread(producer, i); }

    // 创建消费者线程
    for (int i = 0; i < 2; ++i) { consumers[i] = std::thread(consumer, i); }

    // 等待生产者线程结束
    for (int i = 0; i < 2; ++i) { producers[i].join(); }

    // 添加结束信号
    // 生产者线程结束后，向队列添加特殊值通知消费者线程结束
    {
        std::lock_guard<std::mutex> lock(mtx);
        q.push(-1);
        cv.notify_all();
    }

    // 等待消费者线程结束
    for (int i = 0; i < 2; ++i) { consumers[i].join(); }

    return 0;
}