#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

long long int getFileSize(int fd) {
    struct stat buf;
    if (fstat(fd, &buf) < 0) {
        fprintf(stderr, "stat() failed (fd: %d)\n", fd);
        return -1;
    }
    return buf.st_size;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Need file name\n");
        return 1;
    }

    char *filename = argv[1];

    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Fail to open: %s\n", filename);
    }

    long long int size = getFileSize(fd);

    char *buf = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (buf == MAP_FAILED) {
        fprintf(stderr, "mmap() failed\n");
        return 1;
    }

    ssize_t n = write(fileno(stdout), buf, size);
    if (n < 0) {
        fprintf(stderr, "write(2) failed\n");
        return 1;
    } else if (n < size) {
        fprintf(stderr, "Not enough is written out.\n");
        return 1;
    }
    
    return 0;
}
