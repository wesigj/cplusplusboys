#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int fd = open("example.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
write(fd, "Hello, World!", 13);
ftruncate(fd, 13); // 调整文件大小

// 映射文件到内存
void *addr = mmap(nullptr, 13, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
if (addr != MAP_FAILED) {
    // 使用映射的内存
    munmap(addr, 13); // 解除映射
}
close(fd);