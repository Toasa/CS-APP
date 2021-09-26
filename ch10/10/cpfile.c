#include "csapp.h"

int main(int argc, char **argv) {
    int n;
    rio_t rio;
    char buf[MAXLINE];

    if (argc > 1) {
        int fd = open(argv[1], O_RDONLY, 0);
        while ((n = rio_readn(fd, buf, MAXLINE)) > 0)
            rio_writen(fd, buf, n);
        return;
    }

    Rio_readinitb(&rio, STDIN_FILENO);
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
        Rio_writen(STDOUT_FILENO, buf, n);
}
