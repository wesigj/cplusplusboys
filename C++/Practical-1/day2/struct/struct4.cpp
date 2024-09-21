#include <iostream>

// 定义一个结构体，用于表示矩形
struct Rectangle {
    int width;
    int height;
};

int main() {
    // 创建一个矩形数组
    Rectangle rectangles[2] = {
        {10, 20},
        {30, 40}};

    // 遍历数组并输出每个矩形的尺寸
    for (int i = 0; i < 2; ++i) {
        std::cout << "Rectangle " << i + 1 << ": "
                  << "width = " << rectangles[i].width
                  << ", height = " << rectangles[i].height << std::endl;
    }

    return 0;
}