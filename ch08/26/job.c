#include "job.h"

#define MAX_BG_JOB 64

struct Job fg_job;
static struct Job bg_jobs[MAX_BG_JOB];
static bool bg_jobs_used[MAX_BG_JOB];

struct Job create_new_job(pid_t pid, char *cmd) {
    struct Job j =  {
        .pid = pid,
        .bg_jid = -1,
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

struct Job fg_to_bg(struct Job j) {
    static int bg_jid = 0;

    j.bg_jid = bg_jid++;
    return j;
}

void print_all_bg_jobs() {
    for (int i = 0; i < MAX_BG_JOB; i++) {
        if (bg_jobs_used[i])
            printf("[%d] %d %s",
                    bg_jobs[i].bg_jid,
                    bg_jobs[i].pid,
                    bg_jobs[i].cmd);
    }
}

pid_t get_bg_pid(int jid) {
    for (int i = 0; i < MAX_BG_JOB; i++) {
        if (bg_jobs[i].bg_jid == jid)
            return bg_jobs[i].pid;
    }
    return -1;
}
