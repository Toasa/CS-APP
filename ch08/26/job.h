#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

struct Job {
    int jid; // Job id
    int pid; // Process id

    char *cmd;
};

extern struct Job fg_job;
extern struct Job bg_job;

struct Job create_new_job(pid_t pid, char *cmd);

pid_t get_fg_pid();
