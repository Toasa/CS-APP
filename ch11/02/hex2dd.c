#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Invalid argument count\n");
        return 1;
    }

    uint32_t addr;
    sscanf(argv[1], "%x", &addr);
    struct in_addr inaddr;
    inaddr.s_addr = htonl(addr);

    char addr_p[16] = {};
    if (inet_ntop(AF_INET, &inaddr, addr_p, 16) == NULL) {
        fprintf(stderr, "inet_ntop failed\n");
        return 1;
    }

    printf("%s\n", addr_p);
}
