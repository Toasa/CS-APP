#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int counter = 0;

void handler(int ignore) {
    (void)ignore;
    counter++;
    sleep(1);
    return;
}

int main() {
    signal(SIGUSR2, handler);

    if (fork() == 0) {
        for (int i = 0; i < 5; i++) {
            kill(getppid(), SIGUSR2);
            printf("sent SIGUSR2 to parent\n");
        }
        exit(0);
    }

    wait(NULL);
    printf("counter=%d\n", counter);
    exit(0);
}
