#include <iostream>
#include <string>

class Clock {
private:
    int hour;
    int minute;

public:
    Clock(int h, int m) :
        hour(h), minute(m) {
    }

    void setTime(int h, int m) {
        hour   = h;
        minute = m;
    }

    // const成员函数
    void displayTime() const {
        std::cout << "Current time: " << hour << ":" << minute << std::endl;
        // setTime(12, 0); // 错误：不能在const成员函数中调用非const成员函数
    }
};

int main() {
    Clock myClock(11, 59);
    myClock.displayTime(); // 可以调用const成员函数
    return 0;
}