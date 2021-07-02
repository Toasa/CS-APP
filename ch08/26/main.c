#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXLINE 8192
#define MAXARGS 128

extern char **environ;
pid_t pid;

void handler(int sig) {
    if (sig == SIGINT || sig == SIGTSTP)
        killpg(pid, sig);
}

int parseline(char *buf, char **argv) {
    buf[strlen(buf)-1] = ' '; // Replace trailing '\n' with space
    while (*buf && (*buf == ' ')) // Ignore leading spaces
        buf++;

    int argc = 0;
    char *delim;
    while ((argc < MAXARGS) && (delim = strchr(buf, ' '))) {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf ==  ' '))
            buf++;
    }
    argv[argc] = NULL;

    if (argc == 0)
        return 1;

    int bg;
    if ((bg = (*argv[argc-1] == '&')) != 0)
        argv[--argc] = NULL;

    return bg;
}

int builtin_command(char **argv) {
    if (!strcmp(argv[0], "quit"))
        exit(0);
    if (!strcmp(argv[0], "&"))
        return 1;
    return 0;
}

void eval(char *cmdline) {
    char *argv[MAXARGS]; // Argument list execve()
    char buf[MAXLINE];   // Holds modified command line
    int bg;              // Should the job run in bg or fg?

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);
    if (argv[0] == NULL)
        return; // Ignore empty lines

    if (!builtin_command(argv)) {
        if ((pid = fork()) == 0) { // Child runs user job

            // Make process group ID for the job the same as PID of child
            setpgid(getpid(), getpid());
            if (execve(argv[0], argv, environ) < 0) {
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }

        // Parent waits for foreground job to terminate
        if (!bg) {
            int status;
            if (waitpid(pid, &status, WUNTRACED) < 0) {
                fprintf(stderr, "waitfg: waitpid error");
                exit(1);
            }
        } else 
            printf("%d %s", pid, cmdline);
    }
    return;
}

int main() {
    char cmdline[MAXLINE];
    signal(SIGINT, handler);
    signal(SIGTSTP, handler);

    while (1) {
        // Read
        printf("> ");
        fgets(cmdline, MAXLINE, stdin);
        if (feof(stdin))
            exit(0);

        // Eval
        eval(cmdline);
    }
}
