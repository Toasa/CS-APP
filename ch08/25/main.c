#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>
#include <sys/wait.h>

#define BUFSIZE 1024

jmp_buf jbuf;

void timeout_handler(int ignore) {
    (void)ignore;
    longjmp(jbuf, 1);
}

char *tfgets(char *s, int size, FILE *stream) {
    if (SIG_ERR == signal(SIGUSR1, timeout_handler)) {
        fprintf(stderr, "Fail to signel: %s", strerror(errno));
        return NULL;
    }

    pid_t pid;
    if ((pid = fork()) == 0) {
        sleep(5);
        pid_t ppid = getppid();
        kill(ppid, SIGUSR1);
        exit(0);
    }

    char *ss = NULL;
    switch (setjmp(jbuf)) {
        case 0:
            ss = fgets(s, size, stream);
            kill(pid, SIGKILL);
            break;
        case 1:
            break;
        default:
            fprintf(stderr, "Unknown error condition\n");
    }

    wait(NULL);

    return ss;
}

int main() {
    char buf[BUFSIZE];
    if (tfgets(buf, BUFSIZE, stdin) != NULL)
        printf("tfgets read: %s", buf);
    else
        printf("fail to tfgets\n");
}
