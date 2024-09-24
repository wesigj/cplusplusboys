#include <atomic>
#include <ctime>

class Clock {
private:
    std::atomic<time_t> currentTime;

public:
    Clock() {
        currentTime.store(time(0));
    }

    void incrementTime(int seconds) {
        currentTime.fetch_add(seconds, std::memory_order_relaxed);
    }

    Clock &operator++() {
        incrementTime(1);
        return *this;
    }
};