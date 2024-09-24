// 普通模板
template <typename T1, typename T2>
void print(T1 value1, T2 value2) {
    std::cout << value1 << " and " << value2 << std::endl;
}

// 偏特化
template <typename T>
void print(int value1, T value2) {
    std::cout << "Integer and other type: " << value1 << ", " << value2
              << std::endl;
}

int main() {
    print(10, 5.5); // 调用偏特化
    print(5.5, 10); // 调用普通模板
    return 0;
}