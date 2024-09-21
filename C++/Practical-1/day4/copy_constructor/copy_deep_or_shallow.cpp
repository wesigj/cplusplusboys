#include <iostream>
#include <cstring>

class StringHolder {
public:
    StringHolder() :
        data(nullptr) {
    }

    // 拷贝构造函数
    StringHolder(const StringHolder &other) {
        if (other.data) {
            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
        } else {
            data = nullptr;
        }
    }

    // 赋值运算符
    StringHolder &operator=(const StringHolder &other) {
        if (this != &other) {
            delete[] data;
            if (other.data) {
                data = new char[strlen(other.data) + 1];
                strcpy(data, other.data);
            } else {
                data = nullptr;
            }
        }
        return *this;
    }

    ~StringHolder() {
        delete[] data;
    }

    // 添加一个方法来设置字符串
    void setString(const char *str) {
        delete[] data;
        if (str) {
            data = new char[strlen(str) + 1];
            strcpy(data, str);
        } else {
            data = nullptr;
        }
    }

    // 添加一个方法来获取字符串
    const char *getString() const {
        return data;
    }

private:
    char *data;
};

int main() {
    StringHolder holder1;
    holder1.setString("Hello");

    StringHolder holder2 = holder1; // 调用拷贝构造函数

    std::cout << holder1.getString() << std::endl;
    std::cout << holder2.getString() << std::endl;

    return 0;
}