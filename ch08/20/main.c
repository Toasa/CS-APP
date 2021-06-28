#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
    char *ls_path = "/bin/ls";
    if (execve(ls_path, argv, envp) == -1) {
        fprintf(stderr, "Fail to execve: %s\n", strerror(errno));
        exit(1);
    }
}
