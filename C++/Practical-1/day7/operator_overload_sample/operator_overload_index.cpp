#include <iostream>
#include <vector>

class Matrix {
private:
    std::vector<std::vector<int>> data;

public:
    Matrix(int rows, int cols) {
        data.resize(rows, std::vector<int>(cols));
    }

    // 重载下标运算符
    int &operator[](int index) {
        return data[index][0]; // Simplified for demonstration
    }
};

int main() {
    Matrix mat(2, 2);
    mat[0] = 1;
    mat[1] = 2;
    std::cout << "mat[0]: " << mat[0] << std::endl;
    std::cout << "mat[1]: " << mat[1] << std::endl;
    return 0;
}