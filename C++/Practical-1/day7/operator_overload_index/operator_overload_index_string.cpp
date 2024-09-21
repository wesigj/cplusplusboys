#include <iostream>
#include <cstring>
#include <cctype> // 包含toupper函数

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

    ~String() {
        delete[] data;
    }

    // 重载下标运算符
    char &operator[](size_t index) {
        // 边界检查
        if (index >= strlen(data)) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const char &operator[](size_t index) const {
        // 边界检查
        if (index >= strlen(data)) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // 获取字符串数据的访问器
    const char *c_str() const {
        return data;
    }
};

int main() {
    String str("Hello");

    std::cout << "Original string: " << str.c_str() << std::endl;

    // 修改字符串中的字符
    for (size_t i = 0; i < strlen(str.c_str()); ++i) {
        str[i] = toupper(str[i]);
    }

    std::cout << "Modified string: " << str.c_str() << std::endl;

    return 0;
}