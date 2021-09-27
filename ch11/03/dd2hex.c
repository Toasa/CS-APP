#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Invalid argument count\n");
        return 1;
    }

    struct in_addr inaddr;
    if (inet_pton(AF_INET, argv[1], &inaddr) < 0) {
        fprintf(stderr, "inet_pton failed\n");
        return 1;
    }

    uint32_t addr = ntohl(inaddr.s_addr);
    
    printf("%#x\n", addr);
}
