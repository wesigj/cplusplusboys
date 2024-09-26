#include <iostream>

int main() {
    FILE *tempFile = std::tmpfile();
    if (tempFile != nullptr) {
        fprintf(tempFile, "Temporary data");
        rewind(tempFile); // 回到文件开头
        // 读取或处理文件...
        fclose(tempFile); // 关闭文件，文件内容会被删除
    }
}