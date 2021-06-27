#include <stdbool.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int exist_file(const char *path) {
    struct stat st;
    return stat(path, &st) == 0 ? true : false;
}

int mysystem(char *cmd) {
    char *sh_path = "/bin/sh";
    char *argv[] = {
        "-c",
        cmd,
    };

    if (cmd == NULL)
        return exist_file(sh_path);

    if (fork() == 0)
        execl("/bin/sh", "sh", "-c", cmd, (char *)NULL);

    int status;
    waitpid(-1, &status, 0);
    return status;
}

int main() {
    char *cmd = "echo hello";
    mysystem(cmd);
}
