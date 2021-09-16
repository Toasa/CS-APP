#include <stdio.h>

#define BUF_SIZE 8

void good_echo() {
    char buf[BUF_SIZE];

    while(fgets(buf, BUF_SIZE, stdin) != NULL)
        printf("%s", buf);
}

int main() {
    good_echo();
}
