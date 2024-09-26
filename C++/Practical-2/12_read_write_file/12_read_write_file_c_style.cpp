#include <cstdio>

int main() {
    FILE *file = fopen("example.txt", "w"); // 打开文件用于写操作
    if (file != nullptr) {
        fprintf(file, "Hello, World!\n");
        fclose(file); // 关闭文件
    }
}
