#include "csapp.h"

int main(int argc, char **argv) {
    int n;
    char buf[MAXBUF];

    while ((n = rio_readn(STDIN_FILENO, buf, MAXBUF)) > 0) {
        rio_writen(STDOUT_FILENO, buf, n);
    }
}
