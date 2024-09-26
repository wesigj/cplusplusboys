#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd =
        open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd != -1) {
        const char *text = "Hello, World!";
        write(fd, text, strlen(text));
        close(fd);
    }
}
