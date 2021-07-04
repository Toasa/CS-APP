#include "job.h"

#define MAXLINE 8192
#define MAXARGS 128

extern char **environ;
static int bg_jid;

char *copy_cmd(char *cmd) {
    int len = strlen(cmd);
    char *c = calloc(1, len);
    strcpy(c, cmd);
    return c;
}

void handler(int sig) {
    killpg(fg_job.pid, sig);
    printf("Job %d terminated by signal: ", fg_job.pid);
    if (sig == SIGINT)
        printf("Interrupt\n");
    else if (sig == SIGTSTP)
        printf("Stopped\n");
    else if (sig == SIGKILL)
        printf("Terminated\n");
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
    if (!strcmp(argv[0], "jobs")) {
        print_all_bg_jobs();
        return 1;
    }
    if (!strcmp(argv[0], "bg")) {
        if (argv[1] == NULL)
            return 1;

        int pid, jid;
        char *p;
        bool jid_specified = false;
        if ((p = strchr(argv[1], '%')) != NULL) {
            jid_specified = true;
            jid = atoi(p+1);
            pid = get_bg_pid(jid);
        } else {
            pid = atoi(argv[1]);
        }

        struct Job *bg_job = get_bg_job_from_pid(pid);
        if (bg_job == NULL) {
            if (jid_specified)
                printf("Job %d", jid);
            else
                printf("PID %d", pid);
            printf(" not found.\n");
        }

        set_state(bg_job, Running);
        killpg(pid, SIGCONT);

        return 1;
    }
    return 0;
}

void eval_cmd(char *cmdline) {
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

    struct Job job = create_new_job(pid, copy_cmd(cmdline));

    int status;
    // Parent waits for foreground job to terminate
    if (!bg) {
        fg_job = job;
        if (waitpid(fg_job.pid, &status, WUNTRACED) < 0) {
            fprintf(stderr, "waitfg: waitpid error");
            exit(1);
        }
    }

    // Background job
    if (bg || WIFSTOPPED(status)) {
        if (WIFSTOPPED(status))
            set_state(&job, Stopped);
        job = fg_to_bg(job);
        register_new_bg_job(job);
        printf("[%d] %d %s", job.bg_jid, job.pid, cmdline);
    }
}

void eval(char *cmdline) {
    eval_cmd(cmdline);
    check_exited_bg_jobs();
}

int main() {
    char cmdline[MAXLINE];
    signal(SIGINT, handler);
    signal(SIGTSTP, handler);
    signal(SIGKILL, handler);

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
