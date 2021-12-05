#include "control.h"

int semd;

int parse_args(char * line) {
    return 0;
}

int create() {
    semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    return errno;
}

int rem() {
    semctl(semd,IPC_RMID,0);
    return errno;
}

void print_err() {
    if (errno) {
        printf("error %d: %s\n", errno, strerror(errno));
    }
    errno = 0;
}