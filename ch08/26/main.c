#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXLINE 8192
#define MAXARGS 128

struct Job {
    int jid; // Job id
    int pid; // Process id
};

extern char **environ;
static struct Job fg_job;

struct Job create_new_job(pid_t pid) {
    static int jid = 0;

    struct Job j =  {
        .pid = pid,
        .jid = jid++,
    };
    return j;
}

void create_new_fg_job(pid_t pid) {
    fg_job = create_new_job(pid);
}

pid_t get_fg_pid() {
    return fg_job.pid;
}

void handler(int sig) {
    if (sig == SIGINT || sig == SIGTSTP)
        killpg(fg_job.pid, sig);
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

    if (builtin_command(argv))
        return;

    pid_t pid;
    if ((pid = fork()) == 0) { // Child runs user job

        // Make process group ID for the job the same as PID of child
        setpgid(getpid(), getpid());
        if (execve(argv[0], argv, environ) < 0) {
            printf("%s: Command not found.\n", argv[0]);
            exit(0);
        }
    }

    create_new_fg_job(pid);

    // Parent waits for foreground job to terminate
    if (!bg) {
        int status;
        if (waitpid(get_fg_pid(), &status, WUNTRACED) < 0) {
            fprintf(stderr, "waitfg: waitpid error");
            exit(1);
        }
    } else
        printf("%d %s", pid, cmdline);
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
