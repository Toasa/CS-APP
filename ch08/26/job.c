#include "job.h"

struct Job fg_job;
struct Job bg_job;

struct Job create_new_job(pid_t pid, char *cmd) {
    static int jid = 0;

    struct Job j =  {
        .pid = pid,
        .jid = jid++,
        .cmd = cmd,
    };
    return j;
}

pid_t get_fg_pid() {
    return fg_job.pid;
}
