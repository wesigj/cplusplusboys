#include <string>
#include <mutex>
#include <ctime>

class Clock {
private:
    time_t currentTime;
    mutable std::mutex mtx; // 使用mutable因为mtx在const成员函数中使用

public:
    Clock() {
        currentTime = time(0);
    }

    // 重载()运算符
    std::string operator()() const {
        std::lock_guard<std::mutex> lock(mtx); // 使用lock_guard自动加锁和解锁
        tm  *ltm = localtime(&currentTime);
        char buffer[80];
        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", ltm);
        return std::string(buffer);
    }

    // 线程安全的时间递增
    void incrementTime(int seconds) {
        std::lock_guard<std::mutex> lock(mtx);
        currentTime += seconds;
    }

    // 重载后缀++运算符
    Clock &operator++() {
        incrementTime(1);
        return *this;
    }
};