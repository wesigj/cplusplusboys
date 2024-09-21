#include <iostream>
#include <cstring>

class String {
private:
    char *data;

public:
    String(const char *str = "") {
        if (str) {
            data = new char[strlen(str) + 1];
            strcpy(data, str);
        } else {
            data  = new char[1];
            *data = '\0';
        }
    }

    // 拷贝构造函数
    String(const String &other) {
        if (other.data) {
            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
        } else {
            data  = new char[1];
            *data = '\0';
        }
    }

    // 重载赋值运算符
    String &operator=(const String &other) {
        if (this != &other) { // 检查自赋值
            delete[] data;    // 释放现有资源

            if (other.data) {
                data = new char[strlen(other.data) + 1];
                strcpy(data, other.data);
            } else {
                data  = new char[1];
                *data = '\0';
            }
        }
        return *this; // 返回当前对象的引用
    }

    ~String() {
        delete[] data;
    }

    // 输出字符串内容的函数
    const char *c_str() const {
        return data;
    }
};

int main() {
    String str1("Hello");
    String str2 = str1; // 调用拷贝构造函数
    String str3;
    str3 = str1; // 调用赋值运算符

    std::cout << "str1: " << str1.c_str() << std::endl;
    std::cout << "str2: " << str2.c_str() << std::endl;
    std::cout << "str3: " << str3.c_str() << std::endl;

    return 0;
}