#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

struct Job {
    int pid; // Process id
    int bg_jid; // Background Job id

    char *cmd;
};

extern struct Job fg_job;

struct Job create_new_job(pid_t pid, char *cmd);

int register_new_bg_job(struct Job);

struct Job fg_to_bg(struct Job j);

void print_all_bg_jobs();

// Find a job which has jid and return its pid.
pid_t get_bg_pid(int jid);
