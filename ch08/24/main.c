#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 2

int main() {
    int status;
    pid_t pid;

    // Parent creates N children
    for (int i = 0; i < N; i++)
        if ((pid = fork()) == 0) {
            // Write to a readonly memory area
            *((long *) 0x400000) = 123;
        }

    // Parent reaps N children in no particular order
    while ((pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status))
            printf("child %d terminated normally with exit status=%d\n",
                    pid, WEXITSTATUS(status));
        else {
            int sig;
            if (WIFSIGNALED(status))
                sig = WTERMSIG(status);

            char errmsg[64] = {};
            sprintf(errmsg, "child %d terminated by signal %d", pid, sig);
            psignal(sig, errmsg);
        }
    }

    // The only normal termination is if there are no more children
    if (errno != ECHILD) {
        fprintf(stderr, "waitpid error");
        exit(1);
    }

    exit(0);
}

