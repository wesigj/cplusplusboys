#include <iostream>
#include <ctime>

class Clock {
private:
    time_t currentTime;

public:
    // 构造函数
    Clock() {
        currentTime = time(0); // 初始化为当前时间
    }

    // 重载()运算符，返回当前时间的字符串表示
    std::string operator()() const {        // 保持const
        tm  *ltm = localtime(&currentTime); // 转换为本地时间
        char buffer[80];
        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", ltm); // 格式化时间
        return std::string(buffer);
    }

    // 设置时间
    void setTime(time_t newTime) {
        currentTime = newTime;
    }

    // 获取时间
    time_t getTime() const {
        return currentTime;
    }

    // 计算两个时间点之间的差异（秒）
    double timeDifference(const Clock &other) const {
        return difftime(other.currentTime, currentTime);
    }

    // 时间递增
    void incrementTime(int seconds) {
        currentTime += seconds;
    }

    // 重载前置++运算符
    Clock &operator++() {
        incrementTime(1); // 递增1秒
        return *this;
    }

    // 重载后置++运算符
    Clock operator++(int) {
        Clock temp = *this; // 保存当前状态
        incrementTime(1);   // 递增1秒
        return temp;        // 返回递增前的状态
    }
};

int main() {
    Clock myClock;
    std::cout << "Current time: " << myClock() << std::endl;

    // 手动设置时间
    myClock.setTime(time(0)); // 重新设置为当前时间
    std::cout << "Current time after setting: " << myClock() << std::endl;

    // 创建另一个时钟实例
    Clock anotherClock;
    anotherClock.setTime(time(0) + 3600); // 设置为当前时间1小时后

    // 计算两个时间点之间的差异
    double diff = myClock.timeDifference(anotherClock);
    std::cout << "Time difference: " << diff << " seconds" << std::endl;

    // 使用后置++运算符递增时间
    myClock++;
    std::cout << "Current time after incrementing: " << myClock() << std::endl;

    return 0;
}