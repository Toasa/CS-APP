#include "job.h"

#define MAX_BG_JOB 64

struct Job fg_job;
static struct Job bg_jobs[MAX_BG_JOB];
static bool bg_jobs_used[MAX_BG_JOB];

struct Job create_new_job(pid_t pid, char *cmd) {
    struct Job j =  {
        .pid = pid,
        .bg_jid = -1,
        .state = Running,
        .cmd = cmd,
    };
    return j;
}

int register_new_bg_job(struct Job j) {
    bool registered = false;
    // Find empty entry
    for (int i = 0; i < MAX_BG_JOB; i++) {
        if (!bg_jobs_used[i]) {
            bg_jobs[i] = j;
            bg_jobs_used[i] = true;
            registered = true;
            break;
        }
    }

    if (!registered) {
        fprintf(stderr, "No more bg job can be registered\n");
        return -1;
    }

    return 0;
}

void check_exited_bg_jobs() {
    for (int i = 0; i < MAX_BG_JOB; i++) {
        if (!bg_jobs_used[i])
            continue;

        struct Job bg_job = bg_jobs[i];
        pid_t pid = bg_job.pid;

        int status;
        pid_t exited_pid = waitpid(pid, &status, WNOHANG|WUNTRACED);

        if (pid == exited_pid && WIFEXITED(status)) {
            set_state(&bg_job, Stopped);
            bg_jobs_used[i] = false;
        }
    }
}

struct Job fg_to_bg(struct Job j) {
    static int bg_jid = 0;

    j.bg_jid = bg_jid++;
    return j;
}

pid_t get_bg_pid(int jid) {
    for (int i = 0; i < MAX_BG_JOB; i++) {
        if (bg_jobs[i].bg_jid == jid)
            return bg_jobs[i].pid;
    }
    return -1;
}

struct Job *get_bg_job_from_pid(pid_t pid) {
    for (int i = 0; i < MAX_BG_JOB; i++) {
        if (bg_jobs[i].pid == pid)
            return &bg_jobs[i];
    }
    return NULL;
}

void set_state(struct Job *j, enum State s) {
    j->state = s;
}

static char *str_state(enum State s) {
    if (s == Running)
        return "Running";
    else if (s == Stopped)
        return "Stopped";
    else
        return "Exited ";
}

void print_all_bg_jobs() {
    for (int i = 0; i < MAX_BG_JOB; i++) {
        if (bg_jobs_used[i])
            printf("[%d] %d %s %s",
                    bg_jobs[i].bg_jid,
                    bg_jobs[i].pid,
                    str_state(bg_jobs[i].state),
                    bg_jobs[i].cmd);
    }
}
