#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
    char *ls_path = "/bin/ls";
    execve(ls_path, argv, envp);
}
