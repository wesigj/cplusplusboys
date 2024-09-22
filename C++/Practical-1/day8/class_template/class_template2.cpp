#include <iostream>

template <typename T, int size>
class Array {
private:
    T data[size];

public:
    T &operator[](int index) {
        return data[index];
    }
    const T &operator[](int index) const {
        return data[index];
    }
};
