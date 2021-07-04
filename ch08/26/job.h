#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

enum State {
    Running,
    Stopped,
    Exited,
};

struct Job {
    int pid; // Process id
    int bg_jid; // Background Job id

    enum State state;

    char *cmd;
};

extern struct Job fg_job;

struct Job create_new_job(pid_t pid, char *cmd);

int register_new_bg_job(struct Job);

void check_exited_bg_jobs();

struct Job fg_to_bg(struct Job j);

// Find a job which has jid and return its pid.
pid_t get_bg_pid(int jid);

struct Job *get_bg_job_from_pid(pid_t pid);

void set_state(struct Job *j, enum State s);

void print_all_bg_jobs();
